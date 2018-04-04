/*                                                                
 *
 *      ____  ___   ________  ______    _   __   ____  ________  __________  __
 *     / __ \/   | / ____/  |/  /   |  / | / /  / __ \/  _/ __ \/ ____/ __ \/ /
 *    / /_/ / /| |/ /   / /|_/ / /| | /  |/ /  / /_/ // // / / / __/ / /_/ / / 
 *   / ____/ ___ / /___/ /  / / ___ |/ /|  /  / _, _// // /_/ / /___/ _, _/_/  
 *  /_/   /_/  |_\____/_/  /_/_/  |_/_/ |_/  /_/ |_/___/_____/_____/_/ |_(_)   
 *
 * Written by Micky Griffiths for the 16x2 LCD and RPi. -- 16 May 2013
 * Ported to Arduino for the Arduino LCD Keypad Shield by Johannes le Roux (@dadecoza) -- 4 Apr 2018
 * 
 * 
*/


#include <LiquidCrystal.h>
#include <EEPROM.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


static const int SPRITE_PACMAN_OPEN = 0;
static const int SPRITE_PACMAN_CLOSED = 1;
static const int SPRITE_GHOST = 2;
static const int SPRITE_HEART = 3;
static const int SPRITE_SMILEY = 4;
static const int TYPE_NONE = 0;
static const int TYPE_HEART = 1;
static const int TYPE_GHOST = 2;
static const int MAX_SPRITES = 10;
static const int STATE_INTRO = 0;
static const int STATE_PLAY = 1;
static const int STATE_GAMEOVER = 2;
static const int HIGHSCORE_ADDRESS = 0;
static const int TOP = 0;
static const int BOTTOM = 1;

struct sprite {
  int x;
  int y;
  int type;
};

struct sprite sprites[MAX_SPRITES];

long timeToMove, timeToAnimate, timeToDebounce;
int state, score, highScore, gameSpeed, pacmanX, pacmanY, ghostOdds;
boolean mouthState, smile;

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
    EEPROM.write(HIGHSCORE_ADDRESS, 0);
  }

  for (int i = 0; i < (sizeof(spriteBitmaps) / 8); i++) {
    lcd.createChar(i, spriteBitmaps[i]);
  }

  delay(500);
  lcd.begin(16, 2);
  randomSeed(analogRead(1));
  state = STATE_INTRO;
  initVars();
}


void loop() {
  switch (state) {
    case STATE_INTRO: intro(); break;
    case STATE_PLAY: play(); break;
    case STATE_GAMEOVER: gameover(); break;
  }
}


void initVars() {
  for (int i = 0; i < MAX_SPRITES; i++) {
    sprites[i] = {0, 0, TYPE_NONE};
  }
  highScore = EEPROM.read(HIGHSCORE_ADDRESS);
  timeToMove = 0;
  timeToAnimate = 0;
  timeToDebounce = 0;
  score = 0;
  gameSpeed = 600;
  ghostOdds = 6;
  pacmanX = 1;
  pacmanY = 0;
  mouthState = false;
  smile = false;
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
  lcd.clear(); lcd.setCursor(3, 0); lcd.print("COLLECT: "); lcd.write(byte(SPRITE_HEART)); lcd.setCursor(4, 1); lcd.print("AVOID: "); lcd.write(byte(SPRITE_GHOST));
  waitButton(); lcd.clear(); lcd.setCursor(1, 0); lcd.print("ARE YOU READY?"); lcd.setCursor(0, 1); lcd.print("Press the button");
  waitButton();
  animation(1);
  state = STATE_PLAY;
}


void play() {
  drawScreen();
  long now = millis();
  if (checkButton()) {
    hidePacman();
    pacmanY = !pacmanY;
  }

  if (now > timeToMove) {
    moveLeft();
    if (!random(0, ghostOdds)) {
      spawn(TYPE_GHOST);
    }
    if (!random(0, 3)) {
      spawn(TYPE_HEART);
    }
    timeToMove = now + gameSpeed;
  }

  int c = collision();
  if (c == TYPE_HEART) {
    eatHeart();
    increaseScore();
  } else if (c == TYPE_GHOST) {
    state = STATE_GAMEOVER;
  }
}


void gameover() {
  animation(0);
  lcd.setCursor(3, 0); lcd.print("GAME OVER"); lcd.setCursor(0, 1); lcd.print("How did you do?");
  waitButton();
  lcd.clear(); lcd.setCursor(2, 0); lcd.print("YOUR SCORE:"); lcd.setCursor(7, 1); lcd.print(score);
  waitButton();
  if (score > highScore) {
    lcd.clear(); lcd.setCursor(1, 0); lcd.print("NEW HIGHSCORE!");
    EEPROM.write(HIGHSCORE_ADDRESS, score);
    highScore = score;
    waitButton();
  }
  lcd.clear(); lcd.setCursor(3, 0); lcd.print("TRY AGAIN"); lcd.setCursor(2, 1); lcd.print("Highscore: "); lcd.print(highScore);
  waitButton();
  initVars();
  state = STATE_PLAY;
  lcd.clear();
}


