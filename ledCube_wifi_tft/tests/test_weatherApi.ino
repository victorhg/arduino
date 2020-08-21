
#line 2 "weatherApi_test.ino"

#include <AUnit.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "weather_api.h"

String apiKey = "404d2e01359620ba0f6d44cbb1eddf99";

char* ssid2 = "wonderland2G_EXT";
char* password2 = "a1b2c3d4e5";

WeatherApi api;


test(correct) {
  Serial.println("AAAAA >>>>>");
  Serial.println(api.weatherForecast.current.humidity);
 long hum = api.weatherForecast.current.humidity;
  assertNotEqual(0, 1);
}

test(incorrect) {
  int x = 1;
  assertNotEqual(x, 1);
}

void setup() {
  delay(1000); // wait for stability on some boards to prevent garbage Serial
  Serial.begin(115200); // ESP8266 default of 74880 not supported on Linux
  WiFi.begin(ssid2, password2);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  //api.updateWeatherInfo(apiKey);
}

void loop() {
  aunit::TestRunner::run();
}
