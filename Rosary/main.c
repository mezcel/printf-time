#include <stdio.h>				// standard default C library
#include <stdlib.h>			// calloc()/realloc()/malloc(), system(), free()
#include <string.h>			// workhorse header for CLI string manipulation
#include <time.h>				// time_t
#include <sys/ioctl.h>			// ioctl(), TIOCGWINSZ
#include <unistd.h> 			// STDOUT_FILENO
#include "my-csv-parser.h"		// my own homebrew CSV parse functions & structs

// Prototypes
void clearScreen();
void splashCoverPager(int desiredLineLength, int weekdayNo);
void multiLinePrintF(char *labelChars, char *strIn, int desiredLineLength);
int returnDayOfWeekFlag();
int initialMystery(int weekdayNo);
int pressKeyContinue(int navigtionPosition);

// Functions
void clearScreen() {
	//system("@cls||clear");
	system("clear"); //linux
}

void splashCoverPage(int desiredLineLength, int weekdayNo) {

	char * weekday[] = { "Sunday", "Monday", "Tuesday", "Wednesday",
							"Thursday", "Friday", "Saturday" };

	char * weekdayMystery[] = { "Glorious", "Joyful", "Sorrowful", "Glorious",
									"Luminous", "Sorrowful", "Joyful" };

	//int weekdayNo = returnDayOfWeekFlag();

	char *aboutString ="This is a scriptural rosary, written in C, for the command line interface (CLI). The sideshow sequence is intended to resemble the sequential pattern and order of a traditional rosary bead prayer session. This app reads from CSV text files arranged as ER database. It uses standard .h libraries as well as a library I made to parse CSV text into an array of structs. Scriptural readings are quoted from The New American Bible, while additional included readings were curated from a variety of different rosary prayer guides.";

	char *ttySpecs = "Optimal Terminal Display: (+25 rows) x (+100 cols) to Full Screen.";

	clearScreen(); // clear cli

	printf("+++ C/CSV Rosary ++++++++++\n");
	multiLinePrintF("\n About:\n\t", aboutString, desiredLineLength);

	printf("\n Display:\n\t%s\n", ttySpecs);
	printf("\nUser Controls:\n\t Press [b] to step 1 back");
	printf("\n\t Press [enter] to step 1 forward");
	printf("\n\t Press [q] to quit the app");
	printf("\n\n\n Today is a %s, therefore today's mystery is the %s Mystery.", weekday[weekdayNo], weekdayMystery[weekdayNo]);
	printf("\n press [enter] to continue");

	getchar(); // pause for char input
	clearScreen(); // clear cli
}

void multiLinePrintF(char *labelChars, char *strIn, int desiredLineLength) {
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

			if (desiredLengthCounter < desiredLineLength) {
				printf("%s ", parsedStringArray);
			} else {
				printf("\n\t\t%s ", parsedStringArray);
				desiredLengthCounter = 0;
			}

			parsedStringArray = strtok(NULL, delim);
		}

		// free(parsedStringArray);
	}
}

int returnDayOfWeekFlag() {
	time_t rawtime;
	struct tm *timeinfo;

	int year = 2019;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	timeinfo->tm_year = year - 1900;

	/* call mktime: timeinfo->tm_wday will be set */
	mktime ( timeinfo );

	return timeinfo->tm_wday;
}

int initialMystery(int weekdayNo) {

	int navigtionPosition = 0;

	switch (weekdayNo) {
		case 1: // mon joyful
			navigtionPosition = 0;
			break;

		case 2: // tues sorrowful
			navigtionPosition = 158;
			break;

		case 3: // wed glorious
			navigtionPosition = 237;
			break;

		case 4: // thurs Luminous
			navigtionPosition = 79;
			break;

		case 5: // fri sorrowful
			navigtionPosition = 158;
			break;

		case 6: // sat joyful
			navigtionPosition = 0;
			break;

		case 0: // sun glorious
			navigtionPosition = 237;
			break;

		default:
			navigtionPosition = 0;
	}

	return navigtionPosition;
}

int pressKeyContinue(int navigtionPosition) {
	//int c;
	int c = getc(stdin);
	for (;;) {
		switch (c) {
			case '\n': // [enter] navigate 1 step forward
				clearScreen();
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

			/*case EOF:
				return 0;*/

			default: // no nav change
				return navigtionPosition - 1;

		}
	}
}

