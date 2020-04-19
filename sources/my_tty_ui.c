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

    int nabFlag = 0;
    if ( argc == 2 ) {                  // set Latin Vulgate from app launch
        nabFlag = strcmp( "-v", argv );
    } else {                            // no input, default to NAB English
        nabFlag = 1;
    }

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

void splashPage( int desiredDispLen, char *verboseDate ) {

    // display a decorative cover page

    int strLength, center;

    char *title     = "Scriptural Rosary",
         *author    = "by Mezcel",
         *about     = "Wirtten in C for use in a ( CLI ) POSIX/GNU program environment.",
         *git       = "https://github.com/mezcel/printf-time.git";

    printf( "\n\n" );

    strLength   = ( int )strlen( title );
    center      = ( desiredDispLen - strLength ) / 2;
    borderCharPrintF( " ", center );
    printf( "%s\n", title );

    strLength   = ( int )strlen( author );
    center      = ( desiredDispLen - strLength ) / 2;
    borderCharPrintF( " ", center );
    printf( "%s\n\n", author );

    strLength   = ( int )strlen( about );
    center      = ( desiredDispLen - strLength ) / 2;
    borderCharPrintF( " ", center );
    printf( "%s\n", about );

    strLength   = ( int )strlen( git );
    center      = ( desiredDispLen - strLength ) / 2;
    borderCharPrintF( " ", center );
    printf( "%s\n\n\n\n", git );

    strLength   = ( int )strlen( verboseDate );
    center      = ( desiredDispLen - strLength ) / 2;
    borderCharPrintF( " ", center );
    printf( "%s\n\n\n\n", verboseDate );

    borderCharPrintF( ":", desiredDispLen );

    pressEnter();   // wait for user to press enter
    clearScreen();

}

void infoPage( displayFeastVariables_t queryFeastViewStruct, int weekdayNo, int desiredDispLen, char *titleLabel ) {

    // display about and instructions

    char *season        = stringLiturgicalSeason();
    char *feast         = stringFeast( queryFeastViewStruct.feastDay,
                                       queryFeastViewStruct.feastMonth,
                                       queryFeastViewStruct.feastName );
    char *aboutString   = "\tThis program is a scripture rosary for the command line interface ( CLI ). \
                            This app reads from a scripture database arranged in an ER schema. \
                            English readings are quoted from The New American Bible ( CSV files ), \
                            and Latin readings are quoted from the Vulgate Bible ( JSON file ). \
                            User defined feast days can be modified by editing the \"database/csv/feast.csv\" file.";

    int titleLabelLength = ( int )strlen( titleLabel );
    borderCharPrintF( ":", 3 );
    printf( titleLabel );
    borderCharPrintF( ":", ( desiredDispLen - ( titleLabelLength + 3 ) ) );
    printf( "\n" );

    multiLinePrintF( "\n About:\n\t", aboutString, desiredDispLen, 0 );

    printf( "\n\n Display:\n\t\tOptimal Terminal Display: ( +25 rows ) x ( +100 cols ) to Full Screen.\t(cols: %d)\n",
        returnScreenWidth() );

    printf("\n\t\tNAB English\t( POSIX TTY ):\t\t./ttyRosary -n\n");
    printf("\t\t\t\t( CMD/Powershell ):\t.\\ttyRosary.exe\n");
    printf("\t\tVulgate Latin\t( Linux GTK ):\t\t./ttyRosary -v\n");

    printf( "\n Keyboard:\n\t\tGeneral:\t\tq = quit app,\thelp = up/down" );
    printf( "\n\t\tVi controls:\t\th = back,\t   l = next" );
    printf( "\n\t\tGame controls:\t\ta = back,\t   d = next" );
    printf( "\n\t\tJump to Mystery:\t0 = Today's mystery\t1 = Joyful\t2 = Sorrowful" );
    printf( "\n\t\t\t\t\t\t\t\t3 = Luminous\t4 = Glorious" );
    printf( "\n\n Source Code:\n\t\thttps://github.com/mezcel/printf-time.git\n\n" );

    borderCharPrintF( ":", desiredDispLen );

    printf( "\n\n Today's %s mystery is the %s Mystery. ( %s / %s )\n\n",
        retrunWeekdayName( weekdayNo ),
        returnWeekdayMystery( weekdayNo ),
        season, feast );

    borderCharPrintF( ":", desiredDispLen );

    pressEnter();   // wait for user to press enter

}

