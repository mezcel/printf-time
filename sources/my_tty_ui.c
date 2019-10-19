/*
 * my_tty_ui.c
 * */

#include <stdio.h>
#include <stdlib.h>		// calloc(), realloc(), malloc(), system(), free()
#include <string.h>
#include <sys/ioctl.h>	// ioctl(), TIOCGWINSZ, struct winsize
#include <unistd.h> 	// STDOUT_FILENO

#include "../headers/my_calendar.h"
#include "../headers/my_file_to_struct.h"
#include "../headers/my_tty_ui.h"

int returnScreenWidth(int isLinux) {
	// return a number which represents how long/wide the screen text should be
	int col_length = 85;	// 85 chars wide

	if(isLinux) {
		struct winsize w;						// terminal tty info
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);	// tty col/row
		col_length =  w.ws_col;
	}
	return col_length;
}

int initialMystery(int weekdayNo) {
	// return the start of a mystery sequence depending on which day of the week it is
	int navigtionPosition[] = {237, 0, 158, 237, 79, 158, 0};

	if ( (weekdayNo > 6) || (weekdayNo < 0) ) {
		weekdayNo = 0;
	}
	return navigtionPosition[weekdayNo];
}

int pressKeyContinue(int navigtionPosition, int isLinux, int weekdayNo, int desiredDispLen) {
	// Increment or decrement the next desired position in the rosary sequence
	// uses traditional vim or "retro game" navigation keys

	char ch = getchar();

	switch (ch) {
		// help screen
		case 65:	// ASCII up arrow
		case 66:	// ASCII down arrow
			printf("\n");
		case 'w':
		case 's':
		case 'j':
		case 'k':
			clearScreen(isLinux);
			splashCoverPage(weekdayNo, desiredDispLen, " Instructions: ");
			break;

		// Navigate forward

		case 67:	// ASCII right arrow
			printf("\n");
		case 10:	// ASCII enter key
		case 'n':	// [n key] navigates 1 step forward
		case 'l':	// vim input
		case 'd':	// game input
			if (navigtionPosition < 315) {
				navigtionPosition++;
			} else {
				navigtionPosition = 0; // loop to the beginning
			}
			break;

		// Navigate backward

		case 68:	// ASCII left arrow
			printf("\n");
		case 32:	// ASCII spacebar
		case 'h':	// vim input
		case 'a':	// game input
		case 'b':	// [b key] navigates 1 step back
			if (navigtionPosition > 1) {
				navigtionPosition--;
			} else {
				navigtionPosition = 315; // loop back to the end
			}
			break;

		// Exit Application

		//case 27:	// ASCII esc key
		case 'q':	// [q key] quits the app
			printf("%c\n Quit App \n", ch);
			navigtionPosition = 316; // any integer greater than 315
			break;

		// Non-mapped keys

		default:	// other key entries
			//printf("%d", ch);
			printf("\n");
			break;
	}

	return navigtionPosition;
}

void clearScreen(int isLinux) {
	// system("@cls||clear");
	if (isLinux == 1) {
		system("clear");	// linux
	} else {
		system("@cls");		// win
	}
}

void borderCharPrintF(char *charSymbol, int borderWidth) {
	// print a sequence of chars which act as a visual border/divider
	for (int i = 0; i < borderWidth; i++) {
		printf("%s", charSymbol);
	}
}

void multiLinePrintF(char *labelChars, char *strIn, int desiredLineLength) {
	int screenWidth = desiredLineLength;	// max chars per screen line width
	int inputLength = (int)strlen(strIn);	// number of chars contained in input string
	int labelColChars = 17;					// chars used in the label col
	int max_line_chars = screenWidth - labelColChars;

	printf("%s", labelChars); // print the content label, initial printf

	if ( inputLength < max_line_chars ) { // short enough to be 1 line
		printf("%s\n\t\t", strIn);
	} else { // longer than one line

		// input string to an array of words
		char tmpStringArray[inputLength];
		strcpy(tmpStringArray, strIn);
		char *delimiter = " ";
		char *token = strtok(tmpStringArray, delimiter); // array of words

		// init counters
		int chars_in_a_word = 0;
		int potential_line_length = 0;
		int charCounter = 0;

		// parse each word in the long sentence
		while (token != NULL) {
			chars_in_a_word = (int)strlen(token);
			potential_line_length = chars_in_a_word + charCounter;

			if(potential_line_length < max_line_chars) {
				charCounter += chars_in_a_word + 1;
				printf("%s ", token);
			} else {
				charCounter = chars_in_a_word;
				printf("\n\t\t%s ", token); // start new line indent
			}

			token = strtok(NULL, delimiter); // get the next word
		}
	}
}

