# printf-time

### About:

branch: ```v0.3.2.?```

The theme of this app is an embellished scripture Rosary slideshow. Scriptures are quoted from the New American Bible (NAB). The Rosary's starting point is set to 1 of 4 mysteries, depending on which day of the week it is.

This project is an exercise in using the C structured programming language. The TTY component of this project is intended to be __portable__, ___extensible___, and ___cross platform___. One usecase is porting its functionality features into an OOP Gtk API.

This app is still under construction, but many of its features are functional and demo-able.

### Inspiration:

This is the 5th programming platform version in my Rosary App series. Previous language versions were: [C#/MySql/.NET](https://github.com/mezcel/rosary.net) (a WinForm and a WPF/WCF version), [JqueryMobile/Json](https://github.com/mezcel/electron-container) (an Electron and Heroku version), [Bash/Json](https://github.com/mezcel/jq-tput-terminal) (for Arch & Debian), [Python/Json](https://github.com/mezcel/python-curses), and now the [C/CSV](https://github.com/mezcel/printf-time) version.

### Deliverables:

##### 1. A TTY version

A C program that displays queried text from a CSV database in a CLI/TTY screen interface. Data from the CSV files are parsed into type defined structs using GCC standard libraries. The app reads as a  booklet loop or a slideshow loop. The user navigates forwards and backwards using the [enter] key and the key sequence ["b" + enter].

* Terminal screen app ( printf and key inputs )
* C as a structured program
* [outdated animated demo](https://asciinema.org/a/262232.svg) ```v0.2.?```

##### 2. A GTK/GUI version

* Desktop window app ( buttons, labels, progressbars, and other misc. widgets )
* C interfacing with an OOP
* [outdated screenshot](img/screenshot.gif) ```v0.3```

---

### Project Status:

#### v0.3.2.? (current development)

At the moment I am meddling with the Gtk version. I am making the feature that will display the current liturgical calendar state.

I will go back to the TTY version and re-factor it so it can simply be just linked into the Gtk main.


##### Runtime Environment

* [MinGW](http://www.mingw.org/) or Linux
* Command line interface (CLI) / Shell Terminal
* Xorg (linux) or Xlaunch (Win10/WLS)

##### Developer Environment (debug/mod)

* [MinGW](http://www.mingw.org/) or Linux (x86 or x64)
	* this app was developed on Debian WLS and tested on a real Linux
* GCC v6+
* GDB debugger (optional yet recommended)
* git (version control)
* Glade (a gui drawing tool)
* a text editor (I use Geany for everything)
	* Geany macros
	* compile:	gcc -Wall -c "%f" `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
	* build:	gcc -Wall -o "%e" "%f" `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

---

### Compile

Debian
```sh
make
```

Win10

```sh
## Compile in Debian and make it usable on a Win10
sudo apt install mingw-w64
i686-w64-mingw32-gcc "main.c" -o "my-executable-file.exe"

## Compile in Win10 with MinGW installed
gcc "main.c" -o "my-executable-file.exe "
```
