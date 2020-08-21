#include <Arduino_JSON.h>
#include <HTTPClient.h>

const String ENDPOINT = "https://api.openweathermap.org/data/2.5/onecall?lon=-46.64&lat=-23.55&exclude=minutely,hourly&units=metric&appid=";


struct temp
{
  long day;
  long min;
  long max;
  long night;
  long morn;
  long eve;
};
struct weather 
{
  String main;
  String description;
  String icon;
};
typedef struct weather weather;
typedef struct temp temperature;

struct day 
{
  temperature temperatures;
  temperature feels_like;
  weather weatherInfo;
  long humidity;
};
typedef struct day DayWeather;


struct currentWeather
{
   weather weatherInfo;
   long temperature;
   long feels_like;
   long humidity;
};

typedef struct currentWeather CurrentWeather;

struct weatherForecast {
  currentWeather current;
  day days[8];

};
typedef struct weatherForecast WeatherForecast;

class WeatherApi {

   public:
     WeatherApi();
     CurrentWeather currentWeather();
     DayWeather weatherForToday();
     DayWeather weatherForTomorrow();
     void updateWeatherInfo(String apiKey);
     WeatherForecast weatherForecast;
     

   private:
    String APIKey;
    HTTPClient http;
    void serializeWeatherInfo(String weatherJsonPayload);
};
