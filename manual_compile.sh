#!/bin/bash

## install/update dependencies (Debian)

sudo apt install -y build-essential libgtk-3-dev gcc

clear

## clear any previous builds
rm -f *.o ttyRosary gtkRosary ttyRosary_debug gtkRosary_debug

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

## clear object files

rm -f *.o
