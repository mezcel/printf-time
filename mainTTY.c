/*
 * mainTTY_nab.c
 * */

#include <stdio.h>
#include <stdlib.h>				// system()
#include <string.h>				// strcmp()
#include <time.h>				// After year 2038, use an x64 compiler

#include "headers/my_calendar.h"
#include "headers/my_file_to_struct.h"
#include "headers/my_tty_ui.h"

#ifdef __unix__
	#define IS_LINUX 1
#else
	#define IS_LINUX 0
#endif

int main( int argc, char **argv ) {

	rosary_db_t rosary_db_struct;							// declare app's db var
	displayVariables_t queryViewStruct;						// declare db query view var

	struct tm todaysDate = returnTodaysDate( IS_LINUX );	// define today struct
	int weekdayNo = todaysDate.tm_wday;						// day of the week
	int navigtionPosition = initialMystery( weekdayNo );	// starting progress position

	char *titleLabel;										// string to display which db is used
	int nabFlag;											// Sets either NAB or Vulgate

	if ( argc == 2 ) {										// set Latin Vulgate from app launch
		nabFlag = strcmp( "-v", argv[1] );
	} else {												// no input, default to NAB
		nabFlag = 1;
	}

	if ( ( nabFlag == 0 ) && ( IS_LINUX == 1 ) ) {		// Vulgate JSON Database with POSIX
		titleLabel = " C/JSON Rosary ( Latin Vulgate ) ";
		char *jsonFilePath = "database/json/rosaryJSON-vulgate.json";

		make_struct_db_json( &rosary_db_struct, jsonFilePath );	// make struct database
	} else {													// NAB CSV Database
		titleLabel = " C/CSV Rosary ( English NAB ) ";
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

		make_struct_db_csv( &rosary_db_struct, csv_path_array );	// make struct database
	}

	// Welcome display

	int desiredDispLen = returnScreenWidth( IS_LINUX );		// linux terminal width
	clearScreen( IS_LINUX );								// clear screen
	deactivateEcho( IS_LINUX );								// deactivate tty echo

	splashPage( desiredDispLen, IS_LINUX );					// display splash
	infoPage( weekdayNo, desiredDispLen, titleLabel );		// display info

	// User interface application loop

	while ( navigtionPosition <= 315 ) {
		// query database text based on the current navigation position
		updateDisplayVariablesStruct( &rosary_db_struct, &queryViewStruct, navigtionPosition );

		// render display text
		desiredDispLen = returnScreenWidth( IS_LINUX );		// get tty screen width
		outputTtyDisplay( queryViewStruct, desiredDispLen, titleLabel, IS_LINUX );

		// Prompt for navigation user input
		navigtionPosition = pressKeyContinue( navigtionPosition, IS_LINUX, weekdayNo, desiredDispLen );
	}

	activateEcho( IS_LINUX );								// Restore tty echo

	return 0;
}
