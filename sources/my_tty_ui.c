/*
 * my_tty_ui.c
 * */

#include <stdio.h>
#include <stdlib.h>		// calloc(), realloc(), malloc(), system(), free()
#include <string.h>

#include "../headers/my_calendar.h"
#include "../headers/my_file_to_struct.h"
#include "../headers/my_tty_ui.h"

// Seperate files used to minimze errors when compiling on Win10
#ifdef __unix__
	// Ideal functionality, available on Debian linux
	#include "../sources/my_tty_ui_posix.c"
#else
	// win10 workaround
	#include "../sources/my_tty_ui_win.c"
#endif

int initialMystery( int weekdayNo ) {
	// return the start of a mystery sequence depending on which day of the week it is
	int navigtionPosition[ ] = {237, 0, 158, 237, 79, 158, 0};

	if ( ( weekdayNo > 6 ) || ( weekdayNo < 0 ) ) {
		weekdayNo = 0;
	}
	return navigtionPosition[ weekdayNo ];
}

int pressKeyContinue( int navigtionPosition, int isLinux, int weekdayNo, int desiredDispLen ) {
	// Increment or decrement the next desired position in the rosary sequence
	// uses traditional vim or "retro game" navigation keys

	char ch = getchar();

	switch ( ch ) {
		// help screen
		case 65:	// ASCII up arrow
		case 66:	// ASCII down arrow
			printf( "\n" );
		case 'w':
		case 's':
		case 'j':
		case 'k':
			clearScreen( isLinux );
			infoPage( weekdayNo, desiredDispLen, " Instructions: " );
			break;

		// Navigate forward

		case 67:	// ASCII right arrow
			printf( "\n" );
		case 10:	// ASCII enter key
		case 'n':	// [ n key ] navigates 1 step forward
		case 'l':	// vim input
		case 'd':	// game input
			if ( navigtionPosition < 315 ) {
				navigtionPosition++;
			} else {
				navigtionPosition = 0; // loop to the beginning
			}
			break;

		// Navigate backward

		case 68:	// ASCII left arrow
			printf( "\n" );
		case 32:	// ASCII spacebar
		case 'h':	// vim input
		case 'a':	// game input
		case 'b':	// [ b key ] navigates 1 step back
			if ( navigtionPosition > 1 ) {
				navigtionPosition--;
			} else {
				navigtionPosition = 315; // loop back to the end
			}
			break;

		// Exit Application

		//case 27:	// ASCII esc key
		case 'q':	// [ q key ] quits the app
			printf( "\n\n Quit App \n", ch );
			navigtionPosition = 316; // any integer greater than 315
			break;

		// Non-mapped keys

		default:	// other key entries
			//printf( "%d", ch );
			printf( "\n" );
			break;
	}

	return navigtionPosition;
}

void clearScreen( int isLinux ) {
	// system( "@cls||clear" );
	if ( isLinux == 1 ) {
		system( "clear" );	// linux
	} else {
		system( "@cls" );		// win
	}
}

void borderCharPrintF( char *charSymbol, int borderWidth ) {
	// print a sequence of chars which act as a visual border/divider
	for ( int i = 0; i < borderWidth; i++ ) {
		printf( "%s", charSymbol );
	}
}

void multiLinePrintF( char *labelChars, char *strIn, int desiredLineLength, int minRows ) {
	int screenWidth = desiredLineLength;	// max chars per screen line width
	int inputLength = ( int )strlen( strIn );	// number of chars contained in input string
	int labelColChars = 17;					// chars used in the label col
	int max_line_chars = screenWidth - labelColChars;
	int rowCounter = 1;

	printf( "%s", labelChars ); // print the content label, initial printf

	if ( inputLength < max_line_chars ) { // short enough to be 1 line
		printf( "%s\n\t\t", strIn );
		rowCounter++;
	} else { // longer than one line

		// input string to an array of words
		//char tmpStringArray[ inputLength ];
		char *tmpStringArray = malloc( inputLength + 1 );
		strcpy( tmpStringArray, strIn );
		char *delimiter = " ";
		char *token = strtok( tmpStringArray, delimiter ); // array of words

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
				printf( "\n\t\t%s ", token ); // start new line indent
				rowCounter++;
			}

			token = strtok( NULL, delimiter ); // get the next word
		}
	}

	// Add empty rows
	if ( minRows != 0 ) {
		if ( rowCounter < minRows ) {
			int difference = minRows - rowCounter;
			for ( int i = 0; i < difference; i++ ) {
				printf( "\n" );
			}
		}
	}
}

