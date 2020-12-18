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

#define WON 1
#define LOST 0


int red = BUTT_RED;
int yel = BUTT_YEL;
int grn = BUTT_GRN;

int relRedState = LOW;         // the current state of the output pin
int relYelState = LOW;         // the current state of the output pin
int relGrnState = LOW;         // the current state of the output pin

int ltime = 500;               // initial time lights are on and off

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

  Serial.begin(9600);

}

// the loop function runs over and over again forever
// buttons = 0 when they are pressed
// leds and lights = 1 when they are lit
void loop() {

  int startGame = 0;
  int gameOn = 0;
  startGame = digitalRead(BUTT_RED) + digitalRead(BUTT_GRN) + digitalRead(BUTT_YEL);
  if (startGame < 3) gameOn = 1;

  int stopGame = 0;

  // The whole game!  As long as you're stilling playing, this loops
  while (gameOn) {
    int gameSeq[] = {red, yel, grn, yel, red};          // generates the blinking light sequency
    int lenGameSeq = sizeof(gameSeq) / sizeof(gameSeq[0]);
    blinkLights(gameSeq, lenGameSeq);    // blinks the lights in sequence

    int gameResult = WON;

    int i = 0;
    for (i = 0; i < lenGameSeq; i++) {
      int buttonPushed = 0;
      long startTime = millis();
      while ( (millis() - startTime < 3000) && (buttonPushed == 0) ) {
        buttonPushed = checkButt();     // waits for button press, gives the player 3 seconds
      }
      illuminate(buttonPushed, 300);
      // Serial.print("button pushed = ");
      // Serial.println(buttonPushed);
      // Serial.print("color seq = ");
      // Serial.println(gameSeq[i]);
      if (buttonPushed == gameSeq[i]) {
        delay (500);
          // if the correct button was pushed do nothing, continue checking buttons
      }
      else {
        // catches both wrong button press or no button pressed & timeout
        gameResult = LOST;
        break;
      }

    }
    if (gameResult == WON) gameWonSeq();
    else gameLostSeq();

    gameOn = 0;
  }

  delay (100);
}

void illuminate(int color, int lightTime) {
  if (color == red){
    digitalWrite(REL_RED, HIGH);
    digitalWrite(LED_RED, HIGH);
    delay (lightTime);
    digitalWrite(REL_RED, LOW);
    digitalWrite(LED_RED, LOW);
  }
  if (color == grn){
    digitalWrite(REL_GRN, HIGH);
    digitalWrite(LED_GRN, HIGH);
    delay (lightTime);
    digitalWrite(REL_GRN, LOW);
    digitalWrite(LED_GRN, LOW);
  }
  if (color == yel){
    digitalWrite(REL_YEL, HIGH);
    digitalWrite(LED_YEL, HIGH);
    delay (lightTime);
    digitalWrite(REL_YEL, LOW);
    digitalWrite(LED_YEL, LOW);
    }
}

int checkButt() {
  if (digitalRead(BUTT_RED) == 0) return red;
  if (digitalRead(BUTT_GRN) == 0) return grn;
  if (digitalRead(BUTT_YEL) == 0) return yel;
  return 0;
}

int generateSeq(void) {
  return red;
  // write a sequence of 4 blinks, using all colors, in any order
}

void onSequence(void) {
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
  delay (1000);
}

void gameLostSeq(void) {
  delay (500);
  int i = 0;
  for (i = 0; i < 3; i++) {
    illuminate (red, 500);
    delay (500);

  }
}

void gameWonSeq(void) {
  delay(500);
  int i = 0;
  for (i = 0; i < 3; i++) {
    illuminate (grn, 500);
    delay (500);
  }
}

void blinkLights(int colorSeq[], int lenColorSeq) {
  delay(500);
  int i = 0;
  for (i = 0; i < lenColorSeq; i++) {
    if (colorSeq[i] == red){
      digitalWrite (LED_RED, HIGH);
      digitalWrite (REL_RED, HIGH);
      delay(ltime);
      digitalWrite (LED_RED, LOW);
      digitalWrite (REL_RED, LOW);
      delay(ltime);
    }
    if (colorSeq[i] == yel){
      digitalWrite (LED_YEL, HIGH);
      digitalWrite (REL_YEL, HIGH);
      delay(ltime);
      digitalWrite (LED_YEL, LOW);
      digitalWrite (REL_YEL, LOW);
      delay(ltime);
    }
    if (colorSeq[i] == grn){
      digitalWrite (LED_GRN, HIGH);
      digitalWrite (REL_GRN, HIGH);
      delay(ltime);
      digitalWrite (LED_GRN, LOW);
      digitalWrite (REL_GRN, LOW);
      delay(ltime);
    }
  }
}

// void blinkLights(int color) {
//   delay(500);
//   if (color == red){
//     digitalWrite (LED_RED, HIGH);
//     digitalWrite (REL_RED, HIGH);
//     delay(500);
//     digitalWrite (LED_RED, LOW);
//     digitalWrite (REL_RED, LOW);
//     delay(500);
//   }
//   if (color == yel){
//     digitalWrite (LED_YEL, HIGH);
//     digitalWrite (REL_YEL, HIGH);
//     delay(500);
//     digitalWrite (LED_YEL, LOW);
//     digitalWrite (REL_YEL, LOW);
//     delay(500);
//   }
//   if (color == grn){
//     digitalWrite (LED_GRN, HIGH);
//     digitalWrite (REL_GRN, HIGH);
//     delay(500);
//     digitalWrite (LED_GRN, LOW);
//     digitalWrite (REL_GRN, LOW);
//     delay(500);
//   }
// }
