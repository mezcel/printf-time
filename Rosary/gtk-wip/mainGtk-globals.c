/*
 * mainGtk-globals.c (UI trial ane error testing)
 * dependancies: ../my-csv-parser.h, my-gtk-gui-globals.h
 * called by: mainGtk-globals.c
 * compile: gcc -Wall -o "mainGtk-globals" "mainGtk-globals.c" `pkg-config --cflags --libs gtk+-2.0`
 * */

#include <stdlib.h>		// calloc(), realloc(), malloc(), system(), free()
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>	// ioctl(), TIOCGWINSZ
#include <unistd.h> 	// STDOUT_FILENO
#include "gtk/gtk.h"

#include <time.h>				// time_t
#include "../my-csv-parser.h"		// my own homework CSV parse functions & structs
#include "my-gtk-gui-globals.h"			// UI for the gtk display (For testing only)

// Main //
int main(int argc, char **argv) {

	weekdayNo = returnDayOfWeekFlag(); // 0=sun, 1=mon
	navigtionPosition = initialMystery(weekdayNo); // starting progress position

	/*
	 * Populate my struct arrays
	 * (single_struct, struct_array, max_chars_per_line, csv_file_path)
	 * */

	csvToStruct_rosaryBead(rosaryBead_record_field, rosaryBead_dbArray, 300, "../csv/rosaryBead.csv");
	csvToStruct_bead(bead_record_field, bead_dbArray, 40, "../csv/bead.csv");
	csvToStruct_book(book_record_field, book_dbArray, 300, "../csv/book.csv");
	csvToStruct_decade(decade_record_field, decade_dbArray, 800, "../csv/decade.csv");
	csvToStruct_message(message_record_field, message_dbArray, 150, "../csv/message.csv");
	csvToStruct_mystery(mystery_record_field, mystery_dbArray, 100, "../csv/mystery.csv");
	csvToStruct_prayer(prayer_record_field, prayer_dbArray, 1250, "../csv/prayer.csv");
	csvToStruct_scripture(scripture_record_field, scripture_dbArray, 500, "../csv/scripture.csv");

	// Gtk GUI
	gtk_init(&argc, &argv);
	updateDisplayVariablesStruct(&queryViewStruct, navigtionPosition);
	initGtkWindow(queryViewStruct);

	return 0;
}
