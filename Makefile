# Makefile

## declare vars
CC=gcc
CFLAGS=-Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

## install dependencies, then compile and build
all: packages ttyRosary gtkRosary

packages:
	## Debian Library dependencies
	sudo apt update
	sudo apt install libgtk-3-dev
	#sudo apt install mingw-w64

ttyRosary:
	## Terminal App
	$(CC) "mainTTY.c" -o "ttyRosary"
	#i686-w64-mingw32-gcc "mainTTY.c" -o "ttyRosary_Win.exe"

gtkRosary:
	## Desktop Gui
	$(CC) "mainGtk3.c" -o "gtkRosary" $(CFLAGS)
