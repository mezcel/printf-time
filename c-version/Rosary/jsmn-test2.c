#include "jsmn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*#include <math.h>
#include <ctype.h> // isdigit()*/


/* *****************************
 * Prototypes
 * *****************************/

int noOfChars(char *inputString);
char *myConcat(char *str1, char *str2);
int jsoneq(char *json, jsmntok_t *tok, char *s);
char *jsonFile2Char( char *filePath );
int returnEstimatedTokenCount(int attrCount, int objectCount);
char *returnJsonTokenValue( char *JSON_STRING, int estimatedTokens, char *attrString, int indexNo );
char *returnTokenString(char *JSON_STRING, int estimatedTokens, char *objClassNameString, int tokenArrayIndex );
int returnTokenInteger(char *JSON_STRING, int estimatedTokens, char *objClassNameString, int tokenArrayIndex );

/* *****************************
 * Functions
 * *****************************/

int noOfChars(char *inputString) {
	/* count number of chars in a string */
	int count=0;

	while ( inputString[count]!='\0' ) {
		count++;
	}

	return count;
}

char *myConcat(char *str1, char *str2) {
	/* manually concat 2 strings */

	char *outputString = "\0";
	int count1 = 0, count2 = 0;
	int str1Len = 0, str2Len = 0, combinedLen = 0;

	str1Len = noOfChars(str1);
	str2Len = noOfChars(str2);
	combinedLen = str1Len + str2Len;

	printf("\n str1Len=%d str2Len=%d combinedLen=%d", str1Len, str2Len, combinedLen);

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

int jsoneq(char *json, jsmntok_t *tok, char *s) {
	/*
	 * Used to flag if the json string is usable for jsmn
	 * Taken from the jsmn example dir
	 * usecase:
	 * r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t, sizeof(t) / sizeof(t[0])); */
	if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start && strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	} else {
		return -1;
	}

}

char *jsonFile2Char( char *filePath ) {
	/* convert my json file to string variable */

	char *buffer;
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

int returnEstimatedTokenCount(int attrCount, int objectCount) {
	/* my technique for generating a token count number */

	int tokensPerArrayObject;
	int tokensPerEntity;
	int tokensPerClass;

	tokensPerArrayObject = attrCount * 2;
	tokensPerEntity = tokensPerArrayObject + 4;
	tokensPerClass = tokensPerEntity * objectCount;

	return tokensPerClass;
}

char *returnTokenString(char *JSON_STRING, int estimatedTokens, char *objClassNameString, int tokenArrayIndex ) {
	/* query a json token value based on name and sequence order */

	int r;

	jsmn_parser p;
	jsmntok_t t[estimatedTokens]; /* We expect no more than 2800 tokens */
	//memset(t, 0, estimatedTokens);
	jsmn_init(&p);

	r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t, sizeof(t) / sizeof(t[0]));

	if (r < 0) {
		printf("Failed to parse JSON: %d\n", r);
		//return 1;
	}

	/* Assume the top-level element is an object */
	if (r < 1 || t[0].type != JSMN_OBJECT) {
		printf("Object expected\n");
		//return 1;
	}

	int indexCounter = 0;
	char *outString;
	outString = malloc(500); // the longest known centence is ~1300 chars, so I just added some more for overkill
	for (int i = 1; i < r; i++) {
		if (jsoneq(JSON_STRING, &t[i], objClassNameString) == 0) {
			if (indexCounter == tokenArrayIndex) {
				char *strStart = JSON_STRING + t[i + 1].start;
				size_t strLength = t[i + 1].end - t[i + 1].start;
				strncpy(outString, strStart, strLength);
				//break;
				i = r;
			} else {
				indexCounter = indexCounter + 1;
				//i++;
				i += t[i + 1].size + 1;
			}
		}
	}

	return outString;
}

/* *****************************
 * main
 * *****************************/

int main() {

	// int rosaryBeadTokens = returnEstimatedTokenCount(10, 315); // ((number of attributes) * 2 ) * (obj array size)
	int beadTokens = returnEstimatedTokenCount(2, 6);
	int decadeTokens = returnEstimatedTokenCount(6, 20);
	int mysteryTokens = returnEstimatedTokenCount(3, 5);
	int bookTokens = returnEstimatedTokenCount(2, 14);
	int scriptureTokens = returnEstimatedTokenCount(5, 200);
	int messageTokens = returnEstimatedTokenCount(2, 20);
	int prayerTokens = returnEstimatedTokenCount(3, 10);

	char *beadJsonString = jsonFile2Char( "json/bead.json" ); // JSON file to char
	//printf("\n beadID: 1 = %s\n", returnTokenString(beadJsonString, beadTokens, "beadID", 1));
	printf("\n beadType: 1 = %s\n", returnTokenString(beadJsonString, beadTokens, "beadType", 1));

	char *decadeJsonString = jsonFile2Char( "json/decade.json" ); // JSON file to char
	//printf("\n decadeID: 1 = %s\n", returnTokenString(decadeJsonString, decadeTokens, "decadeID", 1));
	printf("\n decadeInfo: 1 = %s\n", returnTokenString(decadeJsonString, decadeTokens, "decadeInfo", 1));

	char *mysteryJsonString = jsonFile2Char( "json/mystery.json" ); // JSON file to char
	//printf("\n mysteryID: 1 = %s\n", returnTokenString(decadeJsonString, decadeTokens, "mysteryID", 1));
	printf("\n mysteryName: 1 = %s\n", returnTokenString(mysteryJsonString, mysteryTokens, "mysteryName", 1));

	char *bookJsonString = jsonFile2Char( "json/book.json" ); // JSON file to char
	//printf("\n bookID: 1 = %s\n", returnTokenString(decadeJsonString, decadeTokens, "bookID", 1));
	printf("\n bookName: 1 = %s\n", returnTokenString(bookJsonString, bookTokens, "bookName", 1));

	char *scriptureJsonString = jsonFile2Char( "json/scripture.json" ); // JSON file to char
	//printf("\n scriptureID: 1 = %s\n", returnTokenString(decadeJsonString, decadeTokens, "scriptureID", 1));
	printf("\n scriptureText: 1 = %s\n", returnTokenString(scriptureJsonString, scriptureTokens, "scriptureText", 1));

	char *messageJsonString = jsonFile2Char( "json/message.json" ); // JSON file to char
	//printf("\n messageID: 1 = %s\n", returnTokenString(decadeJsonString, decadeTokens, "messageID", 1));
	printf("\n mesageText: 1 = %s\n", returnTokenString(messageJsonString, messageTokens, "mesageText", 1));

	char *prayerJsonString = jsonFile2Char( "json/prayer.json" ); // JSON file to char
	//printf("\n prayerID: 1 = %s\n", returnTokenString(decadeJsonString, decadeTokens, "prayerID", 1));
	printf("\n prayerText: 1 = %s\n", returnTokenString(prayerJsonString, prayerTokens, "prayerText", 1));

	return EXIT_SUCCESS;
}
