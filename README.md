<!-- pandoc formatting
title: 'printf-time'
subtitle: 'A scripture rosary written in C for Linux OS's'
author: 'Mezcel'
date: 'Jan 1, 2019'
description: 'Scripture rosary using English and Latin Bible text.'
lang: en-US
-->

# printf-time

## About:

A scripture rosary written in C/GCC for the GTK and the TTY. It uses both a CSV and a JSON Database. The CSV contains NAB quotes in English and the JSON contains Vulgate quotes in Latin.

Developed for use on Linux or WLS.
* All availble features work on Debian Linux and WLS.
* Uses [json-c](https://github.com/json-c/json-c) from the Debian repo.
	* Only the latin translation needs json.

* Also works on Win10 with Visual Studio C++ installed.
	* The Gtk feature does not work outside of WLS on Win10.
	* The compiled ```.exe``` works in Win10 Powershell.
	* The UI is limited where only the ```enter``` and ```q``` keys works, and the user can only navigate forward. No changes occur when the screen is resized.
## GUI Options:

> This app can be run within a terminal or a desktop environment gui.

| English CLI Version | English GTK3 Version |
| :---: | :---: |
| Navigate using Vi kebindings or gamer keys. | The user navigates with push-button widget objects. |
| Outdated screenshot was taken on a Debian WLS (v0.2.?) ![tty-screenshot](img/tty-screenshot.gif) | Outdated screenshot was taken on a i686 Debian (v0.2.?) ![gtk-screenshot](img/screenshot.gif) |
| [A newer-ish animated demo](https://asciinema.org/a/278468) on a i686 Debian (v0.3.5) [![asciicast](https://asciinema.org/a/278468.svg)](https://asciinema.org/a/278468) | - |

---

## Compile on Debian

```sh
## build and compile everything

make

## the following executable binaries will be generated:
## 	ttyRosary and gtkRosary
```

### Run
```sh
## TTY App

./ttyRosary		## NAB English, using a CSV database
./ttyRosary -v		## Vulgate Latin, using a JSON database

## GTK App

./gtkRosary		## NAB English
./gtkRosary -v		## Vulgate Latin
```

### Dependencies

If you get a compile error from the make build: ```#include <json-c/json.h>```, then use ```make debian``` to install potentially missing dependencies. This applies only to compilation on Debian based distros.

```sh
## Get dependencies for Debian 9 or newer
make debian

## debian libjson-c dependencies
sudo apt install autotools-dev debhelper dh-autoreconf dh-exec

## debian stretch (libs)
sudo apt install libjson-c-dev libjson-c-doc libjson-c3

## man page (manual intervention required)
sudo apt install groff pandoc
```

## Compile on Win10
* [Configure VS Code for Microsoft C++](https://code.visualstudio.com/docs/cpp/config-msvc)
* [Visual Studio](https://visualstudio.microsoft.com/downloads/#other)

```ps1
## clean previous builds
Remove-Item *.obj
Remove-Item *.exe

## Compile and build
cl sources\my_calendar.c
cl sources\my_csv_structs.c
cl sources\my_tty_ui.c

cl mainTTY.c my_calendar.obj my_csv_structs.obj my_tty_ui.obj

## run
.\mainTTY.exe
```
---

# Development Evolution:

This is the 5th program language version in my Rosary App series.

Previous versions were:

| .NET/Windows OS | NodeJS/Electron | BASH/GNU | Python (Win/Linux) |
| --- | --- | --- | --- |
|[git](https://github.com/mezcel/rosary.net)|[git](https://github.com/mezcel/electron-container)|[git](https://github.com/mezcel/jq-tput-terminal)|[git](https://github.com/mezcel/python-curses)|
| Windows | cross platform with a web browser | Linux | cross platform with python|
| MySql Database | JSON Database | JSON Database | JSON Database |
| English and Latin | English and Latin | English and Latin | English only|
|a WinForm version and a WPF/WCF version|an Electron and Heroku version|shell on Arch & Debian| a curses app |
| [project design page](https://mezcel.wixsite.com/rosary) ```developed on Windows 9``` | Uses Jquery Mobile and/or Electron. Has variable color themes, liturgical calendar and feast day calculations. | It has variable tty colors, liturgical calendar calculations, windows sizing. Curses bases | just a TTY/Cli App|
| no audio | audio theme song | audio (curated event triggered Libre soundtrack) | no audio |
| lan | internet scraped mass readings | internet scraped mass readings | no interactive networking features |
| multi user / multi session / group synchronization | multi user / multi session / group synchronization | single user | single user |

---

## Project Status:

### v0.3.6.? (current development)

* Refactored the code to allow for Win10 compilation.

### Runtime Environment

* Linux, [MinGW](http://www.mingw.org/) or Win10 Powershell with Visual Studio C++
* Command line interface (CLI) / Shell Terminal
* Xorg (Debian linux) or Xlaunch (Win10/WLS)

### Developer Environment (debug/mod)

* [MinGW](http://www.mingw.org/) or Linux (x86 or x64)
	* this app was developed on Debian WLS and tested on a real Linux
* GCC v6+
* Glade (a gui drawing tool)
* any text editor (I use Geany for everything)
	* Geany macros for quick and easy gtk3 development
	* compile:	gcc -Wall -c "%f" `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
	* build:	gcc -Wall -o "%e" "%f" `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

---

Win10

```sh
## Compile in Debian and make it usable on a Win10

sudo apt install mingw-w64
i686-w64-mingw32-gcc "main.c" -o "my-executable-file.exe"

## Compile in Win10 with MinGW installed

gcc "main.c" -o "my-executable-file.exe "
```
