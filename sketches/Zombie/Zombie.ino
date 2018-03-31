/* 
  Zombie Showdown
  By Markus Ulfberg 2010-01-12
  
  'Graphics' ;) added by Bart Lammers 2010-01-22
  
  More Arduino stuff and future updates of Zombie Showdown at:
  http://genericnerd.blogspot.com

  Description:
    A small game using an 16x2 LCD and a pushbutton.
    The game presents a start screen and awaits player input. 
    If the player presses the button the game starts.
    
    After a random number of milliseconds a Zombie will 
    appear. It will have a random strenght of 1-5. 
    The strenght of the Zombie is equal to how many
    buttonpresses it takes to kill it. 
    
    If the player fails to kill the Zombie within a random 
    timeframe the Zombie will kill the player.
    
    If the player manages to kill the Zombie the game will
    continue and a new Zombie will soon attack. 
    
    When the player dies a Game Over screen is presented
    also displaying the score of the player. 
    
    There is no "beating" this game since in the Zombie apocalypse
    eventually everyone will die. 

  Planned expansion:
    1. Use a vibrator to signal Zombie attack.
    2. Use randomizer to make 
  
  Credits:
    This game uses example code from 
    Debounce and the LiquidCrystal library.

*/


// include the library code:
#include <LiquidCrystal.h>


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


// Set the text strings used in the game
char* gameText[]={"Zombie Showdown",// 0 Title 
                  "Kill to Start",  // 1 
                  "Let's go!",      // 2
                  "Zombie!!!",      // 3                  
                  "You killed it.", // 4
                  "You are dead.",  // 5
                  "Game Over",      // 6
                  "Score: "         // 7
                  };         

// Custom characters for the zombie graphics
byte zombie_head[8] = {
  B00000,
  B00110,
  B01111,
  B11101,
  B11111,
  B11100,
  B11011,
  B11110,
};

byte zombie_body[8] = {
  B11100,
  B11111,
  B11111,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
};
byte zombie_arm[8] = {
  B00000,
  B11110,
  B11111,
  B00001,
  B00000,
  B00000,
  B00000,
  B00000,
};

byte zombie_head_expl[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B01000,
  B11011,
  B11110,
};

// Button variables
//const int buttonPin = 2;

// Two values for debounceing
int buttonState;
int lastButtonState = LOW;

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

// Stores value of button 1 = pressed 0 = released 
int buttonPress = 0;

// Title screen blink variables
long lastBlinkTime = 0;
long blinkDelay = 500;
int blinkState = 0;

// Gameplay variables

// Zombie health a random number between 1 and 5
int zombie;

// Time since last zombie apperance
long lastZombieTime = 0;

// Randomizes between each zombie 
// Timer for next zombie apperance
// a random number between 200 ms and 20 000 ms 
long zombieDelay;

// Randomizes between each zombie 
// Countdown timer for zombie bite
// a random number between 2 000 ms and 7 000 ms 
long zombieBite;

// Status of zombie apperance 1 = zombie 0 = no zombie
int zombieState = 0;

// Total steps the zombie can take
int zombieSteps = 15;
int zombiePosition = 0;
int zombieLastPosition = 0;
int zombieSpeed = 0;

// Status of player 1 = alive 0 = dead
int playerAlive = 1;

// gameRun sets start screen or runs the game
int gameRun = 0;

// Score
int score = 0;

void setup() {
  
  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
  
  // DEBUG ONLY
  Serial.begin(9600);
    
  // Set up the button
  //pinMode(buttonPin, INPUT);
  //buttonState = digitalRead(buttonPin); 
  buttonState = (analogRead(A0) < 1000);
  // Use unconnected analog input pin
  // to generate a random seed for the random generator
  randomSeed(analogRead(0));
  
  // Generate zombie characters
  lcd.createChar(0, zombie_head);
  lcd.createChar(1, zombie_body);
  lcd.createChar(2, zombie_arm);
  lcd.createChar(3, zombie_head_expl);
  
  // The timeframe where a new Zombie appears 
  // this first Zombie will have a shorter random time frame 
  zombieDelay = random(200,10000);
  
  // The timeframe for the first zombie bite
  zombieBite = random(2000,7000);
  setZombieSpeed();
  
}

void loop() {
  
  // Start sequence
  gameStart();
   
  // Gameplay
  gameExecute();
  
  // GameOver
  gameOver();
  
} // loop end

void gameStart() {
  
  while (gameRun == 0) {
    // Set the cursor
    lcd.setCursor(0,0);
    
    // print the name of the game
    lcd.print(gameText[0]);
  
  
    // Pause for blink
    if ((millis() - lastBlinkTime) > blinkDelay) {
    
      // If blinkState is OFF turn it ON
      if (blinkState == 0) {
      
        // Clear the LCD and set the cursor
        lcd.clear();
    
        // move the cursor down 
        lcd.setCursor(0,1);
        // print the blinking text
        lcd.print(gameText[1]);
    
        // Set the cursor for non blinking text
        lcd.setCursor(0,0);
    
        // since blink cleared the whole LCD
        // we need print the name of the game again
        lcd.print(gameText[0]);
      
        // set blinkState to ON
        blinkState = 1;
      // If blinkState is OFF turn it ON
      } else {
      
        // Clear the LCD and set the cursor
        lcd.clear();
    

        // Set the cursor for non blinking text
        lcd.setCursor(0,0);
    
        // print the name of the game
        lcd.print(gameText[0]);
      
        // Set blink to OFF
        blinkState = 0;
      
      } // END: else 
    
      // store the new blink time
      lastBlinkTime = millis();
    

    } // END: if ((millis() - lastBlinkTime) > blinkDelay)
    
    // Check if button is pressed 
    if (button() == 1) {
      // If so start the game
      gameRun = 1;
      playerAlive = 1;
      
      // reset score
      score = 0;
    } // END: if (button() == 1)
    
  } // END: while game start    
} // END: void gameStart 

