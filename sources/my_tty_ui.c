/*
 * my_tty_ui.c
 * */

#ifdef _WIN32 // MinGW
	#include <windows.h>
	#include <stdio.h>
	#include <tchar.h>

	#define IS_LINUX 0
#endif

#ifdef linux // Linux GCC v6+
	#include <stdlib.h>		// calloc(), realloc(), malloc(), system(), free()
	#include <stdio.h>
	#include <string.h>
	#include <sys/ioctl.h>	// ioctl(), TIOCGWINSZ, struct winsize
	#include <unistd.h> 	// STDOUT_FILENO

	#define IS_LINUX 1
#endif

#ifndef linux
	#define IS_LINUX 0
#endif

#include "../headers/my_csv_structs.h"
#include "../sources/my_calendar.c"
#include "../headers/my_tty_ui.h"

/*
 * Local Scope Functions
 * */

int returnScreenWidth(int isLinux) {
	int cols = 85;

	if(IS_LINUX) {
		struct winsize w; // terminal tty info
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); // tty col/row
		cols =  w.ws_col;
	}

	return cols;
}

void clearScreen(int isLinux) {
	//system("@cls||clear");
	if (isLinux == 1) {
		system("clear"); // linux
	} else {
		system("@cls"); // win
	}
}

void borderCharPrintF(char *charSymbol, int borderWidth) {
	for (int i = 0; i < borderWidth; i++) {
		printf("%s", charSymbol);
	}
}

int initialMystery(int weekdayNo) {
	int navigtionPosition[] = {237, 0, 158, 237, 79, 158, 0};

	if ( (weekdayNo > 6) || (weekdayNo < 0) ) {
		weekdayNo = 0;
	}

	return navigtionPosition[weekdayNo];
}

/*
 * Header API Scope Functions
 * */

void splashCoverPage(int weekdayNo, int desiredDispLen) {

	char * weekday[] = { "Sunday", "Monday", "Tuesday", "Wednesday",
		"Thursday", "Friday", "Saturday" };
	char * weekdayMystery[] = { "Glorious", "Joyful", "Sorrowful",
		"Glorious", "Luminous", "Sorrowful", "Joyful" };

	char *aboutString ="This is a scriptural rosary for the command line interface (CLI). This app reads from CSV text files arranged as ER database. It uses .h libraries which are default on most gcc installation. I made an additional library which will parse CSV text into an array of structs for ER db queries. Scriptural readings are quoted from The New American Bible, while additional included readings were curated from a variety of different rosary prayer guides.";

	char *titleLabel = " C/CSV Rosary ";
	int titleLabelLength = (int)strlen(titleLabel);
	borderCharPrintF("+", desiredDispLen);
	printf("\n");
	borderCharPrintF("+", 3);
	printf(titleLabel);
	borderCharPrintF("+", (desiredDispLen - (titleLabelLength + 3 )) );
	printf("\n");
	borderCharPrintF("+", desiredDispLen);
	printf("\n");

	multiLinePrintF("\n About:\n\n\t", aboutString, desiredDispLen );

	printf("\n\n Display:\n\n\tOptimal Terminal Display: (+25 rows) x (+100 cols) to Full Screen.\n");
	printf("\n User Controls:\n\n\t Press [b] and then [enter] to navigate 1 bead back");
	printf("\n\t Press [enter] to navigate 1 bead forward");
	printf("\n\t Press [q] and then [enter] to quit the app");

	printf("\n\n\n Today is %s, therefore today's mystery is the %s Mystery.\n\n", weekday[weekdayNo], weekdayMystery[weekdayNo]);

	borderCharPrintF("+", desiredDispLen);
	printf("\n press [enter] to continue");

	getchar();	// pause for char input
}

void multiLinePrintF(char *labelChars, char *strIn, int desiredLineLength) {
	desiredLineLength = (desiredLineLength / 2) + (desiredLineLength / 5) - 5;

	int lineLength = (int)strlen(strIn);
	printf("%s", labelChars);

	if ( lineLength <= desiredLineLength) {
		printf("%s\n\t\t", strIn);

	} else {

		int inputLength = (int)strlen(strIn);
		char stringInput[inputLength]; // temp copy of string to manipulate
			strcpy(stringInput, strIn);
		char *delim = " ";
		char *parsedStringArray = strtok(stringInput, delim);
		int desiredLengthCounter = 0;
		int wordLength = 0;

		while (parsedStringArray != NULL) {
			wordLength = (int)strlen(parsedStringArray);
			desiredLengthCounter = desiredLengthCounter + wordLength;

			if (desiredLengthCounter < (desiredLineLength)) {
				printf("%s ", parsedStringArray);
			} else {
				printf("\n\t\t%s ", parsedStringArray);
				desiredLengthCounter = 0;
			}

			parsedStringArray = strtok(NULL, delim);
		}
	}
}

int pressKeyContinue(int navigtionPosition, int isLinux) {
	int c = getc(stdin);
	for (;;) {
		switch (c) {
			case '\n': // [enter] navigate 1 step forward
				if (navigtionPosition < 315) {
					navigtionPosition++;
				} else {
					navigtionPosition = 0;
				}
				return navigtionPosition;
				break;

			case 'b': // navigate 1 step back
				if (navigtionPosition > 1) {
					navigtionPosition = navigtionPosition - 2;
				} else {
					navigtionPosition = 315;
				}
				return navigtionPosition;
				break;

			case 'q':
				printf("\n Quit App \n");
				return 316; //retun an integer greater than 315
				break;

			default: // no nav change
				return navigtionPosition - 1;
		}
	}
}

