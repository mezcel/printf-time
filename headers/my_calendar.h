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

struct MyDateStruct setTodaysDateStruct();
struct MyDateStruct setEasterSundayStruct(int yearInt);
double secondsDifference(struct MyDateStruct startDateStruct, struct MyDateStruct endDateStruct);
int daysBetweenSeconds(double secondsInput);

#endif
