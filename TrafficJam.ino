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

int gameSeq[5] = {0};

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
  //  int gameSeq[] = {red, yel, grn, yel, red};          // generates the blinking light sequence
    generateSeq();
    int lenGameSeq = sizeof(gameSeq) / sizeof(gameSeq[0]);

    int gameResult = WON;       // as long as gameResult is WON, the game keeps playing

    int i = 0;
    int currentLoop = 1;
    while ( (currentLoop <= lenGameSeq) && (gameResult == WON) ){

      blinkLights(gameSeq, currentLoop, 500);  // blinks lights up to the current loop

      for (i = 0; i < currentLoop; i++) {
        // detect the sequence up to the current loop

        int buttonPushed = 0;
        long startTime = millis();
        while ( (millis() - startTime < 3000) && (buttonPushed == 0) ) {
          buttonPushed = checkButt();     // waits for button press, gives the player 3 seconds
        }

        long buttTime = millis();
        if (buttonPushed) {
          illuminate(buttonPushed);       // illuminates button & traffic lights for as long as button is pressed
          delay (50);                     // waits for bouncing to stop
          while (checkButt() && (millis() - buttTime < 3000)); // checks to see if button has been pressed for longer than 3 seconds
          deluminate(buttonPushed);
          delay (50);                     // in case of bounce on release
          if (millis() - buttTime >= 3050){   // if button has been pressed for 3 or more seconds YOU LOSE
            gameResult = LOST;
            break;
          }  
        }


        if (buttonPushed == gameSeq[i]) {
  //        delay (500);  // need to give the player time to unpress the button
            // if the correct button was pushed do nothing, continue checking buttons
        }
        else {
          // catches both wrong button press and no button pressed & timeout
          gameResult = LOST;
          break;
        }
      }

      currentLoop++;
    }

    if (gameResult == WON) gameWonSeq();
    else gameLostSeq();

    gameOn = 0;
  }

  delay (100);
}

void blinkLights(int colorSeq[], int lenColorSeq, int lightTime) {
  delay(500);
  int i = 0;
  for (i = 0; i < lenColorSeq; i++) {
    if (colorSeq[i] == red){
      digitalWrite (LED_RED, HIGH);
      digitalWrite (REL_RED, HIGH);
      delay(lightTime);
      digitalWrite (LED_RED, LOW);
      digitalWrite (REL_RED, LOW);
      delay(lightTime);
    }
    if (colorSeq[i] == yel){
      digitalWrite (LED_YEL, HIGH);
      digitalWrite (REL_YEL, HIGH);
      delay(lightTime);
      digitalWrite (LED_YEL, LOW);
      digitalWrite (REL_YEL, LOW);
      delay(lightTime);
    }
    if (colorSeq[i] == grn){
      digitalWrite (LED_GRN, HIGH);
      digitalWrite (REL_GRN, HIGH);
      delay(lightTime);
      digitalWrite (LED_GRN, LOW);
      digitalWrite (REL_GRN, LOW);
      delay(lightTime);
    }
  }
}

void illuminate(int color) {
  if (color == red){
    digitalWrite(REL_RED, HIGH);
    digitalWrite(LED_RED, HIGH);
  }
  if (color == grn){
    digitalWrite(REL_GRN, HIGH);
    digitalWrite(LED_GRN, HIGH);
  }
  if (color == yel){
    digitalWrite(REL_YEL, HIGH);
    digitalWrite(LED_YEL, HIGH);
  }
}

void deluminate(int color) {
  if (color == red){
    digitalWrite(REL_RED, LOW);
    digitalWrite(LED_RED, LOW);
  }
  if (color == grn){
    digitalWrite(REL_GRN, LOW);
    digitalWrite(LED_GRN, LOW);
  }
  if (color == yel){
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

void generateSeq(void) {

//  gameSeq[] = {red, yel, grn, yel, red};
  gameSeq[0] = red;
  gameSeq[1] = yel;
  gameSeq[2] = grn;
  gameSeq[3] = yel;
  gameSeq[4] = red;
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
  int lostSeq[3] = {red, red, red};
  blinkLights (lostSeq, 3, 500);
}

void gameWonSeq(void) {
  delay(500);
  int wonSeq[3] = {grn, grn, grn};
  blinkLights (wonSeq, 3, 500);
}