void updateDisplayVariablesStruct( rosary_db_t *rosary_db_struct, displayVariables_t *queryViewStruct, int navigtionPosition) {

	int rosaryPositionID = 0, beadFK = 0, decadeFK = 0, messageFK = 0, mysteryFK = 0, prayerFK = 0;
	int scriptureFK = 0, loopBody = 0, smallbeadPercent = 0, mysteryPercent = 0;
	int decadeNo = 0, mysteryNo = 0;

	char *beadType, *decadeName, *decadeInfo, *mesageText, *mysteryName;
	char *scriptureText, *prayerText;

	rosaryPositionID = rosary_db_struct->rosaryBead_dbArray[navigtionPosition].rosaryBeadID;
	beadFK = rosary_db_struct->rosaryBead_dbArray[navigtionPosition].beadIndex;
	decadeFK = rosary_db_struct->rosaryBead_dbArray[navigtionPosition].decadeIndex;
	messageFK = rosary_db_struct->rosaryBead_dbArray[navigtionPosition].messageIndex;
	mysteryFK = rosary_db_struct->rosaryBead_dbArray[navigtionPosition].mysteryIndex;
	prayerFK = rosary_db_struct->rosaryBead_dbArray[navigtionPosition].prayerIndex;
	scriptureFK = rosary_db_struct->rosaryBead_dbArray[navigtionPosition].scriptureIndex;
	loopBody = rosary_db_struct->rosaryBead_dbArray[navigtionPosition].loopBody;
	smallbeadPercent = rosary_db_struct->rosaryBead_dbArray[navigtionPosition].smallbeadPercent;
	mysteryPercent = rosary_db_struct->rosaryBead_dbArray[navigtionPosition].mysteryPercent;

	beadType = rosary_db_struct->bead_dbArray[beadFK].beadType;
	decadeName = rosary_db_struct->decade_dbArray[decadeFK].decadeName;
	decadeInfo = rosary_db_struct->decade_dbArray[decadeFK].decadeInfo;
	mesageText = rosary_db_struct->message_dbArray[messageFK].mesageText;
	mysteryName = rosary_db_struct->mystery_dbArray[mysteryFK].mysteryName;
	scriptureText = rosary_db_struct->scripture_dbArray[scriptureFK].scriptureText;
	prayerText = rosary_db_struct->prayer_dbArray[prayerFK].prayerText;

	decadeNo = rosary_db_struct->decade_dbArray[decadeFK].decadeNo;
	mysteryNo = rosary_db_struct->mystery_dbArray[mysteryFK].mysteryNo;

	queryViewStruct -> rosaryPositionID = rosaryPositionID;
	queryViewStruct -> beadFK = beadFK;
	queryViewStruct -> decadeFK = decadeFK;
	queryViewStruct -> messageFK = messageFK;
	queryViewStruct -> mysteryFK = mysteryFK;
	queryViewStruct -> prayerFK = prayerFK;
	queryViewStruct -> scriptureFK = scriptureFK;
	queryViewStruct -> loopBody = loopBody;
	queryViewStruct -> smallbeadPercent = smallbeadPercent;
	queryViewStruct -> mysteryPercent = mysteryPercent;

	// struct strings
	strcpy( queryViewStruct -> beadType, beadType);
	strcpy( queryViewStruct -> decadeName, decadeName);
	strcpy( queryViewStruct -> decadeInfo, decadeInfo);
	strcpy( queryViewStruct -> mesageText, mesageText);
	strcpy( queryViewStruct -> mysteryName, mysteryName);
	strcpy( queryViewStruct -> scriptureText, scriptureText);
	strcpy( queryViewStruct -> prayerText, prayerText);

	queryViewStruct -> decadeNo = decadeNo;
	queryViewStruct -> mysteryNo = mysteryNo;

}

void outputTtyDisplay( displayVariables_t queryViewStruct, int desiredDispLen) {
	// disp header
	char *titleLabel = " C/CSV Rosary ";
	borderCharPrintF("+", 3);
	printf(titleLabel);
	borderCharPrintF("+", desiredDispLen - 17);

	// disp body
	printf("\n\n Mystery:\t%s", queryViewStruct.mysteryName);
	printf("\n Decade:\t%s", queryViewStruct.decadeName);
	multiLinePrintF("\n\t\t", queryViewStruct.mesageText, desiredDispLen);
	multiLinePrintF("\n Background:\t", queryViewStruct.decadeInfo, desiredDispLen);
	multiLinePrintF("\n\n Scripture:\t", queryViewStruct.scriptureText, desiredDispLen);
	multiLinePrintF("\n Prayer:\t", queryViewStruct.prayerText, desiredDispLen);
	printf("\n Bead Type:\t%s\n", queryViewStruct.beadType);

	// disp footer
	char *footerLabel = " Rosary Progress ";
	borderCharPrintF("+", 3);
	printf(footerLabel);
	borderCharPrintF("+", desiredDispLen - 20);
	printf("\n\n position:\t   %d / 315", queryViewStruct.rosaryPositionID);

	if (queryViewStruct.loopBody == 1) {
		printf("\n Decade Progress:    %d / 10\t\t Decade:    %d / 5", queryViewStruct.smallbeadPercent, queryViewStruct.decadeNo);
	} else {
		printf("\n Decade Progress:    %d / introduction", queryViewStruct.smallbeadPercent);
	}

	printf("\n Mystery Progress:   %d / 50\t\t Mystery:   %d / 4", queryViewStruct.mysteryPercent, queryViewStruct.mysteryNo);
	printf("\n:");
}
