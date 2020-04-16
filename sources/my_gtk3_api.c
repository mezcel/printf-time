/*
 * my_gtk3_api.c
 * compile:
 * 	gcc -c my_gtk3_api.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
 * */

#include "gtk/gtk.h"

#include "../headers/my_calendar.h"
#include "../headers/my_file_to_struct.h"
#include "../headers/my_gtk3_api.h"

 /*
 * Header API Scope Functions
 * */

void intializeCalendar( struct tm todaysDate, int *seasonFlag, int *feastFlag );	// local prototype
void intializeCalendar( struct tm todaysDate, int *seasonFlag, int *feastFlag ) { 
	struct tm advent_start = setSpecificDate( todaysDate.tm_year + 1900, 11, 1 );					// Dec 1
	shiftTowardSunday( &advent_start );																// first sun of advent

	struct tm immaculate_conception_mary	= setSpecificDate( todaysDate.tm_year + 1900, 11, 8 );	// Dec 8
	struct tm christmas_day					= setSpecificDate( todaysDate.tm_year + 1900, 11, 25 );	// wed dec 25
	struct tm solemnity_of_mary				= setSpecificDate( todaysDate.tm_year + 1900, 0, 1 );	// Jan 1
	struct tm epiphany						= addDays( christmas_day,12 );							// 12 days after christmas
	shiftTowardSunday( &epiphany );																	// epiphany sunday

	struct tm jesus_baptism					= addDays( christmas_day,12 );
	shiftJesusBaptism( &jesus_baptism );															// avoid epiphany overlap

	struct tm easter_sunday					= setEasterDate( todaysDate.tm_year + 1900 );			// pfm
	struct tm good_saturday					= subtractDays( easter_sunday,1 );
	struct tm good_friday					= subtractDays( easter_sunday,2 );
	struct tm holy_thursday					= subtractDays( easter_sunday,3 );
	struct tm ash_wednesday					= subtractDays( easter_sunday,46 );
	struct tm pentacost						= addDays( easter_sunday,21 );
	shiftTowardSunday( &pentacost ); 																// 7 sundays after easter

	struct tm assension_of_jesus			= addDays( easter_sunday,40 );

	struct tm all_saints_day				= setSpecificDate( todaysDate.tm_year + 1900, 10, 1 );	// Nov 1

	*seasonFlag = returnLiturgicalSeason( &todaysDate, &advent_start, &christmas_day,
			&epiphany, &ash_wednesday, &easter_sunday, &pentacost );

	int isFeast;
	switch ( *seasonFlag ) { 
		case 0:
			isFeast = isFeastDay( todaysDate, advent_start );
			if( isFeast ) { feastFlag = 0; break; }

			isFeast = isFeastDay( todaysDate, immaculate_conception_mary );
			if( isFeast ) { *feastFlag = 1; break; }

			*feastFlag = 15; // generic seasonal day
			break;
		case 1:
			isFeast = isFeastDay( todaysDate, christmas_day );
			if( isFeast ) { *feastFlag = 2; break; }

			isFeast = isFeastDay( todaysDate, solemnity_of_mary );
			if( isFeast ) { *feastFlag = 3; break; }

			isFeast = isFeastDay( todaysDate, epiphany );
			if( isFeast ) { *feastFlag = 4; break; }

			isFeast = isFeastDay( todaysDate, jesus_baptism );
			if( isFeast ) { *feastFlag = 5; break; }

			*feastFlag = 15; // generic seasonal day
			break;
		case 2:
			isFeast = isFeastDay( todaysDate, ash_wednesday );
			if( isFeast ) { *feastFlag = 6; break; }

			isFeast = isFeastDay( todaysDate, holy_thursday );
			if( isFeast ) { *feastFlag = 7; break; }

			isFeast = isFeastDay( todaysDate, good_friday );
			if( isFeast ) { *feastFlag = 8; break; }

			isFeast = isFeastDay( todaysDate, good_saturday );
			if( isFeast ) { *feastFlag = 9; break; }

			isFeast = isFeastDay( todaysDate, easter_sunday );
			if( isFeast ) { *feastFlag = 10; break; }

			*feastFlag = 15; // generic seasonal day
			break;
		case 3:
			isFeast = isFeastDay( todaysDate, pentacost );
			if( isFeast ) { *feastFlag = 11; break; }

			isFeast = isFeastDay( todaysDate, assension_of_jesus );
			if( isFeast ) { *feastFlag = 12; break; }

			*feastFlag = 15; // generic seasonal day
			break;
		default:
			isFeast = isFeastDay( todaysDate, all_saints_day );
			if( isFeast ) { *feastFlag = 13; break; }
			if( isFeast == 0 ) { *feastFlag = 14; break; }
			break;
	}
}

