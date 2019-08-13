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

/* Vars */

struct TableA {
   char *monthLetter, *code;
   int day;
};

struct TableE {
   char *dayOfWeek;
   int daysTillSunay;
};

/* Function Prototypes */

int returnYearDiv19 (int yearInt);
int findArrIndex(int myArray[], int num_elements, int value);
struct TableA returnTableA(int yearInt);
int returnTableB(char *charTableA);
int returnTableC(int yearInt);
int returnTableD(int yearInt);
struct TableE returnTableE(int sumTables);
struct EasterDay pfm_algorithm(int yearInt);

/* Function Definition */

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

int findArrIndex(int myArray[], int num_elements, int value) {
	int i;

	for (i=0; i<num_elements; i++) {
		if (myArray[i] == value) {
			return(i);  /* it was found */
		}
	}
	return(-1);  /* if it was not found */
}

struct TableA returnTableA(int yearInt) {
	struct TableA tableA;

	int tableARecord[19] = {
			0, 52, 105, 157, 210, 263, 315, 368, 421, 473, 562, 578, 631,
			684, 736, 789, 842, 894, 947
		}; /* https://www.assa.org.au/edm */

	int tableAField[6][2] = {
			{326, 1582},
			{1583, 1699},
			{1700, 1899},
			{1900, 2199},
			{2200, 2299},
			{2300, 2399}
		}; /* https://www.assa.org.au/edm */

	char *tableAAttrChar[19][6] = {
			{"A5", "A12", "A13", "A14", "A15", "A16"},
			{"M25", "A1", "A2", "A3", "A4", "A5"},
			{"A13", "M21", "M22", "M23", "M24", "M25"},
			{"A2", "A9", "A10", "A11", "A12", "A13"},
			{"M22", "M29", "M30", "M31", "A1", "A2"},
			{"A10", "A17", "A18", "A18", "M21", "M22"},
			{"M30", "A6", "A7", "A8", "A9", "A10"},
			{"A18", "M26", "M27", "M28", "M29", "M30"},
			{"A7", "A14", "A15", "A16", "A17", "A18"},
			{"M27", "A3", "A4", "A5", "A6", "A7"},
			{"A15", "M23", "M24", "M25", "M26", "M27"},
			{"A4", "A11", "A12", "A13", "A14", "A15"},
			{"M24", "M31", "A1", "A2", "A3", "A4"},
			{"A12", "A18", "M21", "M22", "M23", "M24"},
			{"A1", "A8", "A9", "A10", "A11", "A12"},
			{"M21", "M28", "M29", "M30", "M31", "A1"},
			{"A9", "A16", "A17", "A17", "A18", "M21"},
			{"M29", "A5", "A6", "A7", "A8", "A9"},
			{"A17", "M25", "M26", "M27", "M28", "M29"}
		}; /* https://www.assa.org.au/edm */

	int div19dec, index, fieldIndex, col;

	for( fieldIndex = 0; fieldIndex < 6; fieldIndex++ ) {
		if (( yearInt >= tableAField[fieldIndex][0] ) && ( yearInt <= tableAField[fieldIndex][1] )) {
			// fieldIndex = 3; // reasonable default
			break;
		}
	}

	div19dec = returnYearDiv19(yearInt);
	index = findArrIndex(tableARecord, 19, div19dec);

	tableA.code = tableAAttrChar[index][fieldIndex];

    char monthLetter = tableA.code[0];
    tableA.monthLetter = &monthLetter;

    tableA.day = atoi(&tableA.code[1]);

	return tableA;
}

int returnTableB(char *charTableA) {

	char *tableB[5][7] = {
		{ "  ", "  ", "M21", "M22", "M23", "M24", "M25" },
		{ "M26", "M27", "M28", "M29", "M30", "M31", "A1"},
		{ "A2", "A3", "A4", "A5", "A6", "A7", "A8"},
		{ "A9", "A10", "A11", "A12", "A13", "A14", "A15"},
		{ "A16", "A17", "A18", "  ", "  ", "  ", "  "}
	};  /* https://www.assa.org.au/edm */

    static int row, col, isMatch;

    for (row = 0; row < 5; row++) {
        for (col = 0; col < 7; col++) {
            isMatch = compareStrings(tableB[row][col], charTableA);
            if ( isMatch ) { break; }
        }
    }

    return col;
}

