# Makefile

## declare vars
CC=gcc
CFLAGS=-Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

all: ttyRosary gtkRosary

ttyRosary:
	$(CC) "mainTTY.c" -o "ttyRosary"

gtkRosary:
	$(CC) "mainGtk3.c" -o "gtkRosary" $(CFLAGS)
