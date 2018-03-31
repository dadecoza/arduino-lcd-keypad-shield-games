// This work is licensed under the Creative Commons Attribution-ShareAlike 3.0 Unported License.
// To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/3.0/.

#include <EEPROM.h>
#include <LiquidCrystal.h>

// Class for cycling through a sequence of animation frames
class Animation {
  private:
    int _current_frame;
    int _frame_count;
    int *_frames;

  public:
    Animation(int frame_count, int *frames) {
      _current_frame = 0;
      _frame_count = frame_count;
      _frames = frames;
    }

    int next() {
      _current_frame++;
      if (_current_frame == _frame_count) {
        _current_frame = 0;
      }
      return _frames[_current_frame];
    }
    int prev() {
      _current_frame++;
      if (_current_frame < 0) {
        _current_frame += _frame_count;
      }
      return _frames[_current_frame];
    }
    int current() {
      return _frames[_current_frame];
    }
};

// Constants for identifying each sprite
const byte SPRITE_TAIL0 = 0;
const byte SPRITE_TAIL1 = 1;

const byte SPRITE_BODY0 = 2;
const byte SPRITE_BODY1 = 3;

const byte SPRITE_WALLB = 5;
const byte SPRITE_WALLT = 6;

const byte SPRITE_EXPL = 7;

// Sprite custom character data
byte sprite_tail0[8] = {0b00000, 0b00000, 0b00000, 0b10001, 0b01111, 0b00101, 0b00000, 0b00001};
byte sprite_tail1[8] = {0b00000, 0b00000, 0b00000, 0b00101, 0b01111, 0b10001, 0b00000, 0b00001};

byte sprite_body0[8] = {0b00000, 0b00100, 0b00100, 0b11110, 0b10101, 0b11110, 0b10100, 0b11111};
byte sprite_body1[8] = {0b00000, 0b11111, 0b00100, 0b11110, 0b10101, 0b11110, 0b10100, 0b11111};

byte sprite_wallt[8] = {0b00000, 0b00100, 0b01001, 0b11110, 0b01001, 0b00100, 0b00000, 0b00000};
byte sprite_wallb[8] = {0b00000, 0b00100, 0b00100, 0b01010, 0b01110, 0b01010, 0b01110, 0b01010};

byte sprite_expl[8] = {0b00100, 0b10100, 0b01101, 0b01010, 0b01010, 0b10110, 0b00101, 0b00100};

// Animation sequences
int seq_tail[] = {SPRITE_TAIL0, SPRITE_TAIL1};
int seq_body[] = {SPRITE_BODY0, SPRITE_BODY1};

Animation anim_tail(2, seq_tail);
Animation anim_body(2, seq_body);

// LCD settings
//LiquidCrystal lcd(13, 12, 11, 10, 9, 8, 7, 6, 5, 4);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//const int lcd_backlight = 3;

// Button pin constants
//const int button = 2;

//Speaker pin contstant
const int speaker = 3;

// Some game constants that can be adjusted to control difficulty
const unsigned long frame_rate = 125;
unsigned long frame_next = 0;

int game_mode = 0;

unsigned long score = 0;
boolean new_highscore = false;

boolean first = true;
boolean button_state = false;

const unsigned debounce_time = 20;
//volatile boolean button_toggled = true;
volatile unsigned long next_read = 0;

// Do "smart" spawning of walls so the game is never unplayable
unsigned int mask_wall = 0b1111000000000000;

// Helicopter collision detection mask
unsigned int mask_heli = 0b0000000000000011;

// Bitwise representations of obstacle locations
unsigned int walls_top = 0x0000;
unsigned int walls_bot = 0x0000;

// Maximum and minimum wall advance rates
unsigned long max_wall_advance_rate = 350;
unsigned long min_wall_advance_rate = 140;

unsigned long wall_advance_rate = max_wall_advance_rate;
unsigned long wall_advance_next = 0;

// Death animation and flash times
unsigned long death_rate = 150;
unsigned long death_hold = 1500;

void setup() {

  pinMode(speaker,OUTPUT);

  read_button();
  
  // Seed the random number generator using noise from analog 0
  unsigned long seed = 0;
  for (int n = 0; n < 32; ++n) {
    randomSeed(seed);
    delay(random() & 0xf);

    seed <<= 1;
    seed |= analogRead(1) & 1;
  }

  // Generate the custom characters for the games sprites
  lcd.createChar(SPRITE_TAIL0, sprite_tail0);
  lcd.createChar(SPRITE_TAIL1, sprite_tail1);

  lcd.createChar(SPRITE_BODY0, sprite_body0);
  lcd.createChar(SPRITE_BODY1, sprite_body1);

  lcd.createChar(SPRITE_WALLB, sprite_wallb);
  lcd.createChar(SPRITE_WALLT, sprite_wallt);

  lcd.createChar(SPRITE_EXPL, sprite_expl);

  // Start up the LCD
  lcd.begin(16, 2);
  lcd.noCursor();
  lcd.clear();
  lcd.home();

  // Start at the home screen
  set_game_mode(0);
}

