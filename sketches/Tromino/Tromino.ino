/*
 * Tromino - a Tetris like game for the LCD Keypad Shield.
 * Written by @dadecoza 2016
 * Pretty much the same as https://github.com/dzimboum/triscalino but with less OOP.
 * Tetris music sketch by electric mango https://github.com/electricmango/Arduino-Music-Project/blob/master/A_Theme___Tetris_with_Bass/A_Theme___Tetris_with_Bass.ino
 */
#include <LiquidCrystal.h>
#include <EEPROM.h>
#include "pitches.h"

#define btnRight     0
#define btnUp        1
#define btnDown      2
#define btnLeft      3
#define btnSelect    4
#define btnNone      5
#define maxShapes    3
#define maxRotations 2
#define melodyPin    3

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

boolean matrix[16][4];

int currentX, currentY, currentRot, currentShape, prevKey, gameSpeed, score, highScore, melodyNote;
unsigned long timeToMove;
unsigned long melodyDelay;
boolean melodyOn;

//notes in the melody:
static const int PROGMEM melody[] = {
  NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, 
  NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
  NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2, 
  NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5, 
  NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5, 
  NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0, 
  NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, 
  NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
  NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2, 
  NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5, 
  NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5, 
  NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0,
  NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
  NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_A3, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_GS3, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3, 
  NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
  NOTE_C4, NOTE_E3, NOTE_E4, NOTE_E3, NOTE_A4, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_GS4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3,
  NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, 
  NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
  NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2, 
  NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5, 
  NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5, 
  NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0, 
  NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, 
  NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
  NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2, 
  NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5, 
  NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5, 
  NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0,
  NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
  NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_A3, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_GS3, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3, 
  NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
  NOTE_C4, NOTE_E3, NOTE_E4, NOTE_E3, NOTE_A4, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_GS4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3,
};

//note durations: 4 = quarter note, 8 = eighth note, etc
static const int PROGMEM noteDurations[] = {
  8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,4,8,8,16,16,8,8,8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,4,
  8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,4,8,8,16,16,8,8,8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,4,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,4,8,8,16,16,8,8,8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,4,
  8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,4,8,8,16,16,8,8,8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,4,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
};

byte cfull[] = {B11111, B11111, B11111, B00000, B11111, B11111, B11111, B11111};
byte ctop[] = {B11111, B11111, B11111, B11111, B00000, B00000, B00000, B00000};
byte cbottom[] = {B00000, B00000, B00000, B00000, B11111, B11111, B11111, B11111,};
byte shapes[3][2][3] = {
  {{B111, B000, B000}, {B100, B100, B100}}, //I
  {{B010, B110, B000}, {B110, B010, B000}}, //J
  {{B100, B110, B000}, {B110, B100, B000}} //L
};

void drawScreen() {
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 0);
    if (matrix[i][0] && matrix[i][1]) lcd.write(byte(2));
    else if (matrix[i][0]) lcd.write(byte(0));
    else if (matrix[i][1]) lcd.write(byte(1));
    else lcd.print(' ');
    lcd.setCursor(i, 1);
    if (matrix[i][2] && matrix[i][3]) lcd.write(byte(2));
    else if (matrix[i][2]) lcd.write(byte(0));
    else if (matrix[i][3]) lcd.write(byte(1));
    else lcd.print(' ');
  }
}

void newShape() {
  currentX = 1;
  currentY = 0;
  currentRot = 0;
  currentShape = rand() % maxShapes;
}

void putShape(boolean visible, int shape, int rot, int x, int y) {
  for (int i = 0; i < 3; i++) {
    if ((shapes[shape][rot][i] >> 2) & 1) matrix[y + i][x] = visible;
    if ((shapes[shape][rot][i] >> 1) & 1) matrix[y + i][x + 1] = visible;
    if (shapes[shape][rot][i] & 1) matrix[y + i][x + 2] = visible;
  }
}

void drawShape() {
  putShape(true, currentShape, currentRot, currentX, currentY);
}

void clearShape() {
  putShape(false, currentShape, currentRot, currentX, currentY);
}

void clearDisplay() {
  for (int i = 0; i < 16; i++) {
    for (int n = 0; n < 4; n++) {
      matrix[i][n] = 0;
    }
  }
}

boolean onScreen(int x, int y) {
  if (x < 0) return false;
  if (x > 3) return false;
  if (y < 0) return false;
  if (y > 15) return false;
  return true;
}

boolean isValid(int rot, int x, int y) {
  boolean okay = true;
  for (int i = 0; ((i < 3) && (okay)); i++) {
    if ((shapes[currentShape][rot][i] >> 2) & 1) {
      if (!onScreen(x, y + i) || matrix[y + i][x]) okay = false;
    }

    if ((shapes[currentShape][rot][i] >> 1) & 1) {
      if (!onScreen(x + 1, y + i) || matrix[y + i][x + 1]) okay = false;
    }

    if (shapes[currentShape][rot][i] & 1) {
      if (!onScreen(x + 2, y + i) || matrix[y + i][x + 2]) okay = false;
    }
  }
  return okay;
}

boolean isValid(int x, int y) {
  return isValid(currentRot, x, y);
}

