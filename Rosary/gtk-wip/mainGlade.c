/*
 * mainGlade.c
 * dependency: made for linux, libgtk-3-dev, ./gladeProject.glade
 * compile:
 * 	gcc -o mainGlade mainGlade.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
 * */

#include "gtk/gtk.h"
#include "../my_csv_structs.c" // ER Db structs
#include "my_glade_api.c"

int main(int argc, char *argv[]) {

    GtkBuilder *builder;
    GtkWidget *window;
    app_widgets *widgets = g_slice_new(app_widgets);

    struct MyDateStruct todaysDate = setTodaysDateStruct();
	int navigtionPosition = initialMystery(todaysDate.weekdayInt); // starting progress position

	// Populate ER database structs
	csvToStruct_rosaryBead(rosaryBead_record_field, rosaryBead_dbArray, 300, "../csv/rosaryBead.csv");
	csvToStruct_bead(bead_record_field, bead_dbArray, 40, "../csv/bead.csv");
	csvToStruct_book(book_record_field, book_dbArray, 300, "../csv/book.csv");
	csvToStruct_decade(decade_record_field, decade_dbArray, 800, "../csv/decade.csv");
	csvToStruct_message(message_record_field, message_dbArray, 150, "../csv/message.csv");
	csvToStruct_mystery(mystery_record_field, mystery_dbArray, 100, "../csv/mystery.csv");
	csvToStruct_prayer(prayer_record_field, prayer_dbArray, 1250, "../csv/prayer.csv");
	csvToStruct_scripture(scripture_record_field, scripture_dbArray, 500, "../csv/scripture.csv");

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "myGladeXml.glade", NULL);
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
 * Define functions prototyped by the Glade XML
 * */

void on_gtkRosary_destroy() {
    gtk_main_quit();
}

void on_btnClose_clicked() {
    gtk_main_quit();
}

void on_btnForward_clicked(GtkButton *button, app_widgets *widgets) {
	int navigtionPosition = widgets->navigtionPosition;

	if (navigtionPosition < 315) {
		widgets->navigtionPosition = navigtionPosition + 1;
	} else {
		widgets->navigtionPosition = 0;
	}
	update_widgets_labels(widgets);
}

void on_btnBack_clicked(GtkButton *button, app_widgets *widgets) {
	int navigtionPosition = widgets->navigtionPosition;

	if (navigtionPosition > 0) {
		widgets->navigtionPosition = widgets->navigtionPosition - 1;
	} else {
		widgets->navigtionPosition = 315;
	}
	update_widgets_labels(widgets);
}
