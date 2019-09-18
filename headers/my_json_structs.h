/*
 * my_json_structs.h
 * */


#ifndef MY_JSON_STRUCTS
#define MY_JSON_STRUCTS

/*#include <stdio.h>
#include <json-c/json.h>
#include <sys/stat.h> // used for file size
#include <json-c/json.h>*/

/*
 * Data Structures
 * */

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

size_t returnFileSize(char *filePath);
struct json_object *json_to_struct( char *filePath );
char *queryAttrString(struct json_object *inputObject, char *attrName, int index);
int queryAttrInteger(struct json_object *inputObject, char *attrName, int index);

void make_struct_db_json(rosary_db_t *rosary_db_struct, char *filePath);

#endif