void initializeLabelPointers( GtkBuilder *builder, GtkWidget *window, app_widgets *widgets, char *userDefinedFeast ) { 

	struct tm todaysDate = returnTodaysDate();
	int seasonFlag = 4; // ordinary time
	int feastFlag = 14; // ordinary day

	intializeCalendar( todaysDate, &seasonFlag, &feastFlag );

	// labels
	widgets -> lblTextDate = GTK_WIDGET( gtk_builder_get_object( builder, "lblTextDate" ) );

	widgets -> lblTextMystery			= GTK_WIDGET( gtk_builder_get_object( builder, "lblTextMystery" ) );
	widgets -> lblTextDecade			= GTK_WIDGET( gtk_builder_get_object( builder, "lblTextDecade" ) );
	widgets -> lblTextDecadeMessage 	= GTK_WIDGET( gtk_builder_get_object( builder, "lblTextDecadeMessage" ) );
	widgets -> lblTextBackground		= GTK_WIDGET( gtk_builder_get_object( builder, "lblTextBackground" ) );
	widgets -> lblTextScripture			= GTK_WIDGET( gtk_builder_get_object( builder, "lblTextScripture" ) );
	widgets -> lblTextPrayer			= GTK_WIDGET( gtk_builder_get_object( builder, "lblTextPrayer" ) );
	widgets -> lblTextBeadType			= GTK_WIDGET( gtk_builder_get_object( builder, "lblTextBeadType" ) );
	widgets -> lblTextBeadNo			= GTK_WIDGET( gtk_builder_get_object( builder, "lblTextBeadNo" ) );
	widgets -> lblTextLiturgicalCalendar = GTK_WIDGET( gtk_builder_get_object( builder, "lblTextLiturgicalCalendar" ) );
	widgets -> lblTextFeast				= GTK_WIDGET( gtk_builder_get_object( builder, "lblTextFeast" ) );

	widgets -> lblTextDecadeProgress	= GTK_WIDGET( gtk_builder_get_object( builder, "lblTextDecadeProgress" ) );
	widgets -> lblTextDecadePercent		= GTK_WIDGET( gtk_builder_get_object( builder, "lblTextDecadePercent" ) );
	widgets -> lblTextMysteryProgress	= GTK_WIDGET( gtk_builder_get_object( builder, "lblTextMysteryProgress" ) );
	widgets -> lblTextMysteryPercent	= GTK_WIDGET( gtk_builder_get_object( builder, "lblTextMysteryPercent" ) );

	// progressbars / levelbar
	widgets -> lblTextProgressTitle		= GTK_WIDGET( gtk_builder_get_object( builder, "lblTextProgressTitle" ) );

	widgets -> levelBar_decade			= GTK_WIDGET( gtk_builder_get_object( builder, "levelBar_decade" ) );
	widgets -> levelBar_mystery			= GTK_WIDGET( gtk_builder_get_object( builder, "levelBar_mystery" ) );

	gtk_label_set_text( GTK_LABEL( widgets -> lblTextDate ), retrunWeekdayName( todaysDate.tm_wday ) );
	gtk_label_set_text( GTK_LABEL( widgets -> lblTextLiturgicalCalendar ), retrunLiturgicalName( seasonFlag ) );

	if ( userDefinedFeast[0] != '\0' ) {
		gtk_label_set_text( GTK_LABEL( widgets -> lblTextFeast ), userDefinedFeast );
	} else {
		gtk_label_set_text( GTK_LABEL( widgets -> lblTextFeast ), retrunFeastDayName( feastFlag ) );
	}
}

