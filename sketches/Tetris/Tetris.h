#include "Stone.h"

#define BUTTON_LEFT 13
#define BUTTON_RIGHT 12
#define BUTTON_ROT 11
#define BUTTON_DOWN 10

#define btnRight  0
#define btnUp     1
#define btnDown   2
#define btnLeft   3
#define btnSelect 4
#define btnNone   5


bool BUTTON_LEFT_LAST = false;
bool BUTTON_RIGHT_LAST = false;
bool BUTTON_ROT_LAST = false;
bool BUTTON_DOWN_LAST = false;
long points = 0;

Stone currentStone;

void Te_Init()
{
  currentStone = St_InitStone();
  /*pinMode(BUTTON_LEFT, INPUT);
  pinMode(BUTTON_RIGHT, INPUT);
  pinMode(BUTTON_ROT, INPUT);*/
}

int Te_GetKey() {
  int b = analogRead(A0);
  if (b > 1000) return btnNone;
  if (b < 50) return btnRight;
  if (b < 180) return btnUp;
  if (b < 330) return btnDown;
  if (b < 520) return btnLeft;
  if (b < 700) return btnSelect;    
}

void Te_Draw()
{
  St_Print(currentStone, true);
  Dp_Draw();
  St_Print(currentStone, false);
}

void Te_AddPoints(long p)
{
  points += p;
  lcd.setCursor(10, 0);
  lcd.print(points);
}

void Te_DeleteRow(int row)
{
  bool sw = true;
  for (int i = 0; i < 15; i++)
  {
    Dp_DrawLine(1, row, 8, true, sw);
    Dp_DrawLine(0,0,10,true,!sw); // Linie Oben H
    Dp_DrawLine(0,15,10,true,!sw); // Linie Unten H
    Dp_DrawLine(0,0,16,false,!sw); // Linie Links V
    Dp_DrawLine(9,0,16,false,!sw); // Linie Rechts V
    Dp_Draw();
    delay(90);
    sw = sw ? false : true;
  }
  Dp_DrawLine(1, row, 8, true, false);
  Dp_DrawLine(0,0,10,true,true); // Linie Oben H
  Dp_DrawLine(0,15,10,true,true); // Linie Unten H
  Dp_DrawLine(0,0,16,false,true); // Linie Links V
  Dp_DrawLine(9,0,16,false,true); // Linie Rechts V
  Dp_Draw();
  for (int zeile = row; zeile > 2; zeile--)
  {
    for (int x = 1; x < TE_WIDTH + 1; x++)
    {
      Dp_SetPixel(x, zeile, Dp_GetPixel(x, zeile - 1));
    }
  }
}

void Te_CheckRows()
{
  byte rowWins = 0;
  for (int zeile = TE_HEIGHT; zeile > 0; zeile--)
  {
    bool zeileVoll = true;
    for (int x = 1; x < TE_WIDTH; x++)
    {
      if (!Dp_GetPixel(x, zeile)) // Ist noch ein Stück frei in der aktuellen Zeile?
      {
        zeileVoll = false;
        break;
      }
    }
    if (zeileVoll) // Ist die aktuelle Zeile voll?
    {
      rowWins++;
      Te_DeleteRow(zeile);
      zeile++;
    }
  }
  if (rowWins > 0)
    Te_AddPoints(random(9, 15) * (10 + pow(3,rowWins) * 10));
}

void Te_Reload()
{
  for (int row = 1; row < TE_HEIGHT + 1; row++)
  {
    Dp_DrawLine(1, row, 8, true, true);
    Dp_Draw();
    delay(60);
  }
  delay(400);
  for (int row = TE_HEIGHT; row >= 1 ; row--)
  {
    Dp_DrawLine(1, row, 8, true, false);
    Dp_Draw();
    delay(60);
  }
  currentStone = St_InitStone();
  points = 0;
  lcd.setCursor(10, 0);
  lcd.print("0     ");
  lcd.setCursor(3, 1);
  lcd.print("             ");
}

void Te_Update(long frameCount)
{
  if (frameCount % 40  == 0)
  {
    currentStone.y++;
    if (St_HitTest(currentStone)) // Stein ist unten Angekommen.
    {
      currentStone.y--;
      for(int i = 0; i < 5; i++)
      {
        St_Print(currentStone, true);
        Dp_Draw();
        delay(60);
        St_Print(currentStone, false);
        Dp_Draw();
        delay(60);
      }
      St_Print(currentStone, true);
      currentStone = St_InitStone();
      Dp_Draw();
      if (St_HitTest(currentStone))
      {
        lcd.setCursor(3, 1);
        lcd.write("Game Over!");
        delay(1000);
        //while (!digitalRead(BUTTON_LEFT) || !digitalRead(BUTTON_RIGHT));
        while (!(Te_GetKey() == btnLeft) || !(Te_GetKey() == btnRight));
        Te_Reload();
      }
      Te_AddPoints(random(1, 4) * 10);
      Te_CheckRows();
      return;
    }
  }

  if(frameCount % 10) // Nach Unten Schieben frei geben (Damit man den Knopf gedrückt lassen kann)
  {
    BUTTON_DOWN_LAST=false;
  }


  //if (digitalRead(BUTTON_LEFT))
  if (Te_GetKey() == btnLeft)
  {
    if (!BUTTON_LEFT_LAST)
    {
      BUTTON_LEFT_LAST = true;

      // Versuche Stein zu verschieben
      currentStone.x--;
      if (St_HitTest(currentStone))
        currentStone.x++;
    }
  }
  else BUTTON_LEFT_LAST = false;

  //if (digitalRead(BUTTON_RIGHT))
  if (Te_GetKey() == btnRight)
  {
    if (!BUTTON_RIGHT_LAST)
    {
      BUTTON_RIGHT_LAST = true;

      // Versuche Stein zu verschieben
      currentStone.x++;
      if (St_HitTest(currentStone))
        currentStone.x--;
    }
  }
  else BUTTON_RIGHT_LAST = false;
  
  //if (digitalRead(BUTTON_ROT))
  if (Te_GetKey() == btnUp)
  {
    if (!BUTTON_ROT_LAST)
    {
      BUTTON_ROT_LAST = true;

      // Versuche Stein zu verschieben
      St_Rotate(&currentStone);
      if (St_HitTest(currentStone))
        St_BackRotate(&currentStone);
    }
  }
  else BUTTON_ROT_LAST = false;

  //if (digitalRead(BUTTON_DOWN))
  if (Te_GetKey() == btnDown)
  {
    if (!BUTTON_DOWN_LAST)
    {
      BUTTON_DOWN_LAST = true;

      // Versuche Stein zu verschieben
      currentStone.y++;
      if (St_HitTest(currentStone))
        currentStone.y--;
    }
  }
  else BUTTON_DOWN_LAST = false;
}
