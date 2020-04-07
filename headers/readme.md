## Additional system environment headers

Universal Libraries
```c
#include <stdio.h>
#include <stdlib.h>			// system()
#include <string.h>			// strcmp()
#include <time.h>			// After year 2038, use an x64 compiler
```

Windows 10 (Visual Studio 2019)
```c
#include <windows.h>        // Win10 GetConsoleScreenBufferInfo()
#include <conio.h>          // getch() Win10 only
```

Debian Linux
```c
#include <sys/stat.h>       // used to get file size
#include <sys/ioctl.h>      // ioctl(), TIOCGWINSZ, struct winsize
#include <unistd.h>         // STDOUT_FILENO
#include <json-c/json.h>	// Debian Linux json-c library
#include "gtk/gtk.h"        // used for Gtk
```