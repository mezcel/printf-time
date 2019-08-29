# project-design-plan

```v0.3.?```

## About:

A C program that displays queried text from a CSV database in a CLI/TTY screen interface. Data from the CSV files are parsed into type defined structs using GCC standard libraries. The app reads as a  booklet loop or a slideshow loop. The user navigates forwards and backwards using the [enter] key and the key sequence ["b" + enter].

The subject is a scripture Rosary. Scriptures are quoted from the New American Bible (NAB). The Rosary's starting point is set to 1 of 4 mysteries, depending on which day of the week it is.

## Inspiration:

This is the 5th programming platform version in my Rosary App series. Previous language versions were: [C#/MySql/.NET](https://github.com/mezcel/rosary.net) (a WinForm and a WPF/WCF version), [JqueryMobile/Json](https://github.com/mezcel/electron-container) (an Electron and Heroku version), [Bash/Json](https://github.com/mezcel/jq-tput-terminal) (for Arch & Debian), [Python/Json](https://github.com/mezcel/python-curses), and now the [C/CSV](https://github.com/mezcel/printf-time) version. It aims to be the lightest and most cross compatible with minimal dependencies. It also ams to be portable and extensible.

## Project Status:

#### v0.2.? (Outdated Demo Preview)

* [outdated demo](https://asciinema.org/a/262232) Working stop point.
    * quick preview
    * the demo ui is outdated but the mechanics are the same.
    * [![asciicast](https://asciinema.org/a/262232.svg)](https://asciinema.org/a/262232)

---

## Development

#### v0.3 (current development)

- Database: complete
- Import Database: complete
- Database Query: complete

User Interface:

    * inputs: complete
    * outputs:
        * Linux: complete/pending (display beautification will perpetually be updated)
        * MinGW: I have not completed the "detect OS" logic yet

Documentation: incomplete (under construction)

#### future version considerations

* Add a Feast day calendar

## Install/Compile Dependencies:

#### Command line tty version
```bash
## Compile:
gcc main.c -o main

## RUN:
./main

## Use Navigate:
#  [Enter] to navigate forward 1 step
#  "b" and then [Enter] in sequence to navigate backwards
```

#### Desktop GUI window version, Gtk
```./gtk-wip/```

```bash
## Install the gtk dependency (Debian)
sudo apt install libgtk-3-dev

## Complile:
## gcc -Wall -o "mainGtk" "mainGtk.c" `pkg-config --cflags --libs gtk+-2.0`
gcc -o mainGlade mainGlade.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

## RUN:
./mainGtk
```

#### Runtime Environment

* [MinGW](http://www.mingw.org/) or Linux
* Command line interface (CLI) / Shell Terminal
* Xorg (linux) or Xlaunch (Win10/WLS)

#### Developer Environment (debug/mod)

* [MinGW](http://www.mingw.org/) or Linux (x86 or x64)
* GCC v6+
* GDB debugger (optional yet recommended)
* git (version control)
* Glade (a gui drawing tool)
* a text editor (I use Geany for everything)
	* Geany macros
	* compile:	gcc -Wall -c "%f" `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
	* build:	gcc -Wall -o "%e" "%f" `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

---

## Compile

```sh
## Compile in Debian and make it usable on a Win10
sudo apt install mingw-w64
i686-w64-mingw32-gcc -o my-executable-file.exe main.c

## Compile in Win10 with MinGW installed
gcc -o my-executable-file.exe main.c
```
