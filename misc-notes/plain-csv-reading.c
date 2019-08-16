#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getRecordFieldNoQuotes(char* line, int num);
char *getRecordString(FILE *csvFile, int fieldNo, int recordNo);

int getQueryFK(FILE *csvFile, int fieldNo, int recordNo);
int userNumberInput();

char *getRecordFieldNoQuotes(char* line, int num) {
    char* tok;
    // C provides two functions strtok() and strtok_r() for splitting a string by some delimiter.
    for (tok = strtok(line, ";"); tok && *tok; tok = strtok(NULL, ";\n")) {
        if (!--num) {
            return tok;
        }
    }
    return NULL;
}

char *getRecordString(FILE *csvFile, int fieldNo, int recordNo) {
	char line[1024];
	int counter = 0;
	char *outputChar;

    while (fgets(line, 1024, csvFile)) {
        char* tmp = strdup(line);
        counter++;

        if(counter == recordNo) {
			outputChar = getRecordFieldNoQuotes(tmp, fieldNo);
			return outputChar;
		}
    }

    return NULL;
}

int getQueryFK(FILE *csvFile, int fieldNo, int recordNo) {

    char *charQuery = getRecordString(csvFile, fieldNo, recordNo);
    int returnInteger;
    returnInteger = atoi(charQuery);

    return returnInteger;
}

// UI
int userNumberInput() {
	// simulate navigation
    int myIndex;
    scanf("%d", &myIndex);
    return myIndex;
}

int main() {

    FILE * rosaryBeadCsv = fopen("../Rosary/csv/rosaryBead.csv", "r");
    FILE * scriptureCsv = fopen("../Rosary/csv/scripture.csv", "r");

	int scriptureFKField = 6;
    int scriptureTextField = 5;

    int rosaryBeadID;
    printf("\nEnter a number which simulates a bead progress position [0-200]: ");
    rosaryBeadID = userNumberInput();
    printf("\nrosaryBeadID: %d", rosaryBeadID);

    int scriptureFK;
    scriptureFK = getQueryFK(rosaryBeadCsv, scriptureFKField, rosaryBeadID);
    printf("\nscriptureFK: %d", scriptureFK);

    char *scriptureText = getRecordString(scriptureCsv, scriptureTextField, scriptureFK);
    printf("\nscriptureText: %s\n", scriptureText);

    fclose(rosaryBeadCsv);
    fclose(scriptureCsv);

    return 0;
}
