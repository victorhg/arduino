                                                                  
#include "Ultrasonic.h"
#include "water_display.h"

#define echoPin 9 
#define trigPin 7 
Ultrasonic ultrasonic(trigPin, echoPin);

float distance; 
WaterDisplay waterDisplay;


void setup()
{
  waterDisplay = WaterDisplay();
  Serial.begin(9600); //This pipes to the serial monitor
 
  Serial.println("Initialize Display");
  waterDisplay.startDisplay();

}

void loop() {

  distance = ultrasonic.read();

  waterDisplay.drawWaterLevel(distance);


  delay(1000);
}
