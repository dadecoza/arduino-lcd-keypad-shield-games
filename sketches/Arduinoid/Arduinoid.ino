//Written by Mason 2012
 
#include <LiquidCrystal.h>
 
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
 
int bpm = 30;
const int whole = (60000/bpm);
const int half = 30000/bpm;
const int quarter = 15000/bpm;
const int eight = 7500 / bpm;
const int sixteenth = 3750 / bpm;
const int thirty2 = 1875 / bpm;
int musicpin = 3;
 
float vballx = 1;
float vbally = 0.2;
float xball = 1;
float yball = 1;
int xmax = 80;
int delaytime = 60;
int score;
 
//define graphics
byte dot[8] = {
  0x0,
  0x0,
  0x0,
  0x0,
  0x0,
  0x0,
  0x0,
  0x0
};
byte paddle[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11000,
  B11000,
  B11000
};
byte wallFR [8] = {
  0x0,
  0x0,
  0x0,
  0x0,
  0x0,
  0x0,
  0x0,
  0x0
};
byte wallFL [8] = {
  0x0,
  0x0,
  0x0,
  0x0,
  0x0,
  0x0,
  0x0,
  0x0
};
byte wallBR [8] = {
  0x0,
  0x0,
  0x0,
  0x0,
  0x0,
  0x0,
  0x0,
  0x0
};
byte wallBL [8] = {
  0x0,
  0x0,
  0x0,
  0x0,
  0x0,
  0x0,
  0x0,
  0x0
};
//Define the wall tiles
boolean wallarray [16] = {
  1,1,1,1,
  1,1,1,1,
  1,1,1,1,
  1,1,1,1};
 
int lcd_key     = 0;
int paddle_pos = 1;
 
int read_LCD_buttons()
{
  adc_key_in = analogRead(0);      // read the value from the sensor
  // my buttons when read are centered at these values: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 195)  return btnUP;
  if (adc_key_in < 380)  return btnDOWN;
  if (adc_key_in < 555)  return btnLEFT;
  if (adc_key_in < 790)  return btnSELECT;
  return btnNONE;  // when all others fail, return this...
}
void getPaddle() {
 
  lcd_key = read_LCD_buttons();  // read the buttons
  switch (lcd_key)               // depending on which button was pushed, we perform an action
  {
  case btnUP:
    {
      if (paddle_pos > 1) paddle_pos -= 1;
      break;
    }
  case btnDOWN:
    {
      if (paddle_pos < 14) paddle_pos += 1;
      break;
    }
  }
}
 
void drawwalls()
{
  for (int i=0; i < 8; i+=4)
  {
    for (int j = 0; j<4; j++)
    {
      wallFL[j+i]=wallarray[i/2]*16+wallarray[i/2]*8+wallarray[i/2+1]*2+wallarray[i/2+1]*1;
      wallFR[j+i]=wallarray[i/2+4]*16+wallarray[i/2+4]*8+wallarray[i/2+5]*2+wallarray[i/2+5]*1;
      wallBL[j+i]=wallarray[i/2+8]*16+wallarray[i/2+8]*8+wallarray[i/2+9]*2+wallarray[i/2+9]*1;
      wallBR[j+i]=wallarray[i/2+12]*16+wallarray[i/2+12]*8+wallarray[i/2+13]*2+wallarray[i/2+13]*1;
    }
  }
  lcd.createChar(2,wallFL);
  lcd.createChar(3,wallFR);
  lcd.createChar(4,wallBL);
  lcd.createChar(5,wallBR);
  lcd.setCursor(14,0);
  lcd.write((byte)2);
  lcd.write((byte)4);
  lcd.setCursor(14,1);
  lcd.write((byte)3);
  lcd.write((byte)5);
}
//place dot on screen (80x16)
void placedot(int x, int y) {
  createdot(x%5,y%8);
  lcd.setCursor(x/5,y/8);
  lcd.write((byte)0);
}
void placepaddle(int y) {
  for (int i=0;i<8;i++){
    paddle[i]=0x0;
  }
  if (y%8>0) paddle[y%8-1] = 0x10;
  paddle[y%8] = 0x10;
  if (y%8<7)paddle[y%8+1] = 0x10;
  lcd.createChar(1,paddle);
  lcd.setCursor(0,y/8);
  lcd.write((byte)1);
}
 
