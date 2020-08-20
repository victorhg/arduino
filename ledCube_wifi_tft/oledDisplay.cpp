
#include "oledDisplay.h"


OledDisplay::OledDisplay() {
    display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
}


void OledDisplay::startDisplay(){ 
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

 // display.drawRect(0, 0, 128, 17, WHITE);
  //display.display();
}

void OledDisplay::clearDisplay(){
  display.clearDisplay();
}

void OledDisplay::updateDisplay() {
  display.display();
}

void OledDisplay::displayHeader(){

  /*display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Caixa D'Agua");*/

}


void OledDisplay::putOnDisplay(int size, int x, int y, String unit) {
  display.setTextSize(size);
  display.setTextColor(WHITE);

    display.setCursor(x, y);
    display.print(unit);

}
