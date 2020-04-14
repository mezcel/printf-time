/*
 * my_calendar.c
 * */

#include <stdio.h>
#include <time.h>	// After year 2038, only use an x64 compiler
#include <stdlib.h>	// malloc()

#include "../headers/my_calendar.h"

char *retrunWeekdayName( int indexNo ) {
	char * WEEKDAY_NAME_ARRAY[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

	return WEEKDAY_NAME_ARRAY[ indexNo ];
}

char *retrunMonthName( int indexNo ) {
	char * MONTH_NAME_ARRAY[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

	return MONTH_NAME_ARRAY[ indexNo ];
}

char *retrunFeastDayName( int indexNo ) {
	char * FEAST_DAY_ARRAY[] = { "Advent Start", "Immaculate Conception of Mary", "Christmas Day", "Solemnity of Mary", "Epiphany",
		"Jesus's Baptism", "Ash Wednesday", "Holy Thursday", "Good Friday", "Good Saturday", "Easter Sunday", "Pentecost", "Ascension of Jesus", "Ordinary Day", "Seasonal Day" };

	return FEAST_DAY_ARRAY[ indexNo ];
}

char *retrunLiturgicalName( int indexNo ) {
	char * LITURGICAL_SEASON_ARRAY[] = { "Advent Season", "Christmas Season", "Lent Season", "Easter Season", "Ordinary Time" };

	return LITURGICAL_SEASON_ARRAY[ indexNo ];
}

char *returnWeekdayMystery( int indexNo ) {
	char * WEEKDAY_MYSTERY[] = { "Glorious", "Joyful", "Sorrowful", "Glorious", "Luminous", "Sorrowful", "Joyful" };

	return WEEKDAY_MYSTERY[ indexNo ];
}

struct tm returnTodaysDate() {
	// Return a time struct containing today's date values

	time_t currentDate = time( NULL );
	struct tm output_tm = *localtime( &currentDate );

	return output_tm;
}

char *returnVerboseDate( struct tm tmDate ) {
	char *verboseDate = malloc(32);									// Decorative Date Display

	sprintf( verboseDate, "%s %d %s, %d",							// automatic int to char conversion
		retrunWeekdayName( tmDate.tm_wday ),
		tmDate.tm_mday, retrunMonthName( tmDate.tm_mon ),
		tmDate.tm_year + 1900 );

	return verboseDate;
}

struct tm setSpecificDate( int year, int month, int day ) {
	struct tm newTime = {
		.tm_year = year - 1900,
		.tm_mon = month,
		.tm_mday = day,
		.tm_hour = 0,
		.tm_min = 0,
		.tm_sec = 1
	};

	time_t t = mktime( &newTime );
	newTime.tm_wday = localtime( &t ) -> tm_wday;

	return newTime;
}

struct tm setEasterDate( int year ) {
	/*
	* algorithm source: https://en.wikipedia.org/wiki/Computus
	* */

	int a, b, c, d, e, f, g, h, i, k, l, m, month, day;

	a	= year % 19;
	b	= year / 100;
	c	= year % 100;
	d	= b / 4;
	e	= b % 4;
	f	= (b + 8 ) / 25;
	g	= (b - f + 1 ) / 3;
	h	= ((19 * a ) + b - d - g + 15 ) % 30;
	i	= c / 4;
	k	= c % 4;
	l	= ( 32 + (2 * e ) + (2 * i ) - h - k ) % 7;
	m	= ( a + (11 * h ) + (22 * l ) ) / 451;
	month = ( h + l - (7 * m ) + 114 ) / 31;
	day = ( (h + l - (7 * m ) + 114 ) % 31 ) + 1;

	struct tm easterDay = setSpecificDate( year, month - 1, day );

	return easterDay;
}

struct tm addDay( struct tm referenceDate ) {
	referenceDate.tm_mday += 1;
	time_t t = mktime( &referenceDate );
	referenceDate.tm_wday = localtime( &t ) -> tm_wday;

	return referenceDate;
}

struct tm addDays( struct tm referenceDate, int days ) {
	for ( int i=0; i < days; i++ ) {
		referenceDate = addDay( referenceDate );
	}
	return referenceDate;
}

struct tm subtractDay( struct tm referenceDate ) {
	referenceDate.tm_mday -= 1;
	time_t t = mktime( &referenceDate );
	referenceDate.tm_wday = localtime( &t ) -> tm_wday;

	return referenceDate;
}

struct tm subtractDays( struct tm startDate, int days ) {
	for ( int i=0; i < days; i++ ) {
		startDate = subtractDay( startDate );
	}
	return startDate;
}

void shiftTowardSunday( struct tm *tmDate ) {
	int intial_wday = tmDate -> tm_wday;

	if ( intial_wday != 0 ) {

		if ( intial_wday <= 4 ) {
			tmDate -> tm_mday -= intial_wday;
		} else if ( intial_wday == 6 ) {
			tmDate -> tm_mday += 1;
		} else {
			tmDate -> tm_mday += ( 6 - intial_wday );
		}

		time_t t = mktime( tmDate );
		tmDate -> tm_mday = localtime( &t ) -> tm_mday;
	}
}

void shiftJesusBaptism( struct tm *tmDate ) {
	/*
	* Aprox Jan 13
	* sunday after the Mass which celebrates the Epiphany
	* Monday if Epiphany Sunday shared the same day
	* */
	int intial_wday = tmDate -> tm_wday;

	if ( intial_wday == 0 ) {
		tmDate -> tm_mday += 1;

		time_t t = mktime( tmDate );
		tmDate -> tm_mday = localtime( &t ) -> tm_mday;
	}

}

int isFeastDay( struct tm tmNow, struct tm tmThen ) {
	// return 1 if the difference in tims is within a 1 day duration
	int intFlag = 0;
	double returnSeconds = difftime( mktime ( &tmNow ), mktime( &tmThen ) );
	double days = returnSeconds / ( 24 * 3600 );

	if ( ( days >= 0 ) && ( days <= 1 ) ) {
		intFlag = 1;
	} else {
		intFlag = 0;
	}

	return intFlag;
}

int isLiturgicalSeason( struct tm tmNow, struct tm season_start, struct tm season_end ) {
	/*
	* Easter season is 50 days starting at Pentecost
	* Lent season is 46 days between Ash Wed and Easter
	* Advent season lasts through Christmas Day
	* Christmas season lasts through the epiphany
	* Ordinary is the time outside of the main seasons
	* */

	int returnFlag = 0;

	double durationSeconds = difftime( mktime( &season_end ), mktime( &season_start ) );
	double durationDays = durationSeconds / (24 * 3600 );

	double countdownSeconds = difftime( mktime(&season_end ), mktime(&tmNow ) );
	double countdownDays = countdownSeconds / (24 * 3600 );

	if ( (countdownDays >= 0 ) && (countdownDays <= durationDays ) ) {
		returnFlag = 1;
	} else {
		returnFlag = 0;
	}

	return returnFlag;
}

int returnLiturgicalSeason( struct tm *tmNow, struct tm *advent_start,
	struct tm *christmas_day, struct tm *epiphany, struct tm *ash_wednesday,
		struct tm *easter_sunday, struct tm *pentacost ) {

	int isAdvent	= isLiturgicalSeason( *tmNow, *advent_start, *christmas_day );
	int isChristmas = isLiturgicalSeason( *tmNow, *christmas_day, *epiphany );
	int isLent		= isLiturgicalSeason( *tmNow, *ash_wednesday, *easter_sunday );
	int isEasterTide = isLiturgicalSeason( *tmNow, *easter_sunday, *pentacost );

	int returnFlag;

	if( isAdvent ) {
		returnFlag = 0;
	} else if ( isChristmas ) {
		returnFlag = 1;
	} else if ( isLent ) {
		returnFlag = 2;
	} else if ( isEasterTide ) {
		returnFlag = 3;
	} else {
		returnFlag = 4;
	} // [ "Advent Season", "Christmas Season", "Lent Season", "Easter Season", "Ordinary Time"]

	return returnFlag;
}

char *stringLiturgicalSeason() {
	struct tm todaysDate = returnTodaysDate();

	struct tm advent_start = setSpecificDate( todaysDate.tm_year + 1900, 11, 1 );				// Dec 1
	shiftTowardSunday( &advent_start );															// first sun of advent

	struct tm immaculate_conception_mary = setSpecificDate( todaysDate.tm_year + 1900, 11, 8 );	// Dec 8
	struct tm christmas_day				= setSpecificDate( todaysDate.tm_year + 1900, 11, 25 );	// wed dec 25
	struct tm solemnity_of_mary			= setSpecificDate( todaysDate.tm_year + 1900, 0, 1 );	// Jan 1
	struct tm epiphany					= addDays( christmas_day,12 );							// 12 days after Christmas
	shiftTowardSunday( &epiphany ); // epiphany sunday

	struct tm jesus_baptism = addDays( christmas_day,12 );
	shiftJesusBaptism( &jesus_baptism ); // avoid epiphany overlap

	struct tm easter_sunday	= setEasterDate( todaysDate.tm_year + 1900 ); // pfm, derived from paschal full moon
	/*struct tm good_saturday = subtractDays( easter_sunday, 1 );
	struct tm good_friday	= subtractDays( easter_sunday, 2 );
	struct tm holy_thursday = subtractDays( easter_sunday, 3 );*/
	struct tm ash_wednesday = subtractDays( easter_sunday, 46 );
	struct tm pentacost		= addDays( easter_sunday, 21 );
	shiftTowardSunday( &pentacost );  // sun June 9, 7 Sundays after Easter

	struct tm assension_of_jesus = addDays( easter_sunday, 40 );

	//struct tm all_saints_day = setSpecificDate( todaysDate.tm_year + 1900, 10, 1 );				// Nov 1

	int seasonFlag = returnLiturgicalSeason( &todaysDate, &advent_start, &christmas_day,
			&epiphany, &ash_wednesday, &easter_sunday, &pentacost );

	char *season = retrunLiturgicalName( seasonFlag );
	return season;
}

char *stringFeast( int additionalDay, int additionalMonth, char *userDefinedFeast ) {
	char *feast;																			// feast day display string
	struct tm todaysDate = returnTodaysDate();

	struct tm advent_start = setSpecificDate( todaysDate.tm_year + 1900, 11, 1 );			// Dec 1
	shiftTowardSunday( &advent_start );														// first sun of advent

	struct tm immaculate_conception_mary = setSpecificDate( todaysDate.tm_year + 1900, 11, 8 );	// Dec 8
	struct tm christmas_day		= setSpecificDate( todaysDate.tm_year + 1900, 11, 25 );			// Dec 25
	struct tm solemnity_of_mary = setSpecificDate( todaysDate.tm_year + 1900, 0, 1 );			// Jan 1
	struct tm epiphany			= addDays( christmas_day, 12 );									// 12 days after Christmas
	shiftTowardSunday( &epiphany );																// epiphany Sunday

	struct tm jesus_baptism = addDays( christmas_day, 12 );
	shiftJesusBaptism( &jesus_baptism );													// avoid epiphany overlap

	struct tm easter_sunday = setEasterDate( todaysDate.tm_year + 1900 ); // pfm
	struct tm good_saturday = subtractDays( easter_sunday, 1 );
	struct tm good_friday	= subtractDays( easter_sunday, 2 );
	struct tm holy_thursday = subtractDays( easter_sunday, 3 );
	struct tm ash_wednesday = subtractDays( easter_sunday, 46 );
	struct tm pentacost		= addDays( easter_sunday, 21 );
	shiftTowardSunday( &pentacost );														// 7 Sundays after Easter

	struct tm assension_of_jesus = addDays( easter_sunday, 40 );

	///////////////////////////
	struct tm userFeastDay;
	if ( ( userDefinedFeast != NULL ) && ( userDefinedFeast != "" ) ) {
		//struct tm all_saints_day = setSpecificDate( todaysDate.tm_year + 1900, 10, 1 );			// Nov 1
		userFeastDay = setSpecificDate( todaysDate.tm_year + 1900, additionalMonth, additionalDay );
	}

	int seasonFlag = returnLiturgicalSeason( &todaysDate, &advent_start, &christmas_day,
			&epiphany, &ash_wednesday, &easter_sunday, &pentacost );

	int isFeast, feastFlag;
	switch ( seasonFlag ) {
		case 0:
			feastFlag = 14;										// generic advent seasonal day placeholder

			isFeast = isFeastDay( todaysDate, advent_start );
			if( isFeast ) { feastFlag = 0; break; }

			isFeast = isFeastDay( todaysDate, immaculate_conception_mary );
			if( isFeast ) { feastFlag = 1; break; }
			
			break;

		case 1:
			feastFlag = 14;										// generic Christmas seasonal day placeholder

			isFeast = isFeastDay( todaysDate, christmas_day );
			if( isFeast ) { feastFlag = 2; break; }

			isFeast = isFeastDay( todaysDate, solemnity_of_mary );
			if( isFeast ) { feastFlag = 3; break; }

			isFeast = isFeastDay( todaysDate, epiphany );
			if( isFeast ) { feastFlag = 4; break; }

			isFeast = isFeastDay( todaysDate, jesus_baptism );
			if( isFeast ) { feastFlag = 5; break; }
			
			break;

		case 2:
			feastFlag = 14;										// generic lent seasonal day placeholder

			isFeast = isFeastDay( todaysDate, ash_wednesday );
			if( isFeast ) { feastFlag = 6; break; }

			isFeast = isFeastDay( todaysDate, holy_thursday );
			if( isFeast ) { feastFlag = 7; break; }

			isFeast = isFeastDay( todaysDate, good_friday );
			if( isFeast ) { feastFlag = 8; break; }

			isFeast = isFeastDay( todaysDate, good_saturday );
			if( isFeast ) { feastFlag = 9; break; }

			isFeast = isFeastDay( todaysDate, easter_sunday );
			if( isFeast ) { feastFlag = 10; break; }
			
			break;

		case 3:
			feastFlag = 14;										// generic Easter seasonal day placeholder

			isFeast = isFeastDay( todaysDate, pentacost );
			if( isFeast ) { feastFlag = 11; break; }

			isFeast = isFeastDay( todaysDate, assension_of_jesus );
			if( isFeast ) { feastFlag = 12; break; }
			
			break;

		default:
			feastFlag = 13; break;								// generic day  placeholder
			
			break;
	}

	isFeast = isFeastDay( todaysDate, userFeastDay );
	if( isFeast ) {
		feast = userDefinedFeast;
	} else {
		feast = retrunFeastDayName( feastFlag );
	}
	
	return feast;
	
}
