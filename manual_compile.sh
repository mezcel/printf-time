#!/bin/bash

clear

cd sources/
rm *.o

gcc -c my_calendar.c

gcc -c my_csv_structs.c

gcc -c my_tty_ui.c my_calendar.c

cd ../
#gcc -c mainTTY.c sources/my_calendar.o sources/my_csv_structs.o sources/my_tty_ui.o
gcc mainTTY.c sources/my_calendar.o sources/my_csv_structs.o sources/my_tty_ui.o
