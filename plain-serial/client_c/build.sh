#!/bin/bash

gcc -Isrc/ -Ilib/ -Ilib/arduino-serial src/main.c lib/arduino-serial/arduino-serial-lib.c -o plain_serial_c

