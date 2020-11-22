/*
 * my_calendar.h
 * */

#ifndef MY_CALENDAR
#define MY_CALENDAR

/* ****************************************************
 * Define tm Structs
 * **************************************************** */

/* Return a time.h struct containing today's date values */
struct tm returnTodaysDate();

/* Generate a time.h char time stamp from a defined date */
struct tm setSpecificDate( int year, int month, int day );

/* Calculate Easter Day based on the Paschal Full Moon Date ( PFM )
    * algorithm source: https://en.wikipedia.org/wiki/Computus */
struct tm setEasterDate( int year );

/* Add just 1 day from a date. Set that date as the new time */
struct tm addDay( struct tm referenceDate );

/* Add days from a date. Set that date as the new time */
struct tm addDays( struct tm referenceDate, int days );

/* Subtract just 1 day from a date. Set that date as the new time */
struct tm subtractDay( struct tm referenceDate );

/* Subtract days from a date. Set that date as the new time */
struct tm subtractDays( struct tm startDate, int days );

/* ****************************************************
 * Define time manipulation and verification functions
 * **************************************************** */

/* Input an integer 0-6, and return a weekday name. 0=Sunday */
char *retrunWeekdayName( int indexNo );

/* Input an integer 0-11, and return a month name. 0=January */
char *retrunMonthName( int indexNo );

/* Return a human readable string displaying today's date  */
char *returnVerboseDate( struct tm tmDate );

/* Input an integer 0-15, and return a feast day name. 0=Advent Start */
char *retrunFeastDayName( int indexNo );

/* Input an integer 0-4, and return a liturgical season name. 0=Advent Season */
char *retrunLiturgicalName( int indexNo );

/* Input an integer 0-6, and return a rosary mystery name. 0=Glorious 0-6 corresponds with sun-sat where 0=Sunday */
char *returnWeekdayMystery( int indexNo );

/* Calculate what liturgical season is currently is. Return the name of the current liturgical season. */
char *stringLiturgicalSeason();

/* Input parameters to compare today's date against. Determine if today corresponds with a predefined feast days.
     * Return today's feast day name */
char *stringFeast( int additionalDay, int additionalMonth, char *additionalFeast );

 /* Shift the date forward so that it is Sunday. Set the date for that Sunday */
void shiftTowardSunday( struct tm *tmDate );

/* Aprox Jan 13. Sunday after the Mass which celebrates the Epiphany
     * Monday if Epiphany Sunday shared the same day */
void shiftJesusBaptism( struct tm *tmDate );

/* Input the time struct for "now" and some other time. Compare the difference in time.
     * Return 1 if the difference in time is within a 1 day duration */
int isFeastDay( struct tm tmNow, struct tm tmThen );

/* Easter season is 50 days starting at Pentecost. Lent season is 46 days between Ash Wed and Easter
     * Advent season lasts through Christmas Day. Christmas season lasts through the epiphany
     * Ordinary is the time outside of the main seasons */
int isLiturgicalSeason( struct tm tmNow, struct tm season_start, struct tm season_end );

/* Input the time struct for "now" and liturgical calendar reference point time structs
     * Compare the current time with known seasonal windows
     * Return 1-4 depending on which session the current time resides in. */
int returnLiturgicalSeason(
    struct tm *tmNow, struct tm *advent_start,
    struct tm *christmas_day, struct tm *epiphany, struct tm *ash_wednesday,
    struct tm *easter_sunday, struct tm *pentacost );

#endif
