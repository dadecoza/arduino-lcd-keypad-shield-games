//**************************************************************//
//  Name    : T6963C Interactive Adventure                      //          
//  Author  : Wayne K Jones - www.warmcat.uk                    //
//  Date    : 29 Nov 2014                                       //
//  Modified: 21 Oct 2015                                       //
//  Version : 1.0.0                                             //
//  Notes   : Using T6963C driven LCD display and 4 buttons for //
//          : a simple text based multi-choice adventure game.  //
//  Licence : Free to use, both in part or it's entirety,       //
//            However I do ask that you give credit/mention.    //
//**************************************************************//
//**************************************************************//
//               Adapted for the 1602 LCD Display               //
//                             by                               //
//                       Johannes le Roux                       //  
//                       dade@dade.co.za                        //
//                         27 Mar 2016                          //
//**************************************************************//

#include "Strings.h"
#include <LiquidCrystal.h>

#define btnRight  0
#define btnUp     1
#define btnDown   2
#define btnLeft   3
#define btnSelect 4
#define btnNone   5
long debounce = 0;

void (*state)() = NULL;
boolean wantCD = 0; //after try to drive
boolean haveCD = 0;
boolean haveFrisbee = 0;
boolean bearHasFrisbee = 0;
boolean haveSteeringWheel = 0;
boolean carSteeringWheel = 0;
boolean haveKeys = 0;
boolean carKeys = 0;
boolean haveWinder = 0;
boolean carWinder = 0;
boolean wantEmptyCan = 0;
boolean haveEmptyCan = 0;
boolean havePetrolCan = 0;
boolean carPetrolCan = 0;
boolean haveMirror = 0;
boolean carMirror = 0;
boolean haveRope = 0;
boolean wantHook = 0; //after tried rope in well
boolean haveHook = 0;
boolean wantMouse = 0; //after met cat
boolean haveMouse = 0;
int carPartsReq = 5; //how many parts left until complete

char buffer[16];
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

byte house[8] = {
  B00000,
  B00000,
  B00100,
  B01110,
  B11111,
  B11011,
  B11011
};

byte tree[8] = {
  B00100,
  B01110,
  B11111,
  B11111,
  B01110,
  B00100,
  B00100
};

byte cross[8] = {
  B00100,
  B11111,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
};

byte car[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B1110,
  B11111,
  B01010,
};


void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.createChar(0, house);
  lcd.createChar(1, tree);
  lcd.createChar(2, cross);
  lcd.createChar(3, car);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   The Lonely");
  lcd.setCursor(0,1);
  lcd.print("    Cottage");
  lcd.setCursor(2,1);
  lcd.write(byte(1));
  lcd.setCursor(12,1);
  lcd.write(byte(0));
  lcd.setCursor(13,1);
  lcd.write(byte(3));
  
  inkeys();
  displayText(areaCredits);
  state = AreaStart;  //Set starting area
}

void loop() {
  state();
  delay(100);
}

// **********************
// ***** START AREA *****
// **********************
void AreaStart() {
  int opt = 0;
  while (opt == 0) {
    opt = displayText(areaStart);
  }
  switch (opt) {
    case 1:
      displayText(areaStartOpt1);
      state = AreaDead;
      break;
    case 2:
      displayText(areaStartOpt2);
      state = AreaLitWood;
      break;
    case 3:
      displayText(areaStartOpt3);
      state = AreaCave;
      break;
    case 4:
      displayText(areaStartOpt4);
      break;
  }
}

// ***************************
// ***** LIT WOODED AREA *****
// ***************************
void AreaLitWood() {
  int opt = 0;
  while (opt == 0) {
    if ( haveMouse == 0) {
      opt = displayText(areaLitWoodText);
    } else {
      opt = displayText(areaLitWoodText_noMouse);
    }
  }
  switch (opt) {
    case 1:
      state = AreaCar;
      break;
    case 2:
      state = AreaCave;
      break;
    case 3:
      if (wantMouse == 0) {
        displayText(areaLitWoodOpt3);
      } else {
        displayText(areaLitWoodOpt3mouse);
        haveMouse = 1;
      }
      break;
  }
}

// *********************
// ***** CAVE AREA *****
// *********************
void AreaCave() {
  int opt = 0;
  while (opt == 0) {
    if ( bearHasFrisbee == 0) {
      opt = displayText(areaCaveText);
    } else {
      opt = displayText(areaCaveText_frisbee);
    }
  }
  switch (opt) {
    case 1:
      if (haveFrisbee == 0) {
        displayText(areaCaveOpt1);
        state = AreaDead;
      } else {
        if (bearHasFrisbee == 1) {
          displayText(areaCaveOpt1_wave);
        } else {
          displayText(areaCaveOpt1_frisbee);
          bearHasFrisbee = 1;
          haveSteeringWheel = 1;
        }
      }
      break;
    case 2:
      displayText(areaCaveOpt2);
      break;
    case 3:
      state = AreaLitWood;
      break;
  }
}

