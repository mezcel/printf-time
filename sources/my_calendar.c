/*
 * my_calendar.c
 * */

#include <stdio.h>
#include <time.h>   // After year 2038, only use an x64 compiler
#include <stdlib.h> // malloc()

#include "../headers/my_calendar.h"

char *retrunWeekdayName( int indexNo, int shortFlag ) {
    /* Input an integer 0-6, and return a weekday name. 0=Sunday.
     * Input 1 for abbreviated weekday name. */

    char *weekdayName;

    if ( shortFlag ) {
        char * WEEKDAY_NAME_ARRAY[] = {
            "Sun", "Mon", "Tue", "Wed",
            "Thu", "Fri", "Sat" };
        weekdayName = WEEKDAY_NAME_ARRAY[ indexNo ];

    } else {
        char * WEEKDAY_NAME_ARRAY[] = {
            "Sunday", "Monday", "Tuesday", "Wednesday",
            "Thursday", "Friday", "Saturday" };
        weekdayName = WEEKDAY_NAME_ARRAY[ indexNo ];
    }

    return weekdayName;

}

char *retrunMonthName( int indexNo, int shortFlag ) {
    /* Input an integer 0-11, and return a month name. 0=January
     * Input 1 for abbreviated month name. */

    char *monthName;

    if ( shortFlag ) {
        char * MONTH_NAME_ARRAY[] = {
            "Jan", "Feb", "Mar", "Apr",
            "May", "Jun", "Jul", "Aug",
            "Sep", "Oct", "Nov", "Dec" };

        monthName = MONTH_NAME_ARRAY[ indexNo ];
    } else {
        char * MONTH_NAME_ARRAY[] = {
            "January", "February", "March", "April",
            "May", "June", "July", "August",
            "September", "October", "November", "December" };

        monthName = MONTH_NAME_ARRAY[ indexNo ];
    }

    return monthName;

}

char *retrunFeastDayName( int indexNo ) {
    /* Input an integer 0-15, and return a feast day name. 0=Advent Start */

    char * FEAST_DAY_ARRAY[] = {
        "Advent Start", "Immaculate Conception of Mary",                        // Advent Season
        "Christmas Day", "Solemnity of Mary", "Epiphany", "Jesus's Baptism",    // Christmas Season
        "Ash Wednesday", "Holy Thursday", "Good Friday", "Good Saturday",       // Lent Season
        "Easter Sunday", "Pentecost", "Ascension of Jesus",                     // Easter Season
        "Ordinary Day", "Seasonal Day"                                          // Generic Day
    };

    return FEAST_DAY_ARRAY[ indexNo ];

}

char *retrunLiturgicalName( int indexNo ) {
    /* Input an integer 0-4, and return a liturgical season name. 0=Advent Season */

    char * LITURGICAL_SEASON_ARRAY[] = {
        "Advent Season",
        "Christmas Season",
        "Lent Season",
        "Easter Season",
        "Ordinary Time"
    };

    return LITURGICAL_SEASON_ARRAY[ indexNo ];

}

char *returnWeekdayMystery( int indexNo ) {
    /* Input an integer 0-6, and return a rosary mystery name. 0=Glorious
     * 0-6 corresponds with sun-sat where 0=Sunday */

    char * WEEKDAY_MYSTERY[] = {
        "Glorious",     // sun
        "Joyful",       // mon
        "Sorrowful",    // tues
        "Glorious",     // wed
        "Luminous",     // thurs
        "Sorrowful",    // fri
        "Joyful"        // sat
    };

    return WEEKDAY_MYSTERY[ indexNo ];

}

struct tm returnTodaysDate() {
    /* Return a time.h struct containing today's date values */

    time_t currentDate  = time( NULL );
    struct tm output_tm = *localtime( &currentDate );

    return output_tm;

}

