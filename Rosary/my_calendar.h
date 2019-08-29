/*
 * my_calendar.h
 * */

#ifndef MY_CALENDAR
#define MY_CALENDAR

struct EasterDay {
   char *weekday, *month;
   int day, year;
};

int returnYear();
int returnDayOfWeekFlag();
char *returnDayName(int weekdayNo);
struct EasterDay anonymous_Gregorian_algorithm(int yearInt);

#endif
