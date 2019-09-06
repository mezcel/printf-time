/*
 * mainGtk3.c
 * dependency:
 * 	libgtk-3-dev
 * compile:
 * 	gcc -o mainGlade mainGlade.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
 * */

#include "gtk/gtk.h"
#include "sources/my_csv_structs.c" // ER Db structs
#include "sources/my_gtk3_api.c"

int main(int argc, char *argv[]) {

    GtkBuilder *builder;
    GtkWidget *window;
    app_widgets *widgets = g_slice_new(app_widgets);

	struct tm todaysDate = returnTodaysDate();
	int navigtionPosition = initialMystery(todaysDate.tm_wday); // starting progress position
	navigtionPosition = 298; //debug

	// path to csv db files
	char *rosaryBead_path = "csv/rosaryBead.csv";
	char *bead_path = "csv/bead.csv";
	char *book_path = "csv/book.csv";
	char *decade_path = "csv/decade.csv";
	char *message_path = "csv/message.csv";
	char *mystery_path = "csv/mystery.csv";
	char *prayer_path = "csv/prayer.csv";
	char *scripture_path = "csv/scripture.csv";
	char *csv_path_array[8]={rosaryBead_path, bead_path, book_path,
		decade_path, message_path, mystery_path, prayer_path, scripture_path};

	make_struct_db(&rosary_db_struct, csv_path_array); // make db struct

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "xml/myGladeXml.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "gtkRosary"));

    initializeLabelPointers(builder, window, widgets); // get pointers to label widgets
    widgets->navigtionPosition = navigtionPosition; // starting progress position;

    gtk_builder_connect_signals(builder, widgets);
    g_object_unref(builder);

    gtk_widget_show(window);
    gtk_main();

    return 0;
}

/*
 * functions prototyped by the Glade XML
 * */

// Close App Button Click
void on_gtkRosary_destroy() {
    gtk_main_quit();
}

void on_btnClose_clicked() {
    gtk_main_quit();
}

// Navigate Forward Button Click
void on_btnForward_clicked(GtkButton *button, app_widgets *widgets) {
	int navigtionPosition = widgets->navigtionPosition;

	if (navigtionPosition < 315) {
		widgets->navigtionPosition = navigtionPosition + 1;
	} else {
		widgets->navigtionPosition = 0;
	}
	update_widgets_labels(widgets);
}

// Navigate Backward Button Click
void on_btnBack_clicked(GtkButton *button, app_widgets *widgets) {
	int navigtionPosition = widgets->navigtionPosition;

	if (navigtionPosition > 0) {
		widgets->navigtionPosition = widgets->navigtionPosition - 1;
	} else {
		widgets->navigtionPosition = 315;
	}
	update_widgets_labels(widgets);
}
