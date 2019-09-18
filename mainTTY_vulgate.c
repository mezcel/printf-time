/*
 * mainTTY_vulgate.c
 *
 * compile:
 *	gcc my_calendar.c my_json_structs.c my_tty_ui.c mainTTY_vulgate.c -ljson-c -o "ttyRosary_latin"
 * */

#include <stdio.h>
#include <time.h>	// After year 2038, only use an x64 compiler
#include <sys/stat.h> // used for file size
#include <json-c/json.h>

#include "headers/my_calendar.h"
// #include "sources/my_calendar.c"
#include "headers/my_file_to_struct.h"
// #include "sources/my_json_structs.c"
#include "headers/my_tty_ui.h"
// #include "sources/my_tty_ui.c"

// flag for POSIX specific functions, intended for later cross platform dev
int IS_LINUX = 1;

int main( int argc, char **argv ) {
	rosary_db_t rosary_db_struct; 				// declare app's db var
	displayVariables_t queryViewStruct;			// declare db query view var

	struct tm todaysDate = returnTodaysDate(IS_LINUX);	// define today struct
	int weekdayNo = todaysDate.tm_wday;			// day of the week
	int navigtionPosition = initialMystery(weekdayNo); // starting progress position

	char *filePath = "database/json/rosaryJSON-vulgate.json";
	make_struct_db_json(&rosary_db_struct, filePath); // populate rosary_db_t

	// display
	int desiredDispLen = returnScreenWidth(IS_LINUX);	// linux terminal width
	clearScreen(1);								// clear screen
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
