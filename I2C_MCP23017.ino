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

#include <Wire.h>
#include <Adafruit_MCP23X17.h>

int boardAddress = 0x00;

Adafruit_MCP23X17 mcp;

unsigned int myVals[] = \
{ \
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
  0B0000000000000000 \
};

void setup() 
{
  mcp.begin_I2C(boardAddress);              // join i2c bus
                                        // set all as output
  for (int i=0; i<=15; i++) mcp.pinMode(i, OUTPUT);
}

void loop() 
{

  for (int i = 0; i < sizeof(myVals)/sizeof(int); i++) 
  {
    mcp.writeGPIOAB(myVals[i]);
    delay(50);
  }
  
  exit(0);
    
}

