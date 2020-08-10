// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 6;     // the number of the pushbutton pin
const int ledPin =  12;      // the number of the LED pin


//const int yButtonPin = 7;
//const int yLedPin = 11;


// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int yButtonState = 0;

void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
 // pinMode(yLedPin, OUTPUT);
  
  // initialize the pushbutton pin as an input:
  //pinMode(buttonPin, INPUT);
  //pinMode(yButtonPin, INPUT);

}
void loop() {
  // read the state of the pushbutton value:
  //buttonState = digitalRead(buttonPin);
  //yButtonState = digitalRead(yButtonPin);
  
  // Show the state of pushbutton on serial monitor
  //Serial.print( "Button State: RED = ");
  //Serial.println(buttonState);
  //Serial.print(" | YELLOW = ");
  //Serial.println(yButtonState);

  digitalWrite(ledPin, HIGH);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  //toggleLED(buttonState, ledPin);
  //toggleLED(yButtonState, yLedPin);
  
  
  // Added the delay so that we can see the output of button
  delay(1000);
  //digitalWrite(ledPin, LOW);
}

void toggleLED(int state, int pin) {
    digitalWrite(pin, state);
}
