/*
 * my_file_to_struct.h
 * */

#ifndef MY_FILE_TO_STRUCT
#define MY_FILE_TO_STRUCT

/*
 * Data Structures
 * Structs which server as ER Database Classes
 * Scripture Rosary Database
 * */

/* ER Class Struct: Rosary Bead */
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

/* ER Class Struct: Bead */
typedef struct bead_struct {
    int beadID;
    char *beadType;
} bead_t;

/* ER Class Struct: Book */
typedef struct book_struct {
    int bookID;
    char *bookName;
    char *library;
} book_t;

/* ER Class Struct: Decade */
typedef struct decade_struct {
    int decadeID;
    int mysteryIndex;
    int decadeNo;
    char *decadeName;
    char *decadeInfo;
    char *infoRefference;
} decade_t;

/* ER Class Struct: Message */
typedef struct message_struct {
    int messageID;
    char *mesageText;
} message_t;

/* ER Class Struct: Mystery */
typedef struct mystery_struct {
    int mysteryID;
    int mysteryNo;
    char *mysteryName;
} mystery_t;

/* ER Class Struct: Prayer */
typedef struct prayer_struct {
    int prayerID;
    char *prayerName;
    char *prayerText;
} prayer_t;

/* ER Class Struct: Scripture */
typedef struct scripture_struct {
    int scriptureID;
    int bookIndex;
    int chapterIndex;
    int verseIndex;
    char *scriptureText;
} scripture_t;

/* ER Database Struct: Scripture Rosary Database */
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
 * Feast day mini db
 * Additional ER Class for the feast day database
 * */

/* ER Class Struct: Feast */
typedef struct feast_struct {
    int feastID;
    char *feastName;
    int feastDay;
    int feastMonth;
    char *monthName;
} feast_t;

/* ER Database Struct: Feast Day Database */
typedef struct feast_db {
    // one must know beforehand how many records are there
    feast_t feast_dbArray[100]; // this will accomidate 100 feasts records
} feast_db_t;

/*
 * CSV DB Prototypes
 * */

/* Split string into delineated segments. Used for Parsing a CSV record into attributes. */
char ** strsplit( const char * src, const char * delim );

/* Free char memory used by "char ** strsplit( const char * src, const char * delim );" */
void strsplitfree( char ** strlist );

/* Return the number of records listed in a CSV file */
int returnCsvRecordCount(char * filePath);

/* Parse a CSV record into an ER struct class attribute. (ER Class: Rosary Bead) */
rosaryBead_t * parse_rosaryBead_record( char * scvline );

/* Parse a CSV record into an ER struct class attribute. (ER Class: Bead) */
bead_t * parse_bead_record( char * scvline );

/* Parse a CSV record into an ER struct class attribute. (ER Class: Book) */
book_t * parse_book_record( char * scvline );

/* Parse a CSV record into an ER struct class attribute. (ER Class: Decade) */
decade_t * parse_decade_record( char * scvline );

/* Parse a CSV record into an ER struct class attribute. (ER Class: Message) */
message_t * parse_message_record( char * scvline );

/* Parse a CSV record into an ER struct class attribute. (ER Class: Mystery) */
mystery_t * parse_mystery_record( char * scvline );

/* Parse a CSV record into an ER struct class attribute. (ER Class: Prayer) */
prayer_t * parse_prayer_record( char * scvline );

/* Parse a CSV record into an ER struct class attribute. (ER Class: Scripture) */
scripture_t * parse_scripture_record( char * scvline );

/* Parse a CSV record into an ER struct class attribute. (ER Class: Feast) */
feast_t * parse_feast_record( char * scvline );

/* Make a struct ER Database from Biblical and Rosary CSV files. */
void make_struct_rosary_db_csv( rosary_db_t *rosary_db_struct, char *csv_path_array[8] );

/* Make a struct ER Database from a feast day CSV file. */
void make_struct_feast_db_csv( feast_db_t *feast_db_struct, char *filePath );

/*
 * JSON DB Prototypes
 * */

/* Return the file size of a JSON file. */
size_t returnFileSize(char *filePath);

/* Input a json database file and return that database as a ER struct. */
struct json_object *json_to_struct( char *jsonFilePath );

/* Query an attribute string from a "json to struct" ER database */
char *queryAttrString( struct json_object *inputObject, char *attrName, int index );

/* Query an integer PK/FK from a "json to struct" ER database */
int queryAttrInteger( struct json_object *inputObject, char *attrName, int index );

/* Make a struct ER Database from Biblical and Rosary JSON fils. */
void make_struct_rosary_db_json( rosary_db_t *rosary_db_struct, char *filePath );

/* Make a struct ER Database from a feast day JSON file. */
void make_struct_feast_db_json( feast_db_t *feast_db_struct, char *jsonFilePath );

#endif
