Hunt-The-Wumpus
===============

An Arduino implementation of Hunt The Wumpus.

Requirements
------------
* An Arduino
* An [Adafruit RGB LCD shield](https://www.adafruit.com/products/716) or [Negative Adafruit RGB LCD shield](http://www.adafruit.com/products/714)
* Arduino IDE 1.0

Dependencies
------------
* [Adafruit Industries's RGB 16x2 LCD Shield library](https://github.com/adafruit/Adafruit-RGB-LCD-Shield-Library)
* [Adafruit Industries's MCP23017 I2C Port Expander library](https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library)

Installing
----------
1. Download the most recent ZIP of the project
2. Extract the archive
3. Rename the folder to Hunt_The_Wumpus
3. Open the sketch in Arduino

Changes
-------
2013-08-29 JG - The program can now be compiled on Arduino 1.0.5
2013-08-29 JG - Rooms can only contain up to one hazard now (fixed the problem that hazards that were present in the same room didn't show up on the screen)
2013-08-29 JG - Added map.txt
