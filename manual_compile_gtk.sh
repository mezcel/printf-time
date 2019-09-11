#!/bin/bash

clear

cd sources/
rm *.o

gcc -c my_calendar.c

gcc -c my_csv_structs.c

gcc -c my_gtk3_api.c my_calendar.c `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

cd ../
gcc mainGtk3.c sources/my_calendar.o sources/my_csv_structs.o sources/my_gtk3_api.o `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
