## Additional system environment headers

### Standard Libraries

| library | Linux | Windows 10 |  use case |
| --- | --- | --- | --- |
| ```#include <stdio.h>``` | [stdio.h](http://man7.org/linux/man-pages/man3/stdio.3.html) | [cstdio.h](https://docs.microsoft.com/en-us/cpp/standard-library/cstdio?view=vs-2019) | printf(), fread(), fopen(), fclose() |
| ```#include <stdlib.h>``` | [stdlib.h](http://man7.org/linux/man-pages/man0/stdlib.h.0p.html) | [cstdio.h](https://docs.microsoft.com/en-us/cpp/standard-library/cstdlib?view=vs-2019) | calloc(), realloc(), malloc(), system(), free() |
| ```#include <string.h>``` | [string.h](http://man7.org/linux/man-pages/man0/string.h.0p.html) | [cstring.h](https://docs.microsoft.com/en-us/cpp/standard-library/cstring?view=vs-2019) | strcmp() |
| ```#include <time.h>``` | [time.h](http://man7.org/linux/man-pages/man0/time.h.0p.html) | [ctime.h](https://docs.microsoft.com/en-us/cpp/standard-library/ctime?view=vs-2019) | After year 2038, use an x64 compiler |

### Windows 10

| library | Visual Studio C++ | use case |
| --- | --- | --- |
| ```#include <windows.h>``` | [windows.h](https://en.wikipedia.org/wiki/Windows.h) | GetConsoleScreenBufferInfo() |
| ```#include <conio.h>``` | [conio.h](https://en.wikipedia.org/wiki/Conio.h) | getch() |

### Debian Linux

| library | GCC | use case |
| --- | --- | --- |
| ```#include <sys/stat.h>``` | [sys/stat.h](http://man7.org/linux/man-pages/man0/sys_stat.h.0p.html) | stat() |
| ```#include <sys/ioctl.h>``` | [sys/ioctl.h](http://man7.org/linux/man-pages/man2/ioctl.2.html) | ioctl(), TIOCGWINSZ, struct winsize |
| ```#include <unistd.h>``` | [unistd.h](http://man7.org/linux/man-pages/man0/unistd.h.0p.html) | STDOUT_FILENO |
| ```#include <json-c/json.h>``` | [json-c/json.h](http://json-c.github.io/json-c/json-c-0.13.1/doc/html/files.html) | Debian Linux json-c library |
| ```#include "gtk/gtk.h"``` | ["gtk/gtk.h"](https://developer.gnome.org/gtk3/stable/) | used for Gtk |