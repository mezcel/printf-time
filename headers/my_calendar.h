/*
 * my_calendar.h
 * */

#ifndef MY_CALENDAR_TMP
#define MY_CALENDAR_TMP

char * MONTH_NAME_ARRAY[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
char * WEEKDAY_NAME_ARRAY[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
char * LITURGICAL_SEASON_ARRAY[] = { "Advent Season", "Christmas Season", "Lent Season", "Easter Season", "Ordinary Time"};
char * FEAST_DAY_ARRAY[] = { "advent_start", "immaculate_conception_mary", "christmas_day", "solemnity_of_mary", "epiphany", "jesus_baptism", "ash_wednesday", "holy_thursday", "good_friday", "good_saturday", "easter_sunday", "pentacost", "assension_of_jesus", "all_saints_day", "ordinary_day"};

struct tm returnTodaysDate();
struct tm setSpecificDate(int year, int month, int day);
struct tm setEasterDate(int year);
struct tm addDay(struct tm referenceDate);
struct tm addDays(struct tm referenceDate, int days);
struct tm subtractDay(struct tm referenceDate);
struct tm subtractDays(struct tm startDate, int days);
void shiftTowardSunday(struct tm *tmDate);
void shiftJesusBaptism(struct tm *tmDate);
int isFeastDay(struct tm tmNow, struct tm tmThen);
int isLiturgicalSeason(struct tm tmNow, struct tm season_start,
	struct tm season_end);
int returnLiturgicalSeason(struct tm *tmNow, struct tm *advent_start,
	struct tm *christmas_day, struct tm *epiphany, struct tm *ash_wednesday,
	struct tm *easter_sunday, struct tm *pentacost);

#endif
