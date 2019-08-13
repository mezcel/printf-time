#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my-csv-parser.h"

void clearScreen() {
	//system("@cls||clear");
	system("clear");
}

int pressKeyContinue(int navigtionPosition) {
	int c;
	for (;;) {
		c = getc(stdin);
		switch (c) {
			case '\n': // enter key
				clearScreen();
				if (navigtionPosition < 315) {
					navigtionPosition++;
				} else {
					navigtionPosition = 0;
				}
				return navigtionPosition;
				break;
			case 'b': // enter key
				if (navigtionPosition > 1) {
					navigtionPosition--;
					navigtionPosition--;
				} else {
					navigtionPosition = 315;
				}
				return navigtionPosition;
				break;
			case 'q':
				printf("\n Quit App \n");
				return 316; //retun an integer greater than 315
				break;
			case EOF:
				return 0;
		}
	}

}

int main() {
	clearScreen(); // clear cli

	// Name my strtuct variables

	rosaryBead_t *rosaryBead_record_field = NULL;
	rosaryBead_t rosaryBead_dbArray[317];

	bead_t *bead_record_field = NULL;
	bead_t bead_dbArray[8];

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
	csvToStruct_bead(bead_record_field, bead_dbArray, 50, "csv/bead.csv");
	csvToStruct_book(book_record_field, book_dbArray, 300, "csv/book.csv");
	csvToStruct_decade(decade_record_field, decade_dbArray, 800, "csv/decade.csv");
	csvToStruct_message(message_record_field, message_dbArray, 150, "csv/message.csv");
	csvToStruct_mystery(mystery_record_field, mystery_dbArray, 100, "csv/mystery.csv");
	csvToStruct_prayer(prayer_record_field, prayer_dbArray, 1250, "csv/prayer.csv");
	csvToStruct_scripture(scripture_record_field, scripture_dbArray, 500, "csv/scripture.csv");

	// App Navigation

	int navigtionPosition = 0;

    while (navigtionPosition <= 315) {


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

		int decadeNo = decade_dbArray[decadeFK].decadeNo;
		char *decadeName = decade_dbArray[decadeFK].decadeName;
		char *decadeInfo = decade_dbArray[decadeFK].decadeInfo;

		char *mesageText = message_dbArray[messageFK].mesageText;

		int mysteryNo = mystery_dbArray[mysteryFK].mysteryNo;
		char *mysteryName = mystery_dbArray[mysteryFK].mysteryName;

		char *prayerText = prayer_dbArray[prayerFK].prayerText;

		char *scriptureText = scripture_dbArray[scriptureFK].scriptureText;

		printf("+++ C/CSV Rosary ++++++++++");

		printf("\n\nMystery:\t%s", mysteryName);
		printf("\nDecade:\t\t%s", decadeName);
		printf("\n\t\t%s", mesageText);
		printf("\nBackground:\t%s", decadeInfo);
		printf("\n\nScripture:\t%s", scriptureText);
		printf("\nPrayer:\t\t%s", prayerText);

		printf("\nBead Type:\t%s", beadType);

		printf("\n+++ Rosary Progress ++++++++++ \n");
		printf("\nposition: %d / 315", rosaryPositionID);

		if (loopBody == 1){
			printf("\nDecade Progress:    %d / 10\t\tDecade:    %d / 5", smallbeadPercent, decadeNo);
		} else {
			printf("\nDecade Progress:    %d / introduction", smallbeadPercent);
		}

		printf("\nMystery Progress:   %d / 50\t\tMystery:   %d / 4", mysteryPercent, mysteryNo);

		printf("\n:");

		navigtionPosition = pressKeyContinue(navigtionPosition);

	}

	return 0;
}
