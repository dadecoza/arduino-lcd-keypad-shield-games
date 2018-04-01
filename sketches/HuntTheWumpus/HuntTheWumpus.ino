// -------------------------------------------------------------------------------
// An Arduino sketch that implements the classic game Hunt the Wumpus
//
// http://en.wikipedia.org/wiki/Wumpus
//
// In this variant, there are twenty rooms layed out like a d20; therefore, each room is connected
// to three other rooms.  Two rooms are bottomless pits; if you fall in to a bottomless pit you lose.
// Two rooms contain giant bats; if you enter a room with a giant bat it will pick you up and carry
// you to a random room.  One room contains a wumpus; if you bump into the Wumpus, it will eat you and
// you lose.  You have 2 arrows; if you shoot the Wumpus, you win.  If you run out of arrows, you lose.
//
// MIT license.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//
//      ******************************************************
//      Designed for the Adafruit RGB LCD Shield Kit
//      http://www.adafruit.com/products/716
//      or
//      Adafruit Negative RGB LCD Shield Kit
//      http://www.adafruit.com/products/714
//      ******************************************************
//
//
// --------------------------------------------------------------------------------
// Dependencies
// --------------------------------------------------------------------------------
// Adafruit Industries's RGB 16x2 LCD Shield library:
//       https://github.com/adafruit/Adafruit-RGB-LCD-Shield-Library
// Adafruit Industries's MCP23017 I2C Port Expander library:
//       https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library
// --------------------------------------------------------------------------------
//#include <Wire.h>
//#include <Wire.h>
//#include <Adafruit_RGBLCDShield.h>
//#include <utility/Adafruit_MCP23017.h>
#include <LiquidCrystal.h>
#include "HuntTheWumpus.h"

#define BUTTON_UP 0x08
#define BUTTON_DOWN 0x04
#define BUTTON_LEFT 0x10
#define BUTTON_RIGHT 0x02
#define BUTTON_SELECT 0x01

//! Map of the cavern layout.
/*!
   The first dimension represents the cave number and the second dimension represents
   the connected caves.  NOTE - C indexing starts at 0, but cave number display starts
   at 1 - so the first line below means cave 1 is connected to caves 2, 5, and 8.
*/

const uint8_t cave[20][3] = { { 2,  8, 14},    //  0
                              { 7, 13, 19},    //  1
                              {12, 18,  0},    //  2
                              {16, 17, 19},    //  3
                              {11, 14, 18},    //  4
                              {13, 15, 18},    //  5
                              { 9, 14, 16},    //  6
                              { 1, 15, 17},    //  7
                              { 0, 10, 16},    //  8
                              { 6, 11, 19},    //  9
                              { 8, 12, 17},    // 10
                              { 4,  9, 13},    // 11
                              { 2, 10, 15},    // 12
                              { 1,  5, 11},    // 13
                              { 0,  4,  6},    // 14
                              { 5,  7, 12},    // 15
                              { 3,  6,  8},    // 16
                              { 3,  7, 10},    // 17
                              { 2,  4,  5},    // 18
                              { 1,  3,  9} };  // 19

//! Index in the map of the room the player is in.
uint8_t player_room;

//! Hazards in each room
uint8_t hazards[20];

//! Count of how many arrows the player has left.
uint8_t arrow_count;

//! Index in the map of the room the arrow is shot into.
/*!
  This index is only valid/current during the state changes
  associated with firing an arrow into a room.
*/
uint8_t arrow_room;

//! The current state.
void (*state)() = NULL;

//! The state that the game was in prior to the current state.
void (*last_state)() = NULL;

//! The time in milliseconds since the last state change.
unsigned long last_state_change_time;

//! The current time in milliseconds since boot.
unsigned long time;

//! Array of columns bracketing menu options.
/*!
  The first dimension is the menu item index, the second column is the
  tuple of columns which bracket the menu item text.
 */
const uint8_t menu_col[4][2] = { {0,  3},
                                 {3,  6},
                                 {6,  9},
                                 {9, 15} };

//! The currently selected menu index.
uint8_t selected_menu_idx;

//! The LCD display object.
//Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//! Enum of backlight colors.
enum BackLightColor { RED=0x1, YELLOW=0x3, GREEN=0x2, TEAL=0x6, BLUE=0x4, VIOLET=0x5, WHITE=0x7 };

//! The bitmask of currently clicked buttons.
uint8_t clicked_buttons;

