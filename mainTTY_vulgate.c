#include <stdio.h>
#include <json-c/json.h>
#include <sys/stat.h> // used for file size
#include "headers/my_json_c.h"
#include "sources/my_json_c.c"

/*
 * Compile: gcc main.c -ljson-c
 * */


int main(int argc, char **argv) {

	FILE *fp;
	char * filePath = "database/json/rosaryJSON-vulgate.json";
	int FILE_BUFFER_SIZE = returnFileSize(filePath);
	char buffer[FILE_BUFFER_SIZE];

	fp = fopen(filePath,"r");
	fread(buffer, FILE_BUFFER_SIZE, 1, fp);
	fclose(fp);

	struct json_object *parsed_json;
	parsed_json = json_tokener_parse(buffer); // db

	struct json_object *rosaryBead;
	struct json_object *bead;
	struct json_object *decade;
	struct json_object *mystery;
	struct json_object *book;
	struct json_object *scripture;
	struct json_object *message;
	struct json_object *prayer;
	struct json_object *mysteryInfo;

	json_object_object_get_ex(parsed_json, "rosaryBead", &rosaryBead);
	json_object_object_get_ex(parsed_json, "bead", &bead);
	json_object_object_get_ex(parsed_json, "decade", &decade);
	json_object_object_get_ex(parsed_json, "mystery", &mystery);
	json_object_object_get_ex(parsed_json, "book", &book);
	json_object_object_get_ex(parsed_json, "scripture", &scripture);
	json_object_object_get_ex(parsed_json, "message", &message);
	json_object_object_get_ex(parsed_json, "prayer", &prayer);
	json_object_object_get_ex(parsed_json, "mysteryInfo", &mysteryInfo);

	int position = 23;

	int beadFK = queryAttrInteger(rosaryBead, "beadIndex", position);
	printf("beadType: %s\n",	queryAttrString(bead, "beadType", beadFK) );
	printf("beadID: %d\n",		queryAttrInteger(bead, "beadID", beadFK) );

}
