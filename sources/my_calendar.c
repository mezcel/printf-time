#include <stdio.h>
#include <time.h>	// After year 2038, only use an x64 computer

#include "../headers/my_calendar.h"

struct tm returnTodaysDate() {
	time_t currentDate = time(NULL);
	struct tm output_tm = *localtime(&currentDate);
	return output_tm;
}

struct tm setSpecificDate(int year, int month, int day) {
    struct tm newTime = { .tm_year = year - 1900, .tm_mon = month, .tm_mday = day };
	return newTime;
}

void addDays(struct tm *startDate, const int days) {
	startDate->tm_mday += days;
}
void subtractDays(struct tm *startDate, const int days) {
	startDate->tm_mday -= days;
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
/*
 * example usecase
int main() {
	struct tm mytime1 = returnTodaysDate();
    struct tm mytime2 = setSpecificDate(mytime1.tm_year + 1900, 8, 10);
    struct tm mytime3 = returnTodaysDate();
    
    double returnSeconds = difftime(mktime(&mytime2), mktime(&mytime1));
    double days = returnSeconds / (24 * 3600);
    printf("\ndays = %d\n", (int)days);
    
    int isFeast = isFeastDay(mytime1, mytime2);
    printf("\n isFeast = %d\n", isFeast);
    
    isFeast = isFeastDay(mytime1, mytime3);
    printf("\n isFeast = %d\n", isFeast);
	
    return 0;
}
*/