// ********************
// ***** CAR AREA *****
// ********************
void AreaCar() {
  int opt = 0;
  while (opt == 0) {
    opt = displayText(areaCar);
  }
  switch (opt) {
    case 1:
      state = AreaLitWood;
      break;
    case 2:
      state = AreaCottage;
      break;
    case 3:
      if ( carPartsReq > 0 ) {
        state = AreaInsideCar;
      } else {
        state = AreaInsideCompleteCar;
      }
      break;
  }
}

// ***************************
// ***** INSIDE CAR AREA *****
// ***************************
void AreaInsideCar() {
  int opt = 0;
  while (opt == 0) {
    opt = displayText(areaInsideCar);
  }
  switch (opt) {
    case 1:
      state = AreaCarParts;
      break;
    case 2:
      displayText(areaInsideCarOpt2);
      state = AreaDead;
      break;
    case 3:
        state = AreaCar;
      break;
  }
}

// **************************
// ***** CAR PARTS AREA *****
// **************************
void AreaCarParts() {
  int opt = 0;
  if (carPartsReq > 0) {
    if (carSteeringWheel == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("A steering wheel");
      inkeys();
    }
    if (carKeys == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Car keys");
      inkeys();
    }
    if (carWinder == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Driver's side");
      lcd.setCursor(0, 1);
      lcd.print("window winder");
      inkeys();
    }
    if (carPetrolCan == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Petrol");
      inkeys();
    }
    if (carMirror == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Rear-view mirror");
      inkeys();
    }

    while (opt == 0) {
      opt = displayText(areaCarParts);
    }
  } else {
    displayText(areaCarParts_comp);
    //state = AreaInsideCompleteCar;
  }

  switch (opt) {
    case 0:
      state = AreaInsideCompleteCar;
      break;
    case 1:
      if (carPartsReq == 0) {
        state = AreaInsideCompleteCar;
      } else {
        // Checking Pockets
        int pocketItemCount = 0;
        if ((haveSteeringWheel == 1) && (carSteeringWheel == 0)) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("A steering wheel");
          carSteeringWheel = 1;
          carPartsReq--;
          pocketItemCount++;
          inkeys();
        }
        if ((haveKeys == 1) && (carKeys == 0)) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Car keys");
          carKeys = 1;
          carPartsReq--;
          pocketItemCount++;
          inkeys();
        }
        if ((haveWinder == 1) && (carWinder == 0)) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Driver's side");
          lcd.setCursor(0, 1);
          lcd.print("window winder");
          carWinder = 1;
          carPartsReq--;
          pocketItemCount++;
          inkeys();
        }
        if ((havePetrolCan == 1) && (carPetrolCan == 0)) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Petrol");
          carPetrolCan = 1;
          carPartsReq--;
          pocketItemCount++;
          inkeys();
        }
        if ((haveMirror == 1) && (carMirror == 0)) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Rear-view mirror");
          carMirror = 1;
          carPartsReq--;
          pocketItemCount++;
          inkeys();
        }
        if (pocketItemCount > 0) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("You added ");
          lcd.setCursor(0, 1);
          lcd.print(pocketItemCount);
          if (pocketItemCount > 1) {
            lcd.print(" items.");
          } else {
            lcd.print(" item.");
          }
          inkeys();
        } else {
          displayText(areaCarPartsPockets);
        }
      }
      break;
    case 2:
      if (carPartsReq > 0) {
        state = AreaInsideCar;
      } else {
        state = AreaInsideCompleteCar;
      }
      break;
  }
}

// ************************************
// ***** INSIDE COMPLETE CAR AREA *****
// ************************************
void AreaInsideCompleteCar() {
  int opt = 0;
  while (opt == 0) {
    opt = displayText(areaInsideCompleteCar);
  }
  switch (opt) {
    case 1:
      if (haveCD) {
        displayText(areaInsideCompleteCarOpt1_CD);
        state = AreaFinish;
      } else {
        displayText(areaInsideCompleteCarOpt1);
        wantCD = 1;
      }
      break;
    case 2:
      state = AreaCar;
      break;
  }
}

// ************************
// ***** COTTAGE AREA *****
// ************************
void AreaCottage() {
  int opt = 0;
  while (opt == 0) {
    opt = displayText(areaCottage);
  }
  switch (opt) {
    case 1:
      state = AreaCar;
      break;
    case 2:
      displayText(areaCottageOpt2);
      state = AreaInsideCottage;
      break;
    case 3:
      state = AreaOuthouse;
      break;
    case 4:
      state = AreaGarden;
      break;
  }
}

