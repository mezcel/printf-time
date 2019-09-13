# printf-time

A scripture rosary for Gtk and TTY witten in C for Gcc.

### About:

dev branch: ```v0.3.4```

The text database is CSV, the program is C, and the UI is either a Gtk built with from an Xml or a CLI/TTY.

### 2 Gui options:

| CLI Version | GTK3 Version |
|---|---|
| The user navigates with with typed instructions. \ Press [enter] key or the key sequence ["b" + enter] to navigate forwards or backwards. | The user navigates with push-button widget objects. |
| screenshot taken on Debian WLS | screenshot taken on a i686 Debian |
| ![tty-screenshot](img/tty-screenshot.gif) | ![screenshot](img/screenshot.gif) |
| [outdated animated cli demo](https://asciinema.org/a/266585) ``` from v0.3.3.?``` | - |

### Compile

Debian
```sh
## Makefile Compile ##################

# build everything

make

# or just compile one version or the other

make ttyRosary
make gtkRosary
```

```sh
## Manual Shell Compile ##############

# alternately one can just compile it the basic shell way

./manual_compile.sh
```

---

### Inspiration:

This is the 5th program language version in my Rosary App series.

Previous versions were:

| .NET/Windows OS | NodeJS/Electron | BASH/GNU | Python (Win/Linux) |
| --- | --- | --- | --- |
|[repo](https://github.com/mezcel/rosary.net)|[repo](https://github.com/mezcel/electron-container)|[repo](https://github.com/mezcel/jq-tput-terminal)|[repo](https://github.com/mezcel/python-curses)|
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
