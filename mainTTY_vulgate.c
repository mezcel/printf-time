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

	// convert json into a struct database
	struct json_object *parsed_json;
	parsed_json = json_tokener_parse(buffer); // database var

	// Db entities
	struct json_object *rosaryBead;
	struct json_object *bead;
	struct json_object *decade;
	struct json_object *mystery;
	//struct json_object *book;
	struct json_object *scripture;
	struct json_object *message;
	struct json_object *prayer;
	struct json_object *mysteryInfo;

	// populate entities
	json_object_object_get_ex(parsed_json, "rosaryBead", &rosaryBead);
	json_object_object_get_ex(parsed_json, "bead", &bead);
	json_object_object_get_ex(parsed_json, "decade", &decade);
	json_object_object_get_ex(parsed_json, "mystery", &mystery);
	json_object_object_get_ex(parsed_json, "scripture", &scripture);
	json_object_object_get_ex(parsed_json, "message", &message);
	json_object_object_get_ex(parsed_json, "prayer", &prayer);
	json_object_object_get_ex(parsed_json, "mysteryInfo", &mysteryInfo);

	int navigtionPosition = 0;
	int beadFK, decadeFK, mysteryFK, scriptureFK, messageFK, prayerFK;
	int rosaryBeadID, loopBody, smallbeadPercent, mysteryPercent, mysteryNo;

	int desiredDispLen;	// linux terminal width
	char *titleLabel = " C/CSV Rosary ";
	char *footerLabel = " Rosary Progress ";

	while (navigtionPosition <= 315) {
		clearScreen(1);
		desiredDispLen = returnScreenWidth(1);

		// get FKs
		beadFK = queryAttrInteger(rosaryBead, "beadIndex", navigtionPosition);
		decadeFK = queryAttrInteger(rosaryBead, "decadeIndex", navigtionPosition);
		mysteryFK = queryAttrInteger(rosaryBead, "mysteryIndex", navigtionPosition);
		scriptureFK = queryAttrInteger(rosaryBead, "scriptureIndex", navigtionPosition);
		messageFK = queryAttrInteger(rosaryBead, "messageIndex", navigtionPosition);
		prayerFK = queryAttrInteger(rosaryBead, "prayerIndex", navigtionPosition);

		rosaryBeadID = queryAttrInteger(rosaryBead, "rosaryBeadID", navigtionPosition);
		loopBody = queryAttrInteger(rosaryBead, "loopBody", navigtionPosition);
		smallbeadPercent = queryAttrInteger(rosaryBead, "smallbeadPercent", navigtionPosition);
		mysteryPercent = queryAttrInteger(rosaryBead, "mysteryPercent", navigtionPosition);
		mysteryNo = queryAttrInteger(rosaryBead, "mysteryIndex", navigtionPosition);

		// display header
		borderCharPrintF("+", 3);
		printf(titleLabel);
		borderCharPrintF("+", desiredDispLen - 17);

		// display body
		printf("\n\n Mystery:\t%s", queryAttrString(mystery, "mysteryName", mysteryFK) );
		printf("\n\n Decade:\t%s", queryAttrString(decade, "decadeName", decadeFK) );
		multiLinePrintF("\n\t\t", queryAttrString(message, "mesageText", messageFK), desiredDispLen );
		multiLinePrintF("\n Background:\t", queryAttrString(decade, "decadeInfo", decadeFK), desiredDispLen );
		multiLinePrintF("\n Scripture:\t", queryAttrString(scripture, "scriptureText", scriptureFK), desiredDispLen );
		multiLinePrintF("\n Prayer:\t", queryAttrString(prayer, "prayerText", prayerFK), desiredDispLen );
		printf("\n Bead Type:\t%s\n\n", queryAttrString(bead, "beadType", beadFK) );

		// display footer
		borderCharPrintF("+", 3);
		printf(footerLabel);
		borderCharPrintF("+", desiredDispLen - 20);
		displayProgress(rosaryBeadID, loopBody, smallbeadPercent, mysteryPercent, mysteryNo, prayerFK);

		// Navigation Input & Accumulator
		navigtionPosition = pressKeyContinue(navigtionPosition, 1);
	}

}
