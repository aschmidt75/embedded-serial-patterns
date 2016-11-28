#!/usr/bin/env python

import sys
import serial

if len(sys.argv) < 2:
	print "%s <serialport>" % sys.argv[0]
	exit(1)

ser = serial.Serial(sys.argv[1], 115200);

print("--REQ");
ser.write(b'123456789012345');
print("--RESP (CTRL-C to stop)");

while True:
	sys.stdout.write(ser.read());
