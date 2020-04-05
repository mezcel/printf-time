/*
 * my_file_to_struct.h
 * */

// fileguard
#ifndef MY_FILE_TO_STRUCT
#define MY_FILE_TO_STRUCT

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

typedef struct rosary_db {
	// one must know beforehand how big each array needs to be

	rosaryBead_t rosaryBead_dbArray[317];
	bead_t bead_dbArray[9];
	book_t book_dbArray[17];
	decade_t decade_dbArray[22];
	message_t message_dbArray[22];
	mystery_t mystery_dbArray[7];
	prayer_t prayer_dbArray[11];
	scripture_t scripture_dbArray[202];
} rosary_db_t;

/*
 * CSV Prototypes
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

void make_struct_db_csv( rosary_db_t *rosary_db_struct, char *csv_path_array[8] );

/*
 * JSON Prototypes
 * */

size_t returnFileSize(char *filePath);
struct json_object *json_to_struct( char *jsonFilePath );
char *queryAttrString( struct json_object *inputObject, char *attrName, int index );
int queryAttrInteger( struct json_object *inputObject, char *attrName, int index );

void make_struct_db_json( rosary_db_t *rosary_db_struct, char *filePath );

#endif