char *returnVerboseDate( struct tm tmDate, int shortFlag ) {
    /* Return a human readable string displaying today's date
     * Input 1 for abbreviated date. */

    char *verboseDate = malloc(32);             // Decorative Date Display

    if ( shortFlag == 1 ) {
        sprintf( verboseDate, "%s %d %s",       // automatic int to char conversion
            retrunWeekdayName( tmDate.tm_wday, shortFlag ),
            tmDate.tm_mday,
            retrunMonthName( tmDate.tm_mon, shortFlag )
        );
    } else {
        sprintf( verboseDate, "%s %d %s, %d",       // automatic int to char conversion
            retrunWeekdayName( tmDate.tm_wday, shortFlag ),
            tmDate.tm_mday,
            retrunMonthName( tmDate.tm_mon, shortFlag ),
            tmDate.tm_year + 1900
        );
    }

    return verboseDate;

}

struct tm setSpecificDate( int year, int month, int day ) {
    /* Generate a time.h char time stamp from a defined date */

    struct tm newTime = {
        .tm_year = year - 1900,
        .tm_mon = month,
        .tm_mday = day,
        .tm_hour = 0,
        .tm_min = 0,
        .tm_sec = 1
    };

    time_t t        = mktime( &newTime );
    newTime.tm_wday = localtime( &t ) -> tm_wday;

    return newTime;

}

struct tm setEasterDate( int year ) {
    /* Calculate Easter Day based on the Paschal Full Moon Date ( PFM )
     * algorithm source: https://en.wikipedia.org/wiki/Computus */

    int a, b, c, d, e, f, g, h, i, k, l, m, month, day;

    a       = year % 19;
    b       = year / 100;
    c       = year % 100;
    d       = b / 4;
    e       = b % 4;
    f       = (b + 8 ) / 25;
    g       = (b - f + 1 ) / 3;
    h       = ((19 * a ) + b - d - g + 15 ) % 30;
    i       = c / 4;
    k       = c % 4;
    l       = ( 32 + (2 * e ) + (2 * i ) - h - k ) % 7;
    m       = ( a + (11 * h ) + (22 * l ) ) / 451;
    month   = ( h + l - (7 * m ) + 114 ) / 31;
    day     = ( (h + l - (7 * m ) + 114 ) % 31 ) + 1;

    struct tm easterDay = setSpecificDate( year, month - 1, day );

    return easterDay;

}

struct tm addDay( struct tm referenceDate ) {
    /* Add just 1 day from a date
     * Set that date as the new time */

    referenceDate.tm_mday   += 1;
    time_t t                = mktime( &referenceDate );
    referenceDate.tm_wday   = localtime( &t ) -> tm_wday;

    return referenceDate;

}

struct tm addDays( struct tm referenceDate, int days ) {
    /* Add days from a date
     * Set that date as the new time */

    for ( int i=0; i < days; i++ ) {
        referenceDate = addDay( referenceDate );
    }

    return referenceDate;

}

struct tm subtractDay( struct tm referenceDate ) {
    /* Subtract just 1 day from a date
     * Set that date as the new time */

    referenceDate.tm_mday   -= 1;
    time_t t                = mktime( &referenceDate );
    referenceDate.tm_wday   = localtime( &t ) -> tm_wday;

    return referenceDate;

}

struct tm subtractDays( struct tm startDate, int days ) {
    /* Subtract days from a date
     * Set that date as the new time */

    for ( int i=0; i < days; i++ ) {
        startDate = subtractDay( startDate );
    }

    return startDate;

}

void shiftTowardSunday( struct tm *tmDate ) {
    /* Shift the date forward so that it is Sunday
     * Set the date for that Sunday */

    int intial_wday = tmDate -> tm_wday;

    if ( intial_wday != 0 ) {

        if ( intial_wday <= 4 ) {
            tmDate -> tm_mday -= intial_wday;
        } else if ( intial_wday == 6 ) {
            tmDate -> tm_mday += 1;
        } else {
            tmDate -> tm_mday += ( 6 - intial_wday );
        }

        time_t t            = mktime( tmDate );
        tmDate -> tm_mday   = localtime( &t ) -> tm_mday;
    }

}