// *******************************
// ***** INSIDE COTTAGE AREA *****
// *******************************
void AreaInsideCottage() {
  int opt = 0;
  if (haveKeys == 0) {
    while (opt == 0) {
      opt = displayText(areaInsideCottage);
    }
    wantMouse = 1;
  } else {
    if (haveCD == 0) {
      while (opt == 0) {
        opt = displayText(areaInsideCottage_keys);
      }
    } else {
      while (opt == 0) {
        opt = displayText(areaInsideCottage_cd);
      }
    }
  }

  switch (opt) {
    case 1:
      if (haveMouse == 0) {
        displayText(areaInsideCottageOpt1);
      } else {
        if (haveKeys == 0) {
          displayText(areaInsideCottageOpt1_mouse);
          haveKeys = 1;
        } else {
          displayText(areaInsideCottageOpt1_stroke);
        }
      }
      break;
    case 2:
      if (wantCD == 0) {
        displayText(areaInsideCottageOpt2);
      } else {
        if (haveCD == 0) {
          displayText(areaInsideCottageOpt2_takeCD);
          haveCD = 1;
        } else {
          displayText(areaInsideCottageOpt2_play);
        }
      }
      break;
    case 3:
      state = AreaCottage;
      break;
  }
}

// ***********************
// ***** GARDEN AREA *****
// ***********************
void AreaGarden() {
  int opt = 0;
  while (opt == 0) {
    opt = displayText(areaGarden);
  }
  switch (opt) {
    case 1:
      state = AreaCottage;
      break;
    case 2:
      state = AreaShed;
      break;
    case 3:
      state = AreaWell;
      break;
    case 4:
      displayText(areaGardenOpt4);
      state = AreaBeach;
      break;
  }
}

// *********************
// ***** SHED AREA *****
// *********************
void AreaShed() {
  int opt = 0;
  if (haveFrisbee == 0) {
    while (opt == 0) {
      opt = displayText(areaShed);
    }
  } else {
    while (opt == 0) {
      opt = displayText(areaShed_frisbee);
    }
  }
  switch (opt) {
    case 1:
      if (wantEmptyCan == 0) {
        displayText(areaShedOpt1);
      } else {
        if (haveEmptyCan == 0) {
          displayText(areaShedOpt1_can);
          haveEmptyCan = 1;
        } else {
          displayText(areaShedOpt1_got);
        }
      }
      break;
    case 2:
      displayText(areaShedOpt2);
      state = AreaDead;
      break;
    case 3:
      state = AreaGarden;
      break;
    case 4:
      displayText(areaShedOpt4);
      haveFrisbee = 1;
      break;
  }
}

// *********************
// ***** WELL AREA *****
// *********************
void AreaWell() {
  int opt = 0;
  if (haveMirror == 0) {
    while (opt == 0) {
      opt = displayText(areaWell);
    }
  } else {
    while (opt == 0) {
      opt = displayText(areaWell_mirror);
    }
  }
  switch (opt) {
    case 1:
      if (haveMirror) {
        displayText(areaWellOpt1_coin);
      } else {
        if (haveHook) {
          displayText(areaWellOpt1_hook);
          haveMirror = 1;
        } else {
          if (haveRope) {
            displayText(areaWellOpt1_rope);
            wantHook = 1;
          } else {
            displayText(areaWellOpt1);
          }
        }
      }
      break;
    case 2:
      state = AreaShed;
      break;
    case 3:
      state = AreaOuthouse;
      break;
    case 4:
      state = AreaCottage;
      break;
  }
}

// *************************
// ***** OUTHOUSE AREA *****
// *************************
void AreaOuthouse() {
  int opt = 0;
  if (haveHook == 1) {
    while (opt == 0) {
      opt = displayText(areaOuthouse_hook);
    }
  } else {
    while (opt == 0) {
      opt = displayText(areaOuthouse);
    }
  }
  switch (opt) {
    case 1:
      state = AreaCottage;
      break;
    case 2:
      state = AreaWell;
      break;
    case 3:
      if (haveHook) {
        displayText(areaOuthouseOpt3_wee);
      } else {
        if (wantHook) {
          displayText(areaOuthouseOpt3_hook);
          haveHook = 1;
        } else {
          displayText(areaOuthouseOpt3);
        }
      }
      break;
  }
}

// **********************
// ***** BEACH AREA *****
// **********************
void AreaBeach() {
  int opt = 0;
  if (haveWinder) {
    while (opt == 0) {
      opt = displayText(areaBeach_snail);
    }
  } else {
    while (opt == 0) {
      opt = displayText(areaBeach);
    }
  }
  switch (opt) {
    case 1:
      state = AreaBoat;
      break;
    case 2:
      state = AreaGarden;
      break;
    case 3:
      if (haveWinder) {
        displayText(areaBeachOpt3_search);
      } else {
        displayText(areaBeachOpt3);
        haveWinder = 1;
      }
      break;
  }
}

