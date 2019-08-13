/* Easter Day Calculations (easter-algorithms.h)
 *
 * Algorithms taken from:
 * 	https://en.wikipedia.org/wiki/Computus
 * */

/*
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <math.h>
 * #include "general-header.h"
*/

/* Function Prototypes */

struct EasterDay gauss_Easter_algorithm(int yearInt);
struct EasterDay anonymous_Gregorian_algorithm(int yearInt);
struct EasterDay meeus_Julian_algorithm(int yearInt);

/* Function Definition */

struct EasterDay gauss_Easter_algorithm(int yearInt) { /* Gauss's Easter Algorithm */
    /* Gregorian Calendar */

    struct EasterDay gaussOutputDate;

    int year, a, b, c, k, p, q, M, N, d, e, day;
	double pDouble, qDouble;
	char *monthChar;

	// char title = "Gauss's Easter Algorithm";

	/*year = 1777;*/
	year = yearInt;
	a = year % 19;
	b = year % 4;
	c = year % 7;
	k = year / 100;
	pDouble = (13 + (8 * k) ) / 25;
	p = floor(pDouble);
	qDouble = k / 4;
	q = floor(qDouble);
	M = (15 - p + k - q) % 30;
	N = (4 + k - q) % 7;
	d = ( (19 * a) + M ) % 30;
	e = ( (2*b) + (4*c) + (6*d) + N ) % 7;

	if (e == 6) {
		if (d == 29) {
			day = 19;
		} else if( (( (11*M) + 11 ) % 30) < 9 ) {
			day = 18;
		}
	}

	day = 22 + d + e;

	if (day > 31) {
		monthChar = "April";
		day = day - 31;
	} else {
		monthChar = "March";

	}

    gaussOutputDate.weekday = "Sunday";
    gaussOutputDate.day = day;
    gaussOutputDate.month = monthChar;
    gaussOutputDate.year = yearInt;

	return gaussOutputDate;
}

struct EasterDay anonymous_Gregorian_algorithm(int yearInt) { /* Anonymous Gregorian Algorithm */
    /* Gregorian Calendar */

    struct EasterDay gregorianOutputDate;

	/* Define temporary variables */
	int year, a, b, c, d, e, f, g, h, i, k, l, m, month, day;
	char *monthChar;

	// char title = "Anonymous Gregorian Algorithm";

	/*year = 1961;*/
	year = yearInt;
	a = year % 19;
	b = year / 100;
	c = year % 100;
	d = b / 4;
	e = b % 4;
	f = (b + 8) / 25;
	g = (b - f + 1) / 3;
	h = ((19 * a) + b - d - g + 15) % 30;
	i = c / 4;
	k = c % 4;
	l = ( 32 + (2 * e) + (2 * i) - h - k) % 7;
	m = ( a + (11 * h) + (22 * l) ) / 451;
	month = ( h + l - (7 * m) + 114 ) / 31;
	day = ( (h + l - (7 * m) + 114) % 31 ) + 1;

	if (month == 3) {
		monthChar = "March";
	} else {
		monthChar = "April";

	};

    gregorianOutputDate.weekday = "Sunday";
    gregorianOutputDate.day = day;
    gregorianOutputDate.month = monthChar;
    gregorianOutputDate.year = yearInt;

	return gregorianOutputDate;
}

struct EasterDay meeus_Julian_algorithm(int yearInt) { /* Meeus's Julian Algorithm */
    /* Julian Calendar */

    struct EasterDay julianOutputDate;

	/* Define temporary variables */
	int year, a, b, c, d, e, month, day;
	char *monthChar;

	// char title = "Meeus's Julian Algorithm";

	/*year = 2008;*/
	year = yearInt;
	a = year % 4;
	b = year % 7;
	c = year % 19;
	d = ( (19 * c) + 15 ) % 30;
	e = ( (2 * a) + (4 * b) - d + 34 ) % 7;
	month = ( d + e + 114 ) / 31;
	day = ( (d + e + 114) % 31 ) + 1;

	if (month == 3) {
		monthChar = "March";
	} else {
		monthChar = "April";
	}

    julianOutputDate.weekday = "";
    julianOutputDate.day = day;
    julianOutputDate.month = monthChar;
    julianOutputDate.year = yearInt;

	return julianOutputDate;
}