void shiftJesusBaptism( struct tm *tmDate ) {
    /* Aprox Jan 13
     * Sunday after the Mass which celebrates the Epiphany
     * Monday if Epiphany Sunday shared the same day */

    int intial_wday = tmDate -> tm_wday;

    if ( intial_wday == 0 ) {
        tmDate -> tm_mday   += 1;

        time_t t            = mktime( tmDate );
        tmDate -> tm_mday   = localtime( &t ) -> tm_mday;
    }

}

int isFeastDay( struct tm tmNow, struct tm tmThen ) {
    /* Input the time struct for "now" and some other time
     * Compare the difference in time
     * Return 1 if the difference in time is within a 1 day duration */

    int intFlag             = 0;
    double returnSeconds    = difftime( mktime( &tmNow ), mktime( &tmThen ) );
    double days             = returnSeconds / ( 24 * 3600 );

    if ( ( days >= 0 ) && ( days <= 1 ) ) {
        intFlag = 1;
    } else {
        intFlag = 0;
    }

    return intFlag;

}

double daysDuration( struct tm season_start, struct tm season_end ) {
    /* Return the number of days within input time range */
    double durationSeconds  = difftime( mktime( &season_end ), mktime( &season_start ) );
    double durationDays     = durationSeconds / ( 24 * 3600 );

    return durationDays;
}

double daysRemaining( struct tm tmNow, struct tm season_end ) {
    /* Return the number of days until the end of date range */
    double remainingSeconds = difftime( mktime( &season_end ), mktime( &tmNow ) );
    double remainingDays    = remainingSeconds / ( 24 * 3600 );

    return remainingDays;
}

double daysElapsed( struct tm season_start, struct tm tmNow ) {
    /* Return the number of days since the start of a time range */
    double elapsedSeconds = difftime( mktime( &tmNow ), mktime( &season_start ) );
    double elapsedDays    = elapsedSeconds / (24 * 3600 );

    return elapsedDays;
}

int isLiturgicalSeason( struct tm tmNow, struct tm season_start, struct tm season_end ) {
    /* Is the current date within a liturgical season window?
     *  Easter season is 50 days starting at Pentecost
     *  Lent season is 46 days between Ash Wed and Easter
     *  Advent season lasts through Christmas Day
     *  Christmas season lasts through the epiphany
     *  Ordinary is the time outside of the main seasons */

    int returnFlag = 0;

    double durationDays       = daysDuration(season_start, season_end);
    double remainingDays      = daysRemaining(tmNow, season_end);

    if ( ( remainingDays >= 0.0 ) && ( remainingDays <= durationDays ) ) {
        returnFlag = 1;
    } else {
        if ( remainingDays > 0.0 ) {
            // Workarround for December 26 – January 6 Christmas tide
            returnFlag = 1;
        } else {
            returnFlag = 0;
        }
    }

    return returnFlag;

}

int returnLiturgicalSeason(
        struct tm *tmNow,
        struct tm *advent_start,
        struct tm *christmas_day,
        struct tm *epiphany,
        struct tm *ash_wednesday,
        struct tm *easter_sunday,
        struct tm *pentacost ) {
    /* Input the time struct for "now" and liturgical calendar reference point time structs
     * Compare the current time with known seasonal windows
     * Return 1-4 depending on which session the current time resides in. */

    int isAdvent    = isLiturgicalSeason( *tmNow, *advent_start, *christmas_day );
    int isChristmas = isLiturgicalSeason( *tmNow, *christmas_day, *epiphany );
    int isLent      = isLiturgicalSeason( *tmNow, *ash_wednesday, *easter_sunday );
    int isEasterTide = isLiturgicalSeason( *tmNow, *easter_sunday, *pentacost );

    int returnFlag;

    if ( ( isAdvent == 1 ) && ( isAdvent != isChristmas ) ) {
        returnFlag = 0;     // Advent
    } else if ( isAdvent == isChristmas ) {
        returnFlag = 1;     // Christmas
    } else if ( isLent ) {
        returnFlag = 2;     // Lent
    } else if ( isEasterTide ) {
        returnFlag = 3;     // Easter
    } else {
        returnFlag = 4;     // Ordinary
    }

    return returnFlag;
}

