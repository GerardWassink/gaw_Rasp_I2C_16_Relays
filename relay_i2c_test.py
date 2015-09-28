#!/usr/bin/python

import smbus
import time
import gawRelayHandler

# Device address - defaults to 0x20
boardAddress = 0x20				# Device address (20-27)

relayHandler = gawRelayHandler.relayHandler()

#for MyData in range(0,256):
while 1:
	for MyData in [ \
				"00000000", \
				"10000001", \
				"11000011", \
				"11100111", \
				"11111111", \
				"01111110", \
				"00111100", \
				"00011000", \
				"00000000", \
				"00011000", \
				"00111100", \
				"01111110", \
				"11111111", \
				"11100111", \
				"11000011", \
				"00000000", \
				"10000000", \
				"01000000", \
				"00100000", \
				"00010000", \
				"00001000", \
				"00000100", \
				"00000010", \
				"00000001", \
				"00000001", \
				"00000010", \
				"00000100", \
				"00001000", \
				"00010000", \
				"00100000", \
				"01000000", \
				"10000000", \
				"00000000" \
				]:
								# Count from 1 to 8 which in binary will count
								# from 001 to 111
		for pos in range(0,8):
			EenOfNul = int(MyData[pos])
			relayHandler.setRelay(boardAddress,pos,EenOfNul)

		time.sleep(0.08)

