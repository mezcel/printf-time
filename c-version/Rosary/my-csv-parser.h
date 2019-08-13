/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>*/

/*
 *	Depends on the following .csv files:
 *		bead.csv
 *		decade.csv
 *		message.csv
 *		mystery.csv
 *		prayer.csv
 *		rosaryBead.csv
 * 		scripture.csv
 *
 * 		One .csv mega-file option:
 * 			rosaryJSON-nab.json
 * 			note: I did not make a struct for this (yet), but it follows
 * 				the	same algorithm
 *
 * 	Background:
 * 		I first made my NoSql DB in a JSON format.
 * 		I used npm's json2csv, https://www.csvjson.com/json2csv to
 * 			to convert json to csv
 * 		I chose to use csv instead of json because CSV is easier to
 * 			parse, and since C is legacy software, csv is too
 * */

typedef struct rosaryBead_struct {
	// "scripture.scriptureID";"scripture.bookIndex";"scripture.chapterIndex";"scripture.verseIndex";"scripture.scriptureText"
	int rosaryBeadID;
	int beadIndex;
	int decadeIndex;
	int mysteryIndex;
	int prayerIndex;
	int scriptureIndex;
	int messageIndex;
	int loopBody;
	int smallbeadPercent;
	int mysteryPercent;
} rosaryBead_t;

typedef struct bead_struct {
	// "scripture.scriptureID";"scripture.bookIndex";"scripture.chapterIndex";"scripture.verseIndex";"scripture.scriptureText"
	int beadID;
	char *beadType;
} bead_t;

typedef struct book_struct {
	// "scripture.scriptureID";"scripture.bookIndex";"scripture.chapterIndex";"scripture.verseIndex";"scripture.scriptureText"
	int bookID;
	char *bookName;
	char *library;
} book_t;

typedef struct decade_struct {
	// "decade.decadeID";"decade.mysteryIndex";"decade.decadeNo";"decade.decadeName";"decade.decadeInfo";"decade.infoRefference"
	int decadeID;
	int mysteryIndex;
	int decadeNo;
	char *decadeName;
	char *decadeInfo;
	char *infoRefference;
} decade_t;

typedef struct message_struct {
	// "message.messageID";"message.mesageText"
	int messageID;
	char *mesageText;
} message_t;

typedef struct mystery_struct {
	// "mystery.mysteryID";"mystery.mysteryNo";"mystery.mysteryName"
	int mysteryID;
	int mysteryNo;
	char *mysteryName;
} mystery_t;

typedef struct prayer_struct {
	// "prayer.prayerID";"prayer.prayerName";"prayer.prayerText"
	int prayerID;
	char *prayerName;
	char *prayerText;
} prayer_t;

typedef struct scripture_struct {
	// "scripture.scriptureID";"scripture.bookIndex";"scripture.chapterIndex";"scripture.verseIndex";"scripture.scriptureText"
	int scriptureID;
	int bookIndex;
	int chapterIndex;
	int verseIndex;
	char *scriptureText;
} scripture_t;

/*
 * Prototypes
 * */

/*char ** strsplit( const char * src, const char * delim );
void strsplitfree( char ** strlist );

rosaryBead_t * parse_rosaryBead_record( char * scvline );
bead_t * parse_bead_record( char * scvline );
book_t * parse_book_record( char * scvline );
decade_t * parse_decade_record( char * scvline );
message_t * parse_message_record( char * scvline );
mystery_t * parse_mystery_record( char * scvline );
prayer_t * parse_prayer_record( char * scvline );
scripture_t * parse_scripture_record( char * scvline );

void csvToStruct_rosaryBead(rosaryBead_t *record_field, rosaryBead_t dbArray[317]);
void csvToStruct_bead(bead_t *record_field, bead_t dbArray[8]);
void csvToStruct_book(book_t *record_field, book_t dbArray[17]);
void csvToStruct_decade(decade_t *record_field, decade_t dbArray[22]);
void csvToStruct_message(message_t *record_field, message_t dbArray[22]);
void csvToStruct_mystery(mystery_t *record_field, mystery_t dbArray[7]);
void csvToStruct_prayer(prayer_t *record_field, prayer_t dbArray[11]);
void csvToStruct_scripture(scripture_t *record_field, scripture_t dbArray[202]);*/

