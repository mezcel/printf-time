/*
 * mainTTY.c
 * */

#include <stdio.h>
#include <stdlib.h>     // system()
//#include <string.h>     // strcmp()
#include <time.h>       // After year 2038, use an x64 compiler, my_calendar.h structs

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
    #define IS_LINUX 1  // This app was tested on Debian Linux Gcc ( x86/x64 ) Jan 2020
#else
    #define IS_LINUX 0  // This app was tested on Win10 Visual Studio 2019 ( x86/x64 ) Jan 2020
#endif

int main( int argc, char **argv ) {

    /* Initialize variables */

    rosary_db_t rosary_db_struct;                               // Declare rosary db ER struct
    displayVariables_t queryViewStruct;                         // Declare rosary db query view struct

    feast_db_t feast_db_struct;                                 // Declare app's feast db struct
    displayFeastVariables_t queryFeastViewStruct;               // Declare feast db query view struct

    struct tm todaysDate   = returnTodaysDate();                // Set today's date struct
    char *verboseDate      = returnVerboseDate( todaysDate, 0 );    // Decorative Date Display
    int weekdayNo          = todaysDate.tm_wday;                // Set of the week number
    int navigtionPosition  = initialMystery( weekdayNo );       // Set starting progress position record

    char *titleLabel;                                           // String to display which db is used
    //int nabFlag = returnLaunchArgument( argc, argv[1] );        // Sets either NAB or Vulgate
    int nabFlag = 1;
    char *database_path = returnDefaultDbDir("/database/");
    SetTranslationDatabase( argc, argv, &database_path, &nabFlag);

    int desiredDispLen;                                         // POSIX terminal column width

    /*  DB file path variables */

    char jsonFilePath[FILENAME_MAX];
        setResourcePath(jsonFilePath, database_path, "json/rosaryJSON-vulgate.json");

    /*  English NAB Database */

    char rosaryBead_path[FILENAME_MAX];
        setResourcePath(rosaryBead_path, database_path, "csv/rosaryBead.csv");
    char bead_path[FILENAME_MAX];          // Bead types and names
        setResourcePath(bead_path, database_path, "csv/bead.csv");
    char book_path[FILENAME_MAX];          // Book Titles
        setResourcePath(book_path, database_path, "csv/book.csv");
    char decade_path[FILENAME_MAX];        // Decade beads readings
        setResourcePath(decade_path, database_path, "csv/decade.csv");
    char message_path[FILENAME_MAX];       // Decade mystery information
        setResourcePath(message_path, database_path, "csv/message.csv");
    char mystery_path[FILENAME_MAX];       // Mystery names
        setResourcePath(mystery_path, database_path, "csv/mystery.csv");
    char prayer_path[FILENAME_MAX];        // Prayer database
        setResourcePath(prayer_path, database_path, "csv/prayer.csv");
    char scripture_path[FILENAME_MAX];
        setResourcePath(scripture_path, database_path, "csv/scripture.csv");

    /* User defined feast days, CSV File */

    char feast_csv_file[FILENAME_MAX];
        setResourcePath(feast_csv_file, database_path, "csv/feast.csv");
    int recordCount         = returnCsvRecordCount( feast_csv_file );

    desiredDispLen = returnScreenWidth();                                       // Set terminal width
    clearScreen();                                                              // Clear screen
    deactivateEcho();                                                           // Deactivate POSIX tty echo

    /* Load Database files */

    if ( ( nabFlag == 0 ) && ( IS_LINUX == 1 ) ) {                      // Vulgate JSON Database with POSIX
        titleLabel = " C/JSON Rosary ( Latin Vulgate ) ";               // Decorative label showing which DB is used
        make_struct_rosary_db_json( &rosary_db_struct, jsonFilePath );  // Make struct database from file

    } else {                                                            // NAB CSV Database
        titleLabel = " C/CSV Rosary ( English NAB ) ";                  // Decorative label showing which DB is used
        char *csv_path_array[8] = {
            rosaryBead_path, bead_path, book_path, decade_path,
            message_path, mystery_path, prayer_path, scripture_path };  // Array of ER Class files
        make_struct_rosary_db_csv( &rosary_db_struct, csv_path_array ); // Make struct database from files
    }

    make_struct_feast_db_csv( &feast_db_struct, feast_csv_file );       // User defined static feast day db

    updateFeastDisplayStruct(                                           // Update query view structs
        &feast_db_struct, &queryFeastViewStruct, todaysDate.tm_mday,
        todaysDate.tm_mon, recordCount );

    /* Welcome display */

    splashPage( desiredDispLen, verboseDate  );                                 // Display splash title
    infoPage( queryFeastViewStruct, weekdayNo, desiredDispLen, titleLabel );    // Display info/about

    /* User interface loop */

    int maxBeadRecords = 315;

    while ( navigtionPosition <= maxBeadRecords ) {
        /* Update the displayFeastVariables_t struct
         * based on the current navigation position record */

        updateDisplayVariablesStruct( &rosary_db_struct, &queryViewStruct, navigtionPosition );

        /* render display text */

        desiredDispLen = returnScreenWidth();                                   // Get tty screen width
        mysteryCoverPage( queryViewStruct, navigtionPosition, desiredDispLen ); // New Mystery cycle splash
        renderRosaryDisplay( queryViewStruct, desiredDispLen, titleLabel );     // Populate Rosary TTY Display

        /* Prompt for keyboard navigation user input */

        navigtionPosition = pressKeyContinue(
            queryFeastViewStruct, navigtionPosition, weekdayNo, desiredDispLen );
    }

    activateEcho(); // Restore POSIX TTY echo

    return 0;

}
