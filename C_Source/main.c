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
	/*struct EasterDay outputDate;

	static char *outputString='\0';*/

	yearInt = returnYear();
	
	verboseDisplay(yearInt);
	
	printf("\n\n------------------------\n\nBasic PMF Output Render:\n");
	
	nextPFM();
	
	
	return 0; // 8-bit return val in unix, 255 limit

}
