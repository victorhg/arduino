
#define LCD_RD  2  //LED
#define LCD_WR  4
#define LCD_RS 15  //or LCD_CD - hard-wired to A2 (GPIO35) 
#define LCD_CS 33  //hard-wired to A3 (GPIO34)
#define LCD_RST 32 //hard-wired to A4 (GPIO36)

#define LCD_D0 12
#define LCD_D1 13
#define LCD_D2 26
#define LCD_D3 25
#define LCD_D4 17
#define LCD_D5 16
#define LCD_D6 27
#define LCD_D7 14


#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>
#include <SPI.h>



Adafruit_ILI9341 tft = Adafruit_ILI9341(LCD_CS, LCD_RS, LCD_RST);
XPT2046_Touchscreen ts(LCD_CS);

float p = 3.1415926;
XPT2046_Touchscreen ts(TS_CS);
 
void setup()
{
  Serial.begin(115200);
  ts.begin();
  ts.setRotation(1);
 
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(3);
  tft.println("Touch Test");
 
  while (!Serial &amp;&amp; (millis() &lt;= 1000))
    ;
}
 
void loop()
{
  if (ts.touched())
  {
    TS_Point p = ts.getPoint();
 
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(0, 0);
 
    tft.print("Pressure = ");
    tft.println(p.z);
    tft.print("X = ");
    tft.println(p.x);
    tft.print("Y = ");
    tft.println(p.y);
  }
}
