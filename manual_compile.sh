#!/bin/bash

clear

rm -f *.o

## compile CLI version
gcc -c sources/my_calendar.c
gcc -c sources/my_csv_structs.c
gcc -c sources/my_tty_ui.c -l my_calendar.o
gcc mainTTY.c my_calendar.o my_csv_structs.o my_tty_ui.o

## compile Gtk version

gcc -c sources/my_calendar.c
gcc -c sources/my_csv_structs.c
gcc -c sources/my_gtk3_api.c my_calendar.c `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
gcc mainGtk3.c my_calendar.o my_csv_structs.o sources/my_gtk3_api.o `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

rm -f *.o