void loop() {
  boolean update = false;

  // Update animation sequences
  unsigned long now = millis();
  if (frame_next < now) {
    anim_tail.next();
    anim_body.next();

    frame_next = now + frame_rate;
    update = true;
  }
  
  read_button();
  update = true;

  // Take appropriate action depending on the current game mode
  switch (game_mode) {
    case 0: game_home(update) ; break;
    case 1: game_play(update) ; break;
    case 2: game_over(update); break;
    default: game_mode = 0;
  }
}

// The home state
void game_home(boolean update) {
  if (first) {
    first = false;
    score = get_highscore();
    lcd.clear();
  }
   
   read_button();
   if (!button_state) {
    set_game_mode(1);
  }

  if (update) {
    lcd.setCursor(0, 0);
    lcd.print("Helicopter! ");
    lcd.write(anim_tail.current());
    lcd.write(anim_body.current());

    lcd.setCursor(0, 1);
    lcd.print("Best: ");
    lcd.print(score);
  }
}

// The game play state
void game_play(boolean update) {
  if (first) {
    first = false;

    score = 0;
    new_highscore = false;

    walls_bot = 0;
    walls_top = 0;
    wall_advance_rate = max_wall_advance_rate;

    lcd.clear();
  }

  unsigned long now = millis();

  // Is it time to advance the obstacles?
  if (now > wall_advance_next) {
    if (wall_advance_rate > min_wall_advance_rate) {
      wall_advance_rate--;
    }
    wall_advance_next = now + wall_advance_rate;

    walls_top >>= 1;
    walls_bot >>= 1;
    ++score;

    // Can we spawn a new obstacle for the player?
    if (((walls_top | walls_bot) & mask_wall) == 0) {
      if (random() & 1) {
        walls_top |= 0x8000;
      } else {
        walls_bot |= 0x8000;
      }
    }

    update = true;
  }

  // Render the next frame
  if (update) {
    lcd.setCursor(0, button_state ? 0 : 1);
    lcd.write(0x20);
    lcd.write(0x20);

    for (int n = 0; n < 16; ++n) {
      lcd.setCursor(n, 0);
      if (walls_top & (1 << n)) {
        lcd.write(SPRITE_WALLT);
        lcd.write(0x20);
      }
    }

    for (int n = 0; n < 16; ++n) {
      lcd.setCursor(n, 1);
      if (walls_bot & (1 << n)) {
        lcd.write(SPRITE_WALLB);
        lcd.write(0x20);
      }
    }

    // Handle a collision with an obstacle
    lcd.setCursor(0, button_state ? 1 : 0);
    if (mask_heli & (button_state ? walls_bot : walls_top)) {
      lcd.write(SPRITE_EXPL);
      lcd.write(SPRITE_EXPL);
      tone(speaker,329, 100);
      boolean ramp = false;
      unsigned long curr = millis(), prev = curr, next = curr + death_rate;
      unsigned long death_stop = millis() + death_hold;

      // Flash the LCDs backlight
      while (curr <= death_stop) {
        curr = millis();

        if (curr > next) {
          prev = curr;
          next = prev + death_rate;
        }

        // Fade the backlight on and off
        unsigned long v = map(curr, prev, next, 0, 255);
        if (!ramp) {
          v = 255 - v;
        }
        //analogWrite(lcd_backlight, v);
      }
      //analogWrite(lcd_backlight, 255);

      // Store the new highscore
      if (score > get_highscore()) {
        set_highscore(score);
        new_highscore = true;
      }
      set_game_mode(2);
    } else {
      lcd.write(anim_tail.current());
      lcd.write(anim_body.current());
    }
  }
}

// The game over state
// Displays the players score
void game_over(boolean update) {
  if (first) {
    first = false;
    lcd.clear();  
  }

  read_button();
  if (!button_state) {
    set_game_mode(0);
  }

  if (update) {
    lcd.setCursor(0, 0);
    lcd.print(new_highscore ? "New High Score!" : "Game Over");

    lcd.setCursor(0, 1);
    lcd.print("Score: ");
    lcd.print(score);
  }
}

// Change the game mode and reset some state information
void set_game_mode(int mode) {
  button_state = true;
  game_mode = mode;
  first = true;
  lcd.clear();
}

// Retrieve the high score from EEPROM
unsigned long get_highscore() {
  unsigned long b0 = EEPROM.read(0);
  unsigned long b1 = EEPROM.read(1);
  unsigned long b2 = EEPROM.read(2);
  unsigned long b3 = EEPROM.read(3);
  unsigned long cs = EEPROM.read(4);

  if (((b0 + b1 + b2 + b3) & 0xff) == cs) {
    return b0 | (b1 << 8) | (b2 << 16) | (b3 << 24);
  }
  return 0;
}

// Store the new highscore in EEPROM
void set_highscore(unsigned long score) {
  byte b0 = (byte)((score >> 0) & 0xff);
  byte b1 = (byte)((score >> 8) & 0xff);
  byte b2 = (byte)((score >> 16) & 0xff);
  byte b3 = (byte)((score >> 24) & 0xff);
  byte cs = b0 + b1 + b2 + b3;

  EEPROM.write(0, b0);
  EEPROM.write(1, b1);
  EEPROM.write(2, b2);
  EEPROM.write(3, b3);
  EEPROM.write(4, cs);
}

void read_button() {
  if (millis() > next_read) {
    next_read = millis() + 200;
    button_state = (analogRead(A0) > 1000);
  }
}

