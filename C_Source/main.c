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

	static int isInputValid, yearInt;
	char *yearChar;

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

				simpleDisplay(yearInt);
				break;

			case 3: // verbose output 4 digit char input
				printf("------------------------\nBasic PMF Output Render:"
					"\n------------------------\n");
				nextPFM();

				printf("\n\n\nVerbose PMF and Easter Output Render:\n");
				yearChar = (char *)argv[2];
				yearInt = atoi(yearChar);

				verboseDisplay(yearInt);

				break;
		}

	} else {

		printf("\n!!! Execution interupted !!!\nProvide valid inputs and try again :)"
			"\n\nExample:\n\n  ./main\n or"
			"\n  ./main 2018\n or"
			"\n  ./main -v 2018\n or"
			"\n  ./main -v 2018 -f ~/MyDocument/myOutput.txt"
			"\n\n0000000"); // this last line is just for returing a 0 date

		exit(1);

	}
	printf("\n");

	return 0; // 8-bit return val in unix, 255 limit

}
