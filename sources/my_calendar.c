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
	default:
		lastDayNo = 31;
	}
	
	return lastDayNo;
}


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
		.tm_mday = day,
		.tm_wday = 0
	};
	
    return newTime;
}

struct tm addDay(struct tm referenceDate) {
	int lastDay = lastDayOfMonth(referenceDate.tm_mon, referenceDate.tm_year);
	
	if (referenceDate.tm_mday < lastDay) {
		referenceDate.tm_mday += 1;
	} else {
		
		if (referenceDate.tm_mon == 11) {
			referenceDate.tm_mon = 0;
			referenceDate.tm_year += 1;
		} else {
			referenceDate.tm_mon += 1;
		}
		
		referenceDate.tm_mday = lastDay;
	}
	
	referenceDate.tm_wday = updateWeekday(referenceDate.tm_wday + 1);
	
	return referenceDate;
}

struct tm addDays(struct tm referenceDate, int days) {    
    for (int i=0; i < days; i++) {
		referenceDate = addDay(referenceDate);
	}
	return referenceDate;
}

struct tm subtractDay(struct tm referenceDate) {
	if (referenceDate.tm_mday > 1) {
		referenceDate.tm_mday -= 1;
	} else {
		
		if (referenceDate.tm_mon == 0) {
			referenceDate.tm_mon = 11;
			referenceDate.tm_year -= 1;
		} else {
			referenceDate.tm_mon -= 1;
		}
		
		referenceDate.tm_mday = lastDayOfMonth(referenceDate.tm_mon, referenceDate.tm_year);;
	}
	
	referenceDate.tm_wday = updateWeekday( referenceDate.tm_wday - 1);
	
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
    struct tm easterDate = setEasterDate(tmToday.tm_year + 1900);   
     
    struct tm goodSaturday = subtractDays(easterDate,1);
    struct tm goodFriday = subtractDays(easterDate,2);
    struct tm holyThursday = subtractDays(easterDate,3);
    struct tm ashWednesday = subtractDays(easterDate,46);
    
    printf("\n easterDate Day: %s, %d, %s, %d\n", WEEKDAY_NAME_ARRAY[easterDate.tm_wday], easterDate.tm_mday, MONTH_NAME_ARRAY[easterDate.tm_mon], easterDate.tm_year);
    printf("\n goodSaturday Day: %s, %d, %s, %d\n", WEEKDAY_NAME_ARRAY[goodSaturday.tm_wday], goodSaturday.tm_mday, MONTH_NAME_ARRAY[goodSaturday.tm_mon], goodSaturday.tm_year);
    printf("\n goodFriday Day: %s, %d, %s, %d\n", WEEKDAY_NAME_ARRAY[goodFriday.tm_wday], goodFriday.tm_mday, MONTH_NAME_ARRAY[goodFriday.tm_mon], goodFriday.tm_year);
    printf("\n holyThursday Day: %s, %d, %s, %d\n", WEEKDAY_NAME_ARRAY[holyThursday.tm_wday], holyThursday.tm_mday, MONTH_NAME_ARRAY[holyThursday.tm_mon], holyThursday.tm_year);
    printf("\n ashWednesday Day: %s, %d, %s, %d\n", WEEKDAY_NAME_ARRAY[ashWednesday.tm_wday], ashWednesday.tm_mday, MONTH_NAME_ARRAY[ashWednesday.tm_mon], ashWednesday.tm_year);
    
    double returnSeconds = difftime(mktime(&easterDate), mktime(&goodFriday));
    double days = returnSeconds / (24 * 3600);
    printf("\n | easterDate - goodFriday | = %d days\n", (int)days);
    
    int isFeast = isFeastDay(tmToday, easterDate);
    printf("\n is today easterDate = %d\n", isFeast);
    
    return 0;
}

