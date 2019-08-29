## printf-time ./Rosary/gtk-wip/

#### Gtk version (Under Construction)

I resorted to using the Glade app to design my GUI layout. Glade is a tool for creating Gtk GUIs. Glade generates an XML file, ```.glade```. Gtk's ```libgtk-3-dev``` will translate the XML file into a GUI layout.

* It is a point and click UI for ```libgtk-3-dev```
* It prepares my callback function prototype for use in main()

#### Todo:

* clean up script
* start integrating calendar feast day flags

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
