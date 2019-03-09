/* Easter Day Calculations (runFunctions.h)
 *
 * functions used just for the main.c
 * */

/*
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <math.h>
 * #include <time.h>
 * #include "general-header.h"
 * #include "pfm-tables.h"
 * #include "easter-algorithms.h"
 * */

/* Function Prototypes */

void verboseDisplay(int yearInt);
void simpleDisplay(int yearInt);
int daysUntillPFM(int yearInt);
void nextPFM();
void print2file(char *stringInput, char *filePathInputChar);
int is4DigitChar(char *charInput);
int isVerboseFlag(char *charFlag, char *yearChar);
int isFileOutFlag(char *charFlag, char *filePathChar);
static int inspectMainInputs( int argc, const char *argv[] );

/* Function Definition */

void verboseDisplay(int yearInt) {

	static char *outputString='\0';
	struct EasterDay outputDate;

	printf("----------------------------------------\n"
			"Easter %d Dates:\n"
			"----------------------------------------\n",
			yearInt);

	/* Gauss Algorithm */
	outputDate = gauss_Easter_algorithm(yearInt);
	printf("\nGauss Output:\n\t%s %d, %s %d -- Gregorian Calendar,"
			" mixed var array\n", outputDate.weekday, outputDate.day,
			outputDate.month, outputDate.year);

	/* Anonymous Algorithm */
	outputDate = anonymous_Gregorian_algorithm(yearInt);
	printf("\nAnonymous Output:\n\t%s %d, %s %d -- Gregorian Calendar,"
			" mixed var array\n", outputDate.weekday, outputDate.day,
			outputDate.month, outputDate.year);

	/* Meeus Algorithm */
	outputDate = meeus_Julian_algorithm(yearInt);
	printf("\nMeeus Output:\n\t%s %d, %s %d -- Julian Calendar, mixed var array\n",
			outputDate.weekday, outputDate.day, outputDate.month, outputDate.year);

	/* PFM Table Algorithm */
	outputDate = pfm_algorithm(yearInt);
	printf("\nPaschal Full Moon (PFM) Output:\n\t%s %d, %s %d -- Gregorian Calendar,"
			" mixed var array\n\n",
			outputDate.weekday, outputDate.day, outputDate.month, outputDate.year);


	// Output as as a string variable
	outputString = outputDate2OutputString(outputDate);
	printf("PFM output as a single char array value:\n\tString array: %s\n",
			outputString);

	// Demo Array Illustration
	dispDemoArray(outputString);

	// Last line is for a Bash value parse, for use in other applications
	printf("\n------------------------\n"
		"This following 'last line' line will be used as a string to"
		" input into Bash for any further POSIX formatted date calculations.\n");
	printf("\n%s", outputString);

}

void simpleDisplay(int yearInt) {

	static char *outputString='\0';
	struct EasterDay outputDate;

	/* PFM Table Algorithm */
	outputDate = pfm_algorithm(yearInt);

	// Output as as a string variable
	outputString = outputDate2OutputString(outputDate);

	printf("%s", outputString);

}

int daysUntillPFM(int yearInt) {

	struct tm myTMstruct;
	struct EasterDay pfmStruct;
	int pfmDay, pfmMonth, pfmYear;

	pfmStruct = pfm_algorithm(yearInt);
	// pfmStruct = pfm_algorithm(2019);

    pfmYear = pfmStruct.year;
    pfmDay = pfmStruct.day;

	//if ( pfmStruct.month == "March" ) {
    char *monthCharStr = pfmStruct.month;
    int isMarch = compareStrings( monthCharStr, "March");
    if ( isMarch ) {
		pfmMonth = 3;
	} else {
		pfmMonth = 4;
	}

    myTMstruct = defineTMstruct(pfmYear, pfmMonth, pfmDay); // year, month, day

	time_t now;
	time(&now);

	int inputPfmTime = mktime(&myTMstruct);

	double seconds = difftime(inputPfmTime, now); // end, start
	double days = seconds / 86400; // 86400 seconds / 1 day

	printf("\nThe next Paschal Full Moon:\n\tThis year\n\tIn %f days"
		"\n\tOn %s %d %s %d",
		days, pfmStruct.weekday, pfmStruct.day,  pfmStruct.month, pfmStruct.year);

	return days;
}