void gameExecute() {
  // check wether button is pushed to run game
  while (gameRun == 1) {
      lcd.clear();
      lcd.print(gameText[2]);
      // small delay to get ready
      delay(2000);
 
      // Check if a zombie is here
      if (zombieState == 1) {
        // tell the player that a zombie is here
        lcd.clear();         
        // lcd.print(gameText[3]);
        // Put the zombie in position 0;
        drawZombie();
       
        // Set the strenght and speed of of the zombie
        zombie = random(1,5);
             
         // Resets the zombie timer 
         // this one is for the speed of which the zombie attacks 
         lastZombieTime = millis(); 
       
        // The action part
        while (zombie > 0) {
         // Find out where the zombie has to stand
         zombiePosition = ((millis() - lastZombieTime) / zombieSpeed);
         
         if (zombiePosition != zombieLastPosition) {
            // If it moved, redraw
            zombieLastPosition = zombiePosition;
            drawZombie();
         }
         
         /* // DEBUG 
         Serial.print("Str: ");
         Serial.print(zombie, DEC);
         Serial.print(" Time: ");
         Serial.print(zombieBite);
         Serial.print(" Bite: ");  
         Serial.println((millis() - lastZombieTime));
         */ // END: DEBUG
         
         // Check if button is pressed 
         if (button() == 1) {
           // If so remove 1 health from zombie
           zombie--;
         }
        
         // check if the zombie bites
         if ((millis() - lastZombieTime) > zombieBite) {
            
           // player is bitten and killed
           // Print information on death
           lcd.clear();
           lcd.print(gameText[5]);      
           delay(2000);
            
           // Make sure all loops are exited
           gameRun = 0;
           zombie = 0;
         }
          
       } // END: while zombie > 0
     
       // Add score, first check if the zombie was killed or 
       // it was the player who died and zombie was just reset
       if (gameRun == 1) {
         // The zombie was killed 
         zombieState = 0;
         // Add to the players score
         score++;
         //lcd.clear();
         // Print information of kill
         //lcd.print(gameText[4]);
         lcd.setCursor(zombiePosition,0);
         lcd.write(3);
         // Pause for a while
         delay(1000);
       } 
        
     } else { // END: if Zombie State and Start else 
      
       // zombieState is 0 check if enough time 
       // has passed since last zombie
       if ((millis() - lastZombieTime) > zombieDelay) {
         // A new zombie is here
         zombieState = 1;
         // reset random zombieDelay
         zombieDelay = random(200,2000);
        
         // reset random zombieBite time;
         zombieBite = random(2000,7000);
         setZombieSpeed();
         
         // reset position
         zombiePosition = 0;
         zombieLastPosition = 0;
         
       } // END: if ((millis() - lastZombieTime) > zombieDelay)
     
     } // END: else 

  }  // END: while game run 
  
} // END: gameExecute 

// Calculate the zombie speed, how many ms per step?
void setZombieSpeed() {
  zombieSpeed = zombieBite / zombieSteps;
}

// Draw the zombie on the screen in the correct position
void drawZombie() {
 lcd.clear();
 lcd.setCursor(zombiePosition,0);
 lcd.write(byte(0));
 lcd.setCursor(zombiePosition,1);
 lcd.write(1);
 lcd.setCursor(zombiePosition+1,1);
 lcd.write(2); 
}

int button() {
  // read the state of the switch into a local variable:
  int reading = (analogRead(A0) < 1000);

  // check to see if you just pressed the button 
  // (i.e. the input went from LOW to HIGH),  and you've waited 
  // long enough since the last press to ignore any noise:  

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    buttonState = reading;    
            
    // If button is pressed down 
    if (buttonState == HIGH) {
      // store the state of the button
      buttonPress = 1;             
    }
    // If button is up ...
    if (buttonState == LOW) {
      // ... and was just down i.e released
      if (buttonPress == 1) {
        // Store the new state of the button
        buttonPress = 0;
        
        // also save the reading since we terminate in the next step        
        lastButtonState = reading;      
        
        // Terminate the button() function and return 
        // a positive button press
        return 1;
      }
    } // END: If buttonState == LOW
  } // END: If millis... 
  
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
  
} // END: void button()
  
void gameOver() {
  lcd.clear();
  lcd.setCursor(0,0);
  // Print Game Over
  lcd.print(gameText[6]);
  lcd.setCursor(0,1);
  // Print Score
  lcd.print(gameText[7]);
  lcd.print(score);
  // Pause for a while 
  delay(4000); 
  
}  

