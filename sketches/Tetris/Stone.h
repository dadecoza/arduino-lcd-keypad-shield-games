#include "Display.h"

#define TE_WIDTH (DP_WIDTH - 2)
#define TE_HEIGHT (DP_HEIGHT - 2)

enum Stone_Type {
  TStone = 0,
  LStone = 1,
  IStone = 2,
  SStone = 3,
  ZStone = 5,
  OStone = 4,
};

struct Stone {
  byte field[4];
  char x = TE_WIDTH / 2 - 1;
  char y = 1;
  char rot = 0;
  Stone_Type type;
};

Stone St_InitStone();

bool St_HitTest(Stone st)
{
  for(char x = 0; x < 5; x++) // Zeilen eines Steins
  {
    for(char y = 0; y < 4; y++) // Spalten eines Steins
    {
      if(bitRead(st.field[y],x) == 1) // Ist der aktuelle Stein Pixel gesetzt?
      {
        char xT = st.x  + x; // Absolute x Position
        char yT = st.y + y;  // Absolute y Position
        if(xT < 1 || xT > TE_WIDTH || yT < 1 || yT > TE_HEIGHT) // Aktueller Stein Pixel aus dem Fenster.
        {
          Serial.print("HIT OUTWINDOW xT=");
          Serial.print(xT, DEC);
          Serial.print(" yT=");
          Serial.println(yT, DEC);
          return true;
        }
        if(Dp_GetPixel(xT,yT)) // Aktueller Stein Pixel auf dem Display ist belegt.
        {
          Serial.print("HIT Pixel xT=");
          Serial.print(xT, DEC);
          Serial.print(" yT=");
          Serial.println(yT, DEC);
          return true;
        }
      }
    }
  }
  return false;
}

void St_Print(Stone st, bool printIt)
{
  for(char x = 0; x < 5; x++)
  {
    for(char y = 0; y < 4; y++)
    {
      if(bitRead(st.field[y],x) == 1)
      {
        char xT = st.x  + x;
        char yT = st.y + y;
        if(xT < 1 || xT > TE_WIDTH || yT < 1 || yT > TE_HEIGHT) // Aktueller Stein Pixel aus dem Fenster.
          continue;
        Dp_SetPixel(xT, yT, printIt);
      }
    }
  }
}

void St_SetRot(Stone *st, char rot)
{
  (*st).rot = rot;
  switch((*st).type)
  {
    case TStone: 
    {
      switch(rot)
      {
        case 0: 
        {
          (*st).field[0] = B00000;
          (*st).field[1] = B00100;
          (*st).field[2] = B01110;
          (*st).field[3] = B00000;
        } break;

        case 1: 
        {
          (*st).field[0] = B00000;
          (*st).field[1] = B00100;
          (*st).field[2] = B00110;
          (*st).field[3] = B00100;
        } break;

        case 2: 
        {
          (*st).field[0] = B00000;
          (*st).field[1] = B00000;
          (*st).field[2] = B01110;
          (*st).field[3] = B00100;
        } break;

        case 3: 
        {
          (*st).field[0] = B00000;
          (*st).field[1] = B00100;
          (*st).field[2] = B01100;
          (*st).field[3] = B00100;
        } break;
      }
    } break;
    
    case LStone: 
    {
      switch(rot)
      {
        case 0: 
        {
          (*st).field[0] = B00000;
          (*st).field[1] = B00010;
          (*st).field[2] = B01110;
          (*st).field[3] = B00000;
        } break;

        case 1: 
        {
          (*st).field[0] = B00000;
          (*st).field[1] = B00100;
          (*st).field[2] = B00100;
          (*st).field[3] = B00110;
        } break;

        case 2: 
        {
          (*st).field[0] = B00000;
          (*st).field[1] = B00000;
          (*st).field[2] = B01110;
          (*st).field[3] = B01000;
        } break;

        case 3: 
        {
          (*st).field[0] = B00000;
          (*st).field[1] = B01100;
          (*st).field[2] = B00100;
          (*st).field[3] = B00100;
        } break;
      }
    } break;
    
    case IStone: 
    {
      switch(rot)
      {
        case 0: 
        case 2: 
        {
          (*st).field[0] = B00100;
          (*st).field[1] = B00100;
          (*st).field[2] = B00100;
          (*st).field[3] = B00100;
        } break;
        
        case 1:
        case 3: 
        {
          (*st).field[0] = B00000;
          (*st).field[1] = B00000;
          (*st).field[2] = B01111;
          (*st).field[3] = B00000;
        } break;
      }
    } break;
    
    case SStone: 
    {
      switch(rot)
      {
        case 0: 
        {
          (*st).field[0] = B00000;
          (*st).field[1] = B01100;
          (*st).field[2] = B00110;
          (*st).field[3] = B00000;
        } break;

        case 1: 
        {
          (*st).field[0] = B00000;
          (*st).field[1] = B00100;
          (*st).field[2] = B01100;
          (*st).field[3] = B01000;
        } break;

        case 2: 
        {
          (*st).field[0] = B00000;
          (*st).field[1] = B01100;
          (*st).field[2] = B00110;
          (*st).field[3] = B00000;
        } break;

        case 3: 
        {
          (*st).field[0] = B00000;
          (*st).field[1] = B00010;
          (*st).field[2] = B00110;
          (*st).field[3] = B00100;
        } break;
      }
    } break;

    case OStone: 
    {
      switch(rot)
      {
        case 0: 
        case 1: 
        case 2: 
        case 3: 
        {
          (*st).field[0] = B00000;
          (*st).field[1] = B01100;
          (*st).field[2] = B01100;
          (*st).field[3] = B00000;
        } break;
      }
    } break;
    
    default: break;
  }
}

void St_Rotate(Stone *st)
{
  St_SetRot(st, ((*st).rot+1)%4);
}

void St_BackRotate(Stone *st)
{
  char rot = (*st).rot - 1;
  if(rot == -1)
  rot = 3;
  St_SetRot(st, rot);
}

Stone St_InitStone()
{
  Stone st;
  st.type = (Stone_Type)random(0,5);
  St_SetRot(&st, 0);
  return st;
}

