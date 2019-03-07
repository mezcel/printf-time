/* Easter Day Calculations (pmf-tables.h)
 *
 * Algorithms and Tables taken from:
 * 	https://www.assa.org.au/edm
 * */

/*
 * #include <stdlib.h>
 * #include <stdio.h>
 * #include <math.h>
 * #include "general-header.h"
 * */

 /* Function Prototypes */

char *returnTableA(int yearInt);
int returnTableAB(int yearInt);
int returnYearDiv19 (int yearInt);
int returnTableD(int last2NoYear);
int *returnTableE(int tableSum);
int findIndex(int a[], int num_elements, int value);
struct EasterDay pfm_algorithm(int yearInt);

/* Function Definition */

char *returnTableA(int yearInt) {

	int tableAArray[19] = {
			0, 52, 105, 157, 210, 263, 315, 368, 421, 473, 562, 578, 631,
			684, 736, 789, 842, 894, 947
		}; /* https://www.assa.org.au/edm */

	char *tableAArrayChar[19] = {
			"A14", "A3", "M23", "A11", "M31", "A18", "A8", "M28", "A16", "A5", "M25", "A13",
			"A2", "M22", "A10", "M30", "A17", "A7", "M27"
		}; /* https://www.assa.org.au/edm */

	int div19dec;
	int index, value;


	div19dec = returnYearDiv19(yearInt);

	value = div19dec;
	index = findIndex(tableAArray, 19, value);

	return tableAArrayChar[index];
}

int returnTableAB(int yearInt) {

	int A2 = 0, A9 = 0, A16 = 0, M26 = 0,
		A3 = 1, A10 = 1, A17 = 1, M27 = 1,
		A4 = 2, A11 = 2, A18 = 2, M21 = 2, M28 = 2,
		A5 = 3, A12 = 3, M29 = 3, M22 = 3,
		A6 = 4, A13 = 4, M23 = 4, M30 = 4,
		A7 = 5, A14 = 5, M24 = 5, M31 = 5,
		A1 = 6, A8 = 6, A15 = 6, M25 = 6; /* https://www.assa.org.au/edm */

	int tableAArray[19] = {
			0, 52, 105, 157, 210, 263, 315, 368, 421, 473, 562, 578, 631,
			684, 736, 789, 842, 894, 947
		}; /* https://www.assa.org.au/edm */

	int tableABArray[19] = {
			A14, A3, M23, A11, M31, A18, A8, M28, A16, A5, M25, A13,
			A2,	M22, A10, M30, A17, A7, M27
		}; /* https://www.assa.org.au/edm */

	int div19dec, tableAB;
	int index, value;


	div19dec = returnYearDiv19 (yearInt);

	value = div19dec;
	index = findIndex(tableAArray, 19, value);
	tableAB = tableABArray[index];

	return tableAB;
}

int returnYearDiv19 (int yearInt) {
	int integerPart, wholeNumber;
	double yearDiv9, decimalPart;

	yearDiv9 = (double)yearInt / 19;
	integerPart = (int)yearDiv9;
	decimalPart = yearDiv9 - integerPart;
	decimalPart = decimalPart * 1000.00;
	wholeNumber = (int)decimalPart;

	return wholeNumber;
}

int returnTableD(int last2NoYear){

	int decadeNo;

	switch (last2NoYear) {
		case 23:
		case 28:
			decadeNo = 0;
			break;
		case 18:
		case 29:
			decadeNo = 1;
			break;
		case 19:
		case 24:
			decadeNo = 2;
			break;
		case 25:
		case 31:
			decadeNo = 3;
			break;
		case 20:
		case 26:
			decadeNo = 4;
			break;
		case 21:
		case 27:
			decadeNo = 5;
			break;
		case 22:
		case 33:
			decadeNo = 6;
			break;
	}

	return decadeNo;

}

int *returnTableE(int tableSum) {

	int days2add, pfmDayOfWeek;
	static int returnArray[2];

	switch (tableSum) {
		case 0:
		case 7:
		case 14:
			days2add = 7;
			pfmDayOfWeek = 0; // sun
			break;

		case 1:
		case 8:
		case 15:
			days2add = 6;
			pfmDayOfWeek = 1; // mon
			break;

		case 2:
		case 9:
		case 16:
			days2add = 5;
			pfmDayOfWeek = 2;
			break;

		case 3:
		case 10:
		case 17:
			days2add = 4;
			pfmDayOfWeek = 3;
			break;

		case 4:
		case 11:
		case 18:
			days2add = 3;
			pfmDayOfWeek = 4;
			break;

		case 5:
		case 12:
			days2add = 2;
			pfmDayOfWeek = 5;
			break;

		case 6:
		case 13:
			days2add = 1;
			pfmDayOfWeek = 6; // sat
			break;
	}

	returnArray[0] = days2add;
	returnArray[1] = pfmDayOfWeek;

	return returnArray;

}

int findIndex(int myArray[], int num_elements, int value) {
	int i;

	for (i=0; i<num_elements; i++) {
		if (myArray[i] == value) {
			return(i);  /* it was found */
		}
	}

	return(-1);  /* if it was not found */
}

struct EasterDay pfm_algorithm(int yearInt) {

	struct EasterDay pfmOutputDate;

	int tableAB, tableC, tableD, tableSum, first2NoYear, last2NoYear, *tableE, dayOfWeekNo,
		i, dayNo;

	char *dayOfWeekChar[]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"},
			*tableAChar, *monthChar, *charDayNo;

	// yearInt = returnYear();

	tableAB = returnTableAB(yearInt);

	first2NoYear = yearInt / 100;
	last2NoYear = (yearInt - (first2NoYear * 100));

	tableC = 0;
	tableD = returnTableD(last2NoYear);

	tableSum = tableAB + tableC + tableD;

	tableE = returnTableE(tableSum);

	/*
	 * i=0;
	 * int days2add = days2add = *(tableE + i); // days to add untill Sunday, not used in this usecase
	 * */

	i=1;
	dayOfWeekNo = *(tableE + i); // 0 = sun, 6 = Sat

	tableAChar = returnTableA(yearInt);
    char monthLetter = tableAChar[0];

    if (monthLetter == 'M') {
		monthChar = "March";
	} else {
		monthChar = "April";
	}

    charDayNo = tableAChar+1;
    dayNo = atoi(charDayNo);
	

	pfmOutputDate.weekday = dayOfWeekChar[dayOfWeekNo];
    pfmOutputDate.day = dayNo ;
    pfmOutputDate.month = monthChar;
    pfmOutputDate.year = yearInt;

	return pfmOutputDate;
}
