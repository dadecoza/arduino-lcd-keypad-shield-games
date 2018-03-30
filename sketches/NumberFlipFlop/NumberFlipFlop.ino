
// Number Flip-Flop by Budd Churchward, WB7FHC, @barnacleBudd 

/* Original Video: https://www.youtube.com/watch?v=SqxVIVnzkR0
 * Original Blog Post: http://mypetdigispark.blogspot.co.za/2013/02/lcd-game-set-up-number-flip-flop-intro.html
*/

// Modified for the LCD Keypad Shield by Johannes le Roux, @dadecoza


#include <LiquidCrystal.h>
#include <EEPROM.h>

int address = 0;                        // points to the first address in the EEPROM memory
byte value;                             // stores what we read at that location

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);    // setup the liquid crystal display for the Arduino LCD KeyPad Shield

String winner ="0123456789";            // a test string to easily see if game is over
String workingString = "0123456789";    // these get scrambled
int rnd;                                // will hold a random number for us.
int btnPress;                           // is it down or is it up
byte tick = 0;                          // counts the digits we plan to flip
unsigned long myTime;                   // used with mySpeed to set tick rate

int mySpeed = 1000;                     // start with a 1 second interval
byte highScore = 0;                     // so the first score will always beat it
byte thisScore = 120;                   // start with 120 points


void setup(){
  lcd.begin(16, 2);                     // initialize the lcd 
  lcd.clear();                          // clear the screen
  pinMode(13, OUTPUT);                  // we light the LED when the button is pressed
  value = EEPROM.read(address);         // read the high score left here from earlier
  highScore = value;                    // move it into our highScore variable
  
  if(readButton()){                     // If button is down when we power up ...
    EEPROM.write(address,0);            // Change high score stored in EEPROM to zero
    lcd.clear();
    lcd.print("HIGH SCORE RESET");
    highScore=0;                        // reset the high score used by the sketch
    delay(2000);
  }
    
  lcd.clear();
  delay(1000);
  lcd.print("NUMBER FLIP-FLOP");
  scramblePrompt();                     // Go pick random numbers until user presses button
  scrambleString();                     // puts digits in random order
  displayWorkingString();               // prints digits
  lcd.setCursor(12,1);                  // move to bottom right corner
  lcd.print(thisScore,DEC);             // show starting score
                                        // because thisScore is type 'byte' you need to show it as decimal
  delay(1000);
  myTime = millis();                    // start timer
}


void loop()  {
  btnPress = readButton();              // read analog pin A0
  if (btnPress==1){                     // When button is down ...
    digitalWrite(1,1);                  // light up on-board LED
    flip();                             // go flip some digits
    delay(1000);
  }else{                                // When button is up ...
    digitalWrite(1,0);                  // turn off on-board LED
  }
  if(millis() - myTime > mySpeed ){     // when we have waited long enough
    shiftLeft();                        // move the current digit left
    myTime = millis();                  // reset interval timer
  }
}


void flip(){
  int i=0;                              // a counter
  if(tick<2){tick=10;}                  // power play, flip all if only 1 digit
  tick--;                               // undo the last increment, we don't need it
  do {  
    swap(i,tick-i);                     // swap two digits
    i++;                                // increment counter
  } while (i<=(tick/2));                // do half of them and we're done
  //lcd.clear();
  displayWorkingString();               // put the new order on the screen
  tick= 0;                              // reset the digit counter
  myTime = millis();                    // reset the interval timer
}


void shiftLeft(){
  if (tick < 10){                       // keep us in the range...
    lcd.setCursor(tick + 2,0);          // move to spot in front of our digit
    lcd.print(workingString[tick]);     // put a copy of digit in the new spot
    lcd.print(' ');                     // erase the original digit
    tick++;                             // increment the digit counter
    thisScore--;                        // subtract a point
    int x = 12;                         // cursor location for score when its 3 digits
    if(thisScore<100){x++;}             // nudge location for 2 digit score
    if(thisScore<10){x++;}              // nudge again if only 1 digit
    lcd.setCursor(x,1);                 // set the cursor location
    lcd.print(' ');                     // erase digit if we are dropping from 100's to 10's
    lcd.print(thisScore,DEC);           // show current score
    
    if(thisScore==0){                   // When points are all gone ...
      youLose();                        // Tell the user he lost
      return;                           // go back to loop()
    }

  }else{                                // if user doesn't press the button...
    tick=0;                             // start again at the beginning
    displayWorkingString();             // move the digits back in place
  }
}


void scramblePrompt(){
  lcd.noCursor();                       // some LCDs want to flash at you
  lcd.print("NUMBER FLIP-FLOP");        // show the title on the top line
  lcd.setCursor(0,1);                   // move to the bottom line
  lcd.print("Press Button Now");        // prompt the user to press the button

  do {
    rnd=random(9);                      // pick random numbers over and over
  } while (!readButton());              // until user presses the button
}


void scrambleString() {
  lcd.clear();                          // clear the screen
  lcd.print("NUMBER FLIP-FLOP");        // print the title again
  
  for (int i=0; i<10; i++){             // do this once for each digit
    rnd=random(9);                      // pick a random spot
    swap(i,rnd);                        // swap two of the digits
  }
  delay(1000);
  lcd.clear();                          // clear the screen again
  lcd.setCursor(0,1);                   // move to bottom row
  lcd.print("HS=");                     // print the high score
  lcd.print(highScore,DEC);  
}


void swap(int x, int y){
  byte hold=workingString[x];           // store the first digit
  workingString[x]=workingString[y];    // copy the second digit to the first spot
  workingString[y]=hold;                // put the first digit in the second spot
}


void displayWorkingString(){
  lcd.setCursor(2,0);                   // move to top row
  lcd.print(' ');                       // erase the first digit
  lcd.print(workingString);             // put the whole string back in place
  
  if (workingString==winner){           // if the digits are all in order ...
    youWin();                           // go do the cool stuff for the winner
   }
}


void youWin(){
  lcd.setCursor(0,1);                   // move to the second row
  if(thisScore > highScore){            // when we get a new high score
    lcd.print("HIGH SCORE!");           
    highScore = thisScore;              // update the new high score
    EEPROM.write(address, highScore);   // store it now for a power down later
   
  }else{                                // when score doesn't beat high score
    lcd.print("WINNER");                
  }
  delay(3000);
  mySpeed = mySpeed - 50;               // lower mySpeed means faster game
  if(mySpeed<400){mySpeed=400;}         // don't go too fast
  playAgain();                          // Do it all again
}


void youLose(){
  lcd.setCursor(0,1);                   // move to the second row
  lcd.print("YOU LOSE");
  delay(3000);
  mySpeed = mySpeed + 200;              // higher mySpeed means slower game
  if(mySpeed>1000){mySpeed=1000;}       // never slower than once a second
  tick = 0;                             // reset pointer
  playAgain();                          // do it all again
}


void playAgain(){
  lcd.clear();                          // clear the screen
  scrambleString();                     // go mix up the digits again
  displayWorkingString();               // show us the new order
  thisScore = 120;                      // start again with 120 points
}


int readButton(){
  int b = analogRead(A0);               // read A0
  if (b < 850) {                        // less than 850 a button is being pressed
    return 1;                           // and we return true
  }
  return 0;                             //if no button is pressed return false
}


