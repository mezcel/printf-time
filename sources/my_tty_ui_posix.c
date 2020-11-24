/* my_tty_ui_posix.c
 * USECASE: Supliment the my_tty_ui.c source code.
 *
 * Counterpart to ../sources/my_tty_ui_win.c
 * For use on Debian Linux POSIX terminal environments.
 * Visual Studio's compiler returns errors if non-comliant
 * libraries and functions are mentioned in the code algorithm.
 * */

#include <sys/ioctl.h>  // ioctl(), TIOCGWINSZ, struct winsize
#include <unistd.h>     // STDOUT_FILENO, fflush(stdout)
#include <time.h>       // my_callendar.h structs

#include "../headers/my_tty_ui.h"

void clearScreen() {

    // POSIX
    // system( "@cls||clear" );
    system( "clear" );

}

int returnScreenWidth() {

    // return a number which represents how long/wide the screen text should be
    int col_length = 95;    // Estimate and proximate ( 85 - 120 ) chars screen width

    struct winsize w;                               // terminal tty info
    ioctl( STDOUT_FILENO, TIOCGWINSZ, &w );         // tty col/row
    col_length =  w.ws_col;

    return col_length;

}

void deactivateEcho() {

    system( "stty -echo" );
    system( "stty cbreak" );

}

void activateEcho() {

    system( "stty echo" );                          // Make echo work
    system( "stty -cbreak" );                       // read one key without pressing enter

}

void pressEnter() {

    /*
     * Wait for User to press enter
     * */

    fflush(stdout);

    char chEnter = getchar();

    while( chEnter != 10 ) {
        chEnter = getchar();
    }

    fflush(stdout);

}

int pressKeyContinue( displayFeastVariables_t queryFeastViewStruct,
        int navigtionPosition, int weekdayNo, int desiredDispLen ) {

    // Increment or decrement the next desired position in the rosary sequence
    // uses traditional vim or "retro game" navigation keys

    fflush(stdout);
    char ch = getchar();

    // Workaround for the arrow key input buffer
    if ( ch == '\033') {        // if the first value is esc
        getchar();              // skip the [

        switch( getchar() ) {   // the real value
            case 'A':           // code for arrow up
                ch = 65;
                break;
            case 'B':           // code for arrow down
                ch = 66;
                break;
            case 'C':           // code for arrow right
                ch = 67;
                break;
            case 'D':           // code for arrow left
                ch = 68;
                break;
        }
    }

    switch ( ch ) {
        // help screen
        case 65:                                    // ASCII up arrow
        case 66:                                    // ASCII down arrow
        case 'w':
        case 's':
        case 'j':
        case 'k':
            clearScreen();
            infoPage( queryFeastViewStruct, weekdayNo, desiredDispLen, " Instructions: " );
            break;

        // Navigate forward
        case 67:                                    // ASCII right arrow
        case 10:                                    // ASCII enter key
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
        case 68:                                    // ASCII left arrow
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
            fflush(stdout);
            //printf( "\n" );
    }

    return navigtionPosition;

}

void bashrcHolidayDisplay( rosary_db_t *rosary_db_struct, displayFeastVariables_t queryFeastViewStruct,
        displayVariables_t queryViewStruct, char *verboseDate, int desiredDispLen ) {

    // display feast day or liturgical season state in a bash terminal

    int scriptureFK;
    struct tm todaysDate = returnTodaysDate(); // Today's date

    char *season = stringLiturgicalSeason();
    char *feast  = stringFeast( queryFeastViewStruct.feastDay,
                    queryFeastViewStruct.feastMonth,
                    queryFeastViewStruct.feastName );

    char *monthDay = verboseDate;
    monthDay[strlen(verboseDate)-6] = '\0'; // trim out the year chars from date. Ex: ", 2020"

    if ( desiredDispLen > 79 ) { desiredDispLen = 79; } // Limit display row char length

    borderCharPrintF( "░", desiredDispLen );
    // ansi bold white = \e[1;37m and regular white = \e[0;37m
    printf( "\n\e[1;37mLiturgy Season:\e[0;37m\t%s - %s\t(%s)\n", season, feast, monthDay );

    // Advent related quote
    if ( strcmp( season, "Advent Season" ) == 0 ) {
        // scripture.csv index: [15-40]
        // Nativity scripture quotes from the Gospel of Luke
        int idxBookmark = 15;

        struct tm advent_start  = setSpecificDate( todaysDate.tm_year + 1900, 11, 1 ); // Dec 1
            shiftTowardSunday( &advent_start ); // First Sun of Advent

        scriptureFK          = (int)daysElapsed( advent_start, todaysDate) + 15;
        char *scriptureQuote = rosary_db_struct -> scripture_dbArray[ scriptureFK ].scriptureText;

        multiLinePrintF( "\e[1;37mScripture:\e[0;37m\t", scriptureQuote , desiredDispLen, 0 );
        printf("\n");
    }

    // Post Nativity quote
    if (strcmp(season, "Christmas Season") == 0) {
        // scripture.csv index: [51-90]
        int idxBookmark = 51;

        struct tm christmas_day = setSpecificDate( todaysDate.tm_year + 1900, 11, 25 ); // wed Dec 25

        scriptureFK          = (int)daysElapsed( christmas_day, todaysDate) + idxBookmark;
        char *scriptureQuote = rosary_db_struct -> scripture_dbArray[ scriptureFK ].scriptureText;

        multiLinePrintF( "\e[1;37mScripture:\e[0;37m\t", scriptureQuote , desiredDispLen, 0 );
        printf("\n");
    }

    // Lent related quote
    if (strcmp(season, "Lent Season") == 0) {
        // scripture.csv index: [91-151]
        int idxBookmark = 91;

        struct tm easter_sunday = setEasterDate( todaysDate.tm_year + 1900 ); // PFM Calculation Result
        struct tm ash_wednesday = subtractDays( easter_sunday, 46 ); // count back to ash wed

        scriptureFK          = (int)daysElapsed( ash_wednesday, todaysDate) + idxBookmark;
        char *scriptureQuote = rosary_db_struct -> scripture_dbArray[ scriptureFK ].scriptureText;

        multiLinePrintF( "\e[1;37mScripture:\e[0;37m\t", scriptureQuote , desiredDispLen, 0 );
        printf("\n");
    }

    // Easter related quote
    if (strcmp(season, "Easter Season") == 0) {
        // scripture.csv index: [152-200]
        int idxBookmark = 152;

        struct tm easter_sunday = setEasterDate( todaysDate.tm_year + 1900 ); // PFM Calculation Result

        scriptureFK          = (int)daysElapsed( easter_sunday, todaysDate) + idxBookmark;
        char *scriptureQuote = rosary_db_struct -> scripture_dbArray[ scriptureFK ].scriptureText;

        multiLinePrintF( "\e[1;37mScripture:\e[0;37m\t", scriptureQuote , desiredDispLen, 0 );
        printf("\n");
    }

    borderCharPrintF( "░", desiredDispLen );
    printf("\n");

}
