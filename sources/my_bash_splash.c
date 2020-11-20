/*
 * my_tty_ui.c
 * */

#include <stdio.h>
#include <stdlib.h>     // calloc(), realloc(), malloc(), system(), free()
#include <string.h>

#include "../headers/my_calendar.h"
#include "../headers/my_file_to_struct.h"
#include "../headers/my_tty_ui.h"

// Separate files used to minimize errors when compiling on Win10
#ifdef __unix__
    // Optimized functions for POSIX
    #include "../sources/my_tty_ui_posix.c"
#else
    // Optimized functions for Win10 ( compile workarounds )
    #include "../sources/my_tty_ui_win.c"
#endif

int returnLaunchArgument( int argc, char *argv ) {
    nabFlag = 1;
    return nabFlag;
}

int initialMystery( int weekdayNo ) {

    // return the start of a mystery sequence depending on which day of the week it is

    int navigtionPosition[ ] = { 237, 0, 158, 237, 79, 158, 0 };

    if ( ( weekdayNo > 6 ) || ( weekdayNo < 0 ) ) {
        weekdayNo = 0;
    }
    return navigtionPosition[ weekdayNo ];

}

void borderCharPrintF( char *charSymbol, int borderWidth ) {
    // print a sequence of chars which act as a visual border/divider

    for ( int i = 0; i < borderWidth; i++ ) {
        printf( "%s", charSymbol );
    }

}

void multiLinePrintF( char *labelChars, char *strIn, int desiredLineLength, int minRows ) {

    // Automatically wrap string arrays that are longer than 1 terminal row

    int screenWidth     = desiredLineLength;                // max chars per screen line width
    int inputLength     = ( int )strlen( strIn );           // number of chars contained in input string
    int labelColChars   = 17;                               // chars used in the label col
    int max_line_chars  = screenWidth - labelColChars;
    int rowCounter      = 1;

    printf( "%s", labelChars );                             // print the content label, initial printf

    if ( inputLength < max_line_chars ) {                   // short enough to be 1 line
        printf( "%s\n\t\t", strIn );
        rowCounter++;
    } else { // longer than one line

        // input string to an array of words
        char *tmpStringArray = malloc( inputLength + 1 );
        strcpy( tmpStringArray, strIn );
        char *delimiter = " ";
        char *token = strtok( tmpStringArray, delimiter );  // array of words

        // init counters
        int chars_in_a_word = 0;
        int potential_line_length = 0;
        int charCounter = 0;

        // parse each word in the long sentence
        while ( token != NULL ) {
            chars_in_a_word = ( int )strlen( token );
            potential_line_length = chars_in_a_word + charCounter;

            if( potential_line_length < max_line_chars ) {
                charCounter += chars_in_a_word + 1;
                printf( "%s ", token );
            } else {
                charCounter = chars_in_a_word;
                printf( "\n\t\t%s ", token );               // start new line indent
                rowCounter++;
            }

            token = strtok( NULL, delimiter );              // get the next word
        }
    }

    // Add empty rows for visual spacing
    if ( minRows != 0 ) {
        if ( rowCounter < minRows ) {
            int difference = minRows - rowCounter;
            for ( int i = 0; i < difference; i++ ) {
                printf( "\n" );
            }
        }
    }

}

void updateFeastDisplayStruct( feast_db_t *feast_db_struct, displayFeastVariables_t *queryFeastViewStruct,
        int todayDay, int todayMonth, int recordCount ) {

    int feastDay    = 0,
        feastMonth  = 0,
        counter     = 0;
    int feastID,
        isFeastDay  = 0; // flag if today's date is a user defined feast date

    char *feastName, *monthName;

    while ( counter < recordCount  ) {
        feastDay    = feast_db_struct -> feast_dbArray[ counter ].feastDay;
        feastMonth  = feast_db_struct -> feast_dbArray[ counter ].feastMonth;

        if ( todayDay == feastDay ) {
            if ( todayMonth == feastMonth ) {
                isFeastDay = 1;
                break;
            }
        }

        counter++;
    }

    if ( isFeastDay ) {
        feastID     = feast_db_struct -> feast_dbArray[ counter ].feastID;
        feastDay    = feast_db_struct -> feast_dbArray[ counter ].feastDay;
        feastMonth  = feast_db_struct -> feast_dbArray[ counter ].feastMonth;

        feastName   = feast_db_struct -> feast_dbArray[ counter ].feastName;
        monthName   = feast_db_struct -> feast_dbArray[ counter ].monthName;

        // int's
        queryFeastViewStruct -> feastID     = feastID;
        queryFeastViewStruct -> feastDay    = feastDay;
        queryFeastViewStruct -> feastMonth  = feastMonth;

        // strings
        strcpy( queryFeastViewStruct -> feastName, feastName );
        strcpy( queryFeastViewStruct -> monthName, monthName );
    } else {
        // Populate queryFeastViewStruct with dummy values
        // int's
        queryFeastViewStruct -> feastID     = 0;
        queryFeastViewStruct -> feastDay    = 0;
        queryFeastViewStruct -> feastMonth  = 0;

        // strings
        strcpy( queryFeastViewStruct -> feastName, "" );
        strcpy( queryFeastViewStruct -> monthName, "" );

    }

}

void FeastOneliner( displayFeastVariables_t queryFeastViewStruct) {

    // display feast day or liturgical season state

    char *season        = stringLiturgicalSeason();
    char *feast         = stringFeast( queryFeastViewStruct.feastDay,
                                       queryFeastViewStruct.feastMonth,
                                       queryFeastViewStruct.feastName );

    printf("Liturgical Season:\n\t%s\t%s\n\tMsg.=%s\n", season, feast, "context string");

}
