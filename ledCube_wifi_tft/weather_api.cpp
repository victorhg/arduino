#include "weather_api.h"


CurrentWeather WeatherApi::currentWeather() {
  return weatherForecast.current; 
}

DayWeather WeatherApi::weatherForToday() {
  return weatherForecast.days[0]; 
}

DayWeather WeatherApi::weatherForTomorrow() {
  return weatherForecast.days[1];
}

void WeatherApi::updateWeatherInfo(String apiKey){
  http.begin(ENDPOINT + apiKey);


  int httpCode = http.GET();  //Make the request

   
  if (httpCode > 0) { //Check for the returning code
      String payload = http.getString();
      serializeWeatherInfo(payload);
  } else {
      Serial.println("Error on HTTP request");
  }
 
  http.end(); 
}

void WeatherApi::serializeWeatherInfo(String weatherJsonPayload) {
  JSONVar myObject = JSON.parse(weatherJsonPayload);
  
  if (JSON.typeof(myObject) == "undefined") {
    Serial.println("Parsing input failed!");
    return;
  }

  
  //Serial.println(myObject);
  CurrentWeather currentWeather;
  currentWeather.temperature = myObject["current"]["temp"];
  currentWeather.humidity = myObject["current"]["humidity"];
  currentWeather.feels_like = myObject["current"]["feels_like"];
  
  currentWeather.weatherInfo.main = myObject["current"]["weather"][0]["main"];
  currentWeather.weatherInfo.description = myObject["current"]["weather"][0]["description"];
  currentWeather.weatherInfo.icon = myObject["current"]["weather"][0]["icon"];
  this->weatherForecast.current = currentWeather;

  for (int i = 0; i < 8 ; i++) {//API returns full week
    DayWeather day;
    day.temperatures.day = myObject["daily"][i]["temp"]["day"];
    day.temperatures.min = myObject["daily"][i]["temp"]["min"];
    day.temperatures.max = myObject["daily"][i]["temp"]["max"];
    day.temperatures.night = myObject["daily"][i]["temp"]["night"];
    day.temperatures.morn = myObject["daily"][i]["temp"]["morn"];
    day.temperatures.eve = myObject["daily"][i]["temp"]["eve"];

    day.weatherInfo.main = myObject["daily"][i]["weather"][0]["main"];
    day.weatherInfo.description = myObject["daily"][i]["weather"][0]["description"];
    day.weatherInfo.icon = myObject["daily"][i]["weather"][0]["icon"];
    
    day.humidity = myObject["daily"][i]["humidity"];
    this->weatherForecast.days[i] = day;
   }

}
