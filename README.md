# printf-time

### About:

development branch: ```v0.3.3```

This is a scriptural rosary slideshow. The text database is CSV, the program is C, and the UI is Gtk built with from an Xml.

### Inspiration:

This is the 5th program language version in my Rosary App series. Features used in this app are based on previous other versions of the app.

Previous versions were:
* [C#/MySql/.NET](https://github.com/mezcel/rosary.net) (a WinForm and a WPF/WCF version),
* [JqueryMobile/Json](https://github.com/mezcel/electron-container) (an Electron and Heroku version),
* [Bash/Json](https://github.com/mezcel/jq-tput-terminal) (shell on Arch & Debian),
* [Python/Json](https://github.com/mezcel/python-curses),
* and now the [C/CSV](https://github.com/mezcel/printf-time) version.

### 2 Gui options:

##### 1. A TTY/CLI version

The user navigates with with typed instructions. Press [enter] key or the key sequence ["b" + enter] to navigate forwards or backwards.

* Terminal screen app ( printf and key inputs )
* [outdated animated demo](https://asciinema.org/a/262232.svg) ```v0.2.?```

##### 2. A GTK/GUI version

The user navigates with widget objects.

* Desktop window app ( buttons, labels, progressbars, and other misc. widgets )
* [outdated screenshot](img/screenshot.gif) ```v0.3```

---

### Project Status:

#### v0.3.3.? (current development)

* Works on Linux and WLS, though the latest version is not yet tested on MinGW
* Consolidated the maze of pointer/address and consolidated them into a commonly accessed data structure.

##### Runtime Environment

* [MinGW](http://www.mingw.org/) or Linux
* Command line interface (CLI) / Shell Terminal
* Xorg (Debian linux) or Xlaunch (Win10/WLS)
* GTK3+

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
