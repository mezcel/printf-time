/*
 * my_calendar.h
 * */

#ifndef MY_CALENDAR
#define MY_CALENDAR

struct MyDateStruct {
	int secondsInt;		//seconds [0,61]
	int minutesInt;		//minutes [0,59]
	int hourInt;		//hour [0,23]
	int dayInt;			//day of month [1,31]
	int monthInt;		//month of year [0,11]
	int yearInt;		//years since 1900
	int weekdayInt;		//day of week [0,6] (Sunday = 0)
	int dayYearInt;		//day of year [0,365]
	int daylightSavingsInt;	//daylight savings flag

	char * monthName;
	char * weekdayName;
};

char * MONTH_NAME_ARRAY[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
char * WEEKDAY_NAME_ARRAY[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

double secondsDifference(struct MyDateStruct startDateStruct, struct MyDateStruct endDateStruct);
int daysBetweenSeconds(double secondsInput);
struct MyDateStruct returnTodaysDateStruct();
struct MyDateStruct returnEasterSundayStruct(int yearInt);
struct MyDateStruct returnFixedFeastDay(int monthInt, int dayInt, struct MyDateStruct todaysDate);

#endif
