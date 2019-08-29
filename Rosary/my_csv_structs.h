/*
 * my_csv_structs.h
 * */

/*
 *  Dependencies: stdio.h, stdlib.h, string.h
 *	Database .csv files: bead.csv, decade.csv, message.csv, mystery.csv,
 *		prayer.csv, rosaryBead.csv, scripture.csv
 * 	Background:
 * 		I used npm's json2csv, https://www.csvjson.com/json2csv to
 * 			to convert json to csv
 * */

// fileguard
#ifndef MY_CSV_STRUCTS
#define MY_CSV_STRUCTS

/*
 * Data Structures
 * */

typedef struct rosaryBead_struct {
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
	int beadID;
	char *beadType;
} bead_t;

typedef struct book_struct {
	int bookID;
	char *bookName;
	char *library;
} book_t;

typedef struct decade_struct {
	int decadeID;
	int mysteryIndex;
	int decadeNo;
	char *decadeName;
	char *decadeInfo;
	char *infoRefference;
} decade_t;

typedef struct message_struct {
	int messageID;
	char *mesageText;
} message_t;

typedef struct mystery_struct {
	int mysteryID;
	int mysteryNo;
	char *mysteryName;
} mystery_t;

typedef struct prayer_struct {
	int prayerID;
	char *prayerName;
	char *prayerText;
} prayer_t;

typedef struct scripture_struct {
	int scriptureID;
	int bookIndex;
	int chapterIndex;
	int verseIndex;
	char *scriptureText;
} scripture_t;

/*
 * Prototypes
 * */

char ** strsplit( const char * src, const char * delim );
void strsplitfree( char ** strlist );

rosaryBead_t * parse_rosaryBead_record( char * scvline );
bead_t * parse_bead_record( char * scvline );
book_t * parse_book_record( char * scvline );
decade_t * parse_decade_record( char * scvline );
message_t * parse_message_record( char * scvline );
mystery_t * parse_mystery_record( char * scvline );
prayer_t * parse_prayer_record( char * scvline );
scripture_t * parse_scripture_record( char * scvline );

void csvToStruct_rosaryBead(rosaryBead_t *record_field, rosaryBead_t dbArray[317], int LINE_MAX_LEN, char *filePath);
void csvToStruct_bead(bead_t *record_field, bead_t dbArray[9], int LINE_MAX_LEN, char *filePath);
void csvToStruct_book(book_t *record_field, book_t dbArray[17], int LINE_MAX_LEN, char *filePath);
void csvToStruct_decade(decade_t *record_field, decade_t dbArray[22], int LINE_MAX_LEN, char *filePath);
void csvToStruct_message(message_t *record_field, message_t dbArray[22], int LINE_MAX_LEN, char *filePath);
void csvToStruct_mystery(mystery_t *record_field, mystery_t dbArray[7], int LINE_MAX_LEN, char *filePath);
void csvToStruct_prayer(prayer_t *record_field, prayer_t dbArray[11], int LINE_MAX_LEN, char *filePath);
void csvToStruct_scripture(scripture_t *record_field, scripture_t dbArray[202], int LINE_MAX_LEN, char *filePath);

#endif
