/*
 * my_calendar.c
 * */

#include <stdio.h>
#include <stdlib.h>
#include <math.h> // non-standard library
#include <time.h>

#include "my_calendar.h"

int returnYear() {
	int yearInt;
	char yearChar[5];

	time_t now;
	if ( time(&now) != (time_t)(-1) ) {
		struct tm *mytime = localtime(&now);
		if ( mytime ) {
			if ( strftime(yearChar, sizeof yearChar, "%Y", mytime) ) {
				yearInt = atoi(yearChar);
			}
		}
	}

	return yearInt;
}

int returnDayOfWeekFlag() {
	time_t rawtime;
	struct tm *timeinfo;

	// int year = 2019;
	int year = returnYear();
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	timeinfo->tm_year = year - 1900;

	/* call mktime: timeinfo->tm_wday will be set */
	mktime ( timeinfo );

	return timeinfo->tm_wday;
}

char *returnDayName(int weekdayNo) {
	if ( (weekdayNo > 6) || (weekdayNo < 0) ) {
		weekdayNo = 0;
	}

	char * weekday[] = { "Sunday", "Monday", "Tuesday", "Wednesday",
							"Thursday", "Friday", "Saturday" };

	return weekday[weekdayNo];
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

/*
// usecase example
int main() {
    struct EasterDay outputDate;

    int yearInt = returnYear();

	outputDate = anonymous_Gregorian_algorithm(yearInt);
	printf("Anonymous Output:\n\t%s %d, %s %d -- Gregorian Calendar,"
			" mixed var array\n", outputDate.weekday, outputDate.day,
			outputDate.month, outputDate.year);

    return 0;
}
*/