int initialMystery( int weekdayNo ) { 
	int navigtionPosition[ ] = { 237, 0, 158, 237, 79, 158, 0 };

	if ( ( weekdayNo > 6 ) || ( weekdayNo < 0 ) ) { 
		weekdayNo = 0;
	}

	return navigtionPosition[ weekdayNo ];
}

void update_widgets_labels( rosary_db_t *rosary_db_struct, app_widgets *widgets ) { 
	int navigtionPosition	= widgets->navigtionPosition;

	/*
	* ER Query
	* */

	int rosaryPositionID	= rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].rosaryBeadID;
	int beadFK				= rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].beadIndex;
	int decadeFK			= rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].decadeIndex;
	int messageFK			= rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].messageIndex;
	int mysteryFK			= rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].mysteryIndex;
	int prayerFK			= rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].prayerIndex;
	int scriptureFK			= rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].scriptureIndex;
	int loopBody			= rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].loopBody;
	int smallbeadPercent	= rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].smallbeadPercent;
	int mysteryPercent		= rosary_db_struct -> rosaryBead_dbArray[ navigtionPosition ].mysteryPercent;

	char *beadType			= rosary_db_struct -> bead_dbArray[ beadFK ].beadType;
	char *decadeName		= rosary_db_struct -> decade_dbArray[ decadeFK ].decadeName;
	char *decadeInfo		= rosary_db_struct -> decade_dbArray[ decadeFK ].decadeInfo;
	char *mesageText		= rosary_db_struct -> message_dbArray[ messageFK ].mesageText;
	char *mysteryName		= rosary_db_struct -> mystery_dbArray[ mysteryFK ].mysteryName;
	char *scriptureText		= rosary_db_struct -> scripture_dbArray[ scriptureFK ].scriptureText;
	char *prayerText		= rosary_db_struct -> prayer_dbArray[ prayerFK ].prayerText;

	/*
	* Calculate percentages
	* */
	double smallbeadDouble;
	int sectionWhole;
	char *progressLabel;

	if ( loopBody == 1 ) { 
		sectionWhole	= 10;
		smallbeadDouble = ( double )smallbeadPercent / ( double )sectionWhole;
		progressLabel	= "rosary body";
	} else { 
		if( ( prayerFK == 7 ) || ( prayerFK == 8 ) ) { 
		sectionWhole	= 10; // not really, it is a placeholder
		smallbeadDouble = ( double )smallbeadPercent / ( double )sectionWhole;
		progressLabel	= "conclusion prayers";
	} else { 
		sectionWhole = 7;
		smallbeadDouble = ( double )smallbeadPercent / ( double )sectionWhole;
		progressLabel	= "introduction prayers";
	}
	}

	if ( smallbeadDouble < 0.01 ) { 
		smallbeadDouble = 0.00;
	}
	if ( smallbeadDouble > 1.00 ) { 
		smallbeadDouble = 1.00;
	}
	double smallbeadPercentDouble = smallbeadDouble * 100.0;

	double mysteryDouble = ( double )mysteryPercent / 50.0;
	if ( mysteryDouble < 0.01 ) { 
		mysteryDouble = 0.00;
	}
	if ( mysteryDouble > 1.00 ) { 
		mysteryDouble = 1.00;
	}
	double mysteryPercentDouble = mysteryDouble * 100.0;

	/*
	* Update Label Strings
	* */

	// Readings
	gtk_label_set_text( GTK_LABEL( widgets -> lblTextMystery ),		mysteryName );
	gtk_label_set_text( GTK_LABEL( widgets -> lblTextDecade ),		decadeName );
	gtk_label_set_text( GTK_LABEL( widgets -> lblTextDecadeMessage ), mesageText );
	gtk_label_set_text( GTK_LABEL( widgets -> lblTextBackground ),	decadeInfo );
	gtk_label_set_text( GTK_LABEL( widgets -> lblTextScripture ),	scriptureText );
	gtk_label_set_text( GTK_LABEL( widgets -> lblTextPrayer ),		prayerText );
	gtk_label_set_text( GTK_LABEL( widgets -> lblTextBeadType ),	beadType );

	// Decade
	gchar *str_smallbeadPercentDouble = g_strdup_printf( "%.0f %%", smallbeadPercentDouble ); // 0 decimal places
	gtk_label_set_text( GTK_LABEL( widgets -> lblTextDecadePercent ), str_smallbeadPercentDouble );

	gchar *str_smallbeadPercent = g_strdup_printf( "%d / %d", smallbeadPercent, sectionWhole );
	gtk_label_set_text( GTK_LABEL( widgets -> lblTextDecadeProgress ), str_smallbeadPercent );

	// Mystery
	gchar *str_mysteryPercentDouble = g_strdup_printf( "%.0f %%", mysteryPercentDouble ); // 0 decimal places
	gtk_label_set_text( GTK_LABEL( widgets -> lblTextMysteryPercent ), str_mysteryPercentDouble );

	gchar *str_mysteryPercent = g_strdup_printf( "%d / 50", mysteryPercent );
	gtk_label_set_text( GTK_LABEL( widgets -> lblTextMysteryProgress ), str_mysteryPercent );

	// Position
	gchar *str_rosaryPositionID = g_strdup_printf( "%d / 315", rosaryPositionID );
	gtk_label_set_text( GTK_LABEL( widgets -> lblTextBeadNo ), str_rosaryPositionID );

	// clear tmp char allocations
	g_free( str_smallbeadPercentDouble );
	g_free( str_smallbeadPercent );
	g_free( str_mysteryPercentDouble );
	g_free( str_mysteryPercent );
	g_free( str_rosaryPositionID );

	/*
	* Update Level Bar
	* */

	gtk_label_set_text( GTK_LABEL( widgets -> lblTextProgressTitle ), progressLabel );
	gtk_level_bar_set_value( GTK_LEVEL_BAR( widgets -> levelBar_decade ), smallbeadDouble );
	gtk_level_bar_set_value( GTK_LEVEL_BAR( widgets -> levelBar_mystery ), mysteryDouble );
}

