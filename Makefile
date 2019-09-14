## Makefile (Automated Build)
#
# Detect changes in my sources/headers and compile them into objects
# compile an executable linking pre-compiled object files
# Output:
#	ttyRosary executable
#	gtkRosary executable
#
# Cli Instructions:
#	option 1: make
#	option 2: make ttyRosary
#	option 3: make gtkRosary

## declare variables

CC=gcc
CFLAGS=-Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

all: gnu_dependency ttyRosary gtkRosary

gnu_dependency:
	sudo apt install -y build-essential libgtk-3-dev gcc

## Executable

ttyRosary: mainTTY.o my_calendar.o my_csv_structs.o my_tty_ui.o
	$(CC) mainTTY.o my_calendar.o my_csv_structs.o my_tty_ui.o -o "ttyRosary"

## used for gdb (optional)
ttyRosary_debug: mainTTY.o my_calendar.o my_csv_structs.o my_tty_ui.o
	$(CC) -g mainTTY.o my_calendar.o my_csv_structs.o my_tty_ui.o -o "ttyRosary_debug"

gtkRosary: mainGtk3.o my_calendar.o my_csv_structs.o my_gtk3_api.o
	$(CC) mainGtk3.o my_calendar.o my_csv_structs.o my_gtk3_api.o $(CFLAGS) -o "gtkRosary"

## used for gdb (optional)
gtkRosary_debug: mainGtk3.o my_calendar.o my_csv_structs.o my_gtk3_api.o
	$(CC) -g mainGtk3.o my_calendar.o my_csv_structs.o my_gtk3_api.o $(CFLAGS) -o "gtkRosary_debug"

## Libraries for both apps

my_calendar.o: sources/my_calendar.c headers/my_calendar.h
	$(CC) -c sources/my_calendar.c

my_csv_structs.o: sources/my_csv_structs.c headers/my_csv_structs.h
	$(CC) -c sources/my_csv_structs.c

## TTY app

my_tty_ui.o: sources/my_tty_ui.c headers/my_tty_ui.h my_calendar.o
	$(CC) -c sources/my_tty_ui.c

mainTTY.o: mainTTY.c my_calendar.o my_csv_structs.o my_tty_ui.o
	$(CC) -c mainTTY.c

## GTK3 app

my_gtk3_api.o: sources/my_gtk3_api.c headers/my_gtk3_api.h my_calendar.o my_csv_structs.o
	$(CC) -c sources/my_gtk3_api.c $(CFLAGS)

mainGtk3.o: mainGtk3.c my_calendar.o my_csv_structs.o my_gtk3_api.o
	$(CC) -c mainGtk3.c $(CFLAGS)

## Restore/Clear

clean:
	rm -f *.o ttyRosary gtkRosary ttyRosary_debug gtkRosary_debug
