/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

#define LED_RED 11
#define LED_YEL 10
#define LED_GRN 9
#define BUTT_RED 3
#define BUTT_YEL 2
#define BUTT_GRN 1
#define REL_RED 7
#define REL_YEL 6
#define REL_GRN 5

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode (LED_YEL, OUTPUT);
  pinMode (LED_GRN, OUTPUT);
  pinMode (BUTT_RED, INPUT_PULLUP);
  pinMode (BUTT_YEL, INPUT_PULLUP);
  pinMode (BUTT_GRN, INPUT_PULLUP);
  pinMode (REL_RED, OUTPUT);
  pinMode (REL_YEL, OUTPUT);
  pinMode (REL_GRN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {

  if (digitalRead(BUTT_RED) == 0) {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(REL_RED, HIGH);
  }
  else {
    digitalWrite(LED_RED, LOW);
    digitalWrite(REL_RED, LOW);
  }

  if (digitalRead(BUTT_YEL) == 0) {
    digitalWrite(LED_YEL, HIGH);
    digitalWrite (REL_YEL, HIGH);
  }
  else {
    digitalWrite(LED_YEL, LOW);
    digitalWrite (REL_YEL, LOW);
  }

  if (digitalRead(BUTT_GRN) == 0) {
    digitalWrite(LED_GRN, HIGH);
    digitalWrite (REL_GRN, HIGH);
  }
  else {
    digitalWrite(LED_GRN, LOW);
    digitalWrite (REL_GRN, LOW);
  }
 
//  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(500);                       // wait for 0.5 seconds
//  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//  delay(500);                       // wait for 0.5 seconds
}