/*
 * Functions
 * */

char ** strsplit( const char * src, const char * delim ) {
    char * pbuf = NULL;
    char * ptok = NULL;
    int count = 0;
    int srclen = 0;
    char ** pparr = NULL;

    srclen = strlen( src );
    pbuf = (char*) malloc( srclen + 1 );

    if( !pbuf ) {
        return NULL;
	}

    strcpy( pbuf, src );
    ptok = strtok( pbuf, delim );

    while( ptok ) {
        pparr = (char**) realloc( pparr, (count+1) * sizeof(char*) );
        *(pparr + count) = strdup(ptok);

        count++;
        ptok = strtok( NULL, delim );
    }

    pparr = (char**) realloc( pparr, (count+1) * sizeof(char*) );
    *(pparr + count) = NULL;

    free(pbuf);
    return pparr;
}

void strsplitfree( char ** strlist ) {
	int i = 0;

	while( strlist[i]) {
		free( strlist[i++] );
	}

	free( strlist );
}

/*
 * struct functions
 * */

rosaryBead_t * parse_rosaryBead_record( char * scvline ) {
    char ** pp = NULL;
    rosaryBead_t * record_field = NULL;

    pp = strsplit( scvline, ";" );
    record_field = (rosaryBead_t*) calloc( 1, sizeof(rosaryBead_t) );

    record_field -> rosaryBeadID = atoi(pp[0]);
    record_field -> beadIndex = atoi(pp[1]);
    record_field -> decadeIndex = atoi(pp[2]);
    record_field -> mysteryIndex = atoi(pp[3]);
    record_field -> prayerIndex = atoi(pp[4]);
    record_field -> scriptureIndex = atoi(pp[5]);
    record_field -> messageIndex = atoi(pp[6]);
    record_field -> loopBody = atoi(pp[7]);
    record_field -> smallbeadPercent = atoi(pp[8]);
    record_field -> mysteryPercent = atoi(pp[9]);

    strsplitfree( pp );
    return record_field;
}

bead_t * parse_bead_record( char * scvline ) {
    char ** pp = NULL;
    bead_t * record_field = NULL;

    pp = strsplit( scvline, ";" );
    record_field = (bead_t*) calloc( 1, sizeof(bead_t) );

    record_field -> beadID = atoi(pp[0]);
    record_field -> beadType = strdup(pp[1]);

    strsplitfree( pp );
    return record_field;
}

book_t * parse_book_record( char * scvline ) {
    char ** pp = NULL;
    book_t * record_field = NULL;

    pp = strsplit( scvline, ";" );
    record_field = (book_t*) calloc( 1, sizeof(book_t) );

    record_field -> bookID = atoi(pp[0]);
    record_field -> bookName = strdup(pp[1]);
    record_field -> library = strdup(pp[2]);

    strsplitfree( pp );
    return record_field;
}

decade_t * parse_decade_record( char * scvline ) {
    char ** pp = NULL;
    decade_t * record_field = NULL;

	pp = strsplit( scvline, ";" );
    record_field = (decade_t*) calloc( 1, sizeof(decade_t) );

    record_field -> decadeID = atoi(pp[0]);
    record_field -> mysteryIndex = atoi(pp[1]);
    record_field -> decadeNo = atoi(pp[2]);
    record_field -> decadeName = strdup(pp[3]);
    record_field -> decadeInfo = strdup(pp[4]);
    record_field -> infoRefference = strdup(pp[5]);

    strsplitfree( pp );
    return record_field;
}

message_t * parse_message_record( char * scvline ) {
    char ** pp = NULL;
    message_t * record_field = NULL;

    pp = strsplit( scvline, ";" );
    record_field = (message_t*) calloc( 1, sizeof(message_t) );

    record_field -> messageID = atoi(pp[0]);
    record_field -> mesageText = strdup(pp[1]);

    strsplitfree( pp );
    return record_field;
}

