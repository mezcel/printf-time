/*
 * main.c
 */

#include "my_csv_structs.c"
#include "my_tty_ui.c"

// Main //
int main() {

	int isLinux = 1;
	int weekdayNo = 0;
	int navigtionPosition = 0, desiredDispLen = 80;

	#ifdef linux
		isLinux = 1;
		weekdayNo = returnDayOfWeekFlag(); // 0=sun, 1=mon
		navigtionPosition = initialMystery(weekdayNo); // starting position
		struct winsize w; // terminal tty info
	#endif

	#ifdef _WIN32
		isLinux = 0;
	#endif

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

	splashCoverPage(weekdayNo, isLinux); // intro, cover page, splash text

    while (navigtionPosition <= 315) {

		// linux tty/posix display dimensions
        if(isLinux == 1) {
			ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); // tty col/row
			desiredDispLen = (w.ws_col / 2) + (w.ws_col / 5);
        }

		// update display content struct
		updateDisplayVariablesStruct(rosaryBead_dbArray, bead_dbArray, book_dbArray, decade_dbArray, message_dbArray, mystery_dbArray, prayer_dbArray, scripture_dbArray, &queryViewStruct, navigtionPosition);

		// Render output tty display
		outputTtyDisplay( queryViewStruct, desiredDispLen );

		// Navigation Input & Accumulator
		navigtionPosition = pressKeyContinue(navigtionPosition, isLinux);
	}

	return 0;
}