int returnTableC(int yearInt) {
    int first2Digits, isMatch;

    first2Digits = yearInt / 100;

    int tableC[7][9] = {
        {5,12,16,20, 24,28,32,36,40},
        {4,11,15,19,23,27,31,35,39},
        {3,10,10,10,10,10,10,10,10},
        {9,9,9,18,22,26,30,34,38},
        {8,8,15,15,15,15,15,15,15},
        {7, 7,14,17,21,25,29,33,37},
        {6,6,13,13,13,13,13,13,13}
	};  /* https://www.assa.org.au/edm */

    static int result, attr;

	if ((yearInt >= 1500) && (yearInt <= 1582)) {
		result = 4;
	} else if ((yearInt >= 1583) && (yearInt <= 1599)) {
		result = 1;
	} else {
		for (result = 0; result < 6; result++) {
	        for (attr = 0; attr < 7; attr++) {
	            if ( tableC[result][attr] == first2Digits ) {
	                isMatch = 1;
	                break;
	            }
	        }
	        if ( isMatch ) { break; }
	    }
	}

    return result;
}

int returnTableD(int yearInt) {
	int first2Digits, last2Digits;
	static int isMatch, result, attr;

	int tableD[7][18] = {
		{0,6,6,17,23,28,34,34,45,52,56,62,62,73,79,84,90,90},
		{1,7,12,18,18,29,35,40,46,46,57,63,68,74,74,85,91,96},
		{2,2,13,19,24,30,30,41,47,52,58,58,69,75,80,86,86,97},
		{3,8,14,14,25,31,36,42,42,53,59,64,70,70,81,87,92,98},
		{9,9,15,20,26,26,37,43,48,54,54,65,71,76,82,82,93,99},
		{4,10,10,21,27,32,38,38,49,55,60,66,66,77,83,88,94,94},
		{5,11,16,22,22,33,39,44,50,50,61,67,72,78,78,89,95,95}
	}; /* https://www.assa.org.au/edm */

    first2Digits = yearInt / 100;
	last2Digits = (yearInt - (first2Digits * 100));

	for (result = 0; result < 6; result++) {
		for (attr = 0; attr < 18; attr++) {
			if ( tableD[result][attr] == last2Digits ) {
				isMatch = 1;
				break;
			}
		}
		if ( isMatch ) { break; }
	}

	return result;

}

struct TableE returnTableE(int sumTables) {

	struct TableE tableE;
	static int result, attr, isMatch;
	char *charTableA;

	int tableESum[7][3] = {
		{0,7,14},
		{1,8,15},
		{2,9,16},
		{3,10,17},
		{4,11,18},
		{5,12,12},
		{6,13,13}
	};

	char *tableEChar[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	int day2add[7] = {7,5,4,3,2,1};

	for (result = 0; result < 7; result++) {
		for (attr = 0; attr < 3; attr++) {
			if ( tableESum[result][attr] == sumTables ) {
				isMatch = 1;
				break;
			}
		}
		if ( isMatch ) { break; }
	}

	tableE.dayOfWeek = tableEChar[result];
	tableE.daysTillSunay = day2add[result] + 1;

	return tableE;
}

struct EasterDay pfm_algorithm(int yearInt) {
    struct EasterDay pfm;
    struct TableA tableA;
    struct TableE tableE;
    char *charTableA;

    tableA = returnTableA(yearInt);
    int intTableB = returnTableB(tableA.code);

    int intTableC = returnTableC(yearInt);
    int intTableD = returnTableD(yearInt);

    int sumTables = intTableB + intTableC + intTableD;

    tableE = returnTableE(sumTables);

    pfm.weekday = tableE.dayOfWeek;
    pfm.day = tableA.day ; // Sunday = tableA.day + tableE.daysTillSunay
    pfm.month = tableA.monthLetter;
    pfm.year = yearInt;

    return pfm;
}
