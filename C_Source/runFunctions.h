/* Easter Day Calculations (runFunctions.h)
 *
 * functions used in main.c
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
static int inspectMainInputs( int argc, const char *argv[] );

/* Function Definition */

void verboseDisplay(int yearInt) {

	static char *outputString='\0';
	struct EasterDay outputDate;

	printf("----------------------------------------\n"
			"Easter %d Dates:\n----------------------------------------\n",
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
	printf("\n------------------------\nThis following 'last line' line will be used as a string to input into Bash for any further POSIX formatted date calculations.\n");
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

	printf("\nThe next Paschal Full Moon:\n\tThis year\n\tIn %f days\n\tOn %s %d %s %d", days, pfmStruct.weekday, pfmStruct.day,  pfmStruct.month, pfmStruct.year);

	return days;
}

void nextPFM() {
	int yearInt = 2019;
	int days = daysUntillPFM(yearInt);

	if ( days < 0 ) {
		struct EasterDay pfmStruct;
		pfmStruct = pfm_algorithm(yearInt++);

		printf("\nThe next Paschal Ful Moon:\n\t NEXT year \n\tOn %s %d %s %d", pfmStruct.weekday, pfmStruct.day,  pfmStruct.month, pfmStruct.year);
	}
}

static int inspectMainInputs( int argc, const char *argv[] ) {
	/*
	 * Can the function use the value inputed into it?
	 * Is the input 0-2?
	 * Is the input verbose, -v
	 * If the inpput is 1, is the 1 input a 4 digit char?
	 * return 1 if all tests passed
	 * */

	char *endptr;
	char *yearChar;

	static int inputLength, isNumber, isVerbose, isGoodInput;

	if ( argc == 1 ) {
		isGoodInput = 1;
	} else if ( ( argc > 1 ) && ( argc < 4 ) ) {
		// check if char is a number for 4 digit year number inputs
		yearChar = (char *)argv[1];
		inputLength = noOfChars(yearChar);
		strtol(yearChar, &endptr, 10);

		// is char a 4 digit number
		if ( (*endptr == '\0') && (inputLength == 4) ) {
			isNumber = 1;
		}

		// check if char is a verbose flag if not a year number
		if ( ( !isNumber ) && (argc > 2) ) {
			isVerbose = compareStrings(yearChar, "-v");
			// if verbose, then check if the year input is a usable input
			if ( isVerbose ) {
				// check if the next char input is a 4 digit year number input
				yearChar = (char *)argv[2];
				inputLength = noOfChars(yearChar);
				strtol(yearChar, &endptr, 10);
				// is char a 4 digit number
				if ( (*endptr == '\0') && (inputLength == 4) ) {
					isNumber = 1;
				}
			}
		}

		if (!isNumber) {
			isGoodInput = 0;
		} else {
			isGoodInput = 1;
		}

	} else {
		isGoodInput = 0;
	}

	return isGoodInput;

}
