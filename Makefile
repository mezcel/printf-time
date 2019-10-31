## Makefile (Automated Build)
CC=gcc
CFLAGS=-Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

all: ttyRosary gtkRosary
	## ###################################################################
	## Use the -v flag to run using the optional Latin translation feature
	##   ex: ./ttyRosary -v
	##   ex: ./gtkRosary -v
	## ###################################################################

## Main binaries

ttyRosary: my_calendar.o my_csv_structs.o my_json_structs.o my_tty_ui.o mainTTY.o
	## english and latin
	gcc my_calendar.o my_csv_structs.o my_json_structs.o my_tty_ui.o mainTTY.o -ljson-c -o "ttyRosary"
	#

gtkRosary: mainGtk3.o my_calendar.o my_csv_structs.o my_json_structs.o my_gtk3_api.o
	## GTK UI english and latin
	$(CC) mainGtk3.o my_calendar.o my_csv_structs.o my_json_structs.o  my_gtk3_api.o $(CFLAGS) -ljson-c -o "gtkRosary"
	#

## Compile binary libraries

debian:
	## Dependencies for Debian 9 (Stretch) or later
	sudo apt install -y build-essential gcc libgtk-3-dev libjson-c-dev libjson-c-doc libjson-c3
	sudo apt install -y glade
	#

archlinux:
	## Dependencies for Archlinux
	sudo pacman -Sy base base-devel gcc gtk3
	# sudo pacman -Sy glade
	#

my_calendar.o: sources/my_calendar.c headers/my_calendar.h
	## compile and build "my_calendar.c"
	gcc -c sources/my_calendar.c
	#

my_csv_structs.o: sources/my_csv_structs.c headers/my_file_to_struct.h
	## compile and build "my_csv_structs.c"
	gcc -c sources/my_csv_structs.c
	#

my_json_structs.o: sources/my_json_structs.c headers/my_file_to_struct.h
	## compile and build "my_json_structs.c"
	gcc -c sources/my_json_structs.c
	#

my_tty_ui.o: sources/my_tty_ui.c headers/my_tty_ui.h my_calendar.o my_csv_structs.o my_json_structs.o
	## compile and "build my_tty_ui.c"
	gcc -c sources/my_tty_ui.c
	#

my_gtk3_api.o: sources/my_gtk3_api.c headers/my_gtk3_api.h my_calendar.o my_csv_structs.o my_json_structs.o my_tty_ui.o
	## compile and build "my_gtk3_api.c"
	gcc -c sources/my_gtk3_api.c $(CFLAGS)
	#

mainTTY.o: mainTTY.c  my_calendar.o my_csv_structs.o my_json_structs.o my_tty_ui.o
	## compile and build "mainTTY.c"
	gcc -c mainTTY.c
	#

mainGtk3.o: mainGtk3.c my_calendar.o my_csv_structs.o my_json_structs.o my_tty_ui.o my_gtk3_api.o
	## compile and build "mainGtk3.c"
	gcc -c mainGtk3.c $(CFLAGS)
	#

clean:
	## removing any precompiled binaries
	rm -f *.o ttyRosary gtkRosary *.o
	#
