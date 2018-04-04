#include <LiquidCrystal.h>
#include <EEPROM.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


static const int spritePacmanOpen = 0;
static const int spritePacmanClosed = 1;
static const int spriteGhost = 2;
static const int spriteHeart = 3;
static const int spriteSmiley = 4;
static const int typeNone = 0;
static const int typeHeart = 1;
static const int typeGhost = 2;
static const int maxSprites = 10;
static const int stateIntro = 0;
static const int statePlay = 1;
static const int stateGameover = 2;
static const int highScoreAddress = 0;

struct sprite {
  int x;
  int y;
  int type;
};

struct sprite sprites[maxSprites];

long timeToMove, timeToAnimate, timeToDebounce;
int state, score, highScore, gameSpeed, pacmanX, pacmanY, ghostOdds;
boolean mouthState;

static const byte spriteBitmaps[8][8] = {
  {0x7, 0xF, 0x1E, 0x1C, 0x1C, 0x1E, 0xF, 0x7},
  {0x0, 0xF, 0x1F, 0x1F, 0x1E, 0x1F, 0xF, 0x0},
  {0x19, 0x1F, 0x15, 0x1F, 0x11, 0x1F, 0x1D, 0xC},
  {0x0, 0x0, 0x0, 0xA, 0x15, 0x11, 0xA, 0x4},
  {0x0, 0xA, 0x0, 0x0, 0x11, 0xE, 0x0, 0x0},
  {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0, 0x0, 0x0},
  {0x0, 0x0, 0x0, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F},
  {0x1F, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}
};

void setup() {
  if (checkButton()) {
    EEPROM.write(highScoreAddress, 0);
  }

  for (int i = 0; i < (sizeof(spriteBitmaps) / 8); i++)
    lcd.createChar(i, spriteBitmaps[i]);
  randomSeed(analogRead(1));
  lcd.begin(16, 2);
  Serial.begin(9600);
  delay(1000);
  state = stateIntro;
  initVars();
}

void dumpSprites() {
  Serial.print("Pacman X:");
  Serial.print(pacmanX);
  Serial.print(" Pacman Y:");
  Serial.println(pacmanY);
  for (int i = 0; i < maxSprites; i++) {
      Serial.print(i);
      Serial.print(" --> x:");
      Serial.print(sprites[i].x);
      Serial.print(" y:");
      Serial.print(sprites[i].y);
      Serial.print(" type:");
      Serial.println(sprites[i].type);
  }
  delay(30000);
}

void loop() {
  switch (state) {
    case stateIntro: intro(); break;
    case statePlay: play(); break;
    case stateGameover: gameover(); break;
  }
}

void initVars() {
  for (int i = 0; i < maxSprites; i++) sprites[i] = {0, 0, typeNone};
  highScore = EEPROM.read(highScoreAddress);
  timeToMove = 0;
  timeToAnimate = 0;
  timeToDebounce = 0;
  score = 0;
  gameSpeed = 600;
  ghostOdds = 5;
  pacmanX = 1;
  pacmanY = 0;
  mouthState = false;
}

void intro() {
  lcd.clear(); lcd.setCursor(3, 0); lcd.print("WELCOME TO"); lcd.setCursor(1, 1); lcd.print("MICKY'S ARCADE");
  waitButton();
  lcd.clear(); lcd.setCursor(2, 0); lcd.print("IT'S SIMPLE!");
  waitButton();
  lcd.clear(); lcd.setCursor(0, 0); lcd.print("Press the button"); lcd.setCursor(1, 1); lcd.print("to move pacman");
  waitButton();
  lcd.clear(); lcd.setCursor(6, 0); lcd.print("BUT!");
  lcd.setCursor(0, 1); lcd.print("Don't forget to");
  waitButton();
  lcd.clear(); lcd.setCursor(3, 0); lcd.print("COLLECT: "); lcd.write(byte(spriteHeart)); lcd.setCursor(4, 1); lcd.print("AVOID: "); lcd.write(byte(spriteGhost));
  waitButton(); lcd.clear(); lcd.setCursor(1, 0); lcd.print("ARE YOU READY?"); lcd.setCursor(0, 1); lcd.print("Press the button");
  waitButton();
  animation(1);
  state = statePlay;
}

void play() {
  long now = millis();

  if (now > timeToDebounce) {
    if (checkButton()) {
      erasePacman();
      pacmanY = !pacmanY;
      timeToDebounce = now + 300;
    }
  }

  if (now > timeToMove) {
    if (!random(0, ghostOdds)) {
      spawn(typeGhost);
    }

    if (!random(0, 3)) {
      spawn(typeHeart);
    }
    moveLeft();
    timeToMove = now + gameSpeed;
  }

  if (now > timeToAnimate) {
    drawPacman();
    int collision = at(pacmanX, pacmanY);
    if ( collision == typeHeart) {
      score++;
      if (!(score % 10)) {
        gameSpeed = gameSpeed - 50;
      } else if (!(score % 5)&&(ghostOdds > 0)) {
        ghostOdds--;
      }
      eatHeart(pacmanX, pacmanY);
    } else if (collision == typeGhost) {
      state = stateGameover;
    }
    timeToAnimate = now + 300;
  }

}


