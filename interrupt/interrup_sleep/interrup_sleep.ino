#include "LowPower.h"
// REFERENCE: https://github.com/rocketscream/Low-Power/blob/master/Examples/powerDownWakeExternalInterrupt/powerDownWakeExternalInterrupt.ino

const int wakeUpPin = 0;

int count= 0;

void setup() {
  while(!Serial){ }
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(wakeUpPin, INPUT_PULLUP);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Sleep in: ");
  Serial.print(count);
  Serial.println(" - ");
  Serial.print(digitalRead(wakeUpPin));


  delay(1000);
  if (count == 10) {
    going_to_sleep();
  }
  count++;
}

void going_to_sleep(){
  Serial.println("ZzzZz sleeeeep");
  attachInterrupt(2, wakeUp, CHANGE);
  delay(500);
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);

  delay(500);
  Serial.println("just woke up!");
  detachInterrupt(2);
}

void wakeUp(){
  count = 0;
}
