
#include "water_display.h"


WaterDisplay::WaterDisplay() {
    display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
}


void WaterDisplay::startDisplay(){ 
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
  //Informacoes iniciais do display

  /*
   * ---------------------
   *      MESSAGE 
   * ---------------------
   *          |
   *          |
   *   %      | Tank Bars
   *          |
   * ---------------------
   */
  display.fillScreen(BLACK);
  // display DrawRect (x, y, w, h, color);
  display.drawRect(0, 0, 128, 17, WHITE);
  display.fillRect(0, 0, 128, 17, WHITE);
  display.drawRect(0, 0, 128, 17, WHITE);
  display.drawRect(0, 19 , 74, 45, WHITE);
  display.drawRect(75, 19 , 52, 45, WHITE);
  display.setCursor( 22, 50 );
  display.print("cm");
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor( 32, 5 );
  display.print( "CAIXA D'AGUA" );
  display.display();
  
}

void WaterDisplay::clearDisplay(){
  display.clearDisplay();
}

void WaterDisplay::updateDisplay() {
  display.display();
}

void WaterDisplay::putOnDisplay(int size, int x, int y, String unit) {
  display.setTextSize(size);
  display.setTextColor(WHITE);

    display.setCursor(x, y);
    display.print(unit);

}
void WaterDisplay::putOnDisplay(int size, int x, int y, float value, String unit) {
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

void WaterDisplay::displayHeader(){

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Caixa D'Agua");

}

void WaterDisplay::drawWaterLevel(float distanceToWater) {
  /* water tank dimensions: 
   *  capacity: 1000L
   *  Full height (with lid): 0,94m
   *  Water tank (no lid): 0,72m
   *  >> INSTALATION Tank Lid offset: 12cm
   *  Top diameter: 1,51m
   *  Botton diameter: 1,21m
   */
  Serial.println(distanceToWater);
  int offsetTankLid = 12;
  int tankHeight = 72; 
  int percentage = ((tankHeight - (distanceToWater - offsetTankLid)) / tankHeight) * 100;
  
  //fill percentage box
  display.fillRect(1, 20 , 72, 42, BLACK);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor( 10, 27 );
  //display.print( distanceToWater );

  display.print( percentage );
  
  display.print( "%" );

// distance
display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor( 10, 53 );
  display.print( distanceToWater );
  display.print("cm");
  
  // fill level bars
  // Parameters: X, Y, Width, Height, COLOR
  display.fillRect(77, 22 , 49, 40, BLACK);
  if(percentage > 0) display.fillRect(77, 52 , 48, 9, WHITE);

  if(percentage > 25) display.fillRect(77, 42 , 48, 9, WHITE);

  if(percentage > 50) display.fillRect(77, 32 , 48, 9, WHITE);

  if(percentage > 75) display.fillRect(77, 22 , 48, 9, WHITE);
  
  
  display.display();
}
