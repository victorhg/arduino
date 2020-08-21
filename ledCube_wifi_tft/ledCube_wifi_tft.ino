#include "WiFi.h"
#include "WiFiUdp.h"
#include <Time.h>
#include <Arduino_JSON.h>

#include <NTPClient.h>
#include "oledDisplay.h"
#include "weather_api.h"

const char* ssid = "wonderland2G_EXT";
const char* password = "a1b2c3d4e5";
String apiKey = "404d2e01359620ba0f6d44cbb1eddf99";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "a.ntp.br");

// Variables to save date and time
String formattedDate;
String dayStamp;
String timeStamp;

long currentTemperature;
long currentHumidity;

OledDisplay display;
WeatherApi weatherApi;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
   display = OledDisplay();
  display.startDisplay();
   connectToWifi();

   weatherApi.updateWeatherInfo(apiKey);
  

   delay(800);
  timeClient.begin();
  timeClient.setTimeOffset(-3600*3);//Brazil
  
}

void loop() {
  display.clearDisplay();
  showDateAndTime();
  
  showForecast();
  display.updateDisplay();
  
  delay(2000);
}

void showForecast(){
  currentTemperature = weatherApi.weatherForecast.current.temperature;
  currentHumidity = weatherApi.weatherForecast.current.humidity;
  

  display.putOnDisplay(3, 3, 30, String(currentTemperature)+"C");


  display.putOnDisplay(1, 33, 56, String(currentHumidity)+"%");
  
  display.putOnDisplay(1, 1, 56, weatherApi.weatherForecast.current.weatherInfo.main);
  
  String minDay = "Min " + String(weatherApi.weatherForToday().temperatures.min) + "C";
  String maxDay = "Max " + String( weatherApi.weatherForToday().temperatures.max) + "C";
  display.putOnDisplay(1, 68, 45, minDay);
  display.putOnDisplay(1, 68, 56,  maxDay );

}


void showDateAndTime() {
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  formattedDate = timeClient.getFormattedDate();
  

  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
  String strDay = dayStamp.substring(splitT - 2, splitT) + "/" + dayStamp.substring(splitT-5, splitT -3);

  display.putOnDisplay(2, 59, 28, strDay);
  
  String hoursStr = timeClient.getHours() < 10 ? "0" + String(timeClient.getHours()) : String(timeClient.getHours());

  String minuteStr = timeClient.getMinutes() < 10 ? "0" + String(timeClient.getMinutes()) : String(timeClient.getMinutes());

  timeStamp = hoursStr + ":" + minuteStr;
  //timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);

  display.putOnDisplay(3, 20, 1, timeStamp);



}

void connectToWifi() {
  display.clearDisplay();
  WiFi.begin(ssid, password);
  display.putOnDisplay(2, 1, 20, "Connecting to WiFi..");
  display.updateDisplay();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}
