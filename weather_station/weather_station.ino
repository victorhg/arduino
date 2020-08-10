//Temperature Sensor
#include "DHT.h"


//OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "image_logo.h"

//OLED define
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//Sensor define
#define DHTPIN 2
#define DHTTYPE DHT11
float humidity;
float minHumidity = 100;
float maxHumidity = 0;

float temperature;
float minTemperature = 100;
float maxTemperature = 0;

//Button define
const int buttonPin = 12;
int buttonState = 0;
const int ledPin =  8;


DHT dht(DHTPIN, DHTTYPE) ;//initialize sensor

void setup() {
  Serial.begin(9600);

  //button
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  dht.begin();

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

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(600);
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  buttonState = digitalRead(buttonPin);
  
Serial.println("H:");
Serial.print(humidity);
Serial.print("T:");
Serial.println(temperature);
  
  if(buttonState == HIGH) {
    Serial.println("MAXX"); 
    showMinMaxWeatherHUD();
  } else {
    showWeatherHUD();
    setRecordNumbers();

    
    digitalWrite(ledPin, LOW);
  }  
}

void showMinMaxWeatherHUD() {
  oledDisplayHeader();

  oledDisplay(1, 5, 16, minHumidity, "% min");
  oledDisplay(1, 5, 40, maxHumidity, "% max");
  

  oledDisplay(1, 75, 16, minTemperature, "C min");
  oledDisplay(1, 75, 40, maxTemperature, "C max");
  
  display.display();
}

void showWeatherHUD() { 
  oledDisplayHeader();

  oledDisplay(3, 5, 28, humidity, "%");
  oledDisplay(3, 70, 28, temperature, "C");

  display.display();
}

void setRecordNumbers() {
  if(temperature < minTemperature) { minTemperature = temperature; }
  if(temperature > maxTemperature) { maxTemperature = temperature; }
  if(humidity < minHumidity) { minHumidity = humidity; }
  if(humidity > maxHumidity) { maxHumidity = humidity; }
}

void oledDisplayHeader() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Humidade");
  display.setCursor(60, 0);
  display.print("Temperatura");
}
void oledDisplay(int size, int x, int y, float value, String unit) {
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
