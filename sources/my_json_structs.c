/*
 * my_json_structs.c
 *
 * guidance: https://json-c.github.io/json-c/json-c-0.10/doc/html/json__object_8h.html
 * sudo apt install -y build-essential gcc libgtk-3-dev libjson-c-dev libjson-c-doc libjson-c3
 * compile: gcc -c sources/my_json_structs.c -ljson-c
 * */

#include <stdio.h>
#include <sys/stat.h> 		// used to get file size, stat()
#include <json-c/json.h>	// Debian Linux json-c library

#include "../headers/my_file_to_struct.h"

/*
 * import json using json-c
 * */

size_t returnFileSize( char *jsonFilePath ) {
	// Get the size of a json file
	struct stat st;
	stat( jsonFilePath, &st );
	size_t size = st.st_size; // size in bytes

	return size;
}

struct json_object *json_to_struct( char *jsonFilePath ) {

	FILE *fp;
	int FILE_BUFFER_SIZE = returnFileSize( jsonFilePath );
	char buffer[ FILE_BUFFER_SIZE ];

	fp = fopen( jsonFilePath,"r" );
	fread( buffer, FILE_BUFFER_SIZE, 1, fp );
	fclose( fp );

	return json_tokener_parse( buffer );
}

char *queryAttrString( struct json_object *inputObject, char *attrName, int index ) {
	struct json_object *parsed_json;
	parsed_json = json_object_array_get_idx( inputObject, index );

	struct json_object *attr;
	json_object_object_get_ex( parsed_json, attrName, &attr );

	return ( char * )json_object_get_string( attr );
}

int queryAttrInteger( struct json_object *inputObject, char *attrName, int index ) {
	struct json_object *parsed_json;
	parsed_json = json_object_array_get_idx( inputObject, index );

	struct json_object *attr;
	json_object_object_get_ex( parsed_json, attrName, &attr );

	return json_object_get_int( attr );
}

/*
 * convert json-c struct to rosary_db_t
 * */

void jsonToStruct_rosaryBead( rosary_db_t *rosary_db_struct, struct json_object *parsed_json_db ) {

	struct json_object *er_object;
	json_object_object_get_ex( parsed_json_db, "rosaryBead", &er_object );

	int er_object_size = json_object_array_length( er_object );

	for ( int i = 0; i < er_object_size; i++ ) {
		rosary_db_struct -> rosaryBead_dbArray[ i ].rosaryBeadID = queryAttrInteger( er_object, "rosaryBeadID", i );
		rosary_db_struct -> rosaryBead_dbArray[ i ].beadIndex = queryAttrInteger( er_object, "beadIndex", i );
		rosary_db_struct -> rosaryBead_dbArray[ i ].decadeIndex = queryAttrInteger( er_object, "decadeIndex", i );
		rosary_db_struct -> rosaryBead_dbArray[ i ].mysteryIndex = queryAttrInteger( er_object, "mysteryIndex", i );
		rosary_db_struct -> rosaryBead_dbArray[ i ].prayerIndex = queryAttrInteger( er_object, "prayerIndex", i );
		rosary_db_struct -> rosaryBead_dbArray[ i ].scriptureIndex = queryAttrInteger( er_object, "scriptureIndex", i );
		rosary_db_struct -> rosaryBead_dbArray[ i ].messageIndex = queryAttrInteger( er_object, "messageIndex", i );
		rosary_db_struct -> rosaryBead_dbArray[ i ].loopBody = queryAttrInteger( er_object, "loopBody", i );
		rosary_db_struct -> rosaryBead_dbArray[ i ].smallbeadPercent = queryAttrInteger( er_object, "smallbeadPercent", i );
		rosary_db_struct -> rosaryBead_dbArray[ i ].mysteryPercent = queryAttrInteger( er_object, "mysteryPercent", i );
	}
}

void jsonToStruct_bead( rosary_db_t *rosary_db_struct, struct json_object *parsed_json_db ) {
	struct json_object *er_object;
	json_object_object_get_ex( parsed_json_db, "bead", &er_object );

	int er_object_size = json_object_array_length( er_object );

	for ( int i = 0; i < er_object_size; i++ ) {
		rosary_db_struct -> bead_dbArray[ i ].beadID = queryAttrInteger( er_object, "beadID", i );
		rosary_db_struct -> bead_dbArray[ i ].beadType = queryAttrString( er_object, "beadType", i );
	}
}

void jsonToStruct_book( rosary_db_t *rosary_db_struct, struct json_object *parsed_json_db ) {
	struct json_object *er_object;
	json_object_object_get_ex( parsed_json_db, "book", &er_object );

	int er_object_size = json_object_array_length( er_object );

	for ( int i = 0; i < er_object_size; i++ ) {
		rosary_db_struct -> book_dbArray[ i ].bookID = queryAttrInteger( er_object, "bookID", i );
		rosary_db_struct -> book_dbArray[ i ].bookName = queryAttrString( er_object, "bookName", i );

	}
}

