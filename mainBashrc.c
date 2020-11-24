/*
 * mainBashrc.c
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
    #define IS_LINUX 1  // This app was tested on Debian Linux ( x86/x64 ) Nov 2020
#else
    #define IS_LINUX 0  // Not UNIX
#endif

int main( int argc, char **argv ) {

    // Exit program with a message if the run-time environment is not a Unix-like/Posix-like environment.
    // Redundant
    if ( IS_LINUX == 1 ) {
        printf( "\n" );
        char *stringMessage = "The ttyBashrc binary was designed to work on POSIX terminal environments running the BASH virtual terminal software. The ideal run-time environment is Bash on Debian Linux. The full functionality of this program is not compatible with this system as it is currently configured.";
        multiLinePrintF( "\e[1;31mIncompatible Program:\e[0m", stringMessage, 0, 0 );
        printf("\nSource Code:\thttps://github.com/mezcel/printf-time.git\n");
        printf( "\n" );
    }

    rosary_db_t rosary_db_struct;                               // Declare app's rosary db var
    displayVariables_t queryViewStruct;                         // Declare rosary db query view var

    feast_db_t feast_db_struct;                                 // Declare app's feast db var
    displayFeastVariables_t queryFeastViewStruct;               // Declare feast db query view var

    struct tm todaysDate    = returnTodaysDate();               // Define today struct
    char *verboseDate       = returnVerboseDate( todaysDate );  // Decorative Date Display
    int weekdayNo           = todaysDate.tm_wday;               // Day of the week
    //int navigtionPosition   = initialMystery( weekdayNo );      // Starting progress position

    char *titleLabel;                                           // String to display which db is used
    int nabFlag = returnLaunchArgument( argc, argv[1] );        // Sets either NAB or Vulgate
    int desiredDispLen;                                         // POSIX terminal column width

    // Load Database files // NAB CSV Database
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

    make_struct_rosary_db_csv( &rosary_db_struct, csv_path_array );         // Make struct database from files


    // User defined feast days, CSV File
    char *feast_csv_file    = "database/csv/feast.csv";
    int recordCount         = returnCsvRecordCount( feast_csv_file );

    make_struct_feast_db_csv( &feast_db_struct, feast_csv_file );               // User defined static feast day db
    updateFeastDisplayStruct( &feast_db_struct, &queryFeastViewStruct,
        todaysDate.tm_mday, todaysDate.tm_mon, recordCount );

    desiredDispLen = returnScreenWidth();                                       // Set terminal width

    deactivateEcho();                                                           // Deactivate POSIX tty echo

    // Display a string representing today's Feast/Holiday state
    bashrcHolidayDisplay( &rosary_db_struct, queryFeastViewStruct, queryViewStruct, verboseDate, desiredDispLen );

    activateEcho();                                                             // Restore POSIX TTY echo

    return 0;

}
