/* Easter Day Calculations (main.c) */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "general-header.h"
#include "pfm-tables.h"
#include "easter-algorithms.h"

#include "runFunctions.h"

// Run
int main(int argc, const char *argv[]) {
	
	static int isInputValid;
	isInputValid = inspectMainInputs( argc, argv );
	
	printf("\n isInputValid = %d\n", isInputValid);
	
	if (isInputValid) {
		static int yearInt;
	
		printf("------------------------\nBasic PMF Output Render:\n------------------------\n"); 
		nextPFM();
		
		printf("\n\n\nVerbose PMF and Easter Output Render:\n");
		yearInt = returnYear();
		verboseDisplay(yearInt);
		
	} else {
		printf("\n\n!!! Execution interupted !!!\nProvide valid inputs and try again :)\n\nExample:\n\n  ./main\n or\n  ./main 1985\n\n0000000");
		exit(1);
	}
	
	return 0; // 8-bit return val in unix, 255 limit

}