void jsonToStruct_decade( rosary_db_t *rosary_db_struct, struct json_object *parsed_json_db ) {
	struct json_object *er_object;
	json_object_object_get_ex( parsed_json_db, "decade", &er_object );

	int er_object_size = json_object_array_length( er_object );

	for ( int i = 0; i < er_object_size; i++ ) {
		rosary_db_struct -> decade_dbArray[ i ].decadeID = queryAttrInteger( er_object, "decadeID", i );
		rosary_db_struct -> decade_dbArray[ i ].mysteryIndex = queryAttrInteger( er_object, "mysteryIndex", i );
		rosary_db_struct -> decade_dbArray[ i ].decadeNo = queryAttrInteger( er_object, "decadeNo", i );
		rosary_db_struct -> decade_dbArray[ i ].decadeName = queryAttrString( er_object, "decadeName", i );
		rosary_db_struct -> decade_dbArray[ i ].decadeInfo = queryAttrString( er_object, "decadeInfo", i );
		rosary_db_struct -> decade_dbArray[ i ].infoRefference = queryAttrString( er_object, "infoRefference", i );
	}
}

void jsonToStruct_message( rosary_db_t *rosary_db_struct, struct json_object *parsed_json_db ) {
	struct json_object *er_object;
	json_object_object_get_ex( parsed_json_db, "message", &er_object );

	int er_object_size = json_object_array_length( er_object );

	for ( int i = 0; i < er_object_size; i++ ) {
		rosary_db_struct -> message_dbArray[ i ].messageID = queryAttrInteger( er_object, "messageID", i );
		rosary_db_struct -> message_dbArray[ i ].mesageText = queryAttrString( er_object, "mesageText", i );
	}
}

void jsonToStruct_mystery( rosary_db_t *rosary_db_struct, struct json_object *parsed_json_db ) {
	struct json_object *er_object;
	json_object_object_get_ex( parsed_json_db, "mystery", &er_object );

	int er_object_size = json_object_array_length( er_object );

	for ( int i = 0; i < er_object_size; i++ ) {
		rosary_db_struct -> mystery_dbArray[ i ].mysteryID = queryAttrInteger( er_object, "mysteryID", i );
		rosary_db_struct -> mystery_dbArray[ i ].mysteryNo = queryAttrInteger( er_object, "mysteryNo", i );
		rosary_db_struct -> mystery_dbArray[ i ].mysteryName = queryAttrString( er_object, "mysteryName", i );
	}
}

void jsonToStruct_prayer( rosary_db_t *rosary_db_struct, struct json_object *parsed_json_db ) {
	struct json_object *er_object;
	json_object_object_get_ex( parsed_json_db, "prayer", &er_object );

	int er_object_size = json_object_array_length( er_object );

	for ( int i = 0; i < er_object_size; i++ ) {
		rosary_db_struct -> prayer_dbArray[ i ].prayerID = queryAttrInteger( er_object, "prayerID", i );
		rosary_db_struct -> prayer_dbArray[ i ].prayerName = queryAttrString( er_object, "prayerName", i );
		rosary_db_struct -> prayer_dbArray[ i ].prayerText = queryAttrString( er_object, "prayerText", i );
	}
}

void jsonToStruct_scripture( rosary_db_t *rosary_db_struct, struct json_object *parsed_json_db ) {
	struct json_object *er_object;
	json_object_object_get_ex( parsed_json_db, "scripture", &er_object );

	int er_object_size = json_object_array_length( er_object );

	for ( int i = 0; i < er_object_size; i++ ) {
		rosary_db_struct -> scripture_dbArray[ i ].scriptureID = queryAttrInteger( er_object, "scriptureID", i );
		rosary_db_struct -> scripture_dbArray[ i ].bookIndex = queryAttrInteger( er_object, "bookIndex", i );
		rosary_db_struct -> scripture_dbArray[ i ].chapterIndex = queryAttrInteger( er_object, "chapterIndex", i );
		rosary_db_struct -> scripture_dbArray[ i ].verseIndex = queryAttrInteger( er_object, "verseIndex", i );
		rosary_db_struct -> scripture_dbArray[ i ].scriptureText = queryAttrString( er_object, "scriptureText", i );
	}
}

/*
 * populate rosary_db_t
 * */

void make_struct_db_json( rosary_db_t *rosary_db_struct, char *jsonFilePath ) {
	struct json_object *parsed_json;
	parsed_json = json_to_struct( jsonFilePath );

	jsonToStruct_rosaryBead( rosary_db_struct, parsed_json );
	jsonToStruct_bead( rosary_db_struct, parsed_json );
	jsonToStruct_book( rosary_db_struct, parsed_json );
	jsonToStruct_decade( rosary_db_struct, parsed_json );
	jsonToStruct_message( rosary_db_struct, parsed_json );
	jsonToStruct_mystery( rosary_db_struct, parsed_json );
	jsonToStruct_prayer( rosary_db_struct, parsed_json );
	jsonToStruct_scripture( rosary_db_struct, parsed_json );
}
