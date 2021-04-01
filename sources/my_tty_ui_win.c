/* my_tty_ui_win.c
 * USECASE: Supliment the my_tty_ui.c source code.
 *
 * Counterpart to ../sources/my_tty_ui_posix.c
 * For use on non-linux & non-posix terminal environments.(Win10 VS2019 Cpp, Not Debian Gcc)
 * Visual Studio's compiler returns errors if non-comliant
 * libraries and functions are mentioned in the code algorithm.
 * */

//#include <stdlib.h>   // system()
#include <time.h>       // my_callendar.h structs
#include <windows.h>    // Win10 GetConsoleScreenBufferInfo()
#include <conio.h>      // getch() Win10 only

#include "../headers/my_calendar.h"
#include "../headers/my_file_to_struct.h"
#include "../headers/my_tty_ui.h"


char *returnDefaultDbDir( char *childPath_NA ) {
    /* Use the default local database refference path. */
    char * localRelPath = "database/";
    return localRelPath;
}

char *coloredString( char *inputString, int colorFlag ) {
    // dummy function representing a function used to convert a string into an ansii colored posix string
    return;
}

void SetTranslationDatabase( int argc_NA, char **argv_NA, char **database, int *translationFlag) {

    /* n/a.
     * In the Gcc version of this function, it would have set
     * the parent directory of the database files and set the translation flag. */

    return;
}

void clearScreen() {

    // WIN10, Powershell or Command Terminal
    // system( "@cls||clear" );
    system( "@cls" );

    return;

}

int returnScreenWidth() {

    /*
    * On a POSIX terminal I would use the following headers
    *   #include <sys/ioctl.h>  // ioctl(), TIOCGWINSZ, struct winsize
    *   #include <unistd.h>     // STDOUT_FILENO
    *
    * On Win10 I use #include <windows.h>
    *   #include <windows.h>    // GetConsoleScreenBufferInfo()
    * batch script to get console width:
    * for /F "usebackq tokens=2* delims=: " %%W in (`mode con ^| findstr Columns`) do echo %%W
    * */

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;

    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    //int rows;
    //rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return columns;     // For comfortable readability, aim for an int greater than 95;

}

void deactivateEcho() {

    /*
     * n/a
     * used to deactivate echo on posix compliant terminals
     * */

    return;

}

void activateEcho() {

    /*
     * n/a
     * used to reactivate echo on posix compliant terminals
     * */

    return;

}

void boldString( char *inStr ) {
    // Print a white bold string using Win10 ANSI
    // Not implemented yet
    // https://gist.github.com/mlocati/fdabcaeb8071d5c75a2d51712db24011
    // https://en.wikipedia.org/wiki/ANSI_escape_code

    printf( "\x1b[7m%s\x1b[0m", inStr );    // highlited text on Command Prompt
}

void make_struct_rosary_db_json( rosary_db_t *rosary_db_struct, char *jsonFilePath ) {

    /*
     * n/a
     * This is a place holder just to make the Win10 VS compiler happy.
     * The real function, by the same name, was designed for use on a
     * Debian Linux using the json-c library. This dummy function was
     * likely to be called by a non-linux OS, like Win10.
     *
     * this is based on my_json_structs.c which was not loaded
     * */

    return;

}

void pressEnter() {

    /*
     * Wait for User to press enter
     * */

    printf( "\n\n press [ enter key ] to continue ... " );

    char chEnter = getch();

    while( chEnter != '\r' ) {
        chEnter = getch();
    }

}

