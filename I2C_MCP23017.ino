/* ------------------------------------------------------------------------- *
 * Name   : I2C_MCP23017
 * Author : Gerard Wassink
 * Date   : February 25, 2017
 * Purpose: Test I2C relay driver card
 * ------------------------------------------------------------------------- *
 *
 * ------------------------------------------------------------------------- *
 *             GNU LICENSE CONDITIONS
 * ------------------------------------------------------------------------- *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * ------------------------------------------------------------------------- *
 *       Copyright (C) 2017 Gerard Wassink
 * ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- *
 *       Switch debugging on / off (compiler directives)
 * ------------------------------------------------------------------------- */
#define DEBUG 0
#if DEBUG == 1
  #define debugstart(x) Serial.begin(x)
  #define debug(x) Serial.print(x)
  #define debugln(x) Serial.println(x)
#else
  #define debugstart(x)
  #define debug(x)
  #define debugln(x)
#endif

#include <Wire.h>
#include <Adafruit_MCP23X17.h>

#include <Wire.h>                               // I2C comms library
#include <LiquidCrystal_I2C.h>                  // LCD library

/* ------------------------------------------------------------------------- *
 *       Create objects with addres(ses) for the multiplexer MCP23017
 * ------------------------------------------------------------------------- */
uint8_t mcpAddress = 0x20;                      // Multiplexer address
Adafruit_MCP23X17 mcp;                          // Multiplexer object

/* ------------------------------------------------------------------------- *
 *       Create objects with addres(ses) for the LCD screen
 * ------------------------------------------------------------------------- */
uint8_t displayAddress = 0x25;                  // Display address
LiquidCrystal_I2C display(0x25,20,4);           // Initialize display

char scrLines[4][21];                           // Scroll Array

int rptButton = 4;
/* ------------------------------------------------------------------------- *
 *       Array with test values, used in setup() only
 * ------------------------------------------------------------------------- */
unsigned int myVals[] = \
{ \

  0B0000000000000000, \

  0B0000000110000000, \
  0B0000001111000000, \
  0B0000011111100000, \
  0B0000111111110000, \
  0B0001111111111000, \
  0B0011111111111100, \
  0B0111111111111110, \
  0B1111111111111111, \
  0B1111111001111111, \
  0B1111110000111111, \
  0B1111100000011111, \
  0B1111000000001111, \
  0B1110000000000111, \
  0B1100000000000011, \
  0B1000000000000001, \

  0B0000000000000000, \

  0B1000000000000001, \
  0B1100000000000011, \
  0B1110000000000111, \
  0B1111000000001111, \
  0B1111100000011111, \
  0B1111110000111111, \
  0B1111111001111111, \
  0B1111111111111111, \
  0B0111111111111110, \
  0B0011111111111100, \
  0B0001111111111000, \
  0B0000111111110000, \
  0B0000011111100000, \
  0B0000001111000000, \
  0B0000000110000000, \

  0B0000000000000000, \

  0B0000000110000000, \
  0B0000001111000000, \
  0B0000011111100000, \
  0B0000111111110000, \
  0B0001111111111000, \
  0B0011111111111100, \
  0B0111111111111110, \
  0B1111111111111111, \
  0B0111111111111110, \
  0B0011111111111100, \
  0B0001111111111000, \
  0B0000111111110000, \
  0B0000011111100000, \
  0B0000001111000000, \
  0B0000000110000000, \

  0B0000000000000000, \

  0B1000000000000000, \
  0B0100000000000000, \
  0B0010000000000000, \
  0B0001000000000000, \
  0B0000100000000000, \
  0B0000010000000000, \
  0B0000001000000000, \
  0B0000000100000000, \
  0B0000000010000000, \
  0B0000000001000000, \
  0B0000000000100000, \
  0B0000000000010000, \
  0B0000000000001000, \
  0B0000000000000100, \
  0B0000000000000010, \
  0B0000000000000001, \
  0B0000000000000010, \
  0B0000000000000100, \
  0B0000000000001000, \
  0B0000000000010000, \
  0B0000000000100000, \
  0B0000000001000000, \
  0B0000000010000000, \
  0B0000000100000000, \
  0B0000001000000000, \
  0B0000010000000000, \
  0B0000100000000000, \
  0B0001000000000000, \
  0B0010000000000000, \
  0B0100000000000000, \
  0B1000000000000000, \

  0B0000000000000000  \
};


/* ------------------------------------------------------------------------- *
 *       Initial section                                             setup()
 * ------------------------------------------------------------------------- */
void setup() 
{
  debugstart(9600);
  debugln("Setup starts");
  
  pinMode(rptButton, INPUT_PULLUP);
  
  display.init();                               // Initialize display
  display.backlight();                          // Backlights on by default
  arrayInit();                                  // Initialize scrollArray

  debugln("Initializing Multiplexer MCP23017");
  if (!mcp.begin_I2C(mcpAddress))               // join i2c bus
  {
    LCD_scroll(display, F("MCP init failed     "));
    while(1);
  }
                                                // set all multiplexer pins
                                                //   as output
  for (int i=0; i<=15; i++) mcp.pinMode(i, OUTPUT);

  LCD_scroll(display, F("Testing every pin   "));
  for (int i=0; i<=15; i++) {
    mcp.digitalWrite(i,1);
    delay(250);
  }
  for (int i=0; i<=15; i++) {
    mcp.digitalWrite(i,0);
    delay(250);
  }

  LCD_scroll(display, F("Start test?         "));
  LCD_scroll(display, F("Press button!       "));
}

/* ------------------------------------------------------------------------- *
 *       Repeating section                                            loop()
 * ------------------------------------------------------------------------- */
void loop() 
{
  while(digitalRead(rptButton));

  debugln( F("Start loop()        ") );
  for (int i = 0; i < sizeof(myVals)/sizeof(int); i++) 
  {
    mcp.writeGPIOAB(myVals[i]);
    delay(50);
  }
  debugln( F("End loop()          ") );

  LCD_scroll(display, F("Test again?         "));
  LCD_scroll(display, F("Press button!       "));
}
  

/* ------------------------------------------------------------------------- *
 *       Routine to display stuff on the display of choice     LCD_display()
 * ------------------------------------------------------------------------- */
void LCD_display(LiquidCrystal_I2C screen, int row, int col, String text) 
{
    screen.setCursor(col, row);
    screen.print(text);
}


/* ------------------------------------------------------------------------- *
 *       Initialize array for display                            arrayInit()
 * ------------------------------------------------------------------------- */
void arrayInit() 
{
  for (int r=0; r<=3; r++) {
    for (int c=0; c<=19; c++) {
      scrLines[r][c] = ' ';
    }
    scrLines[r][20] = '\0';
  }
}
  

/* ------------------------------------------------------------------------- *
 *       Routine to scroll text on the display of choice        LCD_scroll()
 * ------------------------------------------------------------------------- */
void LCD_scroll(LiquidCrystal_I2C screen, String text) 
{
  for (int r=0; r<=2; r++) {
    for (int c=0; c<=20; c++) {
      scrLines[r][c] = scrLines[r+1][c];
    }
  }

  for (int c=0; c<=20; c++) {
    scrLines[3][c] = text[c];
  }

  for (int i=0; i <=3; i++) {
    screen.setCursor( 0, i );
    screen.print( scrLines[i] );
  }

  screen.setCursor(0, 3);
  screen.print(text);
}