//! Array of custom bitmap icons.
/*!
  Custom icons created using: http://www.quinapalus.com/hd44780udg.html
*/
byte icons[4][8] = { { 0x0e, 0x15, 0x1f, 0x11, 0x0e, 0x11, 0x11 },
                     { 0x0a, 0x1f, 0x15, 0x00, 0x00, 0x00, 0x00 },
                     { 0x00, 0x00, 0x11, 0x0a, 0x0a, 0x0a, 0x0a },
                     { 0x00, 0x04, 0x02, 0x1f, 0x02, 0x04, 0x00 } };

//! Index into the bitmap array for the wumpus icon.
const int WUMPUS_ICON_IDX = 0;

//! Index into the bitmap array for the bat icon.
const int BAT_ICON_IDX = 1;

//! Index into the bitmap array for the pit icon.
const int PIT_ICON_IDX = 2;

//! Index into the bitmap array for the arrow icon.
const int ARROW_ICON_IDX = 3;

//! Perform one time setup for the game and put the game in the splash screen state.
void setup() {
  // LCD has 16 columns & 2 rows
  lcd.begin(16, 2);
  
  // Define custom icons
  lcd.createChar(WUMPUS_ICON_IDX, icons[WUMPUS_ICON_IDX]);
  lcd.createChar(BAT_ICON_IDX, icons[BAT_ICON_IDX]);
  lcd.createChar(PIT_ICON_IDX, icons[PIT_ICON_IDX]);
  lcd.createChar(ARROW_ICON_IDX, icons[ARROW_ICON_IDX]);
  
  // Use Pin 0 to seed the random number generator
  randomSeed(analogRead(0));
  
  // Initial game state
  state = begin_splash_screen;
}

//! Main loop of execution.
void loop() {
  time = millis();
  
  // Record time of state change so animations
  // know when to stop
  if (last_state != state) {
    last_state = state;
    last_state_change_time = time;
  }
  
  // Read in which buttons were clicked
  read_button_clicks();
  
  // Call current state function
  state();

  delay(10);
}

//! Return a bitmask of clicked buttons.
/*!
  Examine the bitmask of buttons which are currently pressed and compare against
  the bitmask of which buttons were pressed last time the function was called.
  If a button transitions from pressed to released, return it in the bitmask.

  \return the bitmask of clicked buttons
*/
void read_button_clicks() {
  static uint8_t last_buttons = 0;
  
  //uint8_t buttons = lcd.readButtons();
  uint8_t buttons = readButtons();
  clicked_buttons = (last_buttons ^ buttons) & (~buttons);
  last_buttons = buttons;
}

//! Print a cave number to the lcd.
/*!
  Print a cave number to the lcd by adding one to the index number and left
  padding with a single space if needed to make the cave number take up two
  places.
  
  \param cave_idx the index of the cave in the array
*/
void print_cave_number(uint8_t cave_idx) {
  if (cave_idx < 9) {
    lcd.print(' ');
  }
  lcd.print(cave_idx + 1);
}

//! Clear the current menu selection indicator characters
/*!
  Erase the characters bracketing the current menu selection.
*/
void clear_current_menu() {
  lcd.setCursor(menu_col[selected_menu_idx][0], 1);
  lcd.print(' ');
  lcd.setCursor(menu_col[selected_menu_idx][1], 1);
  lcd.print(' ');
}

//! Highlight the current menu selection using indicator characters
/*!
  Draw characters bracketing the current menu selection.
*/
void highlight_current_menu() {
  lcd.setCursor(menu_col[selected_menu_idx][0], 1);
  lcd.write(0x7E);
  lcd.setCursor(menu_col[selected_menu_idx][1], 1);
  lcd.write(0x7F);
}

//! Check for left and right button clicks and update the menu index as needed.
void handle_menu() {
  if (clicked_buttons & (BUTTON_LEFT | BUTTON_UP)) {
    selected_menu_idx = (selected_menu_idx > 0) ? selected_menu_idx - 1 : 3;
  } else if (clicked_buttons & (BUTTON_RIGHT | BUTTON_DOWN)) {
    selected_menu_idx = (selected_menu_idx < 3) ? selected_menu_idx + 1 : 0;
  } 
}

//! Initial game state, draw the splash screen.
void begin_splash_screen() {
  lcd.clear();
  //lcd.setBacklight(TEAL);
  lcd.print(F("HUNT THE WUMPUS"));
  
  state = animate_splash_screen;
}