void mysteryCoverPage( displayVariables_t queryViewStruct, int navigtionPosition, int desiredDispLen ) {

    /*
     * Display a welcome page at the start of each Mystery
     * Display some background behind the mystery
     * */

    int isNewMystery, strLength, center, minAboutRows;
    char *title, *about, *quotationSource;;

    switch ( navigtionPosition ) {
        case 0:
            isNewMystery = 1;
            about = "God wants us to have complete joy. He created us for it. Jesus came so we could be immersed in complete joy: \"I have told you this so that my joy might be in you and your joy might be complete\" (John 15:11). The Joyful Mysteries celebrate when joy entered the world, when God entered into the mess of the world because of his incredible love for us.";
            quotationSource = "https://dynamiccatholic.com/rosary/unlocking-mysteries-rosary";
            break;
        case 79:
            isNewMystery = 1;
            about = "The presence of Jesus is powerful. When he was walking the earth his presence demanded a response. Especially those moments that revealed his divinity. The Luminous Mysteries, often referred to as the Mysteries of Light, capture some incredible moments filled with Jesus' divinity. They proclaim: “This is the chosen one, the one you have been waiting upon for so very long, this is the Messiah, this is the Son of God!\" How will you respond?";
            quotationSource = "https://dynamiccatholic.com/rosary/unlocking-mysteries-rosary";
            break;
        case 158:
            isNewMystery = 1;
            about = "For more than 2,000 years, the heroes, champions, and saints of Christianity have been meditating on the passion and death of Jesus Christ. Perhaps it is time we all spent a little time exploring the genius of the cross. The world changed at three o’clock on that Friday afternoon when Jesus laid down his life for us. The Sorrowful Mysteries of the Rosary meditate on key moments in the passion and death of Jesus.";
            quotationSource = "https://dynamiccatholic.com/rosary/unlocking-mysteries-rosary";
            break;
        case 237:
            isNewMystery = 1;
            about = "In the Glorious Mysteries, we not only see the beautiful glory of God, but we see the incredible dream that God has for each one of us. He wants us to live lives of incredible joy and purpose, and ultimately live with him for eternity.";
            quotationSource = "https://dynamiccatholic.com/rosary/unlocking-mysteries-rosary";
            break;

        default:
            isNewMystery = 0;
            break;
    }

    if ( isNewMystery ) {
        title = queryViewStruct.mysteryName;
        minAboutRows = 0;

        clearScreen();
        printf( "\n\n" );

        strLength   = ( int )strlen( title );
        center      = ( desiredDispLen - strLength ) / 2;
        borderCharPrintF( " ", center );
        printf( "%s\n", title );

        printf( "\n\n" );

        multiLinePrintF( " About:\t\t", about, desiredDispLen, minAboutRows );

        printf( "\n\n" );

        strLength   = ( int )strlen( quotationSource );
        center      = ( desiredDispLen - strLength ) / 2;
        borderCharPrintF( " ", center );
        printf( "%s\n", quotationSource );

        printf( "\n\n\n\n" );

        borderCharPrintF( ":", desiredDispLen );

        pressEnter();   // wait for user to press enter
    }

}