void gameover() {
  dumpSprites();
  animation(0);
  lcd.setCursor(3, 0); lcd.print("GAME OVER"); lcd.setCursor(0, 1); lcd.print("How did you do?");
  waitButton();
  lcd.clear(); lcd.setCursor(2, 0); lcd.print("YOUR SCORE:"); lcd.setCursor(7, 1); lcd.print(score);
  waitButton();
  if (score > highScore) {
    lcd.clear(); lcd.setCursor(1, 0); lcd.print("NEW HIGHSCORE!");
    EEPROM.write(highScoreAddress, score);
    highScore = score;
    waitButton();
  }
  lcd.clear(); lcd.setCursor(3, 0); lcd.print("TRY AGAIN"); lcd.setCursor(2, 1); lcd.print("Highscore: "); lcd.print(highScore);
  waitButton();
  initVars();
  state = statePlay;
  lcd.clear();
}


void spawn(int type) {
  for (int i = 0; i < maxSprites; i++) {
    if (sprites[i].type == typeNone) {
      int x = 16;
      int y;
      if ((type == typeGhost) && (at(x-1, 1) == typeGhost)) {
        y = 1;
      } else if ((type == typeGhost) && (at(x-1, 0) == typeGhost)) {
        y = 0;
      } else if (at(x, 1) != typeNone) {
        y = 0;
      } else if (at(x, 0) != typeNone) {
        y = 1;
      } else {
        y = random(0, 2);
      }
      sprites[i].type = type;
      sprites[i].x = x;
      sprites[i].y = y;
      return;
    }
  }
}


int at(int x, int y) {
  for (int i = 0; i < maxSprites; i++) {
    if (sprites[i].x == x && sprites[i].y == y && sprites[i].type != typeNone) {
      return sprites[i].type;
    }
  }
  return typeNone;
}


int okayToSpawnGhost() {
  for (int i = 14; i < 16; i++) {
    if ((at(i, 0) == typeGhost) || (at(i, 1) == typeGhost)) {
      return 0;
    }
  }
  return 1;
}


void eatHeart(int x, int y) {
  for (int i = 0; i < maxSprites; i++) {
    if (sprites[i].x == x && sprites[i].y == y && sprites[i].type == typeHeart) {
      sprites[i].type = typeNone;
      return;
    }
  }
}


void moveLeft() {
  for (int i = 0; i < maxSprites; i++) {
    if (sprites[i].type != typeNone) {
      lcd.setCursor(sprites[i].x, sprites[i].y);
      lcd.write(byte(32));
      if (sprites[i].x > 0) {
        lcd.setCursor(--sprites[i].x, sprites[i].y);
        switch (sprites[i].type) {
          case typeGhost:
            lcd.write(byte(spriteGhost));
            break;
          case typeHeart:
            lcd.write(byte(spriteHeart));
            break;
        }
      } else {
        sprites[i].type = typeNone;
      }
    }
  }
}


void drawPacman() {
  lcd.setCursor(pacmanX, pacmanY);
  if (at(pacmanX, pacmanY) == typeHeart) lcd.write(byte(spriteSmiley));
  else if (mouthState) lcd.write(byte(spritePacmanOpen));
  else lcd.write(byte(spritePacmanClosed));
  mouthState = !mouthState;
}


void erasePacman() {
  lcd.setCursor(pacmanX, pacmanY);
  lcd.write(byte(32));
}


void animation(int direction) {
  byte animationOpen[6] = {255, 255, 5, 6, 7, 95};
  byte animationClose[6] = {7, 95, 5, 6, 255, 255};
  byte animationChars[6];
  if (direction) {
    memcpy(animationChars, animationOpen, sizeof animationChars);
  } else {
    memcpy(animationChars, animationClose, sizeof animationChars);
  }
  lcd.clear();
  for (int frame = 0; frame < 3; frame++) {
    lcd.setCursor(0, 0);
    for (int i = 0; i < 16; i++) lcd.write(animationChars[frame * 2]);
    lcd.setCursor(0, 1);
    for (int i = 0; i < 16; i++) lcd.write(animationChars[(frame * 2) + 1]);
    delay(300);
    lcd.clear();
  }
}


int checkButton() {
  int b = analogRead(A0);
  if (b < 850) {
    return 1;
  }
  return 0;
}


void waitButton() {
  while (!checkButton()) delay(100);
  delay(300);
}

