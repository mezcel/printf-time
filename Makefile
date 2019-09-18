## Makefile (Automated Build)
CC=gcc
CFLAGS=-Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

all: ttyRosary ttyRosary_latin gtkRosary

ttyRosary: my_calendar.o my_csv_structs.o my_tty_ui.o mainTTY_nab.o
	gcc my_calendar.o my_csv_structs.o my_tty_ui.o mainTTY_nab.o -o "ttyRosary"

ttyRosary_latin: my_calendar.o my_json_structs.o my_tty_ui.o mainTTY_vulgate.o
	gcc my_calendar.o my_json_structs.o my_tty_ui.o mainTTY_vulgate.o -ljson-c -o "ttyRosary_latin"

gtkRosary: mainGtk3.o my_calendar.o my_csv_structs.o my_gtk3_api.o
	$(CC) mainGtk3.o my_calendar.o my_csv_structs.o my_gtk3_api.o $(CFLAGS) -o "gtkRosary"

debian:
	sudo apt install -y build-essential libgtk-3-dev gcc

my_calendar.o: sources/my_calendar.c headers/my_calendar.h
	gcc -c sources/my_calendar.c

my_csv_structs.o: sources/my_csv_structs.c headers/my_file_to_struct.h
	gcc -c sources/my_csv_structs.c

my_json_structs.o: sources/my_json_structs.c headers/my_file_to_struct.h
	gcc -c sources/my_json_structs.c

my_tty_ui.o: sources/my_tty_ui.c headers/my_tty_ui.h my_calendar.o my_csv_structs.o my_json_structs.o
	gcc -c sources/my_tty_ui.c

my_gtk3_api.o: sources/my_gtk3_api.c headers/my_gtk3_api.h my_calendar.o my_csv_structs.o my_json_structs.o my_tty_ui.o
	gcc -c sources/my_gtk3_api.c $(CFLAGS)

mainTTY_vulgate.o: mainTTY_vulgate.c my_calendar.o my_json_structs.o my_tty_ui.o
	gcc -c mainTTY_vulgate.c

mainTTY_nab.o: mainTTY_nab.c  my_calendar.o my_csv_structs.o my_tty_ui.o
	gcc -c mainTTY_nab.c

mainGtk3.o: mainGtk3.c my_calendar.o my_csv_structs.o my_json_structs.o my_tty_ui.o my_gtk3_api.o
	gcc -c mainGtk3.c $(CFLAGS)

clean:
	rm -f *.o ttyRosary ttyRosary_latin gtkRosary