// *********************
// ***** BOAT AREA *****
// *********************
void AreaBoat() {
  int opt = 0;
  while (opt == 0) {
    opt = displayText(areaBoat);
  }
  wantEmptyCan = 1;
  switch (opt) {
    case 1:
      displayText(areaBoatOpt1);
      break;
    case 2:
      if (havePetrolCan) {
        displayText(areaBoatOpt2_dneed);
      } else {
        if (haveEmptyCan) {
          displayText(areaBoatOpt2_can);
          havePetrolCan = 1;
        } else {
          displayText(areaBoatOpt2);
        }
      }
      break;
    case 3:
      if (haveRope) {
        displayText(areaBoatOpt3_dneed);
      } else {
        displayText(areaBoatOpt3);
        haveRope = 1;
      }
      break;
    case 4:
      state = AreaBeach;
      break;
  }
}

// ********************* //
// ***** FINISHED! ***** //
// ********************* //
void AreaFinish() {
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.write(byte(1));
  lcd.write(byte(0));
  for (int i=2;i<16;i++) {
    lcd.setCursor(i,1);
    lcd.write(byte(3));
    delay(400);
    lcd.setCursor(i,1);
    lcd.print(" ");
  }
  displayText(areaFinish);
}

// ************************
// ***** YOU ARE DEAD *****
// ************************
void AreaDead() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  You are dead");
  lcd.setCursor(0, 1);
  lcd.print("Press any button");
  lcd.setCursor(0,0);
  lcd.write(byte(2));
  lcd.setCursor(15,0);
  lcd.write(byte(2));
  inkeys();

  //Erase flags for parts obtained:
  wantCD = 0;
  haveCD = 0;
  haveFrisbee = 0;
  bearHasFrisbee = 0;
  haveSteeringWheel = 0;
  carSteeringWheel = 0;
  haveKeys = 0;
  carKeys = 0;
  haveWinder = 0;
  carWinder = 0;
  wantEmptyCan = 0;
  haveEmptyCan = 0;
  havePetrolCan = 0;
  carPetrolCan = 0;
  haveMirror = 0;
  carMirror = 0;
  haveRope = 0;
  wantHook = 0;
  haveHook = 0;
  wantMouse = 0;
  haveMouse = 0;
  carPartsReq = 5;
  state = AreaStart;
}

int displayText(int area) {
  int pos = area * 6;
  int start = pgm_read_word_near(data + pos);
  int en = pgm_read_word_near(data + pos + 1);
  int opt1 = pgm_read_word_near(data + pos + 2);
  int opt2 = pgm_read_word_near(data + pos + 3);
  int opt3 = pgm_read_word_near(data + pos + 4);
  int opt4 = pgm_read_word_near(data + pos + 5);
  //start, int en, int opt1
  int index = 0;
  int k = btnNone;
  int option = 0;
  while (k != btnSelect) {
    lcd.clear();
    lcd.setCursor(0, 0);
    strcpy_P(buffer, (char*)pgm_read_word(&(text[index + start])));
    lcd.print(buffer);
    if (index < en) {
      lcd.setCursor(0, 1);
      strcpy_P(buffer, (char*)pgm_read_word(&(text[index + 1 + start])));
      lcd.print(buffer);
    }
    lcd.blink();
    if (index == opt1) {
      lcd.setCursor(0, 0);
      option = 1;
    } else if (index + 1 == opt1) {
      lcd.setCursor(0, 1);
      option = 1;
    } else if (index == opt2) {
      lcd.setCursor(0, 0);
      option = 2;
    } else if (index + 1 == opt2) {
      lcd.setCursor(0, 1);
      option = 2;
    } else if (index == opt3) {
      lcd.setCursor(0, 0);
      option = 3;
    } else if (index + 1 == opt3) {
      lcd.setCursor(0, 1);
      option = 3;
    } else if (index == opt4) {
      lcd.setCursor(0, 0);
      option = 4;
    } else if (index + 1 == opt4) {
      lcd.setCursor(0, 1);
      option = 4;
    } else {
      lcd.noBlink();
      option = 0;
    }
    k = inkeys();
    if (k == btnDown) index = index + 2;
    else if ( k == btnUp)index = index - 2;
    if (index < 0) index = 0;
    else if (index > en) index = en;
  }
  lcd.noBlink();
  return option;
}

int inkeys() {
  while (debounce > millis()) {}
  int b = 1001;
  while ( b > 1000) b = analogRead(A0);
  debounce = millis() + 300;
  //if (b > 1000) return btnNone;
  if (b < 50) return btnSelect; //btnRight;
  if (b < 250) return btnUp;
  if (b < 450) return btnDown;
  if (b < 650) return btnSelect; //btnLeft;
  if (b < 850) return btnSelect;
}


