/*
 Arduino LiPo Battery Monitor
 By Roland
 from: https://www.teachmemicro.com/arduino-lipo-battery-monitor
*/
 
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


//OLED define
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
 
float ARef = 1.1;
 
void setup() {
  // put your setup code here, to run once:
   analogReference(INTERNAL);
   if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
   }
   display.setTextSize(2);
   display.setTextColor(WHITE);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  float raw = analogRead(A0);
  float x = raw/1023;
  float voltage = x*ARef*4;
  display.clearDisplay();
  display.setCursor( 32, 10 );
  display.print(" ");
  display.print(voltage);
  display.println(" V");
  if(voltage > 0 ){
    //one bar
    display.fillRect(15,30,10,15,WHITE);//
  } 
  if(voltage > 1 ){
    //two bar
    display.fillRect(25,30,5,15,BLACK);
    display.fillRect(30,30,10,15,WHITE);//
  }
  if(voltage > 2.775 ){
    //three bar
    display.fillRect(40,30,5,15,BLACK);
    display.fillRect(45,30,10,15,WHITE);//
  }
  if(voltage > 3.7) {
    //full bars
    display.fillRect(55,30,5,15,BLACK);
    display.fillRect(60,30,10,15,WHITE);//
  }
  display.display(); 
  delay(1000);
}
