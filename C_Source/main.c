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
int main(int argc, const char * argv[]) {

	static int yearInt;
	
	printf("------------------------\nBasic PMF Output Render:\n------------------------\n"); 
	nextPFM();
	
	printf("\n\n\nVerbose PMF and Easter Output Render:\n");
	yearInt = returnYear();
	verboseDisplay(yearInt);
	
	return 0; // 8-bit return val in unix, 255 limit

}
