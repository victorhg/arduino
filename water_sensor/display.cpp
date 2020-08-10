

#include "display.h"
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void startDisplay(){ 
  //For OLED I2C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  
  display.drawBitmap(0, 0, logo_bmp, 128, 64, WHITE);
  display.display(); //Display logo
  delay(800);
  display.clearDisplay();
}

void clearDisplay(){
  display.clearDisplay();
}

void updateDisplay() {
  display.display();
}

void putOnDisplay(int size, int x, int y, String unit) {
  display.setTextSize(size);
  display.setTextColor(WHITE);

    display.setCursor(x, y);
    display.print(unit);

}
void putOnDisplay(int size, int x, int y, float value, String unit) {
  int charLen = 12;
  int xo = x + charLen * 3.2;
  int xunit = x + charLen * 3.6;
  int xval = x;
  display.setTextSize(size);
  display.setTextColor(WHITE);

    display.setCursor(x, y);
    display.print(value, 0);
    display.print(unit);
}
