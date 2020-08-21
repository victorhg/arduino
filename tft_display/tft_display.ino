
#define LCD_RD  2  //LED
#define LCD_WR  4
#define LCD_RS 15  //or LCD_CD - hard-wired to A2 (GPIO35) 
#define LCD_CS 33  //hard-wired to A3 (GPIO34)
#define LCD_RESET 32 //hard-wired to A4 (GPIO36)

#define LCD_D0 12
#define LCD_D1 13
#define LCD_D2 26
#define LCD_D3 25
#define LCD_D4 17
#define LCD_D5 16
#define LCD_D6 27
#define LCD_D7 14
#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
 
// Assign human-readable names to some common 16-bit color values:
#define    BLACK   0x0000
#define    BLUE    0x001F
#define    RED     0xF800
#define    GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
 
void setup(void) {
  Serial.begin(9600);
  uint16_t ID = tft.readID();
tft.begin(ID); 
Serial.print("Identificador: ");
Serial.println(ID);
  tft.setRotation(0);
  tft.fillScreen(BLACK);
 
  tft.setTextSize(1);
  tft.setTextColor(WHITE);
  tft.println("Hallo Wereld!");
 
  tft.setTextSize(2);
  tft.setTextColor(YELLOW);
  tft.println("Hallo Wereld!");
  
  tft.setTextSize(3);
  tft.setTextColor(GREEN);
  tft.println("Hallo Wereld!");
}
 
void loop(void) {  
  delay(20);
}
