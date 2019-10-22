## Makefile (Automated Build)
CC=gcc
CFLAGS=-Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

all: ttyRosary gtkRosary

ttyRosary: my_calendar.o my_csv_structs.o my_json_structs.o my_tty_ui.o mainTTY.o
	## english and latin
	gcc my_calendar.o my_csv_structs.o my_json_structs.o my_tty_ui.o mainTTY.o -ljson-c -o "ttyRosary"
	#

ttyRosary_english: my_calendar.o my_csv_structs.o my_tty_ui.o mainTTY_nab.o
	## just english
	gcc my_calendar.o my_csv_structs.o my_tty_ui.o mainTTY_nab.o -o "ttyRosary_english"
	#

ttyRosary_latin: my_calendar.o my_json_structs.o my_tty_ui.o mainTTY_vulgate.o
	## just latin
	gcc my_calendar.o my_json_structs.o my_tty_ui.o mainTTY_vulgate.o -ljson-c -o "ttyRosary_latin"
	#

gtkRosary: mainGtk3.o my_calendar.o my_csv_structs.o my_json_structs.o  my_gtk3_api.o
	## GTK UI english
	$(CC) mainGtk3.o my_calendar.o my_csv_structs.o my_json_structs.o  my_gtk3_api.o $(CFLAGS) -ljson-c -o "gtkRosary"
	#

gtkRosary_english: mainGtk3_nab.o my_calendar.o my_csv_structs.o my_gtk3_api.o
	## GTK UI english
	$(CC) mainGtk3_nab.o my_calendar.o my_csv_structs.o my_gtk3_api.o $(CFLAGS) -o "gtkRosary_english"
	#

gtkRosary_latin: mainGtk3_vulgate.o my_calendar.o my_json_structs.o my_gtk3_api.o
	## GTK UI english
	$(CC) mainGtk3_vulgate.o my_calendar.o my_json_structs.o my_gtk3_api.o $(CFLAGS) -ljson-c -o "gtkRosary_latin"
	#

debug: debian ttyRosary_debug ttyRosary_latin_debug gtkRosary_debug
	## install debuging tools
	sudo apt install -y build-essential gcc libgtk-3-dev libjson-c-dev libjson-c-doc libjson-c3
	sudo apt install -y gdb glade
	#

ttyRosary_debug: my_calendar.o my_csv_structs.o my_tty_ui.o mainTTY_nab.o
	gcc -g my_calendar.o my_csv_structs.o my_tty_ui.o mainTTY_nab.o -o "ttyRosary_debug"
	#

ttyRosary_latin_debug: my_calendar.o my_json_structs.o my_tty_ui.o mainTTY_vulgate.o
	gcc -g my_calendar.o my_json_structs.o my_tty_ui.o mainTTY_vulgate.o -ljson-c -o "ttyRosary_latin_debug"
	#

gtkRosary_debug: mainGtk3.o my_calendar.o my_csv_structs.o my_gtk3_api.o
	$(CC) -g mainGtk3.o my_calendar.o my_csv_structs.o my_gtk3_api.o $(CFLAGS) -o "gtkRosary_debug"
	#

debian: ## Dependencies fo Debian 9 (Stretch) or later
	## GCC GDB GTK and JSON-C
	sudo apt install -y build-essential gcc libgtk-3-dev libjson-c-dev libjson-c-doc libjson-c3
	#

my_calendar.o: sources/my_calendar.c headers/my_calendar.h
	## compile and build my_calendar.c
	gcc -c sources/my_calendar.c
	#

my_csv_structs.o: sources/my_csv_structs.c headers/my_file_to_struct.h
	## compile and build my_csv_structs.c
	gcc -c sources/my_csv_structs.c
	#

my_json_structs.o: sources/my_json_structs.c headers/my_file_to_struct.h
	## compile and build my_json_structs.c
	gcc -c sources/my_json_structs.c
	#

my_tty_ui.o: sources/my_tty_ui.c headers/my_tty_ui.h my_calendar.o my_csv_structs.o my_json_structs.o
	## compile and build my_tty_ui.c
	gcc -c sources/my_tty_ui.c
	#

my_gtk3_api.o: sources/my_gtk3_api.c headers/my_gtk3_api.h my_calendar.o my_csv_structs.o my_json_structs.o my_tty_ui.o
	## compile and build my_gtk3_api.c
	gcc -c sources/my_gtk3_api.c $(CFLAGS)
	#

mainTTY_vulgate.o: mainTTY_vulgate.c my_calendar.o my_json_structs.o my_tty_ui.o
	## compile and build mainTTY_vulgate.c
	gcc -c mainTTY_vulgate.c
	#

mainTTY_nab.o: mainTTY_nab.c  my_calendar.o my_csv_structs.o my_tty_ui.o
	## compile and build mainTTY_nab.c
	gcc -c mainTTY_nab.c
	#

mainTTY.o: mainTTY.c  my_calendar.o my_csv_structs.o my_json_structs.o my_tty_ui.o
	## compile and build mainTTY.c
	gcc -c mainTTY.c
	#

mainGtk3.o: mainGtk3.c my_calendar.o my_csv_structs.o my_json_structs.o my_tty_ui.o my_gtk3_api.o
	## compile and build mainGtk3.c
	gcc -c mainGtk3.c $(CFLAGS)
	#

mainGtk3_nab.o: mainGtk3_nab.c my_calendar.o my_csv_structs.o my_tty_ui.o my_gtk3_api.o
	## compile and build mainGtk3_nab.c
	gcc -c mainGtk3_nab.c $(CFLAGS)
	#

mainGtk3_vulgate.o: mainGtk3_vulgate.c my_calendar.o my_json_structs.o my_tty_ui.o my_gtk3_api.o
	## compile and build mainGtk3_vulgate.c
	gcc -c mainGtk3_vulgate.c $(CFLAGS) -ljson-c
	#

clean:
	rm -f *.o ttyRosary ttyRosary_english ttyRosary_latin gtkRosary gtkRosary_english gtkRosary_latin ttyRosary_debug ttyRosary_latin_debug gtkRosary_debug
	#
