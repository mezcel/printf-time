## printf-time ./Rosary/gtk-wip/

#### Gtk version (Under Construction)

I am using my ```my-csv-parser.h``` in a Gtk 3 desktop GUI desktop app.

The back-end is procedural programming and the front end is OOP. I resorted to using a Glade to design my GUI layout. Glade is a tool for creating Gtk GUIs.

Glade generates an XML file. Gtk's ```libgtk-3-dev``` will translate the XML file into a GUI layout.

#### Todo:

* clean up script
* go back and re-factor the tty version
* start integrating calendar feast day flags
* use system to clock to derive the current year

---

#### Instructions:

```bash
## Install the Glade dependency
sudo apt install glade libgtk-3-dev

## Compile with the Glade generated XML file
gcc -o mainGlade mainGlade.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

## RUN:
./mainGtk
```
