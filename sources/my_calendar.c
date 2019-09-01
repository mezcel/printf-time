/*
 * my_calendar.c
 * */

#include <stdio.h>
#include <time.h> // After year 2038, only use an x64 computer

#include "../headers/my_calendar.h"

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


struct MyDateStruct returnTodaysDateStruct() {
	struct MyDateStruct todaysDate;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	/*char * monthNameArray[] = { " ", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	char * weekdayNameArray[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };*/

	todaysDate.secondsInt = tm.tm_sec;
	todaysDate.minutesInt = tm.tm_min;
	todaysDate.hourInt = tm.tm_hour;
	todaysDate.dayInt = tm.tm_mday;
	todaysDate.monthInt = tm.tm_mon;
	todaysDate.yearInt = tm.tm_year + 1900;
	todaysDate.weekdayInt = tm.tm_wday;
	todaysDate.dayYearInt = tm.tm_yday;
	todaysDate.daylightSavingsInt = tm.tm_isdst;

	todaysDate.monthName = MONTH_NAME_ARRAY[tm.tm_mon];
	todaysDate.weekdayName = WEEKDAY_NAME_ARRAY[tm.tm_wday];

	return todaysDate;
}

struct MyDateStruct returnEasterSundayStruct(int yearInt) {
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

struct MyDateStruct returnFixedFeastDay(int monthInt, int dayInt, struct MyDateStruct todaysDate) {

	struct MyDateStruct outputStruct;

	outputStruct.dayInt = dayInt;
	outputStruct.monthInt = monthInt;
	outputStruct.yearInt = todaysDate.yearInt;
	outputStruct.monthName = MONTH_NAME_ARRAY[monthInt];

	double diffSeconds = secondsDifference(todaysDate, outputStruct);
	if(diffSeconds < 0){
		outputStruct.yearInt = todaysDate.yearInt + 1;
	}

	return outputStruct;
}

struct MyDateStruct returnEasterBasedFeastDay(struct MyDateStruct easterDate, struct MyDateStruct todaysDate, int timeShift) {

	// under construction

	/*struct MyDateStruct outputStruct;

	double diffSeconds = secondsDifference(todaysDate, easterDate);
	int days = daysBetweenSeconds(diffSeconds) ;

	if (diffSeconds < 0) {
		days = days + timeShift;
	} else {

		days = days - timeShift;
	}

	return outputStruct;*/
	return todaysDate;
}

/*
// example usecase
int main() {
	struct MyDateStruct todaysDate = returnTodaysDateStruct();
	//struct MyDateStruct thisYearsEaster = returnEasterSundayStruct(todaysDate.yearInt);
	//struct MyDateStruct All_Saints = returnFixedFeastDay(10, 1, todaysDate); // Nov 1
	//struct MyDateStruct Christmas = returnFixedFeastDay(11, 25, todaysDate); // Dec 25
	struct MyDateStruct Solemnity_of_Mary = returnFixedFeastDay(1, 1, todaysDate); // Jan 1
	struct MyDateStruct Solemnity_of_Mary = returnFixedFeastDay(1, 1, todaysDate); // Jan 1


	printf("\n dayInt: %d \n", Solemnity_of_Mary.dayInt);
	printf("\n monthInt: %d \n", Solemnity_of_Mary.monthInt);
	printf("\n yearInt: %d \n", Solemnity_of_Mary.yearInt);
	printf("\n monthName: %s \n", Solemnity_of_Mary.monthName);

	double diffSeconds = secondsDifference(todaysDate, Solemnity_of_Mary);
	int days = daysBetweenSeconds(diffSeconds) ;

	printf("\n days: %d \n", days);

	printf("\n monthName: %s \n", todaysDate.monthName);

	return 0;
}
*/
