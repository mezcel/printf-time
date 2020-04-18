/*
 * my_calendar.h
 * */

#ifndef MY_CALENDAR
#define MY_CALENDAR

struct tm returnTodaysDate();
struct tm setSpecificDate( int year, int month, int day );
struct tm setEasterDate( int year );
struct tm addDay( struct tm referenceDate );
struct tm addDays( struct tm referenceDate, int days );
struct tm subtractDay( struct tm referenceDate );
struct tm subtractDays( struct tm startDate, int days );

char *retrunWeekdayName( int indexNo );
char *retrunMonthName( int indexNo );
char *returnVerboseDate( struct tm tmDate );
char *retrunFeastDayName( int indexNo );
char *retrunLiturgicalName( int indexNo );
char *returnWeekdayMystery( int indexNo );
char *stringLiturgicalSeason();
char *stringFeast( int additionalDay, int additionalMonth, char *additionalFeast );

void shiftTowardSunday( struct tm *tmDate );
void shiftJesusBaptism( struct tm *tmDate );

int isFeastDay( struct tm tmNow, struct tm tmThen );
int isLiturgicalSeason( struct tm tmNow, struct tm season_start, struct tm season_end );
int returnLiturgicalSeason( struct tm *tmNow, struct tm *advent_start,
    struct tm *christmas_day, struct tm *epiphany, struct tm *ash_wednesday,
    struct tm *easter_sunday, struct tm *pentacost );

#endif