mystery_t * parse_mystery_record( char * scvline ) {
    char ** pp = NULL;
    mystery_t * record_field = NULL;

    pp = strsplit( scvline, ";" );
    record_field = (mystery_t*) calloc( 1, sizeof(mystery_t) );

    record_field -> mysteryID = atoi(pp[0]);
    record_field -> mysteryNo = atoi(pp[1]);
    record_field -> mysteryName = strdup(pp[2]);

    strsplitfree( pp );
    return record_field;
}

prayer_t * parse_prayer_record( char * scvline ) {
    char ** pp = NULL;
    prayer_t * record_field = NULL;

    pp = strsplit( scvline, ";" );
    record_field = (prayer_t*) calloc( 1, sizeof(prayer_t) );

    record_field -> prayerID = atoi(pp[0]);
    record_field -> prayerName = strdup(pp[1]);
    record_field -> prayerText = strdup(pp[2]);

    strsplitfree( pp );
    return record_field;
}

scripture_t * parse_scripture_record( char * scvline ) {
    char ** pp = NULL;
    scripture_t * record_field = NULL;

    pp = strsplit( scvline, ";" );

    record_field = (scripture_t*) calloc( 1, sizeof(scripture_t) );

    record_field -> scriptureID = atoi(pp[0]);
    record_field -> bookIndex = atoi(pp[1]);
    record_field -> chapterIndex = atoi(pp[2]);
    record_field -> verseIndex = atoi(pp[3]);
    record_field -> scriptureText = strdup(pp[4]);

    strsplitfree( pp );

    return record_field;
}

/*
 * populate structs functions
 * */

void csvToStruct_rosaryBead(rosaryBead_t *record_field, rosaryBead_t dbArray[317], int LINE_MAX_LEN, char *filePath) {
	/*
	* Copy text string value into struct char var
	* */
	//int LINE_MAX_LEN = 300;
    char scvline[ LINE_MAX_LEN + 1 ];
	int counter=0;
	int arrayIndex=0;
	FILE * csvFile = fopen( filePath, "r" );

	while( fgets( scvline, LINE_MAX_LEN, csvFile ) ) {
		if (counter > 0 ) {
			record_field = parse_rosaryBead_record( scvline );

			arrayIndex = counter - 1;
			dbArray[arrayIndex].rosaryBeadID = record_field -> rosaryBeadID;
			dbArray[arrayIndex].beadIndex = record_field -> beadIndex;
			dbArray[arrayIndex].decadeIndex = record_field -> decadeIndex;
			dbArray[arrayIndex].mysteryIndex = record_field -> mysteryIndex;
			dbArray[arrayIndex].prayerIndex = record_field -> prayerIndex;
			dbArray[arrayIndex].scriptureIndex = record_field -> scriptureIndex;
			dbArray[arrayIndex].messageIndex = record_field -> messageIndex;
			dbArray[arrayIndex].loopBody = record_field -> loopBody;
			dbArray[arrayIndex].smallbeadPercent = record_field -> smallbeadPercent;
			dbArray[arrayIndex].mysteryPercent = record_field -> mysteryPercent;
		}
		counter++;
	}

	// destroy temp string memory
	free(record_field);
	fclose(csvFile);
}

void csvToStruct_bead(bead_t *record_field, bead_t dbArray[8], int LINE_MAX_LEN, char *filePath) {
	/*
	* Copy text string value into struct char var
	* */
	//int LINE_MAX_LEN = 50;
    char scvline[ LINE_MAX_LEN + 1 ];
	int counter=0;
	int arrayIndex=0;
	FILE * csvFile = fopen( filePath, "r" );

	while( fgets( scvline, LINE_MAX_LEN, csvFile ) ) {
		if (counter > 0 ) {
			record_field = parse_bead_record( scvline );

			arrayIndex = counter - 1;
			dbArray[arrayIndex].beadID = record_field -> beadID;
			dbArray[arrayIndex].beadType = record_field -> beadType;
			dbArray[arrayIndex].beadType = record_field -> beadType;
		}
		counter++;
	}

	// destroy temp string memory
	free(record_field -> beadType);
	free(record_field);
	fclose(csvFile);
}

