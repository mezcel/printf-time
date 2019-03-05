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
int daysUntillPFM(int yearInt);
void nextPFM();

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
	printf("\n------------------------\nThis next last line will ne used as a string to input into Bash for any futher POSIX date calculations.\n");
	printf("\n%s", outputString);
	
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
	
	printf("\nThe next Paschal Ful Moon:\n\tThis year\n\tIn %f days\n\tOn %s %d %s %d", days, pfmStruct.weekday, pfmStruct.day,  pfmStruct.month, pfmStruct.year);
		
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