void splashPage( int desiredDispLen, int isLinux ) {
	int strLength, center;

	char *title = "Scriptural Rosary";
	char *author = "by Mezcel";
	char *about = "Wirtten in C for use in a ( CLI ) POSIX/GNU program environment.";
	char *git = "https://github.com/mezcel/printf-time.git";

	printf( "\n\n" );

	strLength = ( int )strlen( title );
	center = ( desiredDispLen - strLength ) / 2;
	borderCharPrintF( " ", center );
	printf( "%s\n", title );

	strLength = ( int )strlen( author );
	center = ( desiredDispLen - strLength ) / 2;
	borderCharPrintF( " ", center );
	printf( "%s\n\n", author );

	strLength = ( int )strlen( about );
	center = ( desiredDispLen - strLength ) / 2;
	borderCharPrintF( " ", center );
	printf( "%s\n", about );

	strLength = ( int )strlen( git );
	center = ( desiredDispLen - strLength ) / 2;
	borderCharPrintF( " ", center );
	printf( "%s\n\n\n\n", git );

	borderCharPrintF( ":", desiredDispLen );
	printf( "\n\n press [ any key ] to continue ... " );

	getchar();	// pause for keyboard input
	clearScreen( isLinux ); // posix
}

void infoPage( int weekdayNo, int desiredDispLen, char *titleLabel ) {
	// display intro and instructions
	char *season = stringLiturgicalSeason();
	char *feast = stringFeast();
	char *aboutString ="\tThis program is a scripture rosary for the command line interface ( CLI ). This app reads from a scripture database arranged in an ER schema. English readings are quoted from The New American Bible ( CSV files ), and Latin readings are quoted from the Vulgate Bible ( JSON file ). Additional enclosed readings are curated from a variety of different Rosary prayer guides. This program was developed in C/GCC and tested for use in BASH.";

	int titleLabelLength = ( int )strlen( titleLabel );
	borderCharPrintF( ":", 3 );
	printf( titleLabel );
	borderCharPrintF( ":", ( desiredDispLen - ( titleLabelLength + 3 ) ) );
	printf( "\n" );

	multiLinePrintF( "\n About:\n\t", aboutString, desiredDispLen, 0 );

	printf( "\n\n Display:\n\t\tOptimal Terminal Display: ( +25 rows ) x ( +100 cols ) to Full Screen.\n" );
	printf( "\n\t\tNAB English ( mode ):\t./ttyRosary -n\n\t\tVulgate Latin ( mode ):\t./ttyRosary -v\n" );

	printf( "\n Keyboard:\n\t\tq = quit app, space = back, enter = next, help = up/down\n" );
	printf( "\n\t\tvi controls:\th = back, l = next" );
	printf( "\n\t\tgame controls:\ta = back, d = next" );
	printf( "\n\n Source Code:\n\t\thttps://github.com/mezcel/printf-time.git\n\n" );

	borderCharPrintF( ":", desiredDispLen );

	printf( "\n\n Today's %s mystery is the %s Mystery. ( %s / %s )\n\n",
			retrunWeekdayName( weekdayNo ),
			returnWeekdayMystery( weekdayNo ),
			season, feast );

	borderCharPrintF( ":", desiredDispLen );
	printf( "\n\n press [ any key ] to continue ... " );

	getchar();	// pause for keyboard input
}

