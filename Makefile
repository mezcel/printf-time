# Makefile

# declare vars
CC=gcc
CFLAGS=-c -Wall

all: cRosary

cRosary: main.o
	#gcc "main.c" -o "mainTTY"
	$(CC) main.o -o cRosary

clean:
	rm -rf *o cRosary
