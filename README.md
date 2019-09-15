# printf-time

dev branch: ```v0.3.5```

	starting on the (json/latin) addon
	less code, but uses resources needed to run libjson-c

A scripture rosary for Gtk and TTY witten in C for Gcc. It primarily uses a CSV Database, but there is a JSON database option which uses Latin from the Vulgate.

### GUI Options:

CSV Database:

| English CLI Version | English GTK3 Version |
| --- | --- |
| The user navigates with with typed instructions. \ Press [enter] key or the key sequence ["b" + enter] to navigate forwards or backwards. | The user navigates with push-button widget objects. |
| screenshot taken on Debian WLS | screenshot taken on a i686 Debian |
| ![tty-screenshot](img/tty-screenshot.gif) | ![screenshot](img/screenshot.gif) |
| [outdated animated cli demo](https://asciinema.org/a/266585) ```from the depreciated v0.3.3``` | - |

JSON Database:

| Latin CLI Version |
| --- |
| Same UI as the English version, but it uses the json-c library |

---

### Compile on Debian

```sh
## Makefile Compile ##################

# build everything
make

# or just build the TTY version
make ttyRosary

# or just build the GTK3 version
make gtkRosary
```

```sh
## Vulgate Latin JSON Database Version
## I did not add it to the Makefile, and the file linking is just done within the .c files

## debian libjson-c dependencies
sudo apt install autotools-dev debhelper dh-autoreconf dh-exec

## debian stretch (libs): 0.12.1-1.1
sudo apt install libjson-c-dev libjson-c-doc libjson-c3

## compile and build an executable
gcc -o ttyRosary_vulgate mainTTY_vulgate.c -ljson-c
```

---

### Inspiration:

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

### Project Status:

#### v0.3.4.? (current development)

* Tested on Linux and WLS, I have not yet tested it on a Mac or MinGW
* Refactoring object libraries
* Gradually making documentation readable
* I intend to go back and merge the 3 versions so their libraries overalap better with each other..

##### Runtime Environment

* [MinGW](http://www.mingw.org/) or Linux
* Command line interface (CLI) / Shell Terminal
* Xorg (Debian linux) or Xlaunch (Win10/WLS)

##### Developer Environment (debug/mod)

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
