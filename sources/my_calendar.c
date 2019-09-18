/*
 * my_calendar.c
 * */

#include <stdio.h>
#include <time.h>	// After year 2038, only use an x64 compiler

#include "../headers/my_calendar.h"

// for use in local my_calendar.c demo
void print_date(struct tm tmDate, char *labelString) {
	int monthIndex = tmDate.tm_mon;
	int weekIndex = tmDate.tm_wday;
	char * MONTH_NAME_ARRAY[] = { "January", "February", "March", "April", "May",
				"June", "July", "August", "September", "October", "November", "December" };
	char * WEEKDAY_NAME_ARRAY[] = { "Sunday", "Monday", "Tuesday", "Wednesday",
				"Thursday", "Friday", "Saturday" };

	printf("\n%s: %s, %d, %s, %d\n",
		labelString,
		WEEKDAY_NAME_ARRAY[weekIndex],
		tmDate.tm_mday,
		MONTH_NAME_ARRAY[monthIndex],
		tmDate.tm_year + 1900
	);
}

char *retrunWeekdayName(int indexNo) {
	char * WEEKDAY_NAME_ARRAY[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
	return WEEKDAY_NAME_ARRAY[indexNo];
}

char *retrunMonthName(int indexNo) {
	char * MONTH_NAME_ARRAY[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	return MONTH_NAME_ARRAY[indexNo];
}

char *retrunFeastDayName(int indexNo) {
	char * FEAST_DAY_ARRAY[] = { "advent_start", "immaculate_conception_mary", "christmas_day", "solemnity_of_mary", "epiphany",
		"jesus_baptism", "ash_wednesday", "holy_thursday", "good_friday", "good_saturday", "easter_sunday", "pentacost", "assension_of_jesus", "all_saints_day", "ordinary_day" };
	return FEAST_DAY_ARRAY[indexNo];
}

char *retrunLiturgicalName(int indexNo) {
	char * LITURGICAL_SEASON_ARRAY[] = { "Advent Season", "Christmas Season", "Lent Season", "Easter Season", "Ordinary Time" };
	return LITURGICAL_SEASON_ARRAY[indexNo];
}

char *returnWeekdayMystery(int indexNo) {
	char * WEEKDAY_MYSTERY[] = { "Glorious", "Joyful", "Sorrowful", "Glorious", "Luminous", "Sorrowful", "Joyful" };
	return WEEKDAY_MYSTERY[indexNo];
}

struct tm returnTodaysDate(int indexNo) {
	time_t currentDate = time(NULL);
	struct tm output_tm = *localtime(&currentDate);
	return output_tm;
}

struct tm setSpecificDate(int year, int month, int day) {
	struct tm newTime = {
		.tm_year = year - 1900,
		.tm_mon = month,
		.tm_mday = day,
		.tm_hour = 0,
		.tm_min = 0,
		.tm_sec = 1
	};

	time_t t = mktime(&newTime);
	newTime.tm_wday = localtime(&t) -> tm_wday;

	return newTime;
}

struct tm setEasterDate(int year) {
	/*
	* algorithm source: https://en.wikipedia.org/wiki/Computus
	* */

	int a, b, c, d, e, f, g, h, i, k, l, m, month, day;

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

	struct tm easterDay = setSpecificDate(year, month - 1, day);

	return easterDay;
}

struct tm addDay(struct tm referenceDate) {
	referenceDate.tm_mday += 1;
	time_t t = mktime(&referenceDate);
	referenceDate.tm_wday = localtime(&t) -> tm_wday;

	return referenceDate;
}

struct tm addDays(struct tm referenceDate, int days) {
	for (int i=0; i < days; i++) {
		referenceDate = addDay(referenceDate);
	}
	return referenceDate;
}

struct tm subtractDay(struct tm referenceDate) {
	referenceDate.tm_mday -= 1;
	time_t t = mktime(&referenceDate);
	referenceDate.tm_wday = localtime(&t) -> tm_wday;

	return referenceDate;
}

struct tm subtractDays(struct tm startDate, int days) {
	for (int i=0; i < days; i++) {
		startDate = subtractDay(startDate);
	}
	return startDate;
}

void shiftTowardSunday(struct tm *tmDate) {
	int intial_wday = tmDate -> tm_wday;

	if (intial_wday != 0) {

	if (intial_wday <= 4) {
		tmDate -> tm_mday -= intial_wday;
	} else if (intial_wday == 6) {
		tmDate -> tm_mday += 1;
	} else {
		tmDate -> tm_mday += (6 - intial_wday);
	}

	time_t t = mktime(tmDate);
		tmDate -> tm_mday = localtime(&t) -> tm_mday;
	}
}

void shiftJesusBaptism(struct tm *tmDate) {
	/*
	* Aprox Jan 13
	* sunday after the Mass which celbrates the Epiphany
	* Monday if Epiphany Sunday shared the same day
	* */
	int intial_wday = tmDate -> tm_wday;

	if (intial_wday == 0) {
		tmDate -> tm_mday += 1;

		time_t t = mktime(tmDate);
		tmDate -> tm_mday = localtime(&t) -> tm_mday;
	}

}

int isFeastDay(struct tm tmNow, struct tm tmThen) {
	int intFlag;
	double returnSeconds = difftime(mktime(&tmNow), mktime(&tmThen));
	double days = returnSeconds / (24 * 3600);

	if (days != 0) {
		intFlag = 0;
	} else {
		intFlag = 1;
	}

	return intFlag;
}

int isLiturgicalSeason(struct tm tmNow, struct tm season_start, struct tm season_end) {
	/*
	* Easter season is 50 days starting at Pentacost
	* Lent season is 46 days between Ash Wed and Easter
	* Advent season lasts through Christmas Day
	* Christmas season lasts through the epiphany
	* Ordinary is the time outside of the main seasons
	* */

	int returnFlag = 0;

	double durationSeconds = difftime(mktime(&season_end), mktime(&season_start));
	double durationDays = durationSeconds / (24 * 3600);

	double countdownSeconds = difftime(mktime(&season_end), mktime(&tmNow));
	double countdownDays = countdownSeconds / (24 * 3600);

	if ((countdownDays >= 0) && (countdownDays <= durationDays)) {
	returnFlag = 1;
	}

	return returnFlag;
}

int returnLiturgicalSeason(struct tm *tmNow, struct tm *advent_start,
		struct tm *christmas_day, struct tm *epiphany, struct tm *ash_wednesday,
		struct tm *easter_sunday, struct tm *pentacost) {

	int isAdvent = isLiturgicalSeason(*tmNow, *advent_start, *christmas_day);
	int isChristmas = isLiturgicalSeason(*tmNow, *christmas_day, *epiphany);
	int isLent = isLiturgicalSeason(*tmNow, *ash_wednesday, *easter_sunday);
	int isEasterTide = isLiturgicalSeason(*tmNow, *easter_sunday, *pentacost);

	int returnFlag;

	if(isAdvent) {
		returnFlag = 0;
	} else if (isChristmas) {
		returnFlag = 1;
	} else if (isLent) {
		returnFlag = 2;
	} else if (isEasterTide) {
		returnFlag = 3;
	} else {
		returnFlag = 4;
	} // [ "Advent Season", "Christmas Season", "Lent Season", "Easter Season", "Ordinary Time"]

	return returnFlag;
}