//! Animate the splash screen.
/*!
  Blink the text "PRESS SELECT" and wait for the user to press the select button.
*/
void animate_splash_screen() {
  static boolean blink = true;
  static unsigned long last_blink_time;
  
  if (time - last_blink_time >= 1000) {
    lcd.setCursor(0, 1);
    if (blink) {
      lcd.write(0x7E);
      lcd.print(F(" PRESS SELECT "));
      lcd.write(0x7F);
    } else {
      lcd.print(F("                "));
    }
    blink = !blink;
    last_blink_time = time;
  }
  
  if (clicked_buttons & BUTTON_SELECT) {
    state = start_game;
  }
}

//! Put the given hazard in a random room
/*
  The function generates a random room into which it puts the given hazard.
  It keeps trying until it finds a room that doesn't already have another
  hazard.
*/
void init_hazard(HazardType hazard)
{
  for(;;) {
    int index = random(20);
    
    if (!hazards[index])
    {
      hazards[index] = (uint8_t)hazard;
      break;
    }
  }
}

//! Initialize a new game.
/*
  Randomize locations and reset variables.
*/
void start_game() {
  lcd.clear();

  for (int i = 0; i < 20; i++) {
    hazards[i] = 0;
  }
  init_hazard(WUMPUS);
  init_hazard(PIT);
  init_hazard(PIT);
  init_hazard(BAT);
  init_hazard(BAT);

  // Make sure the player starts in a room with no hazards.
  // It's not fun to be killed before you make the first move.
  do {
    player_room = random(20);
  } while (hazards[player_room]);

  arrow_count = 2;
  selected_menu_idx = 0;
  
  state = begin_move_room;
}

//! Delay to show a status before continuing with the room move.
void status_delay() {
  if (time - last_state_change_time >= 3000) {
    state = begin_move_room;
  }
}

//! Check for hazards when a player changes rooms
void begin_move_room() {
  switch (hazards[player_room]) {    
    case BAT:
      state = begin_bat_move;
      break;
    
    case PIT:
      state = game_over_pit;
      break;
      
    case WUMPUS:
      state = game_over_wumpus;
      break;
    
    default:
      state = enter_new_room;
      break;
  }
}


// -------------------------------------------------------------------------------
// Bat states
// -------------------------------------------------------------------------------

void begin_bat_move() {
  lcd.clear();
  //lcd.setBacklight(BLUE);
  lcd.write(BAT_ICON_IDX);
  lcd.setCursor(5, 0);
  lcd.print(F("Bats!"));
  lcd.setCursor(0, 1);
  lcd.write(BAT_ICON_IDX);
  
  state = animate_bat_move;
}

void animate_bat_move() {
   static unsigned long last_animate_time;
  
  if (time - last_animate_time > 200) {
    lcd.scrollDisplayRight();
    last_animate_time = time;
  }
  
  if (time - last_state_change_time >= 3000) {
    state = end_bat_move;
  }
}

void end_bat_move() {
  hazards[player_room] = 0;
  init_hazard(BAT);

  player_room = random(20);
  
  state = begin_move_room;
}


// -------------------------------------------------------------------------------
// Moving states / functions
// -------------------------------------------------------------------------------

void enter_new_room() {
  int adjacent_hazards = NONE;
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Room "));
  print_cave_number(player_room);
  
  for (int i=0; i<3; i++) {
    adjacent_hazards |= hazards[cave[player_room][i]];
  }
  
  lcd.print(' ');    
  if (adjacent_hazards & WUMPUS) {
    lcd.write(byte(WUMPUS_ICON_IDX));
  } else {
    lcd.print(' ');
  }
  if (adjacent_hazards & BAT) {
    lcd.write(BAT_ICON_IDX);
  } else {
    lcd.print(' ');
  }
  if (adjacent_hazards & PIT) {
    lcd.write(PIT_ICON_IDX);
  } else {
    lcd.print(' ');
  }

  lcd.setCursor(14, 0);
  lcd.write(ARROW_ICON_IDX);
  lcd.print(arrow_count);

  if (adjacent_hazards) {
    //lcd.setBacklight(YELLOW);
  } else {
    //lcd.setBacklight(TEAL);
  }

  lcd.setCursor(1, 1);
  for (int i=0; i<3; i++) {
    print_cave_number(cave[player_room][i]);
    lcd.print(' ');
  }

  selected_menu_idx = 0;
  lcd.setCursor(menu_col[selected_menu_idx][0], 1);
  lcd.print('[');
  lcd.setCursor(menu_col[selected_menu_idx][1], 1);
  lcd.print(']');

  state = begin_input_move;
}

void begin_input_move() {
  lcd.setCursor(0, 0);
  lcd.print(F("Room "));
  print_cave_number(player_room);
  lcd.print(' ');
  
  lcd.setCursor(10, 1);
  lcd.print(F("Shoot"));
  
  state = input_move;
}

