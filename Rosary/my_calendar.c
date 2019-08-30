/*
 * my_calendar.c
 * */

#include <stdio.h>
#include <time.h> // After year 2038, only use an x64 computer

#include "my_calendar.h"

struct MyDateStruct setTodaysDateStruct() {
	struct MyDateStruct todaysDate;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	char * monthNameArray[] = { " ", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	char * weekdayNameArray[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

	todaysDate.secondsInt = tm.tm_sec;
	todaysDate.minutesInt = tm.tm_min;
	todaysDate.hourInt = tm.tm_hour;
	todaysDate.dayInt = tm.tm_mday;
	todaysDate.monthInt = tm.tm_mon;
	todaysDate.yearInt = tm.tm_year + 1900;
	todaysDate.weekdayInt = tm.tm_wday;
	todaysDate.dayYearInt = tm.tm_yday;
	todaysDate.daylightSavingsInt = tm.tm_isdst;

	todaysDate.monthName = monthNameArray[tm.tm_mon];
	todaysDate.weekdayName = weekdayNameArray[tm.tm_wday];

	return todaysDate;
}

struct MyDateStruct setEasterSundayStruct(int yearInt) {
	/*
		Anonymous Gregorian algorithm, Easter algorithms
		// https://en.wikipedia.org/wiki/Computus#Anonymous_Gregorian_algorithm

		"A New York correspondent" submitted this algorithm for determining the Gregorian Easter to the journal Nature in 1876. It has been reprinted many times, e.g., in 1877 by Samuel Butcher in The Ecclesiastical Calendar, in 1916 by Arthur Downing in The Observatory, in 1922 by H. Spencer Jones in General Astronomy, in 1977 by the Journal of the British Astronomical Association, in 1977 by The Old Farmer's Almanac, in 1988 by Peter Duffett-Smith in Practical Astronomy with your Calculator, and in 1991 by Jean Meeus in Astronomical Algorithms. Because of the Meeus’ book citation, that is also called "Meeus/Jones/Butcher" algorithm.
	*/

    struct MyDateStruct outputStruct;

	/* Define temporary variables */
	int year, a, b, c, d, e, f, g, h, i, k, l, m, month, day;
	char *monthChar;

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

    outputStruct.yearInt = yearInt;
	outputStruct.monthInt = month;
	outputStruct.dayInt = day;
	outputStruct.weekdayInt = 0;
	outputStruct.monthName = monthChar;
	outputStruct.weekdayName = "Sunday";

	return outputStruct;
}

double secondsDifference(struct MyDateStruct startDateStruct, struct MyDateStruct endDateStruct) {
	double returnSeconds;

	struct tm d = { 0 }, dd = { 0 };
	dd.tm_year = endDateStruct.yearInt - 1900; /* years since 1900 */
	dd.tm_mon = endDateStruct.monthInt;
	dd.tm_mday = endDateStruct.dayInt;
	dd.tm_hour = endDateStruct.hourInt; /* times are based on 24-hr clock */

	d.tm_year = startDateStruct.yearInt - 1900; /* years since 1900 */
	d.tm_mon = startDateStruct.monthInt;
	d.tm_mday = startDateStruct.dayInt;
	d.tm_hour = startDateStruct.hourInt; /* times are based on 24-hr clock */

	returnSeconds = difftime(mktime(&dd), mktime(&d));

	return returnSeconds;
}

int daysBetweenSeconds(double secondsInput) {
	double days = secondsInput / (24 * 3600);
	return (int) days; // absolute value
}

/*
 * // example usecase
int main() {
	struct MyDateStruct todaysDate = setTodaysDateStruct();
	struct MyDateStruct thisYearsEaster = setEasterSundayStruct(todaysDate.yearInt);

	double diffSeconds = secondsDifference(thisYearsEaster, todaysDate);
	int days = daysBetweenSeconds(diffSeconds) ;

	printf("\n yearInt: %d \n", todaysDate.yearInt);
	printf("\n monthInt: %d \n", todaysDate.monthInt);
	printf("\n dayInt: %d \n", todaysDate.dayInt);
	printf("\n weekdayInt: %d \n", todaysDate.weekdayInt);
	printf("\n monthName: %s \n", todaysDate.monthName);
	printf("\n weekdayName: %s \n", todaysDate.weekdayName);

	printf("\n --- \n yearInt: %d \n", thisYearsEaster.yearInt);
	printf("\n monthInt: %d \n", thisYearsEaster.monthInt);
	printf("\n dayInt: %d \n", thisYearsEaster.dayInt);
	printf("\n weekdayInt: %d \n", thisYearsEaster.weekdayInt);
	printf("\n monthName: %s \n", thisYearsEaster.monthName);
	printf("\n weekdayName: %s \n", thisYearsEaster.weekdayName);

	printf("\n --- \n diffSeconds: %f \n", diffSeconds);
	printf("\n days: %d \n", days);

	double diffSeconds2 = secondsDifference(todaysDate, thisYearsEaster);
	int days2 = daysBetweenSeconds(diffSeconds);

	printf("\n --- \n diffSeconds2: %f \n", diffSeconds2);
	printf("\n days2: %d \n", days2);

	return 0;
}*/