void updateFeastDisplayStruct( feast_db_t *feast_db_struct, displayFeastVariables_t *queryFeastViewStruct, int todayDay, int todayMonth ) {
	int feastDay	= 0,
		feastMonth	= 0,
		counter		= 0;
	int feastID;
	char *feastName, *monthName;

	while ( ( todayDay != feastDay ) && ( todayMonth != feastMonth ) ) {
		feastDay = feast_db_struct		-> feast_dbArray[ counter ].feastDay;
		feastMonth = feast_db_struct	-> feast_dbArray[ counter ].feastMonth;
		counter++;
	}

	if ( ( todayDay == feastDay ) && ( todayMonth == feastMonth ) ) {
		counter--;

		feastID = feast_db_struct	-> feast_dbArray[ counter ].feastID;
		feastDay = feast_db_struct	-> feast_dbArray[ counter ].feastDay;
		feastMonth = feast_db_struct -> feast_dbArray[ counter ].feastMonth;

		feastName = feast_db_struct	-> feast_dbArray[ counter ].feastName;
		monthName = feast_db_struct	-> feast_dbArray[ counter ].monthName;

		// int's
		queryFeastViewStruct -> feastID		= feastID;
		queryFeastViewStruct -> feastDay	= feastDay;
		queryFeastViewStruct -> feastMonth	= feastMonth;

		// strings
		strcpy( queryFeastViewStruct -> feastName, feastName );
		strcpy( queryFeastViewStruct -> monthName, monthName );
	} else {
		// Populate queryFeastViewStruct with dummy values
		// int's
		queryFeastViewStruct -> feastID		= 0;
		queryFeastViewStruct -> feastDay	= 0;
		queryFeastViewStruct -> feastMonth	= 0;

		// strings
		strcpy( queryFeastViewStruct -> feastName, "" );
		strcpy( queryFeastViewStruct -> monthName, "" );

	}

}