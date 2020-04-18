/*
 * mainTTY.c
 * */

#include <stdio.h>
#include <stdlib.h>     // system()
#include <string.h>     // strcmp()
#include <time.h>       // After year 2038, use an x64 compiler

#include "headers/my_calendar.h"
#include "headers/my_file_to_struct.h"
#include "headers/my_tty_ui.h"

/*
 * // Dependency:
 * #include "sources/my_calendar.c"
 * #include "sources/my_csv_structs.c"
 * #include "sources/my_tty_ui.c"
 * */

#ifdef __unix__
    #define IS_LINUX 1  // This app was tested on Debian Linux ( x86/x64 ) Jan 2020
#else
    #define IS_LINUX 0  // This app was tested on Win10 ( x86/x64 ) Jan 2020
#endif

int main( int argc, char **argv ) {

    rosary_db_t rosary_db_struct;                               // declare app's rosary db var
    displayVariables_t queryViewStruct;                         // declare rosary db query view var

    feast_db_t feast_db_struct;                                 // declare app's feast db var
    displayFeastVariables_t queryFeastViewStruct;               // declare feast db query view var

    struct tm todaysDate    = returnTodaysDate();               // define today struct
    char *verboseDate       = returnVerboseDate( todaysDate );  // Decorative Date Display
    int weekdayNo           = todaysDate.tm_wday;               // day of the week
    int navigtionPosition   = initialMystery( weekdayNo );      // starting progress position

    char *titleLabel;                                           // string to display which db is used
    int nabFlag = returnLaunchArgument( argc, argv[1] );        // Sets either NAB or Vulgate
    int desiredDispLen;                                         // POSIX terminal column width

    // Load Database files
    if ( ( nabFlag == 0 ) && ( IS_LINUX == 1 ) ) {              // Vulgate JSON Database with POSIX
        titleLabel              = " C/JSON Rosary ( Latin Vulgate ) ";
        char *jsonFilePath      = "database/json/rosaryJSON-vulgate.json";

        make_struct_rosary_db_json( &rosary_db_struct, jsonFilePath );  // make struct database from file
    } else {                                                            // NAB CSV Database
        titleLabel = " C/CSV Rosary ( English NAB ) ";
        char *rosaryBead_path   = "database/csv/rosaryBead.csv";
        char *bead_path         = "database/csv/bead.csv";
        char *book_path         = "database/csv/book.csv";
        char *decade_path       = "database/csv/decade.csv";
        char *message_path      = "database/csv/message.csv";
        char *mystery_path      = "database/csv/mystery.csv";
        char *prayer_path       = "database/csv/prayer.csv";
        char *scripture_path    = "database/csv/scripture.csv";
        char *csv_path_array[8] = { rosaryBead_path, bead_path, book_path, decade_path,
                message_path, mystery_path, prayer_path, scripture_path };

        make_struct_rosary_db_csv( &rosary_db_struct, csv_path_array ); // make struct database from files
    }

    // User defined feast days, CSV File
    char *feast_csv_file    = "database/csv/feast.csv";
    int recordCount         = returnCsvRecordCount( feast_csv_file );

    make_struct_feast_db_csv( &feast_db_struct, feast_csv_file );       // fixed feast day db
    updateFeastDisplayStruct(
        &feast_db_struct, &queryFeastViewStruct,
        todaysDate.tm_mday, todaysDate.tm_mon, recordCount );

    // Welcome display

    desiredDispLen = returnScreenWidth();                               // terminal width
    clearScreen();                                                      // clear screen
    deactivateEcho();                                                   // deactivate posix tty echo

    splashPage( desiredDispLen, verboseDate  );                         // display splash title
    infoPage( queryFeastViewStruct, weekdayNo, desiredDispLen, titleLabel );    // display info/about

    // User interface loop

    while ( navigtionPosition <= 315 ) {
        // Update the displayFeastVariables_t struct based on the current navigation position
        updateDisplayVariablesStruct( &rosary_db_struct, &queryViewStruct, navigtionPosition );

        // render display text
        desiredDispLen      = returnScreenWidth();                      // get tty screen width
        outputTtyDisplay( queryViewStruct, desiredDispLen, titleLabel );

        // Prompt for keyboard navigation user input
        navigtionPosition   = pressKeyContinue( queryFeastViewStruct, navigtionPosition, weekdayNo, desiredDispLen );
    }

    activateEcho();                                                     // Restore posix tty echo

    return 0;

}
