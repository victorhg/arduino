#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE) ;//initialize sensor

void setup()
{
  Serial.begin(9600);
  
  Serial.println(F("DHTxx test!"));
  dht.begin();
}

void loop()
{
  delay(2000);

  Serial.print("Humidity (%): ");
  Serial.println((float)dht.readHumidity(), 2);

  Serial.print("Temperature (C): ");
  Serial.println((float)dht.readTemperature(), 2);

  delay(2000);

}
