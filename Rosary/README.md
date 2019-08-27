# project-design-plan

```v0.3.?```

## About:

A C program that displays queried text from a CSV database in a CLI/TTY screen interface. Data from the CSV files are parsed into type defined structs using GCC standard libraries. The app reads as a  booklet loop or a slideshow loop. The user navigates forwards and backwards using the [enter] key and the key sequence ["b" + enter].

The subject is a scripture Rosary. Scriptures are quoted from the New American Bible (NAB). The Rosary's starting point is set to 1 of 4 mysteries, depending on which day of the week it is.

## Inspiration:

This app functionally resembles a Rosary Python app I made prior to this project. This the 5th programming platform in my Rosary App series. Previous languages were: [C#/MySql/.NET](https://github.com/mezcel/rosary.net) (a WinForm and a WPF/WCF version), [JqueryMobile/Json](https://github.com/mezcel/electron-container) (an Electron and Heroku version), [Bash/Json](https://github.com/mezcel/jq-tput-terminal) (for Arch & Debian), [Python/Json](https://github.com/mezcel/python-curses), and now [C/CSV](https://github.com/mezcel/printf-time). It aims to be the lightest and most cross compatible with minimal dependencies. It also ams to be portable and extensible.

## Project Status:

#### v0.2.? (Demo Preview)

* [outdated demo](https://asciinema.org/a/262232) Working stop point.
    * quick preview
    * the ui is outdated but the mechanics are the same.
    * [![asciicast](https://asciinema.org/a/262232.svg)](https://asciinema.org/a/262232)

---
## Development

#### v0.3 (current development)

Database: complete

Import Database: complete

Database Query: complete

User Interface:

    * inputs: complete
    * outputs: complete/pending (display beautification will perpetually be updated)

Documentation: incomplete (under construction)

#### future version considerations

Desktop GUI: Windowed Gtk App

Additional Functional Feature: Feast day calendar

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
## Complile:
gcc -Wall -o "mainGtk" "mainGtk.c" `pkg-config --cflags --libs gtk+-2.0`

## RUN:
./mainGtk
```

#### Runtime Environment

* MinGW or Linux
* Command line interface (CLI) / Shell Terminal

#### Developer Environment (debug/mod)

* MinGW or Linux
* GCC v6+
* GDB debugger
* git (version control)
* a text editor
