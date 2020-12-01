## GNU Linux	make (GCC)
## MS Windows	nmake (CL)

CC=gcc
CFLAGS = -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

all: notes ttyRosary gtkRosary ttyBashrc manpage

## Notes
notes:
	##
	## Makefile note:
	##
	## Install dependencies:
	##	sudo make debian
	##	sudo make archlinux
	##
	## ###################################################################
	## Use the "-v" flag to use the optional Latin translation feature
	##   ex: ./ttyRosary -v
	##   ex: ./gtkRosary -v
	## ###################################################################
	##

################
## Main Binaries
################


## english and latin
ttyRosary: my_calendar.o my_csv_structs.o my_json_structs.o my_tty_ui.o my_tty_ui_posix.o mainTTY.o
	$(CC) my_calendar.o my_csv_structs.o my_json_structs.o my_tty_ui.o my_tty_ui_posix.o mainTTY.o -ljson-c -o "ttyRosary"

## GTK UI english and latin
gtkRosary: mainGtk3.o my_calendar.o my_csv_structs.o my_json_structs.o my_gtk3_api.o
	$(CC) mainGtk3.o my_calendar.o my_csv_structs.o my_json_structs.o  my_gtk3_api.o $(CFLAGS) -ljson-c -o "gtkRosary"

## holiday season bash environment splash
ttyBashrc: my_calendar.o my_csv_structs.o  my_tty_ui.o mainBashrc.o
	$(CC) my_calendar.o my_csv_structs.o my_tty_ui.o mainBashrc.o -o "ttyBashrc"
	bash sources/make-holiday-bashrc.sh

###########################
## Compile binary libraries
###########################

my_calendar.o: sources/my_calendar.c headers/my_calendar.h
	## compile and build "my_calendar.c"
	$(CC) -c sources/my_calendar.c
	#

my_csv_structs.o: sources/my_csv_structs.c headers/my_file_to_struct.h
	## compile and build "my_csv_structs.c"
	$(CC) -c sources/my_csv_structs.c
	#

my_json_structs.o: sources/my_json_structs.c headers/my_file_to_struct.h
	## compile and build "my_json_structs.c"
	$(CC) -c sources/my_json_structs.c
	#

my_tty_ui.o: sources/my_tty_ui.c headers/my_tty_ui.h my_calendar.o my_csv_structs.o my_json_structs.o
	## compile and "build my_tty_ui.c"
	$(CC) -c sources/my_tty_ui.c
	#

my_tty_ui_posix.o: sources/my_tty_ui_posix.c headers/my_tty_ui.h my_calendar.o my_csv_structs.o my_json_structs.o
	## compile and "build my_tty_ui_posix.c"
	$(CC) -c sources/my_tty_ui_posix.c
	#

my_gtk3_api.o: sources/my_gtk3_api.c headers/my_gtk3_api.h my_calendar.o my_csv_structs.o my_json_structs.o
	## compile and build "my_gtk3_api.c"
	$(CC) -c sources/my_gtk3_api.c $(CFLAGS)
	#

mainTTY.o: mainTTY.c  my_calendar.o my_csv_structs.o my_json_structs.o my_tty_ui.o my_tty_ui_posix.o
	## compile and build "mainTTY.c"
	$(CC) -c mainTTY.c
	#

mainGtk3.o: mainGtk3.c my_calendar.o my_csv_structs.o my_json_structs.o my_gtk3_api.o
	## compile and build "mainGtk3.c"
	$(CC) -c mainGtk3.c $(CFLAGS)
	#

mainBashrc.o: mainBashrc.c  my_calendar.o my_csv_structs.o my_tty_ui.o
	## compile and build "mainBashrc.c"
	$(CC) -c mainBashrc.c
	#

#####################
## Linux dependencies
#####################

debian:
	## Dependencies for Debian 9 (Stretch) or later
	sudo apt install -y build-essential gcc libgtk-3-dev libjson-c-dev libjson-c-doc libjson-c3
	sh sources/make-Holiday-Alias.sh
	# sudo apt install -y glade
	#

archlinux:
	## Dependencies for Archlinux
	sudo pacman -Sy --needed base base-devel gcc gtk3
	# sudo pacman -Sy glade
	#

tclinux:
	## Dependencies for Tiny Core Linux (busybox)
	tce-load -wil compiletc.tcz
	tce-load -wil json-c-dev.tcz
	tce-load -wil gtk3-dev.tcz
	# tce-load -wil glade-dev.tcz
	#

alpine:
	## Dependencies for Alpine Linux (busybox, chrony)
	sudo apk add build-base
	sudo apk add json-c-dev
	sudo apk add gtk+3.0-dev
	#

manpage: .manpage.md
	## generate a man file with Pandoc from an Rmarkdown file
	## global man page
	# pandoc .manpage.md -s -t man > /usr/bin/printf-time
	## local man page
	pandoc .manpage.md -s -t man > printf-time

clean:
	## removing any precompiled binaries (Linux)
	rm -f *.o ttyRosary gtkRosary ttyBashrc *.o *.out *.obj *.exe
	bash sources/clean-holiday-bashrc.sh
	#

#####################
## Windows 10 nmake
#####################

nclean:
	:::: clean previous *.obj and *.exe builds (Win10)
	@IF EXIST *.obj DEL /F *.obj;
	@IF EXIST *.exe DEL /F *.exe;
	::
	:::: clean vscode related files
	@IF EXIST *.obj DEL /F *.ilk;
	@IF EXIST *.exe DEL /F *.pdb;
	::
	:::: batch script tp perform clean
	::Makefile_win.bat clean

build:
	:::: compile ttyRosary
	cl /c sources\my_calendar.c
	cl /c sources\my_csv_structs.c
	cl /c sources\my_tty_ui.c
	::
	:::: build executable ttyRosary.exe
	cl mainTTY.c my_calendar.obj my_csv_structs.obj my_tty_ui.obj /Fe"ttyRosary.exe"
	::
	:::: batch script to perform build
	::Makefile_win.bat build
