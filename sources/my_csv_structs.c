/*
 * my_csv_structs.c
 * */

/*
 *  Dependencies: stdio.h, stdlib.h, string.h
 *	Database .csv files: bead.csv, decade.csv, message.csv, mystery.csv,
 *		prayer.csv, rosaryBead.csv, scripture.csv
 * 	Background:
 * 		I used npm's json2csv, https://www.csvjson.com/json2csv to
 * 			to convert json to csv
 * */

/*
 * Functions
 * */

#ifdef _WIN32 // MinGW
	#include <windows.h>
	#include <stdio.h>
	#include <tchar.h>
#endif

#ifdef linux // Linux GCC v6+
	#include <stdlib.h>		// calloc(), realloc(), malloc(), system(), free()
	#include <stdio.h>
	#include <string.h>
	#include <sys/ioctl.h>	// ioctl(), TIOCGWINSZ
	#include <unistd.h> 	// STDOUT_FILENO
#endif

#include "../headers/my_csv_structs.h"

/*
 * Header API Scope Functions
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

void csvToStruct_bead(bead_t *record_field, bead_t dbArray[9], int LINE_MAX_LEN, char *filePath) {
	/*
	* Copy text string value into struct char var
	* */
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