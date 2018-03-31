#include <LiquidCrystal.h>
#include <SPI.h>
#define SS_PIN 10
#define DP_HEIGHT 16
#define DP_WIDTH 10

//LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
void Dp_DrawLine(int x, int y, int length, bool hori, bool isSet);

struct ZeichenFlaeche {
  byte grid[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
};

ZeichenFlaeche zeichen[2][2]; 

void Dp_Init()
{
  lcd.createChar(0, zeichen[0][0].grid);
  lcd.createChar(1, zeichen[0][1].grid);
  lcd.createChar(2, zeichen[1][0].grid);
  lcd.createChar(3, zeichen[1][1].grid);
  Dp_DrawLine(0,0,10,true,true); // Linie Oben H
  Dp_DrawLine(0,15,10,true,true); // Linie Unten H
  Dp_DrawLine(0,0,16,false,true); // Linie Links V
  Dp_DrawLine(9,0,16,false,true); // Linie Rechts V
}

void Dp_Draw()
{
  lcd.createChar(0, zeichen[0][0].grid);
  lcd.createChar(1, zeichen[0][1].grid);
  lcd.createChar(2, zeichen[1][0].grid);
  lcd.createChar(3, zeichen[1][1].grid);
  lcd.setCursor(0, 0);
  lcd.write(byte(0));
  
  lcd.setCursor(0, 1);
  lcd.write(byte(1));
  
  lcd.setCursor(1, 0);
  lcd.write(byte(2));
  
  lcd.setCursor(1, 1);
  lcd.write(byte(3));
}

void Dp_SetPixel(int x, int y, bool isOn)
{
  if(isOn)
    bitSet  (zeichen[x/5][y/8].grid[y%8],4-x%5);
  else 
    bitClear(zeichen[x/5][y/8].grid[y%8],4-x%5);
}

bool Dp_GetPixel(int x, int y)
{
  return bitRead(zeichen[x/5][y/8].grid[y%8],4-x%5)==1?true:false;
}

void Dp_DrawLine(int x, int y, int length, bool hori, bool isSet)
{
  for(int offset = 0; offset < length; offset++)
  {
    if(hori)
      Dp_SetPixel(x + offset, y, isSet);
    else
      Dp_SetPixel(x, y + offset, isSet);
  }
}

