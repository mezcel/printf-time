/* Easter Day Calculations (main.c) */

#include <stdio.h>
#include <stdlib.h>
#include <math.h> // non-standard library
#include <time.h>

// my libraries
#include "general-header.h"
#include "pfm-tables.h"
#include "easter-algorithms.h"
#include "runFunctions.h"

// Run
int main(int argc, const char *argv[]) {

	static int isInputValid, yearInt, flagInt;
	char *yearChar, *flagChar, *filePathInputChar, *outputString;
	struct EasterDay outputDate, outputDate1, outputDate2, outputDate3;

	isInputValid = inspectMainInputs( argc, argv );

	if (isInputValid) {

		switch (argc) {
			case 1: // minimal output with no char input
				yearInt = returnYear();
				simpleDisplay(yearInt);
				break;

			case 2: // minimal output 4 digit char input
				yearChar = (char *)argv[1];
				yearInt = atoi(yearChar);
				int isHelp = compareStrings((char *)argv[1], "-h");
				if (!isHelp){
					simpleDisplay(yearInt);
				} else {
					helpDisplay();
				}

				break;

			case 3: // verbose output or print to file
				flagChar = (char *)argv[1];
				flagInt = inputFlagType(flagChar);

				if ( flagInt == 1 ) { // verbose year
					printf("------------------------\nBasic PMF Output Render:"
						"\n------------------------\n");
					nextPFM();

					printf("\n\n\nVerbose PMF and Easter Output Render:\n");
					yearChar = (char *)argv[2];
					yearInt = atoi(yearChar);
					verboseDisplay(yearInt);

				} else { // output to file
					filePathInputChar = (char *)argv[2];
					yearInt = returnYear();
					outputDate = pfm_algorithm(yearInt);
					outputString = outputDate2OutputString(outputDate);
					print2file(outputString, filePathInputChar);
				}
				break;

			case 5: // verbose and print to file
				printf("------------------------\nBasic PMF Output Render:"
					"\n------------------------\n");
				nextPFM();

				printf("\n\n\nVerbose PMF and Easter Output Render:\n");
				yearChar = (char *)argv[2];
				yearInt = atoi(yearChar);
				verboseDisplay(yearInt);

				filePathInputChar = (char *)argv[4];
				outputDate = pfm_algorithm(yearInt);
				outputString = outputDate2OutputString(outputDate);
				print2file(outputString, filePathInputChar);


				break;
		}

	} else {

		printf("\n!!! Execution interupted !!!\n"
			"Provide valid inputs and try again :)\n"); // this last line is just for returing a 0 date

		helpDisplay();

		exit(1);

	}
	printf("\n");

	return 0; // 8-bit return val in unix, 255 limit

}