// Main
int main() {
	// terminal tty info
	struct winsize w;


	// Name my strtuct variables
	rosaryBead_t *rosaryBead_record_field = NULL;
	rosaryBead_t rosaryBead_dbArray[317];

	bead_t *bead_record_field = NULL;
	bead_t bead_dbArray[9];

	book_t *book_record_field = NULL;
	book_t book_dbArray[17];

	decade_t *decade_record_field = NULL;
	decade_t decade_dbArray[22];

	message_t *message_record_field = NULL;
	message_t message_dbArray[22];

	mystery_t *mystery_record_field = NULL;
	mystery_t mystery_dbArray[7];

	prayer_t *prayer_record_field = NULL;
	prayer_t prayer_dbArray[11];

	scripture_t *scripture_record_field = NULL;
	scripture_t scripture_dbArray[202];

	/*
	 * Populate my struct arrays
	 * (single_struct, struct_array, max_chars_per_line, csv_file_path)
	 * */

	csvToStruct_rosaryBead(rosaryBead_record_field, rosaryBead_dbArray, 300, "csv/rosaryBead.csv");
	csvToStruct_bead(bead_record_field, bead_dbArray, 40, "csv/bead.csv");
	csvToStruct_book(book_record_field, book_dbArray, 300, "csv/book.csv");
	csvToStruct_decade(decade_record_field, decade_dbArray, 800, "csv/decade.csv");
	csvToStruct_message(message_record_field, message_dbArray, 150, "csv/message.csv");
	csvToStruct_mystery(mystery_record_field, mystery_dbArray, 100, "csv/mystery.csv");
	csvToStruct_prayer(prayer_record_field, prayer_dbArray, 1250, "csv/prayer.csv");
	csvToStruct_scripture(scripture_record_field, scripture_dbArray, 500, "csv/scripture.csv");

	// App Navigation
	//int desiredDispLen = 80;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int desiredDispLen = w.ws_col / 2;
	int weekdayNo = returnDayOfWeekFlag();
	int navigtionPosition = initialMystery(weekdayNo); // starting position

	splashCoverPage(desiredDispLen, weekdayNo);

    while (navigtionPosition <= 315) {
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		desiredDispLen = w.ws_col / 2;

		int rosaryPositionID = rosaryBead_dbArray[navigtionPosition].rosaryBeadID;

		int beadFK = rosaryBead_dbArray[navigtionPosition].beadIndex;
		int decadeFK = rosaryBead_dbArray[navigtionPosition].decadeIndex;
		int messageFK = rosaryBead_dbArray[navigtionPosition].messageIndex;
		int mysteryFK = rosaryBead_dbArray[navigtionPosition].mysteryIndex;
		int prayerFK = rosaryBead_dbArray[navigtionPosition].prayerIndex;
		int scriptureFK = rosaryBead_dbArray[navigtionPosition].scriptureIndex;
		int loopBody = rosaryBead_dbArray[navigtionPosition].loopBody;
		int smallbeadPercent = rosaryBead_dbArray[navigtionPosition].smallbeadPercent;
		int mysteryPercent = rosaryBead_dbArray[navigtionPosition].mysteryPercent;

		char *beadType = bead_dbArray[beadFK].beadType;

		char *decadeName = decade_dbArray[decadeFK].decadeName;
		char *decadeInfo = decade_dbArray[decadeFK].decadeInfo;
		char *mesageText = message_dbArray[messageFK].mesageText;
		char *mysteryName = mystery_dbArray[mysteryFK].mysteryName;
		char *scriptureText = scripture_dbArray[scriptureFK].scriptureText;
		char *prayerText = prayer_dbArray[prayerFK].prayerText;

		int decadeNo = decade_dbArray[decadeFK].decadeNo;
		int mysteryNo = mystery_dbArray[mysteryFK].mysteryNo;

		printf("+++ C/CSV Rosary ++++++++++");

		printf("\n\n Mystery:\t%s", mysteryName);
		printf("\n Decade:\t%s", decadeName);

		multiLinePrintF("\n\t\t", mesageText, desiredDispLen);
		multiLinePrintF("\n Background:\t", decadeInfo, desiredDispLen);
		multiLinePrintF("\n\n Scripture:\t", scriptureText, desiredDispLen);
		multiLinePrintF("\n Prayer:\t", prayerText, desiredDispLen);

		printf("\n Bead Type:\t%s", beadType);
		printf("\n+++ Rosary Progress ++++++++++ \n");
		printf("\n position: %d / 315", rosaryPositionID);

		if (loopBody == 1) {
			printf("\n Decade Progress:    %d / 10\t\t Decade:    %d / 5", smallbeadPercent, decadeNo);
		} else {
			printf("\n Decade Progress:    %d / introduction", smallbeadPercent);
		}

		printf("\n Mystery Progress:   %d / 50\t\t Mystery:   %d / 4", mysteryPercent, mysteryNo);
		printf("\n:");

		navigtionPosition = pressKeyContinue(navigtionPosition);
		// getchar(); // pause for char input
	}

	return 0;
}