void nextPFM() {
	int yearInt = 2019;
	int days = daysUntillPFM(yearInt);

	if ( days < 0 ) {
		struct EasterDay pfmStruct;
		pfmStruct = pfm_algorithm(yearInt++);

		printf("\nThe next Paschal Ful Moon:\n\t NEXT year "
			"\n\tOn %s %d %s %d",
			pfmStruct.weekday, pfmStruct.day,  pfmStruct.month, pfmStruct.year);
	}
}

/////////// v0.1.1 //////////////////

void print2file(char *stringInput, char *filePathInputChar) {

	FILE *fp;
	fp = fopen( filePathInputChar, "w+" );
	fputs(stringInput, fp);
	fclose(fp);

}

int inputFlagType (char *inputChar) {
	int isVerbose, isPrintToFile, returnState;

	isVerbose = compareStrings(inputChar, "-v");
	isPrintToFile = compareStrings(inputChar, "-f");

	if (isVerbose) {
		returnState = 1;
	} else if(isPrintToFile) {
		returnState = 2;
	} else {
		returnState = 0;
	}

	return returnState;
}

int is4DigitChar(char *charInput) {
	char *endptr;
	static int inputLength, isNumber;

	inputLength = noOfChars(charInput);
	strtol(charInput, &endptr, 10);

	// is char a 4 digit number
	if ( (*endptr == '\0') && (inputLength == 4) ) {
		isNumber = 1;
	}

	return isNumber;
}

int isVerboseFlag(char *charFlag, char *yearChar) {
	static int isVerbose, isNumber; // default 0

	isVerbose = compareStrings(charFlag, "-v");
	if ( isVerbose ) {
		isNumber = is4DigitChar(charFlag); // want number
	}

	if (isNumber) {
		isVerbose = 1;
	}

	return isVerbose;
}

int isFileOutFlag(char *charFlag, char *filePathChar) {
	static int isFileOut, isNumber;

	isFileOut = compareStrings(charFlag, "-f");
	if ( isFileOut ) {
		isNumber = is4DigitChar(filePathChar); // dont want number
	}

	if (!isNumber) {
		isFileOut = 1;
	}

	return isFileOut;
}

static int inspectMainInputs( int argc, const char *argv[] ) {
	/*
	 * Can the function use the value inputed into it?
	 * Is the input 0-4?
	 * Are output flags present
	 * Are the flags and year in the appropriate format
	 * return 1 if all tests passed
	 * */

	char *yearChar;

	static int isNumber, isVerbose, isFileOut, isGoodInput;

	switch (argc) {
		case 1: // no input
			isGoodInput = 1;
			break;
		case 2: // year input only or verbose only
			yearChar = (char *)argv[1];
			isNumber = is4DigitChar(yearChar);
			if (isNumber) {
				isGoodInput = 1;
			}
			break;
		case 3: // 1 flag input with value

			isVerbose = isVerboseFlag((char *)argv[1], (char *)argv[2]);
			isFileOut = isFileOutFlag((char *)argv[1], (char *)argv[2]);

			if ( isVerbose || isFileOut ) {
				isGoodInput = 1;
			}

			break;

		case 5: // 2 flag inputs with values

			isVerbose = isVerboseFlag((char *)argv[1], (char *)argv[2]);
			isFileOut = isFileOutFlag((char *)argv[1], (char *)argv[2]);

			if ( isVerbose || isFileOut ) {
				isGoodInput = 1;
			}

			isVerbose = isVerboseFlag((char *)argv[3], (char *)argv[4]);
			isFileOut = isFileOutFlag((char *)argv[3], (char *)argv[4]);

			if ( isVerbose || isFileOut ) {
				isGoodInput = 1;
			}

			break;

		default:
			isGoodInput = 0;

	}

	return isGoodInput;

}
