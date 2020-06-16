/* Traffic lights toggle switch version 2 light stays o or off when button is pushed*/

#define LED_RED 11
#define LED_YEL 10
#define LED_GRN 9
#define BUTT_RED 3
#define BUTT_YEL 2
#define BUTT_GRN 1
#define REL_RED 7
#define REL_YEL 6
#define REL_GRN 5

int relRedState = LOW;         // the current state of the output pin
int relYelState = LOW;         // the current state of the output pin
int relGrnState = LOW;         // the current state of the output pin

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.

  pinMode(LED_RED, OUTPUT);
  pinMode (LED_YEL, OUTPUT);
  pinMode (LED_GRN, OUTPUT);
  pinMode (BUTT_RED, INPUT_PULLUP);
  pinMode (BUTT_YEL, INPUT_PULLUP);
  pinMode (BUTT_GRN, INPUT_PULLUP);
  pinMode (REL_RED, OUTPUT);
  pinMode (REL_YEL, OUTPUT);
  pinMode (REL_GRN, OUTPUT);
  digitalWrite(REL_RED, relRedState);
  digitalWrite(REL_YEL, relYelState);
  digitalWrite(REL_GRN, relGrnState);

  onSequence();

}

// the loop function runs over and over again forever
void loop() {

// I don't think this section was doing anything?  REL pins are outputs, so reading them
// generally doesn't have an effect.
  if (digitalRead(BUTT_RED) == 1) {
    relRedState = digitalRead(REL_RED);
  }

  if (digitalRead(BUTT_YEL) == 1) {
    relYelState = digitalRead(REL_YEL);
  }

  if (digitalRead(BUTT_GRN) == 1) {
    relGrnState = digitalRead(REL_GRN);
  }

  //First, load this code and see if it behaves the same
  //Then, make it so if the red button is pressed, testSeq happens.
  // Keep LED_RED on while testSeq is going, turn it off when the sequence is done.

  if (digitalRead(BUTT_RED) == 0) {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(REL_RED, !relRedState);
    delay(50);
  }
  else {
    digitalWrite(LED_RED, LOW);
    // digitalWrite(REL_RED, LOW);
  }

  if (digitalRead(BUTT_YEL) == 0) {
    digitalWrite(LED_YEL, HIGH);
    digitalWrite(REL_YEL, !relYelState);
    delay(50);
  }
  else {
    digitalWrite(LED_YEL, LOW);
    // digitalWrite (REL_YEL, LOW);
  }

  if (digitalRead(BUTT_GRN) == 0) {
    digitalWrite(LED_GRN, HIGH);
    digitalWrite(REL_GRN, !relGrnState);
    delay(50);
  }
  else {
    digitalWrite(LED_GRN, LOW);
    //  digitalWrite (REL_GRN, LOW);

  }
  //  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  //  delay(500);                       // wait for 0.5 seconds
  //  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  //  delay(500);                       // wait for 0.5 seconds
}

void gameSeq (void) {
  // write a sequence of 4 blinks, using all colors, in any order
}

void onSequence (void) {
  //startup - traffic lights

delay (1000);
digitalWrite (REL_RED, HIGH);
digitalWrite (REL_YEL, HIGH);
digitalWrite (REL_GRN, HIGH);
digitalWrite (LED_RED, HIGH);
digitalWrite (LED_YEL, HIGH);
digitalWrite (LED_GRN, HIGH);
delay (1000);
digitalWrite (REL_RED, LOW);
digitalWrite (REL_YEL, LOW);
digitalWrite (REL_GRN, LOW);
digitalWrite (LED_RED, LOW);
digitalWrite (LED_YEL, LOW);
digitalWrite (LED_GRN, LOW);
}



//     digitalWrite (REL_RED, HIGH);
//     delay (500);
//     digitalWrite (REL_RED, LOW);
//    // delay (100);
//
//     digitalWrite (REL_YEL, HIGH);
//     delay (500);
//     digitalWrite (REL_YEL, LOW);
//     //delay (100);
//
//     digitalWrite (REL_GRN, HIGH);
//     delay (500);
//     digitalWrite (REL_GRN, LOW);
//   //  delay (100);
//
//     digitalWrite (REL_RED, HIGH);
//     digitalWrite (REL_YEL, HIGH);
//     digitalWrite (REL_GRN, HIGH);
//     delay (500);
//     digitalWrite (REL_RED, LOW);
//     digitalWrite (REL_YEL, LOW);
//     digitalWrite (REL_GRN, LOW);
//     delay (100);
//
//
//   //startup button leds
//     digitalWrite (LED_RED, HIGH);
//     delay (500);
//     digitalWrite (LED_RED, LOW);
//    // delay (100);
//
//     digitalWrite (LED_YEL, HIGH);
//     delay (500);
//     digitalWrite (LED_YEL, LOW);
//     //delay (100);
//
//     digitalWrite (LED_GRN, HIGH);
//     delay (500);
//     digitalWrite (LED_GRN, LOW);
//   //  delay (100);
//
//     digitalWrite (LED_RED, HIGH);
//     digitalWrite (LED_YEL, HIGH);
//     digitalWrite (LED_GRN, HIGH);
//     delay (500);
//     digitalWrite (LED_RED, LOW);
//     digitalWrite (LED_YEL, LOW);
//     digitalWrite (LED_GRN, LOW);
// }
