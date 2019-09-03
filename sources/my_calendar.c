#include <stdio.h>
#include <time.h>	// After year 2038, only use an x64 computer

#include "../headers/my_calendar.h"

int updateWeekday(int weekdayNo) {
	if (weekdayNo > 6) {
		weekdayNo = 0;
	}
	
	if (weekdayNo < 0) {
		weekdayNo = 6;
	}
	
	return weekdayNo;
}

int lastDayOfMonth(int month, int year) {
	int lastDayNo;
	
	switch (month) {
		case 4:
		case 6:
		case 9:
		case 11:
			lastDayNo = 30;
			break;
		case 2:
			if ( ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 != 0)) {
				lastDayNo = 28;
			} else {
				lastDayNo = 29;
			}
			break;
		case 0:
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
			lastDayNo = 31;
			break;
		default:
			lastDayNo = 31;
	}
	
	return lastDayNo;
}

void print_date(struct tm tmDate, char *labelString) {
	int monthIndex = tmDate.tm_mon;
	int weekIndex = tmDate.tm_wday;
	printf("\n%s: %s, %d, %s, %d\n",
		labelString,
		WEEKDAY_NAME_ARRAY[weekIndex], 
		tmDate.tm_mday, 
		MONTH_NAME_ARRAY[monthIndex], 
		tmDate.tm_year + 1900
	);
}

struct tm returnTodaysDate() {
	time_t currentDate = time(NULL);
	struct tm output_tm = *localtime(&currentDate);
	return output_tm;
}

struct tm setSpecificDate(int year, int month, int day) {
	//month = month + 1;
	struct tm newTime = { 
		.tm_year = year - 1900, 
		.tm_mon = month, 
		.tm_mday = day,
		.tm_hour = 0,
		.tm_min = 0,
		.tm_sec = 1
	};
	
	time_t t = mktime(&newTime);
	newTime.tm_wday = localtime(&t)->tm_wday;
	
	return newTime;
}

struct tm setEasterDate(int year) {
	/* 
	 * algorithm is taken from:
	 * 	https://en.wikipedia.org/wiki/Computus
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
	
	struct tm easterDay = setSpecificDate(year, month, day);
	
    return easterDay;
}

struct tm addDay(struct tm referenceDate) {
	referenceDate.tm_mday += 1;
	time_t t = mktime(&referenceDate);
	referenceDate.tm_wday = localtime(&t)->tm_wday;
	
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
	referenceDate.tm_wday = localtime(&t)->tm_wday;
	
	return referenceDate;
}

struct tm subtractDays(struct tm startDate, int days) {    
    for (int i=0; i < days; i++) {
		startDate = subtractDay(startDate);
	}
	return startDate;
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

// example usecase
int main() {
	    
    struct tm tmToday = returnTodaysDate();
    struct tm easter_sunday = setEasterDate(2019); // sun, apr 21
     
    struct tm good_saturday = subtractDays(easter_sunday,1); // sat, apr 20
    struct tm good_friday = subtractDays(easter_sunday,2); // fri, apr 19
    struct tm holy_thursday = subtractDays(easter_sunday,3); // thur, apr 18
    struct tm ash_wednesday = subtractDays(easter_sunday,46); // wed, mar 6
    struct tm assension_of_jesus = addDays(easter_sunday,40); // thurs, may 30
    struct tm immaculate_conception_mary = setSpecificDate(2019, 11, 8); // Dec 8
    
    print_date(easter_sunday, "easter_sunday");
    print_date(good_saturday, "good_saturday");
    print_date(good_friday, "good_friday");
    print_date(holy_thursday, "holy_thursday");
    print_date(ash_wednesday, "ash_wednesday");
    print_date(assension_of_jesus, "assension_of_jesus");
    print_date(immaculate_conception_mary, "immaculate_conception_mary");
    
    double returnSeconds = difftime(mktime(&easter_sunday), mktime(&good_friday));
    double days = returnSeconds / (24 * 3600);
    printf("\n | easterDate - goodFriday | = %d days\n", (int)days);
    
    int isFeast = isFeastDay(tmToday, easter_sunday);
    printf("\n is today easterDate = %d\n", isFeast);
    
    return 0;
}

