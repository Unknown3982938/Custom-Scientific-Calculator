// Status: Under development
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#define I2C_SDA 21
#define I2C_SCL 22
#define MCP1_ADDR 0x20
#define MCP2_ADDR 0x21
#define TFT_CS   5
#define TFT_DC   25
#define TFT_RST  26
#define TFT_BL   27

Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_RST);

// The exact matrix scanning implementation can be filled in after the final PCB pin mapping is confirmed.

String inputBuffer = "";
String resultBuffer = "";

bool calculatorOn = true;

void mcpWrite(uint8_t address, uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

uint8_t mcpRead(uint8_t address, uint8_t reg)
{
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(address, (uint8_t)1);

    if (Wire.available())
        return Wire.read();

    return 0;
}

void initMCP23017(uint8_t address)
{
  
    mcpWrite(address, 0x00, 0xFF);
    mcpWrite(address, 0x01, 0xFF);

    mcpWrite(address, 0x0C, 0xFF);
    mcpWrite(address, 0x0D, 0xFF); 
}

void initDisplay()
{
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);

    tft.init(240, 320);
    tft.setRotation(1);

    tft.fillScreen(ST77XX_BLACK);

    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(2);

    tft.setCursor(10, 10);
    tft.println("Scientific Calculator");

    tft.setCursor(10, 40);
    tft.println("Firmware WIP");
}

void updateDisplay()
{
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(2);
    tft.setCursor(10, 20);
    tft.println(inputBuffer);
    tft.setCursor(10, 70);
    tft.println(resultBuffer);
}

void handleKey(char key)
{
    switch (key)
    {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.':
            inputBuffer += key;
            break;

        case '+':
        case '-':
        case '*':
        case '/':
            inputBuffer += key;
            break;

        case '=':
            resultBuffer = "TODO";
            break;

        case 'C':
            inputBuffer = "";
            resultBuffer = "";
            break;

        default:
            break;
    }

    updateDisplay();
}


void scanMatrix()
{
     /* TODO list:
     * 1. Configure one matrix row as active.
     * 2. Read the column inputs.
     * 3. Determine which key is pressed.
     * 4. Debounce the key.
     * 5. Convert the matrix position into a calculator key.
     * (The final implementation should use the actual
     * MCP23017 pin assignments from the PCB)
     */
}

void setup()
{
    Serial.begin(115200);

    Wire.begin(I2C_SDA, I2C_SCL);

    Serial.println();
    Serial.println("Custom Scientific Calculator");
    Serial.println("Firmware WIP");

    initMCP23017(MCP1_ADDR);
    initMCP23017(MCP2_ADDR);

    initDisplay();

    Serial.println("Initialization complete. Confirm function");
}


void loop()
{
    scanMatrix();

    // Future:
    // - Key debounce
    // - Calculator expression parser
    // - Scientific functions
    // - Angle modes
    // - Memory functions
    // - SD card functionality
    // - Touchscreen UI
    // - Power management

    delay(5);
}