void updateDisplayVariablesStruct( rosary_db_t *rosary_db_struct, displayVariables_t *queryViewStruct, int navigtionPosition ) {

	int rosaryPositionID = 0, beadFK = 0, decadeFK = 0, messageFK = 0, mysteryFK = 0,
		prayerFK = 0, scriptureFK = 0, loopBody = 0;
	int smallbeadPercent = 0, mysteryPercent = 0;
	int decadeNo 		= 0, mysteryNo = 0;

	char *beadType, *decadeName, *decadeInfo, *mesageText, *mysteryName;
	char *scriptureText, *prayerText;

	// Get values from DB Struct
	rosaryPositionID = rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].rosaryBeadID;
	beadFK		= rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].beadIndex;
	decadeFK 	= rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].decadeIndex;
	messageFK 	= rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].messageIndex;
	mysteryFK 	= rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].mysteryIndex;
	prayerFK 	= rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].prayerIndex;
	scriptureFK = rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].scriptureIndex;
	loopBody 	= rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].loopBody;
	smallbeadPercent = rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].smallbeadPercent;
	mysteryPercent 	= rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].mysteryPercent;

	beadType 	= rosary_db_struct -> bead_dbArray[ beadFK ].beadType;
	decadeName 	= rosary_db_struct -> decade_dbArray[ decadeFK ].decadeName;
	decadeInfo 	= rosary_db_struct -> decade_dbArray[ decadeFK ].decadeInfo;
	mesageText 	= rosary_db_struct -> message_dbArray[ messageFK ].mesageText;
	mysteryName = rosary_db_struct -> mystery_dbArray[ mysteryFK ].mysteryName;
	scriptureText = rosary_db_struct -> scripture_dbArray[ scriptureFK ].scriptureText;
	prayerText 	= rosary_db_struct -> prayer_dbArray[ prayerFK ].prayerText;

	decadeNo 	= rosary_db_struct -> decade_dbArray[ decadeFK ].decadeNo;
	mysteryNo 	= rosary_db_struct -> mystery_dbArray[ mysteryFK ].mysteryNo;

	// Populate/Update Query View Struct
	queryViewStruct -> rosaryPositionID = rosaryPositionID;
	queryViewStruct -> beadFK 		= beadFK;
	queryViewStruct -> decadeFK 	= decadeFK;
	queryViewStruct -> messageFK 	= messageFK;
	queryViewStruct -> mysteryFK 	= mysteryFK;
	queryViewStruct -> prayerFK 	= prayerFK;
	queryViewStruct -> scriptureFK 	= scriptureFK;
	queryViewStruct -> loopBody 	= loopBody;
	queryViewStruct -> smallbeadPercent = smallbeadPercent;
	queryViewStruct -> mysteryPercent = mysteryPercent;

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

void outputTtyDisplay( displayVariables_t queryViewStruct, int desiredDispLen, char *titleLabel, int isLinux ) {
	// Render all rosary bead content onto the screen
	int minFruitsRow = 3,
		minBackgroundRows = 4,
		minScriptureRows = 4,
		minPrayerRows = 4;

	int trailingDots = 0,
		historyDots = 0;

	int titleLabelLength	= ( int )strlen( titleLabel ) + 3;
	int mysteryLabelLength	= ( int )strlen( queryViewStruct.mysteryName ) + 4;

	char *footerLabel		= " Rosary Progress ";
    int footerLabelLength	= ( int )strlen( footerLabel ) + 3;

	char *rosaray_region_string;
	int segment_whole, segment_part, decade_flag, footerLabel2Length;

	if ( queryViewStruct.loopBody == 1 ) {
		rosaray_region_string = "Rosary Body";
		footerLabel2Length	= ( int )strlen( rosaray_region_string ) + 5;
		segment_whole 		= 10;
		decade_flag 		= 5;
		segment_part		= queryViewStruct.smallbeadPercent;
	} else {
		if ( queryViewStruct.mysteryPercent == 50 ) {
		//if ( ( queryViewStruct.prayerFK == 7 ) || ( queryViewStruct.prayerFK == 8 ) ) {
			rosaray_region_string = "Conclusion Prayers";
			footerLabel2Length = ( int )strlen( rosaray_region_string ) + 5;
			segment_whole = 2;
			decade_flag = 0;
			segment_part = queryViewStruct.smallbeadPercent / 5;
			minFruitsRow = 0;
			minBackgroundRows = 0;
			minScriptureRows = 0;
			minPrayerRows = 7;
		} else {
			rosaray_region_string = "Introduction Prayers";
			footerLabel2Length = ( int )strlen( rosaray_region_string ) + 5;
			segment_whole = 7;
			decade_flag = 0;
			segment_part = queryViewStruct.smallbeadPercent;
			minFruitsRow = 0;
			minBackgroundRows = 0;
			minScriptureRows = 0;
			minPrayerRows = 7;
		}
	}

	if ( segment_whole == 10 ) {
		historyDots = ( queryViewStruct.decadeNo * 10 ) - segment_whole;
		trailingDots = 50 - ( segment_whole * queryViewStruct.decadeNo );
	} else if ( segment_whole == 7 ) {
		trailingDots = 50 - segment_whole;
	} else {
		historyDots = 48;
	}

	clearScreen( isLinux ); // optimized for posix

	// header

	borderCharPrintF( ":", 3 );
	printf( titleLabel );
	borderCharPrintF( ":", desiredDispLen - titleLabelLength - mysteryLabelLength );
	printf( " %s", queryViewStruct.mysteryName );
	borderCharPrintF( ":", 3 );

	// body

	printf( "\n\n Decade:\t%s", queryViewStruct.decadeName );
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
