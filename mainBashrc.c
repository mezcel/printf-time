/*
 * mainBashrc.c
 * */

#include <stdio.h>
#include <stdlib.h>     // system()
#include <string.h>     // strcmp()
#include <time.h>       // After year 2038, use an x64 compiler

//#include <unistd.h>

#include "headers/my_calendar.h"
#include "headers/my_file_to_struct.h"
#include "headers/my_tty_ui.h"

/*
 * // Dependency scripts:
 * #include "sources/my_calendar.c"
 * #include "sources/my_csv_structs.c"
 * #include "sources/my_tty_ui.c"
 * */

#ifdef __unix__
    #define IS_LINUX 1  // This app was tested on Debian Linux ( x86/x64 ) Nov 2020

    #include <unistd.h>
#else
    #define IS_LINUX 0  // Not UNIX
#endif


int main( int argc, char **argv ) {

    // A var flag to set which translation to use.
    int translationFlag = 1; // N/A. This is a dummy variable used for SetTranslationDatabase()

    char *database_path = returnDefaultDbDir("/database/");

    SetTranslationDatabase( argc, argv, &database_path, &translationFlag);

    rosary_db_t rosary_db_struct;                               // Declare app's rosary db var
    displayVariables_t queryViewStruct;                         // Declare rosary db query view var

    feast_db_t feast_db_struct;                                 // Declare app's feast db var
    displayFeastVariables_t queryFeastViewStruct;               // Declare feast db query view var

    struct tm todaysDate    = returnTodaysDate();               // Define today struct
    char *verboseDate       = returnVerboseDate( todaysDate, 0 );  // Decorative Date Display (abbreviated)
    int weekdayNo           = todaysDate.tm_wday;               // Day of the week

    int desiredDispLen;                                         // POSIX terminal column width

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

    char *csv_path_array[8] = { rosaryBead_path, bead_path, book_path, decade_path,
            message_path, mystery_path, prayer_path, scripture_path };

    make_struct_rosary_db_csv( &rosary_db_struct, csv_path_array );         // Make struct database from files

    // User defined feast days, CSV File
    char feast_csv_file[FILENAME_MAX];
    setResourcePath(feast_csv_file, database_path, "csv/feast.csv");

    int recordCount         = returnCsvRecordCount( feast_csv_file );

    make_struct_feast_db_csv( &feast_db_struct, feast_csv_file );               // User defined static feast day db
    updateFeastDisplayStruct( &feast_db_struct, &queryFeastViewStruct,
        todaysDate.tm_mday, todaysDate.tm_mon, recordCount );

    desiredDispLen = returnScreenWidth();                                       // Set terminal width

    deactivateEcho();                                                           // Deactivate POSIX tty echo

    // Display a string representing today's Feast/Holiday state
    bashrcHolidayDisplay( &rosary_db_struct, queryFeastViewStruct, verboseDate, desiredDispLen );

    activateEcho();                                                             // Restore POSIX TTY echo

    return 0;

}
