#include <LiquidCrystal.h>
#include <SPI.h>
#include "Tetris.h"
#define SS_PIN 10


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.print("   Score: 0");
  Serial.begin(9600);
  randomSeed(analogRead(0));
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Loading ...");
  Dp_Init();
  Te_Init();
  Serial.println(random(9, 15) * (10 + pow(3,1) * 10));
  Serial.println(random(9, 15) * (10 + pow(3,2) * 10));
  Serial.println(random(9, 15) * (10 + pow(3,3) * 10));
  Serial.println(random(9, 15) * (10 + pow(3,4) * 10));
}



byte xC = 0;
byte yC = 0;
long frameCount = 0;

void loop() {
  // put your main code here, to run repeatedly:
  frameCount++;
  Te_Draw();
  Te_Update(frameCount);
  delay(1);
}
