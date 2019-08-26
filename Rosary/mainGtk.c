/*
 * mainGtk.c
 */

#include <stdlib.h>		// calloc(), realloc(), malloc(), system(), free()
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>	// ioctl(), TIOCGWINSZ
#include <unistd.h> 	// STDOUT_FILENO
#include "gtk/gtk.h"

#include <time.h>				// time_t
#include "my-csv-parser.h"		// my own homework CSV parse functions & structs
#include "my-gtk-gui.h"			// UI for the gtk display

// Main //
int main(int argc, char **argv) {

	int weekdayNo = 0;
	int navigtionPosition = 0;

	weekdayNo = returnDayOfWeekFlag(); // 0=sun, 1=mon
	navigtionPosition = initialMystery(weekdayNo); // starting progress position

	// Name my strtuct variables
	rosaryBead_t *rosaryBead_record_field = NULL;
	rosaryBead_t rosaryBead_dbArray[317];

	bead_t *bead_record_field = NULL;
	bead_t bead_dbArray[9];

	book_t *book_record_field = NULL;
	book_t book_dbArray[17];

	decade_t *decade_record_field = NULL;
	decade_t decade_dbArray[22];

	message_t *message_record_field = NULL;
	message_t message_dbArray[22];

	mystery_t *mystery_record_field = NULL;
	mystery_t mystery_dbArray[7];

	prayer_t *prayer_record_field = NULL;
	prayer_t prayer_dbArray[11];

	scripture_t *scripture_record_field = NULL;
	scripture_t scripture_dbArray[202];

	//struct displayVariables_struct displayVariables_t;
	displayVariables_t queryViewStruct;

	/*
	 * Populate my struct arrays
	 * (single_struct, struct_array, max_chars_per_line, csv_file_path)
	 * */

	csvToStruct_rosaryBead(rosaryBead_record_field, rosaryBead_dbArray, 300, "csv/rosaryBead.csv");
	csvToStruct_bead(bead_record_field, bead_dbArray, 40, "csv/bead.csv");
	csvToStruct_book(book_record_field, book_dbArray, 300, "csv/book.csv");
	csvToStruct_decade(decade_record_field, decade_dbArray, 800, "csv/decade.csv");
	csvToStruct_message(message_record_field, message_dbArray, 150, "csv/message.csv");
	csvToStruct_mystery(mystery_record_field, mystery_dbArray, 100, "csv/mystery.csv");
	csvToStruct_prayer(prayer_record_field, prayer_dbArray, 1250, "csv/prayer.csv");
	csvToStruct_scripture(scripture_record_field, scripture_dbArray, 500, "csv/scripture.csv");

	// Gtk GUI
	gtk_init(&argc, &argv);
	updateDisplayVariablesStruct(rosaryBead_dbArray, bead_dbArray, book_dbArray, decade_dbArray, message_dbArray, mystery_dbArray, prayer_dbArray, scripture_dbArray, &queryViewStruct, navigtionPosition);
	initGtkWindow(queryViewStruct);

	return 0;
}
