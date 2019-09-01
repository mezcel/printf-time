/*
 * my_calendar_tmp.h
 * */

#ifndef MY_CALENDAR_TMP
#define MY_CALENDAR_TMP

char * MONTH_NAME_ARRAY[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
char * WEEKDAY_NAME_ARRAY[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

/*
 * time.h struct
int    tm_sec   seconds [0,61]
int    tm_min   minutes [0,59]
int    tm_hour  hour [0,23]
int    tm_mday  day of month [1,31]
int    tm_mon   month of year [0,11]
int    tm_year  years since 1900
int    tm_wday  day of week [0,6] (Sunday = 0)
int    tm_yday  day of year [0,365]
int    tm_isdst daylight savings flag
*/

struct tm returnTodaysDate();
struct tm setSpecificDate(int year, int month, int day);
void addDays(struct tm *startDate, const int days);
void subtractDays(struct tm *startDate, const int days);
int isFeastDay(struct tm time1, struct tm time2);

#endif