void splashCoverPage(int weekdayNo, int desiredDispLen, char *titleLabel) {
	// display intro and instructions
	char *aboutString ="This is a scriptural rosary for the command line interface (CLI). This app reads from CSV text files arranged as an ER database schema. Scriptural readings are quoted from The New American Bible. Additional readings were curated from a variety of different Rosary prayer guides.";

	int titleLabelLength = (int)strlen(titleLabel);
	borderCharPrintF(":", 3);
	printf(titleLabel);
	borderCharPrintF(":", (desiredDispLen - (titleLabelLength + 3 )) );
	printf("\n");

	multiLinePrintF("\n About:\n\t", aboutString, desiredDispLen );

	printf("\n\n Display:\n\tOptimal Terminal Display: (+25 rows) x (+100 cols) to Full Screen.\n");
	printf("\tFull screen is the optimal dimension.\n");

	printf("\n User Controls:\n\tq = quit app, space = back, enter = next\n");
	printf("\n\tvi controls:\n\t\th = back, l = next\n");
	printf("\n\tgame controls:\n\t\ta = back, d = next\n");

	printf("\n\n Today is %s, therefore today's focal mystery is the %s Mystery.\n\n", retrunWeekdayName(weekdayNo), returnWeekdayMystery(weekdayNo));

	borderCharPrintF(":", desiredDispLen);
	printf("\n\n press [any key] to continue ... ");

	getchar();	// pause for keyboard input
}

void updateDisplayVariablesStruct( rosary_db_t *rosary_db_struct, displayVariables_t *queryViewStruct, int navigtionPosition) {

	int rosaryPositionID = 0, beadFK = 0, decadeFK = 0, messageFK = 0,
		mysteryFK = 0, prayerFK = 0, scriptureFK = 0, loopBody = 0;
	int smallbeadPercent = 0, mysteryPercent = 0;
	int decadeNo = 0, mysteryNo = 0;

	char *beadType, *decadeName, *decadeInfo, *mesageText, *mysteryName;
	char *scriptureText, *prayerText;

	// Get values from DB Struct
	rosaryPositionID = rosary_db_struct -> rosaryBead_dbArray[navigtionPosition].rosaryBeadID;
	beadFK 	= rosary_db_struct -> rosaryBead_dbArray[navigtionPosition].beadIndex;
	decadeFK 	= rosary_db_struct -> rosaryBead_dbArray[navigtionPosition].decadeIndex;
	messageFK 	= rosary_db_struct -> rosaryBead_dbArray[navigtionPosition].messageIndex;
	mysteryFK 	= rosary_db_struct -> rosaryBead_dbArray[navigtionPosition].mysteryIndex;
	prayerFK 	= rosary_db_struct -> rosaryBead_dbArray[navigtionPosition].prayerIndex;
	scriptureFK = rosary_db_struct -> rosaryBead_dbArray[navigtionPosition].scriptureIndex;
	loopBody 	= rosary_db_struct -> rosaryBead_dbArray[navigtionPosition].loopBody;
	smallbeadPercent = rosary_db_struct -> rosaryBead_dbArray[navigtionPosition].smallbeadPercent;
	mysteryPercent 	= rosary_db_struct -> rosaryBead_dbArray[navigtionPosition].mysteryPercent;

	beadType 	= rosary_db_struct -> bead_dbArray[beadFK].beadType;
	decadeName 	= rosary_db_struct -> decade_dbArray[decadeFK].decadeName;
	decadeInfo 	= rosary_db_struct -> decade_dbArray[decadeFK].decadeInfo;
	mesageText 	= rosary_db_struct -> message_dbArray[messageFK].mesageText;
	mysteryName = rosary_db_struct -> mystery_dbArray[mysteryFK].mysteryName;
	scriptureText = rosary_db_struct -> scripture_dbArray[scriptureFK].scriptureText;
	prayerText 	= rosary_db_struct -> prayer_dbArray[prayerFK].prayerText;

	decadeNo 	= rosary_db_struct -> decade_dbArray[decadeFK].decadeNo;
	mysteryNo 	= rosary_db_struct -> mystery_dbArray[mysteryFK].mysteryNo;

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
	strcpy(queryViewStruct -> beadType, beadType);
	strcpy(queryViewStruct -> decadeName, decadeName);
	strcpy(queryViewStruct -> decadeInfo, decadeInfo);
	strcpy(queryViewStruct -> mesageText, mesageText);
	strcpy(queryViewStruct -> mysteryName, mysteryName);
	strcpy(queryViewStruct -> scriptureText, scriptureText);
	strcpy(queryViewStruct -> prayerText, prayerText);

	// progress info
	queryViewStruct -> decadeNo = decadeNo;
	queryViewStruct -> mysteryNo = mysteryNo;

}

