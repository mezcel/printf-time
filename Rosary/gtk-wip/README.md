## printf-time ./Rosary/gtk-wip/

#### Gtk version (Under Construction)

I am translating the tty version into a GUI gtk version option. I am using the same CSV parser, but instead of ```printf()```, a gui window will be the display screen.

I am calling OOP/Gtk from C.

#### Development Status:

* ```mainGtk-globals.c```

I have a working version, but I am using a lot of globals, which are mostly structs. In the working version, my containers are resizing. When the string becomes lengthy, the display extends past the window and monitor screen.

* ```mainGtk.c```

I have a "non-global" version too. The final should bee more like this one. The problem with this one is the "Data Structures". I need a handy way to pass in by database structs. At the moment, the program is not updating search queries.

---

#### Instructions:

```bash
## Complile:
gcc -Wall -o "mainGtk" "mainGtk.c" `pkg-config --cflags --libs gtk+-2.0`

## RUN:
./mainGtk
```
