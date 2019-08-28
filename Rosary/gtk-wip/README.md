## printf-time ./Rosary/gtk-wip/

#### Gtk version (Under Construction)

I am translating the tty version into a GUI gtk version option. I am using the same CSV parser, but instead of ```printf()```, a gui window will be the display screen.

I am calling OOP/Gtk from C.

#### Development Status:

* ```mainGtk-globals.c```

I have a working version, but I am using a lot of globals, which are mostly structs. In the working version, my containers are resizing. When the string becomes lengthy, the display extends past the window and monitor screen.

* ```mainGtk.c```

I have a "non-global" version too. The final should bee more like this one. The problem with this one is the "Data Structures". I need a handy way to pass in by database structs. At the moment, the program is not updating search queries.

* ```mainGlade.c```

I resorted to using a Glade to design my GUI. Glade is a tool for creating Gtk GUIs. It generates an XML file, and it is that file which libgtk-3-dev will convert into the appropriate C script for gtk.


---

#### Instructions:

```bash
## Complile:
## hand crafted gtk2 version
gcc -Wall -o "mainGtk" "mainGtk.c" `pkg-config --cflags --libs gtk+-2.0`

## Glade generated XML file
gcc -o gladewin main.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

## RUN:
./mainGtk
```

#### Import Glade file

Glade is a tool for creating Gtk GUIs. It generates an XML file which Gtk can use to build an app

```sh
sudo apt-get install glade libgtk-3-dev
```

#### Example usecase:

```c
#include "gtk/gtk.h"

/*
 * Just A GUI Container
 *
 * compile:
 * gcc -o mainGlade mainGlade.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
 * */

int main(int argc, char *argv[]) {
    GtkBuilder      *builder;
    GtkWidget       *window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "gladeProject.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "gtkRosary"));
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    gtk_widget_show(window);
    gtk_main();

    return 0;
}

// called when window is closed
void on_gtkRosary_destroy() {
    gtk_main_quit();
}
```
