/*
 * main.c
 */

#include "sources/my_csv_structs.c"
#include "sources/my_tty_ui.c"

int main() {

	rosary_db_t rosary_db_struct; 		// app's db
	displayVariables_t queryViewStruct;	// db query view

	int isLinux = 1;			// OS flag
	int weekdayNo = 0;			// day of the week
	int navigtionPosition = 0;	// navigation position
	int desiredDispLen = 85;	// display row length chars

	// path to csv db files
	char *rosaryBead_path = "csv/rosaryBead.csv";
	char *bead_path = "csv/bead.csv";
	char *book_path = "csv/book.csv";
	char *decade_path = "csv/decade.csv";
	char *message_path = "csv/message.csv";
	char *mystery_path = "csv/mystery.csv";
	char *prayer_path = "csv/prayer.csv";
	char *scripture_path = "csv/scripture.csv";
	char *csv_path_array[8] = {rosaryBead_path, bead_path, book_path, decade_path, message_path, mystery_path, prayer_path, scripture_path};

	#ifdef linux
		isLinux = 1;
		struct tm todaysDate = returnTodaysDate();
		weekdayNo = todaysDate.tm_wday;
		navigtionPosition = initialMystery(weekdayNo); // starting progress position
	#endif

	#ifndef linux
		isLinux = 0;
	#endif

	// make a full struct db
	make_struct_db(&rosary_db_struct, csv_path_array);

	// linux tty/posix display dimensions
	desiredDispLen = returnScreenWidth(isLinux);

	// intro, cover page, splash text
	splashCoverPage(weekdayNo, isLinux, desiredDispLen );

	// UI Loop
    while (navigtionPosition <= 315) {
		clearScreen(isLinux);
        desiredDispLen = returnScreenWidth(isLinux);

		// update query view struct
		updateDisplayVariablesStruct(&rosary_db_struct, &queryViewStruct, navigtionPosition);

		// Render output display
		outputTtyDisplay( queryViewStruct, desiredDispLen );

		// Navigation Input & Accumulator
		navigtionPosition = pressKeyContinue(navigtionPosition, isLinux);
	}

	return 0;
}
