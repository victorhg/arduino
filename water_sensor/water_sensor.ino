
#include <avr/sleep.h>
#include "display.h"


#define echoPin 9 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 7 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
float duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement



//define button
int buttonPin = 0;
#define interruptPin 0

int wakePin = 15;                 // pin used for waking up
int sleepStatus = 0;             // variable to store a request for sleep
int count = 0;                   // counter

void setup()
{
  while(!Serial) {} // Waiting pro micro to start Serial

  //Sonic Sensor
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT

  pinMode(interruptPin, INPUT);
  
  Serial.begin(9600); //This pipes to the serial monitor
 
  Serial.println("Initialize Display");
  startDisplay();

}

void loop() {
  calculateDistance();

  int buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  count++;

  Serial.print("Sleep: ");
  Serial.println(count);
  clearDisplay();
  putOnDisplay(4, 20, 16, distance, "cm");
  updateDisplay();

  if (Serial.available()) {
    int val = Serial.read();
    if (val == 'S') {
      Serial.println("Serial: Entering Sleep mode");
      delay(100);     // this delay is needed, the sleep 
                      //function will provoke a Serial error otherwise!!
      count = 0;
      sleepNow();     // sleep function called here
    }
    if (val == 'A') {
      Serial.println("Hola Caracola"); // classic dummy message
    }
  }

  
  // check if it should go to sleep because of time
  if (count >= 10) {
      Serial.println("Timer: Entering Sleep mode");
      delay(100);     // this delay is needed, the sleep 
                      //function will provoke a Serial error otherwise!!
      count = 0;
      sleepNow();     // sleep function called here
  }

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



/* --------------- */
/* SLEEP FUNCTIONS */

// here we put the arduino to sleep
void sleepNow()         
{
    /* Now is the time to set the sleep mode. In the Atmega8 datasheet
     * http://www.atmel.com/dyn/resources/prod_documents/doc2486.pdf on page 35
     * there is a list of sleep modes which explains which clocks and 
     * wake up sources are available in which sleep mode.
     *
     * In the avr/sleep.h file, the call names of these sleep modes are to be found:
     *
     * The 5 different modes are:
     *     SLEEP_MODE_IDLE         -the least power savings 
     *     SLEEP_MODE_ADC
     *     SLEEP_MODE_PWR_SAVE
     *     SLEEP_MODE_STANDBY
     *     SLEEP_MODE_PWR_DOWN     -the most power savings
     *
     * For now, we want as much power savings as possible, so we 
     * choose the according 
     * sleep mode: SLEEP_MODE_PWR_DOWN
     * 
     */  
    sleep_enable();
    
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);   // sleep mode is set here

    // enables the sleep bit in the mcucr register
    // so sleep is possible. just a safety pin 

    /* Now it is time to enable an interrupt. We do it here so an 
     * accidentally pushed interrupt button doesn't interrupt 
     * our running program. if you want to be able to run 
     * interrupt code besides the sleep function, place it in 
     * setup() for example.
     * 
     * In the function call attachInterrupt(A, B, C)
     * A   can be either 0 or 1 for interrupts on pin 2 or 3.   
     * 
     * B   Name of a function you want to execute at interrupt for A.
     *
     * C   Trigger mode of the interrupt pin. can be:
     *             LOW        a low level triggers
     *             CHANGE     a change in level triggers
     *             RISING     a rising edge of a level triggers
     *             FALLING    a falling edge of a level triggers
     *
     * In all but the IDLE sleep modes only LOW can be used.
     */

     clearDisplay();
     putOnDisplay(3,5,10, "zZZzz");
     updateDisplay();
     delay(500);
     clearDisplay();
     updateDisplay();

    attachInterrupt(0,wakeUpNow, HIGH); // use interrupt 0 (pin 2) and run function
                                       // wakeUpNow when pin 2 gets LOW 

    sleep_mode();            // here the device is actually put to sleep!!
                             // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP

    sleep_disable();         // first thing after waking from sleep:
                             // disable sleep...
    detachInterrupt(0);      // disables interrupt 0 on pin 2 so the 
                             // wakeUpNow code will not be executed 
                             // during normal running time.

}


void wakeUpNow()        // here the interrupt is handled after wakeup
{
  // execute code here after wake-up before returning to the loop() function
  // timers and code using timers (serial.print and more...) will not work here.
  // we don't really need to execute any special functions here, since we
  // just want the thing to wake up
 Serial.println("WAKE UPPPPPP");
}