void csvToStruct_book(book_t *record_field, book_t dbArray[17], int LINE_MAX_LEN, char *filePath) {
	/*
	* Copy text string value into struct char var
	* */
	//int LINE_MAX_LEN = 300;
    char scvline[ LINE_MAX_LEN + 1 ];
	int counter=0;
	int arrayIndex=0;
	FILE * csvFile = fopen( filePath, "r" );

	while( fgets( scvline, LINE_MAX_LEN, csvFile ) ) {
		if (counter > 0 ) {
			record_field = parse_book_record( scvline );

			arrayIndex = counter - 1;
			dbArray[arrayIndex].bookID = record_field -> bookID;
			dbArray[arrayIndex].bookName = record_field -> bookName;
			dbArray[arrayIndex].library = record_field -> library;
		}
		counter++;
	}

	// destroy temp string memory
	free(record_field -> bookName);
	free(record_field -> library);
	free(record_field);
	fclose(csvFile);
}

void csvToStruct_decade(decade_t *record_field, decade_t dbArray[22], int LINE_MAX_LEN, char *filePath) {
	/*
	* Copy text string value into struct char var
	* */
	//int LINE_MAX_LEN = 800;
    char scvline[ LINE_MAX_LEN + 1 ];
	int counter=0;
	int arrayIndex=0;
	FILE * csvFile = fopen( filePath, "r" );

	while( fgets( scvline, LINE_MAX_LEN, csvFile ) ) {
		if (counter > 0 ) {
			record_field = parse_decade_record( scvline );

			arrayIndex = counter - 1;
			dbArray[arrayIndex].decadeID = record_field -> decadeID;
			dbArray[arrayIndex].mysteryIndex = record_field -> mysteryIndex;
			dbArray[arrayIndex].decadeNo = record_field -> decadeNo;
			dbArray[arrayIndex].decadeName = record_field -> decadeName;
			dbArray[arrayIndex].decadeInfo = record_field -> decadeInfo;
			dbArray[arrayIndex].infoRefference = record_field -> infoRefference;
		}
		counter++;
	}

	// destroy temp string memory
	free(record_field -> decadeName);
	free(record_field -> decadeInfo);
	free(record_field -> infoRefference);
	free(record_field);
	fclose(csvFile);
}

void csvToStruct_message(message_t *record_field, message_t dbArray[22], int LINE_MAX_LEN, char *filePath) {
	/*
	* Copy text string value into struct char var
	* */
	//int LINE_MAX_LEN = 150;
    char scvline[ LINE_MAX_LEN + 1 ];
	int counter=0;
	int arrayIndex=0;
	FILE * csvFile = fopen( filePath, "r" );

	while( fgets( scvline, LINE_MAX_LEN, csvFile ) ) {
		if (counter > 0 ) {
			record_field = parse_message_record( scvline );

			arrayIndex = counter - 1;
			dbArray[arrayIndex].messageID = record_field -> messageID;
			dbArray[arrayIndex].mesageText = record_field -> mesageText;
		}
		counter++;
	}

	// destroy temp string memory
	free(record_field -> mesageText);
	free(record_field);
	fclose(csvFile);
}

void csvToStruct_mystery(mystery_t *record_field, mystery_t dbArray[7], int LINE_MAX_LEN, char *filePath) {
	/*
	* Copy text string value into struct char var
	* */
	//int LINE_MAX_LEN = 100;
    char scvline[ LINE_MAX_LEN + 1 ];
	int counter=0;
	int arrayIndex=0;
	FILE * csvFile = fopen( filePath, "r" );

	while( fgets( scvline, LINE_MAX_LEN, csvFile ) ) {
		if (counter > 0 ) {
			record_field = parse_mystery_record( scvline );

			arrayIndex = counter - 1;
			dbArray[arrayIndex].mysteryID = record_field -> mysteryID;
			dbArray[arrayIndex].mysteryNo = record_field -> mysteryNo;
			dbArray[arrayIndex].mysteryName = record_field -> mysteryName;
		}
		counter++;
	}

	// destroy temp string memory
	free(record_field -> mysteryName);
	free(record_field);
	fclose(csvFile);
}