//draw a dot in the 5x8 space of the character at location x,y
void createdot(int x, int y)  {
  for (int i=0;i<8;i++){
    dot[i]=0x0;
  }
  if (y > 0) dot[y-1] = (B11000 >> x);
  dot[y] = (B11000 >> x);
  lcd.createChar(0,dot);
}
int blockcounter = 0;
void handlecollisions()
{
  xball = xball + vballx;
  yball = yball + vbally;
  //Handle collisions in y
  if ((yball > 15) || (yball < 1)) {
    vbally = -vbally;
    tone(musicpin,880,eight);
  }
  //Handle Collisions in x
 
  if (xball > 69) //is the ball in the correct area
  {
    for (int i=0;i < 16; i++)
    {
      if (xball>(70+2*(i%2)+5*(i/8))) {//x condition met
        if ((yball>(2*(i%8)))&&(yball<(2*(i%8)+4))){ // y condition met
          if (wallarray[i] == 1){ //wall exists
           tone(musicpin,1174,eight);
           delay(eight);
            wallarray[i]=0;
            vballx = -vballx;
            xball = 70;
          }
        }
      }
    }
  }
  // Check to see if at edge of screen.
  if (xball > xmax)   {
    vballx = -vballx;
    tone(musicpin,880,eight);
  }
 
  //check for ball and paddle
  if (xball < 1)   {
    if (paddle_pos > int(yball)-2 && paddle_pos < int(yball)+2){
      tone(musicpin,1397,sixteenth);
      delay(sixteenth);
      tone(musicpin,1567,eight);
      vballx = -vballx;
      vbally *= random(1,4) ;
      vbally /= 2;
      Serial.println(vbally);
      score += 1;
      //xmax -= 2;
      delaytime -= 2;
      vballx += 0.1;
      int left = 0;
      for (int i=0;i<16;i++)
      { left += wallarray[i];
      }
      if (left < 1)       {
        lcd.clear();
        lcd.print("You Win! ");
        arkanoidsong();
        lcd.print(score);
        delay(15000);
        xmax = 80;
        score = 0;
        delaytime = 60;
        for (int i=0;i< 16;i++)
        {wallarray[i]=1;}
 
      }
    }
    else {
      tone(musicpin,349,sixteenth);
      delay(sixteenth);
      tone(musicpin,329,eight);
      vballx = -vballx;
      vbally *= random(1,4) ;
      vbally /= 2;
      score -=1;
    }
  }
}
 
void arkanoidsong(){
    tone(musicpin, 1568, eight);//g6
  delay(eight);
  noTone(musicpin);
  delay(sixteenth);
  tone(musicpin, 1568, sixteenth);//g6
  delay(sixteenth);
  tone(musicpin, 1864, half);//a#6
  delay(half);
  noTone(musicpin);
  delay(thirty2);
  tone(musicpin, 1760, eight);//a6
  delay(eight);
  tone(musicpin, 1568, eight);//g6
  delay(eight);
  tone(musicpin, 1396, eight);//f6
  delay(eight);
  tone(musicpin, 1760, eight);//a6
  delay(eight);
  tone(musicpin, 1568, half);
  delay(half);
}
 
void setup() {
  lcd.begin(16, 2);
  delay(100);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Arduinoid");
  lcd.setCursor(0,1);
  lcd.print("Get the Bricks");
 
  delay(500);
  arkanoidsong();
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("Press to Start");
  while(analogRead(0)>1000)
  {
    delay(10);
  }
  Serial.begin(9600);
}
 
void loop() {
  lcd.clear();
  getPaddle();
 
  drawwalls();
  placepaddle(paddle_pos);
    handlecollisions();
  placedot(xball,yball);
 
  delay(delaytime);
 
}