char *stringLiturgicalSeason() {
    /* Calculate what liturgical season is currently is.
     * Return the name of the current liturgical season. */

    struct tm todaysDate    = returnTodaysDate();

    // Advent Season
    struct tm advent_start  = setSpecificDate( todaysDate.tm_year + 1900, 11, 1 );  // Dec 1
    shiftTowardSunday( &advent_start );                                             // first Sun of Advent

    // Christmas Season
    struct tm christmas_day = setSpecificDate( todaysDate.tm_year + 1900, 11, 25 ); // wed Dec 25
    struct tm epiphany      = addDays( christmas_day,12 );                          // 12 days after Christmas
    shiftTowardSunday( &epiphany );         // epiphany Sunday

    // Lent Season
    struct tm easter_sunday = setEasterDate( todaysDate.tm_year + 1900 );           // PFM Calculation Result
    struct tm ash_wednesday = subtractDays( easter_sunday, 46 );

    // Easter Season
    struct tm pentacost     = addDays( easter_sunday, 21 );
    shiftTowardSunday( &pentacost );                                                // 7 Sundays after Easter
    struct tm assension_of_jesus = addDays( easter_sunday, 40 );

    // ["Advent Season", "Christmas Season", "Lent Season", "Easter Season", "Ordinary Time" ]
    int seasonFlag = returnLiturgicalSeason(
            &todaysDate,
            &advent_start,
            &christmas_day,
            &epiphany,
            &ash_wednesday,
            &easter_sunday,
            &pentacost );   // returns 0-4

    return retrunLiturgicalName( seasonFlag );

}

