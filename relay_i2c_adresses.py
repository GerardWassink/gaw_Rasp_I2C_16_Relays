#!/usr/bin/python

# Device address - defaults to 0x20
DEVICE		= 0x20					# Device address (A0-A2)


# Adresses for IOCON.BANK = 0 (default at startup and after reset)

# GPIO bank A
IODIRA		= 0x00					# Pin direction register
IPOLA		= 0x02					# Input polarity port register
GPINTENA	= 0x04					# Interrupt on change register
DEFVALA		= 0x06					# compare for interrupt register
INTCONA		= 0x08					# Interrupt on change control register
IOCON		= 0x0A					# Configuration register
GPPUA		= 0x0C					# ?? register
INTFA		= 0x0E					# ?? register
INTCAPA		= 0x10					# ?? register
GPIOA		= 0x12					# ?? register
OLATA		= 0x14					# ?? register

# GPIO bank B
IODIRB		= 0x01					# Pin direction register
IPOLB		= 0x03					# ?? register
GPINTENB	= 0x05					# ?? register
DEFVALB		= 0x07					# ?? register
INTCONB		= 0x09					# ?? register
IOCON		= 0x0B					# ?? register
GPPUB		= 0x0C					# ?? register
INTFB		= 0x0E					# ?? register
INTCAPB		= 0x11					# ?? register
GPIOB		= 0x13					# ?? register
OLATB		= 0x15					# ?? register

# IOCON bit definitions
BANK		= 0b10000000			# Bank bit
MIRROR		= 0b01000000			# Mirror bit
SEQOP		= 0b00100000			# Sequential operations bit
DISSLW		= 0b00010000			# Slew rate control bit for SLA output
HAEN		= 0b00001000			# Hardware Address Enable (only on MCP23S17 chip)
ODR			= 0b00000100			# Open Drain Output
INTPOL		= 0b00000010			# Interrupt Polarity
NOTUSED		= 0b00000000			# Bit not used

