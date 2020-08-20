#include "WiFi.h"
#include "WiFiUdp.h"
#include <Time.h>
#include <Arduino_JSON.h>

#include <HTTPClient.h>
#include <NTPClient.h>
#include "oledDisplay.h"

const char* ssid = "wonderland2G_EXT";
const char* password = "a1b2c3d4e5";


const String endpoint = "https://api.openweathermap.org/data/2.5/onecall?lon=-46.64&lat=-23.55&exclude=minutely,hourly&units=metric&appid=";
const String weatherAPIKey = "404d2e01359620ba0f6d44cbb1eddf99";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "a.ntp.br");

HTTPClient http;


// Variables to save date and time
String formattedDate;
String dayStamp;
String timeStamp;

OledDisplay display;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  //display = OledDisplay();
  //display.startDisplay();
   connectToWifi();
   delay(800);
  //timeClient.begin();
  //timeClient.setTimeOffset(-3600*3);//Brazil
  
}

void loop() {
  //showDateAndTime();


  http.begin(endpoint+weatherAPIKey);


  int httpCode = http.GET();  //Make the request
 
  if (httpCode > 0) { //Check for the returning code
      String payload = http.getString();
      weatherOnScreen(payload);
    }
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end(); 

    delay(1000);
}

void weatherOnScreen(String weatherJson) {
 JSONVar myObject = JSON.parse(weatherJson);
 if (JSON.typeof(myObject) == "undefined") {
    Serial.println("Parsing input failed!");
    //display.putOnDisplay(2, 1, 40, "ERROR JSON");
    //display.updateDisplay();
    return;
  }
  //Serial.println(myObject);
  Serial.println("Today");
  Serial.println(myObject["current"]["temp"]);
  Serial.println(myObject["current"]["humidity"]);
  Serial.println(myObject["current"]["weather"][0]["main"]);
  Serial.println("Tomorrow");
  Serial.println(myObject["daily"][1]["weather"][0]["main"]);
  Serial.println(myObject["daily"][1]["temp"]["day"]);
   //display.putOnDisplay(2, 1, 40, (const char*) myObject["lon"]);


  //display.updateDisplay();

}

void showDateAndTime() {
  display.clearDisplay();
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  // The formattedDate comes with the following format:
  // 2018-05-28T16:00:13Z
  // We need to extract date and time
  formattedDate = timeClient.getFormattedDate();
  

  // Extract date
  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
  display.putOnDisplay(2, 1, 1, dayStamp);
  // Extract time
  timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);
  display.putOnDisplay(2, 1, 20, timeStamp);


  display.updateDisplay();

}

void connectToWifi() {
  //display.clearDisplay();
  WiFi.begin(ssid, password);
  //display.putOnDisplay(2, 1, 20, "Connecting to WiFi..");
  //display.updateDisplay();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}
