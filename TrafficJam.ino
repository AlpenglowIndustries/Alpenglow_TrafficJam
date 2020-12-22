/* Traffic lights toggle switch version 2 light stays o or off when button is pushed*/

// Arduino Pin Assignments
#define LED_RED 11
#define LED_YEL 10
#define LED_GRN 9
#define MODE_SW 8
#define BUTT_RED 3
#define BUTT_YEL 2
#define BUTT_GRN 1
#define REL_RED 7
#define REL_YEL 6
#define REL_GRN 5

// Constants
#define WON 1
#define LOST 0

// Variables

// ...for any mode
int red = BUTT_RED;
int yel = BUTT_YEL;
int grn = BUTT_GRN;

// ...for Mood Light mode
int lightMode = 0;
int redState = 0;
int yelState = 0;
int grnState = 0;

// ...for Game mode
int gameSeq[10] = {0};

// the setup function runs once when you press reset or power the board
void setup() {
  
  pinMode(LED_RED, OUTPUT);
  pinMode (LED_YEL, OUTPUT);
  pinMode (LED_GRN, OUTPUT);
  pinMode (MODE_SW, INPUT);
  pinMode (BUTT_RED, INPUT_PULLUP);
  pinMode (BUTT_YEL, INPUT_PULLUP);
  pinMode (BUTT_GRN, INPUT_PULLUP);
  pinMode (REL_RED, OUTPUT);
  pinMode (REL_YEL, OUTPUT);
  pinMode (REL_GRN, OUTPUT);
  digitalWrite(REL_RED, LOW);
  digitalWrite(REL_YEL, LOW);
  digitalWrite(REL_GRN, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YEL, LOW);
  digitalWrite(LED_GRN, LOW);

  onSequence();

  randomSeed(analogRead(0));
  Serial.begin(9600);
}

// the loop function runs over and over again forever
// buttons = 0 when they are pressed
// leds and lights = 1 when they are lit
void loop() {
  lightMode = digitalRead (MODE_SW);

  // operates lights in Mood Light or Game mode
  switch (lightMode) {
    case 0: // MOOD LIGHT - button presses turn lights on and off
    {
      int moodButt = 0;
      moodButt = checkButt();

      if (moodButt == red){       // these checks take enough time that no debounce is neeeded
        redState = !redState;
        digitalWrite(REL_RED, redState);
        digitalWrite(LED_RED, redState);
      }
      if (moodButt == yel){
        yelState = !yelState;
        digitalWrite(REL_YEL, yelState);
        digitalWrite(LED_YEL, yelState);
      }
      if (moodButt == grn){
        grnState = !grnState;
        digitalWrite(REL_GRN, grnState);
        digitalWrite(LED_GRN, grnState);
      }

      while (checkButt());    // delays as long as a button is pressed
      delay(50);              // in case of bounce on button release
      break;
    }
    case 1: // SIMON SAYS game
    {
      int startGame = 0;
      int gameOn = 0;
      //deluminate(red);
      //deluminate(yel);
      //deluminate(grn);
      startGame = digitalRead(BUTT_RED) + digitalRead(BUTT_GRN) + digitalRead(BUTT_YEL);

      if (startGame < 3) gameOn = 1;

      // The whole game!  As long as you're stilling playing, this loops
      while (gameOn) {
      //  int gameSeq[] = {red, yel, grn, yel, red};          // generates the blinking light sequence

        int lenGameSeq = sizeof(gameSeq) / sizeof(gameSeq[0]);
        generateSeq(lenGameSeq);
        int gameResult = WON;       // as long as gameResult is WON, the game keeps playing

        int i = 0;
        int currentLoop = 1;
        int lightDelay = 500;
        while ( (currentLoop <= lenGameSeq) && (gameResult == WON) ){

          blinkLights(gameSeq, currentLoop, lightDelay);  // blinks lights up to the current loop

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
                // if the correct button was pushed do nothing, continue checking buttons
            }
            else {
              // catches both wrong button press and no button pressed & timeout
              gameResult = LOST;
              break;
            }
          }

          currentLoop++;
          lightDelay = lightDelay - 25;
        }

        if (gameResult == WON) gameWonSeq();
        else gameLostSeq();

        gameOn = 0;
      }
      delay(100);
      break;
    }
  }


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

void generateSeq(int lenSeq) {

  int i = 0;
  for (i = 0; i < lenSeq; i++){
    gameSeq[i] = random()%3 + 1;
  }

  // gameSeq[0] = red;
  // gameSeq[1] = yel;
  // gameSeq[2] = grn;
  // gameSeq[3] = yel;
  // gameSeq[4] = red;
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
