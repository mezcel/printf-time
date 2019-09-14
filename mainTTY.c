/*
 * mainTTY.c
 * compile:
 * 	gcc mainTTY.c -o mainTTY
 */

#include <stdio.h>
#include <time.h>	// After year 2038, only use an x64 compiler
#include "headers/my_calendar.h"
#include "headers/my_csv_structs.h"
#include "headers/my_tty_ui.h"

#ifdef linux
	//int IS_LINUX = 1;
	#define IS_LINUX 1		// os flag
#endif
#ifndef linux
	//int IS_LINUX = 0;
	#define IS_LINUX 0		// os flag
#endif

int main() {

	rosary_db_t rosary_db_struct; 				// declare app's db var
	displayVariables_t queryViewStruct;			// declare db query view var

	struct tm todaysDate = returnTodaysDate();	// define today struct
	int weekdayNo = todaysDate.tm_wday;			// day of the week
	int navigtionPosition = initialMystery(weekdayNo); // starting progress position

	// path to csv db files
	char *rosaryBead_path	= "database/csv/rosaryBead.csv";
	char *bead_path 		= "database/csv/bead.csv";
	char *book_path 		= "database/csv/book.csv";
	char *decade_path 		= "database/csv/decade.csv";
	char *message_path 		= "database/csv/message.csv";
	char *mystery_path 		= "database/csv/mystery.csv";
	char *prayer_path 		= "database/csv/prayer.csv";
	char *scripture_path 	= "database/csv/scripture.csv";
	char *csv_path_array[8]	= {rosaryBead_path, bead_path, book_path, decade_path,
			message_path, mystery_path, prayer_path, scripture_path};

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
