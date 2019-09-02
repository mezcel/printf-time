#include <stdio.h>
#include <time.h>	// After year 2038, only use an x64 computer

#include "../headers/my_calendar.h"

struct tm returnTodaysDate() {
	time_t currentDate = time(NULL);
	struct tm output_tm = *localtime(&currentDate);
	return output_tm;
}

struct tm setSpecificDate(int year, int month, int day) {
    struct tm newTime = { 
		.tm_year = year - 1900, 
		.tm_mon = month, 
		.tm_mday = day 
	};
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
	
	struct tm newTime = { 
		.tm_year = year,
		.tm_mon = month, 
		.tm_mday = day
	};
	
    return newTime;
}

struct tm addDays(struct tm startDate, int days) {
	startDate.tm_mday += days;
	return startDate;
}

int updateWeekday(int weekdayNo) {
	if (weekdayNo > 6) {
		weekdayNo = 0;
	}
	
	if (weekdayNo < 0) {
		weekdayNo = 6;
	}
	
	return weekdayNo;
}

struct tm subtractDays(struct tm startDate, int days) {
	
	if (startDate.tm_mday > 1) {
		startDate.tm_mday -= days;
	} else {
		int previousMonth = startDate.tm_mon - 1;
		int lastDay = lastDayOfMonth(previousMonth, startDate.tm_year);
		
		startDate.tm_mon = previousMonth;
		startDate.tm_mday = lastDay;
	}
	startDate.tm_wday = updateWeekday( startDate.tm_wday - 1);
	return startDate;
}

int isFeastDay(struct tm time1, struct tm time2) {
	int intFlag;
    double returnSeconds = difftime(mktime(&time1), mktime(&time2));
    double days = returnSeconds / (24 * 3600);
    
    if (days != 0) {
		intFlag = 0;
	} else {	
		intFlag = 1;
	}
	
	return intFlag;
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
	default:
		lastDayNo = 31;
	}
	
	return lastDayNo;
}
// example usecase
int main() {
	/*struct tm mytime1 = returnTodaysDate();
    struct tm mytime2 = setSpecificDate(mytime1.tm_year + 1900, 8, 10);
    struct tm mytime3 = returnTodaysDate();
    
    double returnSeconds = difftime(mktime(&mytime2), mktime(&mytime1));
    double days = returnSeconds / (24 * 3600);
    printf("\ndays = %d\n", (int)days);
    
    int isFeast = isFeastDay(mytime1, mytime2);
    printf("\n isFeast = %d\n", isFeast);
    
    isFeast = isFeastDay(mytime1, mytime3);
    printf("\n isFeast = %d\n", isFeast);*/
    
    struct tm easterDate = setEasterDate(2019);
    printf("\nEaster Day: %d %d, %d, %d\n", easterDate.tm_wday, easterDate.tm_mday, easterDate.tm_mon, easterDate.tm_year);
    
    struct tm goodSaturday = subtractDays(easterDate,1);
    struct tm goodFriday = subtractDays(easterDate,2);
    struct tm holyThursday = subtractDays(easterDate,3);
    
    printf("\n goodSaturday Day: %d, %d, %d\n", goodSaturday.tm_mday, goodSaturday.tm_mon, goodSaturday.tm_year);
    printf("\n goodFriday Day: %d, %d, %d\n", goodFriday.tm_mday, goodFriday.tm_mon, goodFriday.tm_year);
    printf("\n holyThursday Day: %d, %d, %d\n", holyThursday.tm_mday, holyThursday.tm_mon, holyThursday.tm_year);
    
    
    struct tm loopDate = setEasterDate(2019);
		printf("\n -- \n loopDate Day: %s %d, %s, %d \n --- \n", WEEKDAY_NAME_ARRAY[loopDate.tm_wday], loopDate.tm_mday, MONTH_NAME_ARRAY[loopDate.tm_mon], loopDate.tm_year);
    for (int i=0; i < 46; i++) {
		loopDate = subtractDays(loopDate,1);
		printf("\n loopDate Day: %s %d, %s, %d\n", WEEKDAY_NAME_ARRAY[loopDate.tm_wday], loopDate.tm_mday, MONTH_NAME_ARRAY[loopDate.tm_mon], loopDate.tm_year);
	}
	
    return 0;
}