char *stringFeast( int additionalDay, int additionalMonth, char *userDefinedFeast ) {
    /* Input parameters to compare today's date against.
     * Determine if today corresponds with a predefined feast days.
     * Return today's feast day name */

    char *feast;                                                                                // Feast string output
    int feastFlag = 14;                                                                         // Default to Ordinary
    struct tm todaysDate    = returnTodaysDate();                                               // Today's date

    // Advent Season Feasts
    int isAdvent, isImmConcept;
    struct tm advent_start  = setSpecificDate( todaysDate.tm_year + 1900, 11, 1 );              // Dec 1
    shiftTowardSunday( &advent_start );                                                         // First Sun of Advent
    struct tm immaculate_conception_mary = setSpecificDate( todaysDate.tm_year + 1900, 11, 8 ); // Dec 8

    // Christmas Season Feasts
    int isChristmas, isSolemOfMary, isEpiphany, isJesusBatism;
    struct tm christmas_day         = setSpecificDate( todaysDate.tm_year + 1900, 11, 25 );     // Dec 25
    struct tm solemnity_of_mary     = setSpecificDate( todaysDate.tm_year + 1900, 0, 1 );       // Jan 1
    struct tm epiphany              = addDays( christmas_day, 12 );                             // 12 days after Christmas
    shiftTowardSunday( &epiphany );                                                             // Epiphany Sunday
    struct tm jesus_baptism = addDays( christmas_day, 12 );
    shiftJesusBaptism( &jesus_baptism );                                                        // Avoid Epiphany overlap

    // Lent Season Feasts
    int isAshWed, isHolyThurs, isGoodFri, isGoodSat, isEaster;
    struct tm easter_sunday = setEasterDate( todaysDate.tm_year + 1900 );                       // PFM Calculation Result
    struct tm good_saturday = subtractDays( easter_sunday, 1 );
    struct tm good_friday   = subtractDays( easter_sunday, 2 );
    struct tm holy_thursday = subtractDays( easter_sunday, 3 );
    struct tm ash_wednesday = subtractDays( easter_sunday, 46 );

    // Easter Season Feasts
    int isPentacost, isAssension;
    struct tm pentacost = addDays( easter_sunday, 21 );
    shiftTowardSunday( &pentacost );                                                            // 7 Sundays after Easter
    struct tm assension_of_jesus = addDays( easter_sunday, 40 );

    // User Defined Feast Days
    struct tm userFeastDay = setSpecificDate( todaysDate.tm_year + 1900, additionalMonth, additionalDay );
    int isUserDefinedFeast = isFeastDay( todaysDate, userFeastDay );                            // Is today defined by the user?

    // ["Advent Season", "Christmas Season", "Lent Season", "Easter Season", "Ordinary Time" ]
    int seasonFlag = returnLiturgicalSeason(
            &todaysDate,
            &advent_start,
            &christmas_day,
            &epiphany,
            &ash_wednesday,
            &easter_sunday,
            &pentacost );   // returns 0-4

    // Determine Available Feast Day Strings
    switch ( seasonFlag ) {
        case 0:
            isAdvent        = isFeastDay( todaysDate, advent_start );
            isImmConcept    = isFeastDay( todaysDate, immaculate_conception_mary );

            if ( isAdvent ) {
                feastFlag = 0;
            } else if ( isImmConcept ) {
                feastFlag = 1;
            }

            break;

        case 1:
            isChristmas     = isFeastDay( todaysDate, christmas_day );
            isSolemOfMary   = isFeastDay( todaysDate, solemnity_of_mary );
            isEpiphany      = isFeastDay( todaysDate, epiphany );
            isJesusBatism   = isFeastDay( todaysDate, jesus_baptism );

            if ( isChristmas ) {
                feastFlag = 2;
            } else if ( isSolemOfMary ) {
                feastFlag = 3;
            } else if ( isEpiphany ) {
                feastFlag = 4;
            } else if ( isJesusBatism ) {
                feastFlag = 5;
            }

            break;

        case 2:
            isAshWed        = isFeastDay( todaysDate, ash_wednesday );
            isHolyThurs     = isFeastDay( todaysDate, holy_thursday );
            isGoodFri       = isFeastDay( todaysDate, good_friday );
            isGoodSat       = isFeastDay( todaysDate, good_saturday );
            isEaster        = isFeastDay( todaysDate, easter_sunday );

            if ( isAshWed ) {
                feastFlag = 6;
            } else if ( isHolyThurs ) {
                feastFlag = 7;
            } else if ( isGoodFri ) {
                feastFlag = 8;
            } else if ( isGoodSat ) {
                feastFlag = 9;
            } else if ( isEaster ) {
                feastFlag = 10;
            }

            break;

        case 3:
            isPentacost     = isFeastDay( todaysDate, pentacost );
            isAssension     = isFeastDay( todaysDate, assension_of_jesus );

            if ( isPentacost ) {
                feastFlag = 11;
            } else if ( isAssension ) {
                feastFlag = 12;
            }

            break;

        default:
            feastFlag = 13; break;  // generic day  placeholder

            break;
    }

    // Select A Feast Day String
    if ( isUserDefinedFeast ) {
        feast = userDefinedFeast;
    } else {
        /* [ "Advent Start", "Immaculate Conception of Mary", "Christmas Day", "Solemnity of Mary", "Epiphany",
         * "Jesus's Baptism", "Ash Wednesday", "Holy Thursday", "Good Friday", "Good Saturday", "Easter Sunday",
         * "Pentecost", "Ascension of Jesus", "Ordinary Day", "Seasonal Day" ] */

        feast = retrunFeastDayName( feastFlag );
    }

    return feast;

}