void drawScreen() {
  for (int i = 0; i < MAX_SPRITES; i++) {
    drawSprite(i);
  }
  drawPacman();
}


void eatHeart() {
  for (int i = 0; i < MAX_SPRITES; i++) {
    if (sprites[i].x == pacmanX && sprites[i].y == pacmanY && sprites[i].type == TYPE_HEART) {
      smile = true;
      deleteSprite(i);
      return;
    }
  }
}


void increaseScore() {
  score++;
  if (!(score % 10)) {
    gameSpeed = gameSpeed - 30;
    if (ghostOdds > 1) {
      ghostOdds--;
    }
  }
}


void spawn(int type) {
  int x = 15;
  int y = random(0, 2);
  for (int i = 0; i < MAX_SPRITES; i++) {
    int spriteType = sprites[i].type;
    if (spriteType == TYPE_NONE) {
      if (((type == TYPE_GHOST) && okayToSpawnGhost(y)) || ((type == TYPE_HEART) && okayToSpawnHeart(y))) {
        createSprite(i, x, y, type);
      }
      return;
    }
  }
}


int at(int x, int y) {
  for (int i = 0; i < MAX_SPRITES; i++) {
    if (sprites[i].x == x && sprites[i].y == y && sprites[i].type != TYPE_NONE) {
      return sprites[i].type;
    }
  }
  return TYPE_NONE;
}


int okayToSpawnGhost(int pos) {
  if (at(15, pos) != TYPE_NONE) {
    return 0;
  } else if (at(15, !pos) == TYPE_GHOST) {
    return 0;
  } else if ((pos == TOP) && (at(14, BOTTOM) == TYPE_GHOST)) {
    return 0;
  } else if ((pos == BOTTOM) && (at(14, TOP) == TYPE_GHOST)) {
    return 0;
  }
  return 1;
}


int okayToSpawnHeart(int pos) {
  if (at(15, pos) != TYPE_NONE) {
    return 0;
  }
  return 1;
}


void moveLeft() {
  for (int i = 0; i < MAX_SPRITES; i++) {
    if (sprites[i].type != TYPE_NONE) {
      int x = sprites[i].x - 1;
      int y = sprites[i].y;
      moveSprite(i, x, y);
    }
  }
}


void createSprite(int s, int x, int y, int type) {
  sprites[s].x = x;
  sprites[s].y = y;
  sprites[s].type = type;
}


void drawSprite(int s) {
  int spriteType = sprites[s].type;
  if (spriteType == TYPE_NONE) {
    return;
  }
  int x = sprites[s].x;
  int y = sprites[s].y;
  if (!((x == pacmanX) && (y == pacmanY))) {
    lcd.setCursor(x, y);
    switch (spriteType) {
      case TYPE_GHOST: lcd.write(byte(SPRITE_GHOST)); break;
      case TYPE_HEART: lcd.write(byte(SPRITE_HEART)); break;
      default: lcd.write(byte(32)); break;
    }
  }
}


void hideSprite(int s) {
  lcd.setCursor(sprites[s].x, sprites[s].y);
  lcd.write(byte(32));
}


void drawPacman() {
  if ((millis() > timeToAnimate) || (smile)) {
    int wait = 350;
    lcd.setCursor(pacmanX, pacmanY);
    if (smile) {
      lcd.write(byte(SPRITE_SMILEY));
      wait = 600;
      smile = false;
    } else if (mouthState) {
      lcd.write(byte(SPRITE_PACMAN_OPEN));
    } else {
      lcd.write(byte(SPRITE_PACMAN_CLOSED));
    }
    mouthState = !mouthState;
    timeToAnimate = millis() + wait;
  }
}


void hidePacman() {
  lcd.setCursor(pacmanX, pacmanY);
  lcd.write(byte(32));
}


void deleteSprite(int s) {
  hideSprite(s);
  sprites[s].x = 0;
  sprites[s].y = 0;
  sprites[s].type = TYPE_NONE;
}


void moveSprite(int s, int x, int y) {
  if ((x < 0) || (x > 15)) {
    deleteSprite(s);
  } else {
    hideSprite(s);
    sprites[s].x = x;
    sprites[s].y = y;
  }
}


int collision() {
  return at(pacmanX, pacmanY);
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
  long now = millis();
  if (now > timeToDebounce) {
    int b = analogRead(A0);
    if (b < 850) {
      timeToDebounce = now + 300;
      return 1;
    }
  }
  return 0;
}


void waitButton() {
  while (!checkButton()) delay(50);
}


