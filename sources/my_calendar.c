#include <stdio.h>
#include <time.h>	// After year 2038, only use an x64 compiler

#include "../headers/my_calendar.h"

// for use in local my_calendar.c demo
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

void shiftTowardSunday(struct tm *tmDate) {
	int intial_wday = tmDate->tm_wday;
	
	if (intial_wday != 0) {
		
		if (intial_wday <= 4) {
			tmDate->tm_mday -= intial_wday;
		} else if (intial_wday == 6) {
			tmDate->tm_mday += 1;
			
		} else {
			tmDate->tm_mday += (6 - intial_wday);
		}
		
		time_t t = mktime(tmDate);
		tmDate->tm_mday = localtime(&t)->tm_mday;
	}
	
}

void shiftJesusBaptism(struct tm *tmDate) {
	/* 
	 * Aprox Jan 13 
	 * sunday after the Mass which celbrates the Epiphany 
	 * Monday if Epiphany Sunday shared the same day
	 * */
	int intial_wday = tmDate->tm_wday;
	
	if (intial_wday == 0) {
		tmDate->tm_mday += 1;
		
		time_t t = mktime(tmDate);
		tmDate->tm_mday = localtime(&t)->tm_mday;
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

int isLiturgicalSeason(struct tm tmNow, struct tm season_start, 
	struct tm season_end) {
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
	}
	
	// { "Advent Season", "Christmas Season", "Lent Season", "Easter Season", "Ordinary Time"}
	
	return returnFlag;
}

/*
// example usecase demo
int main() {
	    
    struct tm tmToday = returnTodaysDate();
    
	struct tm advent_start = setSpecificDate(tmToday.tm_year + 1900, 11, 1); // Dec 1
		shiftTowardSunday(&advent_start); // first sun of advent
    struct tm immaculate_conception_mary = setSpecificDate(tmToday.tm_year + 1900, 11, 8); // Dec 8
    struct tm christmas_day = setSpecificDate(tmToday.tm_year + 1900, 11, 25); // wed dec 25
    struct tm solemnity_of_mary = setSpecificDate(tmToday.tm_year + 1900, 0, 1); // Jan 1
	struct tm epiphany = addDays(christmas_day,12); // 12 days after christmas
		shiftTowardSunday(&epiphany); // epiphany sunday
	struct tm jesus_baptism = addDays(christmas_day,12);
		shiftJesusBaptism(&jesus_baptism); // avoid epiphany overlap
		
	struct tm easter_sunday = setEasterDate(tmToday.tm_year + 1900); // pfm
    struct tm good_saturday = subtractDays(easter_sunday,1);
    struct tm good_friday = subtractDays(easter_sunday,2);
    struct tm holy_thursday = subtractDays(easter_sunday,3);
    struct tm ash_wednesday = subtractDays(easter_sunday,46);
    struct tm pentacost = addDays(easter_sunday,21);
		shiftTowardSunday(&pentacost);  // sun june 9, 7 sundays after easter
    struct tm assension_of_jesus = addDays(easter_sunday,40);
		
    struct tm all_saints_day = setSpecificDate(tmToday.tm_year + 1900, 10, 1); // Nov 1
		    
    print_date(advent_start, "advent_start");
    print_date(immaculate_conception_mary, "immaculate_conception_mary");
    print_date(christmas_day, "christmas_day");
    print_date(solemnity_of_mary, "solemnity_of_mary");
    print_date(epiphany, "epiphany");
    print_date(jesus_baptism, "jesus_baptism");
    print_date(ash_wednesday, "ash_wednesday");
    print_date(holy_thursday, "holy_thursday");
    print_date(good_friday, "good_friday");
    print_date(good_saturday, "good_saturday");
    print_date(easter_sunday, "easter_sunday");
    print_date(pentacost, "pentacost");
    print_date(assension_of_jesus, "assension_of_jesus");
    print_date(all_saints_day, "all_saints_day");
    
    printf("\n ---------- \n");
    
    int seasonFlag = returnLiturgicalSeason(&tmToday, &advent_start, 
		&christmas_day, &epiphany, &ash_wednesday, &easter_sunday, &pentacost);
    
    printf("\n %s \n", LITURGICAL_SEASON_ARRAY[seasonFlag]);
		
	int isFeast;
    switch (seasonFlag) {
		case 0:
			isFeast = isFeastDay(tmToday, advent_start);
			if(isFeast) { printf("\n %s \n", FEAST_DAY_ARRAY[0]); }
			
			isFeast = isFeastDay(tmToday, immaculate_conception_mary);
			if(isFeast) { printf("\n %s \n", FEAST_DAY_ARRAY[1]); }
			break;
		case 1:
			isFeast = isFeastDay(tmToday, christmas_day);
			if(isFeast) { printf("\n %s \n", FEAST_DAY_ARRAY[2]); }
			
			isFeast = isFeastDay(tmToday, solemnity_of_mary);
			if(isFeast) { printf("\n %s \n", FEAST_DAY_ARRAY[3]); }
			
			isFeast = isFeastDay(tmToday, epiphany);
			if(isFeast) { printf("\n %s \n", FEAST_DAY_ARRAY[4]); }
			
			isFeast = isFeastDay(tmToday, jesus_baptism);
			if(isFeast) { printf("\n %s \n", FEAST_DAY_ARRAY[5]); }
			break;
		case 2:
			isFeast = isFeastDay(tmToday, ash_wednesday);
			if(isFeast) { printf("\n %s \n", FEAST_DAY_ARRAY[6]); }
			
			isFeast = isFeastDay(tmToday, holy_thursday);
			if(isFeast) { printf("\n %s \n", FEAST_DAY_ARRAY[7]); }
			
			isFeast = isFeastDay(tmToday, good_friday);
			if(isFeast) { printf("\n %s \n", FEAST_DAY_ARRAY[8]); }
			
			isFeast = isFeastDay(tmToday, good_saturday);
			if(isFeast) { printf("\n %s \n", FEAST_DAY_ARRAY[9]); }
			
			isFeast = isFeastDay(tmToday, easter_sunday);
			if(isFeast) { printf("\n %s \n", FEAST_DAY_ARRAY[10]); }
			break;
		case 3:
			isFeast = isFeastDay(tmToday, pentacost);
			if(isFeast) { printf("\n %s \n", FEAST_DAY_ARRAY[11]); }
			
			isFeast = isFeastDay(tmToday, assension_of_jesus);
			if(isFeast) { printf("\n %s \n", FEAST_DAY_ARRAY[12]); }
			break;
		default:
			isFeast = isFeastDay(tmToday, all_saints_day);
			if(isFeast) { printf("\n %s \n", FEAST_DAY_ARRAY[12]); }
			break;
	} 
    
    return 0;
}
*/