void updateDisplayVariablesStruct( rosary_db_t *rosary_db_struct, displayVariables_t *queryViewStruct,
        int navigtionPosition ) {

    // Redefine all string variables used in rosary text display

    int rosaryPositionID = 0,   // Rosary DB Query Keys
        beadFK           = 0,
        decadeFK         = 0,
        messageFK        = 0,
        mysteryFK        = 0,
        prayerFK         = 0,
        scriptureFK      = 0,
        loopBody         = 0;   // Main Prayer Circuit Flag
    int smallbeadPercent = 0,   // Progress flags
        mysteryPercent   = 0;
    int decadeNo         = 0,
        mysteryNo        = 0;

    char *beadType, *decadeName, *decadeInfo, *mesageText, *mysteryName;
    char *scriptureText, *prayerText;

    // Get values from DB Struct
    rosaryPositionID = rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].rosaryBeadID;
    beadFK           = rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].beadIndex;
    decadeFK         = rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].decadeIndex;
    messageFK        = rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].messageIndex;
    mysteryFK        = rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].mysteryIndex;
    prayerFK         = rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].prayerIndex;
    scriptureFK      = rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].scriptureIndex;
    loopBody         = rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].loopBody;
    smallbeadPercent = rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].smallbeadPercent;
    mysteryPercent   = rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].mysteryPercent;

    beadType         = rosary_db_struct -> bead_dbArray[ beadFK ].beadType;
    decadeName       = rosary_db_struct -> decade_dbArray[ decadeFK ].decadeName;
    decadeInfo       = rosary_db_struct -> decade_dbArray[ decadeFK ].decadeInfo;
    mesageText       = rosary_db_struct -> message_dbArray[ messageFK ].mesageText;
    mysteryName      = rosary_db_struct -> mystery_dbArray[ mysteryFK ].mysteryName;
    scriptureText    = rosary_db_struct -> scripture_dbArray[ scriptureFK ].scriptureText;
    prayerText       = rosary_db_struct -> prayer_dbArray[ prayerFK ].prayerText;

    decadeNo         = rosary_db_struct -> decade_dbArray[ decadeFK ].decadeNo;
    mysteryNo        = rosary_db_struct -> mystery_dbArray[ mysteryFK ].mysteryNo;

    // Populate/Update Query View Struct
    queryViewStruct -> rosaryPositionID = rosaryPositionID;
    queryViewStruct -> beadFK           = beadFK;
    queryViewStruct -> decadeFK         = decadeFK;
    queryViewStruct -> messageFK        = messageFK;
    queryViewStruct -> mysteryFK        = mysteryFK;
    queryViewStruct -> prayerFK         = prayerFK;
    queryViewStruct -> scriptureFK      = scriptureFK;
    queryViewStruct -> loopBody         = loopBody;
    queryViewStruct -> smallbeadPercent = smallbeadPercent;
    queryViewStruct -> mysteryPercent   = mysteryPercent;

    // strings
    strcpy( queryViewStruct -> beadType, beadType );
    strcpy( queryViewStruct -> decadeName, decadeName );
    strcpy( queryViewStruct -> decadeInfo, decadeInfo );
    strcpy( queryViewStruct -> mesageText, mesageText );
    strcpy( queryViewStruct -> mysteryName, mysteryName );
    strcpy( queryViewStruct -> scriptureText, scriptureText );
    strcpy( queryViewStruct -> prayerText, prayerText );

    // progress info
    queryViewStruct -> decadeNo = decadeNo;
    queryViewStruct -> mysteryNo = mysteryNo;

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

