/*
 * mainTTY.c
 * compile:
 * 	gcc mainTTY.c -o mainTTY
 */

#include "sources/my_csv_structs.c"
#include "sources/my_tty_ui.c"

int main() {

	rosary_db_t rosary_db_struct; 				// declare app's db var
	displayVariables_t queryViewStruct;			// declare db query view var

	struct tm todaysDate = returnTodaysDate();	// define today struct
	int weekdayNo = todaysDate.tm_wday;			// day of the week
	int navigtionPosition = initialMystery(weekdayNo); // starting progress position
	navigtionPosition = 298; //debug

	// path to csv db files
	char *rosaryBead_path	= "csv/rosaryBead.csv";
	char *bead_path 		= "csv/bead.csv";
	char *book_path 		= "csv/book.csv";
	char *decade_path 		= "csv/decade.csv";
	char *message_path 		= "csv/message.csv";
	char *mystery_path 		= "csv/mystery.csv";
	char *prayer_path 		= "csv/prayer.csv";
	char *scripture_path 	= "csv/scripture.csv";
	char *csv_path_array[8]	= {rosaryBead_path, bead_path, book_path,
		decade_path, message_path, mystery_path, prayer_path, scripture_path};

	make_struct_db(&rosary_db_struct, csv_path_array);	// make db struct

	// display
	int desiredDispLen = returnScreenWidth(IS_LINUX);	// linux terminal width
	clearScreen(IS_LINUX);								// clear screen
	splashCoverPage(weekdayNo, desiredDispLen);			// display splash

	// UI Loop
    while (navigtionPosition <= 315) {
		updateDisplayVariablesStruct(&rosary_db_struct, &queryViewStruct,
			navigtionPosition); 						// update query

		// display
        desiredDispLen = returnScreenWidth(IS_LINUX); 	// screen width
		clearScreen(IS_LINUX); 							// clear screen
		outputTtyDisplay( queryViewStruct, desiredDispLen );

		// Navigation Input & Accumulator
		navigtionPosition = pressKeyContinue(navigtionPosition, IS_LINUX);
	}

	return 0;
}
