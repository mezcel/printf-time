#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my-csv-parser.h"

int main() {
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

	// Populate my struct arrays

	csvToStruct_rosaryBead(rosaryBead_record_field, rosaryBead_dbArray);
	csvToStruct_bead(bead_record_field, bead_dbArray);
	csvToStruct_book(book_record_field, book_dbArray);
	csvToStruct_decade(decade_record_field, decade_dbArray);
	csvToStruct_message(message_record_field, message_dbArray);
	csvToStruct_message(message_record_field, message_dbArray);
	csvToStruct_mystery(mystery_record_field, mystery_dbArray);
	csvToStruct_prayer(prayer_record_field, prayer_dbArray);
	csvToStruct_scripture(scripture_record_field, scripture_dbArray);


	int navigtionPosition = 105;

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

	printf("--- test --- \n");

	printf("rosaryPositionID = %d\n", rosaryPositionID);

	printf("beadType = %s\n", beadType);
	printf("decadeNo = %d\n", decadeNo);
	printf("decadeName = %s\n", decadeName);
	printf("decadeInfo = %s\n", decadeInfo);
	printf("mesageText = %s\n", mesageText);
	printf("mysteryNo = %d\n", mysteryNo);
	printf("mysteryName = %s\n", mysteryName);
	printf("prayerText = %s\n", prayerText);
	printf("scriptureText = %s\n", scriptureText);

	printf("loopBody = %d\n", loopBody);
	printf("smallbeadPercent = %d\n", smallbeadPercent);
	printf("mysteryPercent = %d\n", mysteryPercent);

	return 0;
}
