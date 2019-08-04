#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jsmn.h"

// #include <math.h> /* gcc jsmn-test2.c -lm */
//#include <time.h>
//#include "/home/mezcel/Downloads/MyCPrgm/general-functions.h"


/*
 * A small example of jsmn parsing when JSON structure is known and number of
 * tokens is predictable.
 */

/*static const char *JSON_STRING =
    "{\"user\": \"johndoe\", \"admin\": false, \"uid\": 1000,\n  "
    "\"groups\": [\"users\", \"wheel\", \"audio\", \"video\"]}";*/

/* Prototypes */
int noOfChars(char *inputString);
char *myConcat(char *str1, char *str2);
static int jsoneq(const char *json, jsmntok_t *tok, const char *s);
char *jsonFile2Char( char *filePath );
char *returnJsonObject( char *jsonDBstring, char *jsonObjName );
char *returnJsonTokenValue(char *jsonDBstring, char *attrString, int indexNo );

/* Functions */
int noOfChars(char *inputString) {
	int count=0;

	while ( inputString[count]!='\0' ) {
		count++;
	}

	return count;
}

char *myConcat(char *str1, char *str2) {
	char *outputString = "\0";
	int count1 = 0, count2 = 0;
	int str1Len = 0, str2Len = 0, combinedLen = 0;

	str1Len = noOfChars(str1);
	str2Len = noOfChars(str2);
	combinedLen = str1Len + str2Len;

	outputString = malloc( combinedLen );

	while ( count1 < str1Len ) {
		outputString[count1] = str1[count1];
		count1++;
	}

	while ( count2 < str2Len ) {
		outputString[count1+count2] = str2[count2];
		count2++;
	}

	outputString[count1+count2] = '\0'; //termination char

	return outputString;
}

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
	strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}

char *jsonFile2Char( char *filePath ) {
	char *buffer = 0;
	long length;
	FILE *f = fopen (filePath, "rb");

	if (f) {
		fseek (f, 0, SEEK_END);
		length = ftell (f);
		fseek (f, 0, SEEK_SET);
		buffer = malloc (length);

		if (buffer)	{
			fread (buffer, 1, length, f);
		}

		fclose (f);
	}

	if (buffer) {
		return buffer;
	} else {
		// file is no good
		return 0;
	}

}

char *returnJsonObject( char *jsonDBstring, char *jsonObjName ) {

	int i;
	int r;
	jsmn_parser p;
	int noTokens = 9473; // a number >= total number of tokens
	jsmntok_t t[noTokens]; //* We expect no more than 9473 tokens ??? i trial and errored this

	jsmn_init(&p);
	r = jsmn_parse(&p, jsonDBstring, strlen(jsonDBstring), t, sizeof(t) / sizeof(t[0]));

	char *jsonObject = malloc(noTokens);

	for (i = 1; i < r; i++) {
		if (jsoneq(jsonDBstring, &t[i], jsonObjName) == 0) {
			//printf("- bead: \n%.*s\n", t[i + 1].end - t[i + 1].start, JSON_STRING + t[i + 1].start); // stringwidth, string

			sprintf(jsonObject, "%.*s", t[i + 1].end - t[i + 1].start, jsonDBstring + t[i + 1].start);
			i++;
		}
	}

	/*char *openBracket = "{";
	char *closeBracket = "}";
	jsonObject = myConcat(openBracket, jsonObject);
	jsonObject = myConcat(jsonObject, closeBracket);*/

	return jsonObject;
}

char *returnJsonTokenValue(char *jsonEntityObj, char *attrString, int indexNo ) {
	int noTokens = 9473; // a number >= total number of tokens
	char *jsonTokenValue = malloc(noTokens);
	jsmntok_t t[noTokens]; //* We expect no more than 9473 tokens ??? i trial and errored this

	jsmn_parser p;
	jsmn_init(&p);

	int r = 0;
	r = jsmn_parse(&p, jsonEntityObj, strlen(jsonEntityObj), t, sizeof(t) / sizeof(t[0]));

	int indexCounter = 0;
	int i;
	for (i = 1; i < r; i++) {
		if (jsoneq(jsonEntityObj, &t[i], attrString) == 0) {
			if (indexCounter == indexNo) {

				sprintf(jsonTokenValue, "%.*s", t[i + 1].end - t[i + 1].start, jsonEntityObj + t[i + 1].start);

				char *openBracket = "{";
				char *closeBracket = "}";
				jsonTokenValue = myConcat(openBracket, jsonTokenValue);
				jsonTokenValue = myConcat(jsonTokenValue, closeBracket);

				break;
			} else {
				indexCounter = indexCounter + 1;
				i++;
			}
		}
	}

	return jsonTokenValue;

}

/* Main */

int main() {
	system("clear"); // linux

	char *JSON_STRING = jsonFile2Char( "test.json" ); // JSON file to char

	/*char *rosaryBead = returnJsonObject( JSON_STRING, "rosaryBead" ); // Store json object class to char
	char *bead = returnJsonObject( JSON_STRING, "bead" ); // Store json object class to char
	char *decade = returnJsonObject( JSON_STRING, "decade" ); // Store json object class to char
	char *mystery = returnJsonObject( JSON_STRING, "mystery" ); // Store json object class to char
	char *book = returnJsonObject( JSON_STRING, "book" ); // Store json object class to char
	char *scripture = returnJsonObject( JSON_STRING, "scripture" ); // Store json object class to char
	char *message = returnJsonObject( JSON_STRING, "message" ); // Store json object class to char
	char *prayer = returnJsonObject( JSON_STRING, "prayer" ); // Store json object class to char*/


	char *mystery = returnJsonObject( JSON_STRING, "mystery" ); // Store json object class to char
	printf("\n %s \n", returnJsonTokenValue( mystery, "mysteryName", 3 )); // query val by entity attr

	char *prayer = returnJsonObject( JSON_STRING, "prayer" ); // Store json object class to char
	printf("\n %s \n", returnJsonTokenValue( prayer, "prayerName", 3 )); // query val by entity attr

	return EXIT_SUCCESS;
}
