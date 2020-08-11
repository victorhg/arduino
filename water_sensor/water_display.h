//OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "image_logo.h"

//OLED define
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)


class WaterDisplay {
  public:
    WaterDisplay();
    void putOnDisplay(int size, int x, int y, float value, String unit);
    void putOnDisplay(int size, int x, int y, String unit);
    void drawWaterLevel(int percentage);

    void clearDisplay();
    void updateDisplay();
    void startDisplay();
    void displayHeader();
  private:

    Adafruit_SSD1306 display;
};