int pressKeyContinue( displayFeastVariables_t queryFeastViewStruct,
        int navigtionPosition, int weekdayNo, int desiredDispLen ) {

    /*
     * User keyboard input on win10
     * Increment or decrement the next desired position in the rosary sequence
     * Uses traditional vim or "retro game" navigation keys
     * https://www.alt-codes.net/arrow_alt_codes.php
     * */

    char ch = getch();  // input keyboard key without the enter key on Win10

    switch ( ch ) {

        // help screen
        case 72:                                    // ASCII up arrow
        case 80:                                    // ASCII down arrow
        case 'w':
        case 's':
        case 'j':
        case 'k':
            clearScreen();
            infoPage( queryFeastViewStruct, weekdayNo, desiredDispLen, " Instructions: " );
            break;

        // Navigate forward
        case 77:                                    // ASCII right arrow
        case '\r':                                  // [ enter ] key
        case 'n':                                   // [ n key ] navigates 1 step forward
        case 'l':                                   // vim input
        case 'd':                                   // game input
            if ( navigtionPosition < 315 ) {
                navigtionPosition++;
            } else {
                navigtionPosition = 0;              // loop to the beginning
            }
            break;

        // Navigate backward
        case 75:                                    // ASCII left arrow
        case 32:                                    // ASCII space bar
        case 'h':                                   // vim input
        case 'a':                                   // game input
        case 'b':                                   // [ b key ] navigates 1 step back
            if ( navigtionPosition > 1 ) {
                navigtionPosition--;
            } else {
                navigtionPosition = 315;            // loop back to the end
            }
            break;

        // Jump to a mystery
        case '0':                                   // Mystery of the day
            navigtionPosition = initialMystery( weekdayNo );
            break;
        case '1':                                   // Joyful
            navigtionPosition = 0;
            break;
        case '2':                                   // Luminous
            navigtionPosition = 79;
            break;
        case '3':                                   // Sorrowful
            navigtionPosition = 158;
            break;
        case '4':                                   // Glorius
            navigtionPosition = 237;
            break;

        // Exit Application
        //case 27:                                  // ASCII esc key
        case 'q':                                   // [ q key ] quits the app
            printf( "\n\n Quit App \n", ch );
            navigtionPosition = 316;                // any integer greater than 315
            break;

        // Non-mapped keys
        default:                                    // other key entries
            printf( "(use Vim keys.) " );           // The full arrow keys dont always get read in
            for ( int c = 1; c <= 20000; c++ ) {
                for ( int d = 1; d <= 15000; d++ ) {
                    // momentary display delay
                }
            }
            break;
    }

    return navigtionPosition;

}

