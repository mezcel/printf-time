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

// #include "sources/my_csv_structs.c"
// #include "sources/my_tty_ui.c"
int IS_LINUX = 1;
/*char * MONTH_NAME_ARRAY[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
char * WEEKDAY_NAME_ARRAY[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
char * LITURGICAL_SEASON_ARRAY[] = { "Advent Season", "Christmas Season", "Lent Season", "Easter Season", "Ordinary Time" };
char * FEAST_DAY_ARRAY[] = { "advent_start", "immaculate_conception_mary", "christmas_day", "solemnity_of_mary", "epiphany", "jesus_baptism", "ash_wednesday", "holy_thursday", "good_friday", "good_saturday", "easter_sunday", "pentacost", "assension_of_jesus", "all_saints_day", "ordinary_day" };*/


int main() {

	rosary_db_t rosary_db_struct; 				// declare app's db var
	displayVariables_t queryViewStruct;			// declare db query view var

	struct tm todaysDate = returnTodaysDate();	// define today struct
	int weekdayNo = todaysDate.tm_wday;			// day of the week
	int navigtionPosition = initialMystery(weekdayNo); // starting progress position

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
