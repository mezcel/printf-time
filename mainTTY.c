/*
 * mainTTY_nab.c
 * */

/*#include <stdio.h>
#include <stdlib.h> // system()
#include <time.h>	// After year 2038, only use an x64 compiler

#include "headers/my_calendar.h"
#include "headers/my_file_to_struct.h"
#include "headers/my_tty_ui.h"*/

#include <stdio.h>
#include <stdlib.h>		// system()
#include <string.h>		// strcmp()
#include <time.h>		// After year 2038, only use an x64 compiler
#include <sys/stat.h>	// used for file size
#include <json-c/json.h>	// parse json db

#include "headers/my_calendar.h"
#include "headers/my_file_to_struct.h"
#include "headers/my_tty_ui.h"

// flag for POSIX specific functions, intended for later cross platform dev
int IS_LINUX = 1;

int main( int argc, char **argv ) {

	rosary_db_t rosary_db_struct; 				// declare app's db var
	displayVariables_t queryViewStruct;			// declare db query view var

	struct tm todaysDate = returnTodaysDate(IS_LINUX);	// define today struct
	int weekdayNo = todaysDate.tm_wday;			// day of the week
	int navigtionPosition = initialMystery(weekdayNo); // starting progress position

	char *filePath;
	char *titleLabel;

	// load text data from the appropriate database

	int nabFlag = 1;
	if ( argc == 2 ) {
		nabFlag = strcmp( "-v", argv[1] );
	}

	if ( nabFlag == 0 ) {
		// Vulgate JSON Database
		char *filePath = "database/json/rosaryJSON-vulgate.json";

		make_struct_db_json(&rosary_db_struct, filePath); // populate rosary_db_t
		titleLabel = " C/JSON Rosary (Latin Vulgate) ";
	} else {
		// NAB CSV Database
		char *rosaryBead_path	= "database/csv/rosaryBead.csv";
		char *bead_path 		= "database/csv/bead.csv";
		char *book_path 		= "database/csv/book.csv";
		char *decade_path 		= "database/csv/decade.csv";
		char *message_path 		= "database/csv/message.csv";
		char *mystery_path 		= "database/csv/mystery.csv";
		char *prayer_path 		= "database/csv/prayer.csv";
		char *scripture_path 	= "database/csv/scripture.csv";
		char *csv_path_array[8]	= { rosaryBead_path, bead_path, book_path, decade_path,
				message_path, mystery_path, prayer_path, scripture_path };

		make_struct_db_csv(&rosary_db_struct, csv_path_array);	// make db struct
		titleLabel = " C/CSV Rosary (English NAB) ";
	}

	// start display

	int desiredDispLen = returnScreenWidth(IS_LINUX);	// linux terminal width
	clearScreen(IS_LINUX);								// clear screen

	system("stty -echo");
	system("stty cbreak");

	splashPage(desiredDispLen);

	infoPage(weekdayNo, desiredDispLen, titleLabel);	// display splash

	// UI Loop

	while (navigtionPosition <= 315) {
		updateDisplayVariablesStruct(&rosary_db_struct, &queryViewStruct,
		navigtionPosition); 						// update query

		// display
		desiredDispLen = returnScreenWidth(IS_LINUX); 	// screen width
		//clearScreen(IS_LINUX); 							// clear screen
		outputTtyDisplay( queryViewStruct, desiredDispLen, titleLabel);

		// Navigation Input & Accumulator
		navigtionPosition = pressKeyContinue(navigtionPosition, IS_LINUX, weekdayNo, desiredDispLen);
	}

	system("stty echo"); // Make echo work
	system("stty -cbreak");// go to COOKED mode

	return 0;
}