void csvToStruct_prayer(prayer_t *record_field, prayer_t dbArray[11], int LINE_MAX_LEN, char *filePath) {
	/*
	* Copy text string value into struct char var
	* */
	//int LINE_MAX_LEN = 1250;
    char scvline[ LINE_MAX_LEN + 1 ];
	int counter=0;
	int arrayIndex=0;
	FILE * csvFile = fopen( filePath, "r" );

	while( fgets( scvline, LINE_MAX_LEN, csvFile ) ) {
		if (counter > 0 ) {
			record_field = parse_prayer_record( scvline );

			arrayIndex = counter - 1;
			dbArray[arrayIndex].prayerID = record_field -> prayerID;
			dbArray[arrayIndex].prayerName = record_field -> prayerName;
			dbArray[arrayIndex].prayerText = record_field -> prayerText;
		}
		counter++;
	}

	// destroy temp string memory
	free(record_field -> prayerName);
	free(record_field -> prayerText);
	free(record_field);
	fclose(csvFile);
}

void csvToStruct_scripture(scripture_t *record_field, scripture_t dbArray[202], int LINE_MAX_LEN, char *filePath) {
	/*
	* Copy text string value into struct char var
	* */
	//int LINE_MAX_LEN = 500;
    char scvline[ LINE_MAX_LEN + 1 ];
	int counter=0;
	int arrayIndex=0;
	FILE * csvFile = fopen( filePath, "r" );

	while( fgets( scvline, LINE_MAX_LEN, csvFile ) ) {
		if (counter > 0 ) {
			record_field = parse_scripture_record( scvline );

			arrayIndex = counter - 1;
			dbArray[arrayIndex].scriptureID = record_field -> scriptureID;
			dbArray[arrayIndex].bookIndex = record_field -> bookIndex;
			dbArray[arrayIndex].chapterIndex = record_field -> chapterIndex;
			dbArray[arrayIndex].verseIndex = record_field -> verseIndex;
			dbArray[arrayIndex].scriptureText = record_field -> scriptureText;
		}
		counter++;
	}

	// destroy temp string memory
	free(record_field -> scriptureText);
	free(record_field);
	fclose(csvFile);
}

/*
 * Main
 *
 * Usecase Example
 * */

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my-csv-parser.h"

int main() {
    rosaryBead_t *rosaryBead_record_field = NULL;
    rosaryBead_t rosaryBead_dbArray[317];

    scripture_t *scripture_record_field = NULL;
    scripture_t scripture_dbArray[202];

	csvToStruct_rosaryBead(rosaryBead_record_field, rosaryBead_dbArray); 	// navigation roadmap FK db
    csvToStruct_scripture(scripture_record_field, scripture_dbArray);		// the er class I want to read

	int testIdx = rosaryBead_dbArray[111].rosaryBeadID;

    printf( "\n---\n Test: scripture_record_array[%d] \n", testIdx );
    printf(" scriptureID: %d\n", scripture_dbArray[testIdx].scriptureID );
    printf( " bookIndex: %d\n", scripture_dbArray[testIdx].bookIndex );
    printf( " chapterIndex: %d\n", scripture_dbArray[testIdx].chapterIndex );
    printf( " verseIndex: %d\n", scripture_dbArray[testIdx].verseIndex );
    printf( " scriptureText: %s\n", scripture_dbArray[testIdx].scriptureText );

	testIdx = 200;
    printf( "\n---\n Test: scripture_record_array[%d] \n", testIdx );
    printf(" scriptureID: %d\n", scripture_dbArray[testIdx].scriptureID );
    printf( " bookIndex: %d\n", scripture_dbArray[testIdx].bookIndex );
    printf( " chapterIndex: %d\n", scripture_dbArray[testIdx].chapterIndex );
    printf( " verseIndex: %d\n", scripture_dbArray[testIdx].verseIndex );
    printf( " scriptureText: %s\n", scripture_dbArray[testIdx].scriptureText );

	testIdx = 1;
    printf( "\n---\n Test: scripture_record_array[%d] \n", testIdx );
    printf(" scriptureID: %d\n", scripture_dbArray[testIdx].scriptureID );
    printf( " bookIndex: %d\n", scripture_dbArray[testIdx].bookIndex );
    printf( " chapterIndex: %d\n", scripture_dbArray[testIdx].chapterIndex );
    printf( " verseIndex: %d\n", scripture_dbArray[testIdx].verseIndex );
    printf( " scriptureText: %s\n", scripture_dbArray[testIdx].scriptureText );

    return 0;
}
*/