void input_move() {
  if (clicked_buttons) {
    clear_current_menu();

    if (clicked_buttons & BUTTON_SELECT) {
      if (selected_menu_idx < 3) {
        player_room = cave[player_room][selected_menu_idx];
        state = begin_move_room;
      } else {
        state = begin_input_arrow;
      }
    } else {
      handle_menu();
    }
    
    highlight_current_menu();
  }
}

// -------------------------------------------------------------------------------
// Arrow shooting states / functions
// -------------------------------------------------------------------------------

void begin_input_arrow() {
  //lcd.setBacklight(WHITE);
  lcd.setCursor(0, 0);
  lcd.print(F("Shoot at"));
  
  lcd.setCursor(10, 1);
  lcd.print(F("Move "));
  
  state = input_arrow;
}

void input_arrow() {
  if (clicked_buttons) {
    clear_current_menu();

    if (clicked_buttons & BUTTON_SELECT) {
      if (selected_menu_idx < 3) {
        arrow_room = cave[player_room][selected_menu_idx];
        state = being_shooting_arrow;
      } else {
        state = cancel_input_arrow;
      }
    } else {
      handle_menu();
    }
    
    highlight_current_menu();
  }
}

void cancel_input_arrow() {
  int adjacent_hazards = NONE;

  for (int i=0; i<3; i++) {
    adjacent_hazards |= hazards[cave[player_room][i]];
  }

  if (adjacent_hazards) {
    //lcd.setBacklight(YELLOW);
  } else {
    //lcd.setBacklight(TEAL);
  }
  
  state = begin_input_move;
}

void being_shooting_arrow() {
  lcd.clear();
  //lcd.setBacklight(VIOLET);
  lcd.print(F(">-->"));
  
  arrow_count--;
  state = animate_shooting_arrow;
}

void animate_shooting_arrow() {
  static unsigned long last_animate_time;
  
  if (time - last_animate_time > 200) {
    lcd.scrollDisplayRight();
    last_animate_time = time;
  }
  
  if (time - last_state_change_time >= 3000) {
    if (hazards[arrow_room] == WUMPUS) {
      state = game_over_win;
    } else {
      state = arrow_missed;
    }
  }
}

void arrow_missed() {
  lcd.clear();
  lcd.print(F("Missed..."));
  
  if (arrow_count <= 0) {
    state = game_over_arrow;
  } else {
    state = status_delay;
  }
}


// -------------------------------------------------------------------------------
// Game over states / functions
// -------------------------------------------------------------------------------

void draw_game_over_screen(uint8_t backlight, const __FlashStringHelper *message, uint8_t icon) {
  lcd.clear();
  //lcd.setBacklight(backlight);
  lcd.print(message);
  lcd.setCursor(0, 1);
  lcd.write(icon);
  lcd.setCursor(3, 1);
  lcd.print(F("GAME OVER"));
  lcd.setCursor(15, 1);
  lcd.write(icon);
}

void game_over_arrow() {
  draw_game_over_screen(RED, F(" Out of arrows"), ARROW_ICON_IDX);
  state = game_over_delay;
}

void game_over_pit() {
  draw_game_over_screen(RED, F(" Fell in a pit"), PIT_ICON_IDX);
  state = game_over_delay;
}

void game_over_wumpus() {
  draw_game_over_screen(RED, F("Eaten by Wumpus"), WUMPUS_ICON_IDX);
  state = game_over_delay;
}

void game_over_win() {
  draw_game_over_screen(GREEN, F("    You win!"), WUMPUS_ICON_IDX);  
  state = game_over_delay;
}

void game_over_delay() {
  if (time - last_state_change_time >= 3000) {
    state = begin_splash_screen;
  }
}

//Emulates the Adafruit LCD Keypad Button presses - @dadecoza
uint8_t readButtons(void) {
  uint8_t reply = 0x1F;
  boolean button[5];
  for (uint8_t i=0; i<5; i++) button[i] = 1;
  int adc_key_in = analogRead(A0);
  if (adc_key_in < 50)        button[1] = 0;  
  else if (adc_key_in < 195)  button[3] = 0; 
  else if (adc_key_in < 380)  button[2] = 0; 
  else if (adc_key_in < 555)  button[4] = 0; 
  else if (adc_key_in < 790)  button[0] = 0;
  for (uint8_t i=0; i<5; i++) {
    reply &= ~(button[i] << i);
  }
  return reply;
}

