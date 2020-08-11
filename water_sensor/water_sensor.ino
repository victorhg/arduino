
#include "water_display.h"

#define echoPin 9 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 7 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
float duration; // variable for the duration of sound wave travel
int distance; // variable for the distance m
WaterDisplay waterDisplay;


void setup()
{
  while(!Serial) {} // Waiting pro micro to start Serial
  waterDisplay = WaterDisplay();
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPU
  Serial.begin(9600); //This pipes to the serial monitor
 
  Serial.println("Initialize Display");
  waterDisplay.startDisplay();

}

void loop() {
  calculateDistance();

  //waterDisplay.clearDisplay();
  //waterDisplay.displayHeader();
  waterDisplay.drawWaterLevel(distance);
  //waterDisplay.putOnDisplay(3, 30, 16, distance, "cm");
  //waterDisplay.updateDisplay();

  delay(1000);
}
  
void calculateDistance(){
// Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  /* Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");*/
}
