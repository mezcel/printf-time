# Makefile

## declare vars
CC=gcc
CFLAGS=-Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

## install dependencies, then compile and build
all: packages ttyRosary gtkRosary

packages:
	# Debian Library dependencies
	sudo apt update
	sudo apt install libgtk-3-dev

ttyRosary:
	# Terminal App
	$(CC) "mainTTY.c" -o "ttyRosary"

gtkRosary:
	# Desktop Gui
	$(CC) "mainGtk3.c" -o "gtkRosary" $(CFLAGS)