void renderRosaryDisplay( displayVariables_t queryViewStruct, int desiredDispLen, char *titleLabel ) {

    // Render all rosary bead content onto the screen
    // Primary display rendering

    int minFruitsRow      = 3,
        minBackgroundRows = 4,
        minScriptureRows  = 4,
        minPrayerRows     = 4;

    int trailingDots = 0,
        historyDots  = 0;

    int titleLabelLength    = ( int )strlen( titleLabel ) + 3;
    int mysteryLabelLength  = ( int )strlen( queryViewStruct.mysteryName ) + 4;

    char *footerLabel       = " Rosary Progress ";
    int footerLabelLength   = ( int )strlen( footerLabel ) + 3;

    char *rosaray_region_string;
    int segment_whole, segment_part, decade_flag, footerLabel2Length;

    if ( queryViewStruct.loopBody == 1 ) {
        rosaray_region_string = "Rosary Body";
        footerLabel2Length    = ( int )strlen( rosaray_region_string ) + 5;
        segment_whole         = 10;
        decade_flag           = 5;
        segment_part          = queryViewStruct.smallbeadPercent;
    } else {
        if ( queryViewStruct.mysteryPercent == 50 ) {
            rosaray_region_string   = "Conclusion Prayers";
            footerLabel2Length      = ( int )strlen( rosaray_region_string ) + 5;
            segment_whole           = 2;
            decade_flag             = 0;
            segment_part            = queryViewStruct.smallbeadPercent / 5;
            minFruitsRow            = 0;
            minBackgroundRows       = 0;
            minScriptureRows        = 0;
            minPrayerRows           = 7;
        } else {
            rosaray_region_string   = "Introduction Prayers";
            footerLabel2Length      = ( int )strlen( rosaray_region_string ) + 5;
            segment_whole           = 7;
            decade_flag             = 0;
            segment_part            = queryViewStruct.smallbeadPercent;
            minFruitsRow            = 0;
            minBackgroundRows       = 0;
            minScriptureRows        = 0;
            minPrayerRows           = 7;
        }
    }

    if ( segment_whole == 10 ) {
        historyDots  = ( queryViewStruct.decadeNo * 10 ) - segment_whole;
        trailingDots = 50 - ( segment_whole * queryViewStruct.decadeNo );
    } else if ( segment_whole == 7 ) {
        trailingDots = 50 - segment_whole;
    } else {
        historyDots  = 48;
    }

    clearScreen();

    // header

    borderCharPrintF( ":", 3 );
    printf( titleLabel );
    borderCharPrintF( ":", desiredDispLen - titleLabelLength - mysteryLabelLength );
    printf( " %s", queryViewStruct.mysteryName );
    borderCharPrintF( ":", 3 );

    // body

    char *decadeString; // Variable decade names for intros and outros.

    if ( strcmp( queryViewStruct.decadeName, "decade.decadeName" ) ) {
        decadeString = queryViewStruct.mysteryName;
    } else {
        decadeString = queryViewStruct.decadeName;
    }

    printf( "\n\n Decade:\t%s", decadeString );
    multiLinePrintF( "\n\t\t", queryViewStruct.mesageText, desiredDispLen, minFruitsRow );
    multiLinePrintF( "\n Background:\t", queryViewStruct.decadeInfo, desiredDispLen, minBackgroundRows );
    multiLinePrintF( "\n\n Scripture:\t", queryViewStruct.scriptureText, desiredDispLen, minScriptureRows );
    multiLinePrintF( "\n\n Prayer:\t", queryViewStruct.prayerText, desiredDispLen, minPrayerRows );
    printf( "\n\n" );

    // footer

    borderCharPrintF( ":", 3 );
    printf( footerLabel );
    borderCharPrintF( ":", desiredDispLen - footerLabelLength - footerLabel2Length );

    // Progress Status Bar Meter

    printf( " %s ", rosaray_region_string );
    borderCharPrintF( ":", 3 );

    printf( "\n\n Decade Counter\t\t %d / %d\t\t[ ", queryViewStruct.decadeNo, decade_flag );
    if ( queryViewStruct.mysteryPercent != 50 ) {
        borderCharPrintF( "o", queryViewStruct.decadeNo );
        borderCharPrintF( "-", 5 - queryViewStruct.decadeNo );
    } else {
        borderCharPrintF( "o", 5 );
        borderCharPrintF( "-", 0 );
    }
    printf( " ]" );

    if ( segment_whole == 10 ) {
        if ( segment_part < 10 ) {
            printf( "\n Decade Progress\t %d / %d\t\t", segment_part, segment_whole );
        } else {
            printf( "\n Decade Progress\t%d / %d\t\t", segment_part, segment_whole );
        }
        borderCharPrintF( ".", historyDots );
    } else {
        printf( "\n Segment Progress\t %d / %d\t\t", segment_part, segment_whole );
        borderCharPrintF( ".", historyDots );
    }
    printf( "[ " );

    borderCharPrintF( "o", segment_part );
    borderCharPrintF( "-", segment_whole - segment_part );
    printf( " ]" );

    borderCharPrintF( ".", trailingDots );

    if ( queryViewStruct.mysteryPercent < 10 ) {
        printf( "\n Total Progress\t\t %d / 50\t\t[ ", queryViewStruct.mysteryPercent );
    } else {
        printf( "\n Total Progress\t\t%d / 50\t\t[ ", queryViewStruct.mysteryPercent );
    }

    borderCharPrintF( "o", queryViewStruct.mysteryPercent );
    borderCharPrintF( "-", 50 - queryViewStruct.mysteryPercent );
    printf( " ]" );

    printf( "\n:" );

}