boolean moveDown() {
  clearShape();
  if (isValid(currentX, currentY + 1)) {
    currentY++;
    drawShape();
    drawScreen();
    return true;
  }
  drawShape();
  return false;
}

boolean moveLeft() {
  clearShape();
  if (isValid(currentX - 1, currentY)) {
    currentX--;
    drawShape();
    drawScreen();
    return true;
  }
  drawShape();
  return false;
}

boolean moveRight() {
  clearShape();
  if (isValid(currentX + 1, currentY)) {
    currentX++;
    drawShape();
    drawScreen();
    return true;
  }
  drawShape();
  return false;
}

boolean rotate() {
  int r;
  clearShape();
  if (currentRot == maxRotations - 1) r = 0;
  else r = currentRot + 1;
  if (isValid(r, currentX, currentY)) {
    currentRot = r;
    drawShape();
    drawScreen();
    return true;
  }
  drawShape();
  return false;
}

void flashLine(int y) {
  for (int t = 0; t < 3; t++) {
    for (int i = 0; i < 4; i++) matrix[y][i] = 1;
    drawScreen();
    tone(melodyPin,NOTE_E5,50);
    //delay(50);
    for (int i = 0; i < 4; i++) matrix[y][i] = 0;
    drawScreen();
    //delay(50);
    tone(melodyPin,NOTE_C5,50);
  }
}

int clearLines() {
  int lineCount = 0;
  boolean tmpmatrix[16][4];
  for (int i = 0; i < 16; i++) {
    for (int n = 0; n < 4; n++) {
      tmpmatrix[i][n] = 0;
    }
  }
  int tmpY = 15;
  boolean found = false;
  for (int y = 15; y >= 0; y--) {
    if (matrix[y][0] && matrix[y][1] && matrix[y][2] && matrix[y][3]) {
      flashLine(y);
      lineCount++;
    } else {
      for (int x = 0; x < 4; x++) tmpmatrix[tmpY][x] = matrix[y][x];
      tmpY--;
    }
  }
  if (lineCount > 0) {
    for (int i = 0; i < 16; i++) {
      for (int n = 0; n < 4; n++) {
        matrix[i][n] = tmpmatrix[i][n];
      }
    }
  }
  return lineCount;
}

int getKey() {
  int b = analogRead(A0);
  if (b > 1000) return btnNone;
  delay(8);
  if (b < 66) return btnRight;
  if (b < 221) return btnUp;
  if (b < 395) return btnDown;
  if (b < 602) return btnLeft;
  if (b < 902) return btnSelect;
}

int getHighScore() {
  //long two = EEPROM.read(0);
  //long one = EEPROM.read(1);
  //return ((two << 0) & 0xFF) + ((one << 8) & 0xFFFF);
  return 0;
}

void saveHighScore() {
  EEPROM.write(0, (score & 0xFF));
  EEPROM.write(1, ((score >> 8) & 0xFF));
  highScore = score;
}

int getNote(int k) {
  return pgm_read_word_near(melody + k);
}

int getNoteDuration(int k) {
  return pgm_read_word_near(noteDurations + k);
}

void playNote() {
    if (!melodyOn) return;
    if (millis() > melodyDelay) {
      int noteDuration = 1000/getNoteDuration(melodyNote);
      tone(melodyPin, getNote(melodyNote),noteDuration);
      if (melodyNote < 385) melodyNote++;
      else melodyNote = 0;
      int pauseBetweenNotes = noteDuration * 1.30;
      melodyDelay = millis()+pauseBetweenNotes;
    }
}

void initialize() {
  newShape();
  clearDisplay();
  gameSpeed = 600;
  score = 0;
  timeToMove = millis() + gameSpeed;
  melodyDelay = 0;
  highScore = getHighScore();
  melodyNote = 0;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(melodyPin, OUTPUT);
  melodyOn = true;
  lcd.begin(16, 2);
  lcd.createChar(0, ctop);
  lcd.createChar(1, cbottom);
  lcd.createChar(2, cfull);
  Serial.begin(9600);
  randomSeed(A1);
  initialize();
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Tromino");
  lcd.setCursor(2, 1);
  lcd.print("by @dadecoza");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Highscore:");
  lcd.setCursor(0, 1);
  lcd.print(highScore);
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  newShape();
  drawShape();
  drawScreen();
  while (moveDown()) {
    while (millis() < timeToMove) {
      playNote();
      int k = getKey();
      if (k != prevKey) {
        switch (k) {
          case btnUp:
            moveLeft();
            break;
          case btnDown:
            moveRight();
            break;
          case btnLeft:
            rotate();
            break;
          case btnRight:
            while(moveDown()){playNote();}
            break;
          case btnSelect:
            melodyOn = !melodyOn;
            break;
        }
        prevKey = k;
      }
    }
    timeToMove = millis() + gameSpeed;
  }
  int cleared = clearLines();
  gameSpeed = gameSpeed - (cleared * 20);
  score = score + (10 * (cleared + 1));
  if (currentY == 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Game Over");
    lcd.setCursor(0, 1);
    lcd.print("Score:");
    lcd.print(score);
    if (score > highScore) saveHighScore();
    while (1) {
      delay(100);
    }
  }
}