void bashrcHolidayDisplay( rosary_db_t *rosary_db_struct, displayFeastVariables_t queryFeastViewStruct,
        char *verboseDate, int desiredDispLen ) {

    // display feast day or liturgical season state in a bash terminal

    int scriptureFK;
    struct tm todaysDate = returnTodaysDate(); // Today's date

    char *season = stringLiturgicalSeason();
    char *feast  = stringFeast( queryFeastViewStruct.feastDay,
                    queryFeastViewStruct.feastMonth,
                    queryFeastViewStruct.feastName );

    char *monthDay = verboseDate;
    char *seasonString = malloc(32); // liturgical season string

    if ( desiredDispLen > 79 ) { desiredDispLen = 79; } // Limit display row char length

    borderCharPrintF( ".", desiredDispLen );
    printf("\n");

    // Basic Ordinary time
    if ( strcmp( season, "Ordinary Time" ) == 0 ) {

        sprintf( seasonString, "%s - %s ( %s )", season, feast, verboseDate ); // combine strings
        multiLinePrintF( "Liturgy Season:\t", seasonString , desiredDispLen  + 13, 0 );
    }

    // Advent related quote
    if ( strcmp( season, "Advent Season" ) == 0 ) {
        // scripture.csv index: [15-40]
        // Nativity scripture quotes from the Gospel of Luke
        int idxBookmark = 15;

        struct tm advent_start  = setSpecificDate( todaysDate.tm_year + 1900, 11, 1 ); // Dec 1
            shiftTowardSunday( &advent_start ); // First Sun of Advent

        scriptureFK          = (int)daysElapsed( advent_start, todaysDate) + 15;

        char * originalCsv = rosary_db_struct -> scripture_dbArray[ scriptureFK ].scriptureText;
        char * scriptureQuote = cleanQuote( originalCsv ); // clean csv text formatting

        sprintf( seasonString, "%s - %s ( %s )", season, feast, verboseDate ); // combine strings
        multiLinePrintF( "Liturgy Season:\t", seasonString , desiredDispLen + 13 , 0 );
        printf( "\n" );
        multiLinePrintF( "Scripture:\t", scriptureQuote , desiredDispLen, 0 );
    }

    // Post Nativity / Christmastide quote
    if ( strcmp(season, "Christmas Season" ) == 0 ) {
        // scripture.csv index: [41-53]
        int idxBookmark = 41;
        int remainingDec = 31 - 25; // elapsed days in Christmas tide December
        int remainingJan = 1 + 5;   // remaining days of Christmastide January

        // Remaining days in December
        struct tm dec_thirtyone  = setSpecificDate( todaysDate.tm_year + 1900, 11, 31 ); // Dec 31
        remainingDec = (int)daysRemaining( todaysDate, dec_thirtyone);

        // Initial days in January
        struct tm epiphany = setSpecificDate( todaysDate.tm_year + 1900, 0, 6 );
        shiftTowardSunday( &epiphany );                    // Epiphany Sunday
        shiftJesusBaptism( &epiphany );                    // Baptism of Jesus

        remainingJan = (int)daysRemaining( todaysDate, epiphany );

        if ( remainingDec <= 6 ) {
            scriptureFK = ( 6 -remainingDec ) + idxBookmark;
        } else if ( remainingJan >= 0 ) {
            scriptureFK = ( 6 + remainingJan ) + idxBookmark;
        }

        char * originalCsv = rosary_db_struct -> scripture_dbArray[ scriptureFK ].scriptureText;
        char * scriptureQuote = cleanQuote( originalCsv );      // clean csv text formatting

        sprintf( seasonString, "%s - %s ( %s )", season, feast, verboseDate ); // combine strings
        multiLinePrintF( "Liturgy Season:\t", seasonString , desiredDispLen + 13, 0 );
        printf( "\n" );
        multiLinePrintF( "Scripture:\t", scriptureQuote , desiredDispLen, 0 );
    }

    // Lent related quote
    if ( strcmp(season, "Lent Season") == 0 ) {
        // scripture.csv index: [91-151]
        int idxBookmark = 91;

        struct tm easter_sunday = setEasterDate( todaysDate.tm_year + 1900 );   // PFM Calculation Result
        struct tm ash_wednesday = subtractDays( easter_sunday, 46 );            // count back to ash wed

        scriptureFK = (int)daysElapsed( ash_wednesday, todaysDate) + idxBookmark;

        char * originalCsv    = rosary_db_struct -> scripture_dbArray[ scriptureFK ].scriptureText;
        char * scriptureQuote = cleanQuote( originalCsv ); // clean csv text formatting

        sprintf( seasonString, "%s - %s ( %s )", season, feast, verboseDate ); // combine strings
        multiLinePrintF( "Liturgy Season:\t", seasonString , desiredDispLen  + 13, 0 );
        printf( "\n" );
        multiLinePrintF( "Scripture:\t", scriptureQuote , desiredDispLen, 0 );

    }

    // Easter related quote
    if ( strcmp(season, "Easter Season") == 0 ) {
        // scripture.csv index: [152-200]
        int idxBookmark = 152;

        struct tm easter_sunday = setEasterDate( todaysDate.tm_year + 1900 ); // PFM Calculation Result

        scriptureFK          = (int)daysElapsed( easter_sunday, todaysDate) + idxBookmark;

        char * originalCsv = rosary_db_struct -> scripture_dbArray[ scriptureFK ].scriptureText;
        char * scriptureQuote = cleanQuote( originalCsv ); // clean csv text formatting

        sprintf( seasonString, "%s - %s ( %s )", season, feast, verboseDate ); // combine strings
        multiLinePrintF( "Liturgy Season:\t", seasonString , desiredDispLen  + 13, 0 );
        printf( "\n" );
        multiLinePrintF( "Scripture:\t", scriptureQuote , desiredDispLen, 0 );
    }

    printf("\n");
    borderCharPrintF( ".", desiredDispLen );
}