void outputTtyDisplay( displayVariables_t queryViewStruct, int desiredDispLen, char *titleLabel) {
	// Render all rosary bead content onto the screen

	// header
	borderCharPrintF(":", 3);
	printf(titleLabel);
	int inputLength = (int)strlen(titleLabel) + 3;
	borderCharPrintF(":", desiredDispLen - inputLength);

	// body
	printf("\n\n Mystery:\t%s", queryViewStruct.mysteryName);
	printf("\n Decade:\t%s", queryViewStruct.decadeName);
	multiLinePrintF("\n\t\t", queryViewStruct.mesageText, desiredDispLen);
	multiLinePrintF("\n Background:\t", queryViewStruct.decadeInfo, desiredDispLen);
	multiLinePrintF("\n\n Scripture:\t", queryViewStruct.scriptureText, desiredDispLen);
	multiLinePrintF("\n\n Prayer:\t", queryViewStruct.prayerText, desiredDispLen);
	printf("\n\n Bead Type:\t%s\n\n", queryViewStruct.beadType);

	// footer
	char *footerLabel = " Rosary Progress ";
    int footerLabelLength = (int)strlen(footerLabel) + 3;

	borderCharPrintF(":", 3);
	printf(footerLabel);
	borderCharPrintF(":", desiredDispLen - footerLabelLength);

	char *rosaray_region_string;
	int segment_whole, segment_part, decade_flag;

	if (queryViewStruct.loopBody == 1) {
		rosaray_region_string = "     rosary body loop";
		segment_whole = 10;
		decade_flag = 5;
		segment_part = queryViewStruct.smallbeadPercent;
	} else {
		if ( (queryViewStruct.prayerFK == 7) || (queryViewStruct.prayerFK == 8) ) {
			rosaray_region_string = "\tconclusion prayer icon";
			segment_whole = 2;
			decade_flag = 0;
			segment_part = queryViewStruct.smallbeadPercent / 5;
		} else {
			rosaray_region_string = "introduction prayers segment";
			segment_whole = 7;
			decade_flag = 0;
			segment_part = queryViewStruct.smallbeadPercent;
		}
	}
	printf("\n\n position:\t\t%d / %d", queryViewStruct.rosaryPositionID, 315);
	//printf("\n Decade Progress:\t%d / %d\t\t%s", segment_part, segment_whole, rosaray_region_string);
	//printf("\n Mystery Progress:\t%d / 50\t\tMystery:   %d / 4", queryViewStruct.mysteryPercent, queryViewStruct.mysteryNo);
	printf("\n Decade Progress:\t%d / %d\t[ ", segment_part, segment_whole);
	borderCharPrintF("o", segment_part);
	borderCharPrintF("-", segment_whole - segment_part);
	printf(" ] D[%d/%d]\t%s", queryViewStruct.decadeNo, decade_flag, rosaray_region_string );

	printf("\n Mystery Progress:\t%d / 50\t[ ", queryViewStruct.mysteryPercent);
	borderCharPrintF("o", queryViewStruct.mysteryPercent);
	borderCharPrintF("-", 50 - queryViewStruct.mysteryPercent);
	printf(" ]");

	printf("\n:");
}
