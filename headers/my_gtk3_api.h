/*
 * my_gtk3_api.h
 * */

#ifndef MY_GTK3_API
#define MY_GTK3_API

/*
 * Data Structures
 * */

//#include "../headers/my_csv_structs.h"

typedef struct {
	// accumulator var
	int navigtionPosition;

	// labels
	GtkWidget *lblTextDate;

	GtkWidget *lblTextMystery;
	GtkWidget *lblTextDecade;
	GtkWidget *lblTextDecadeMessage;
	GtkWidget *lblTextBackground;
	GtkWidget *lblTextScripture;
	GtkWidget *lblTextPrayer;
	GtkWidget *lblTextBeadType;
	GtkWidget *lblTextBeadNo;

	GtkWidget *lblTextDecadePercent;
	GtkWidget *lblTextDecadeProgress;
	GtkWidget *lblTextMysteryPercent;
	GtkWidget *lblTextMysteryProgress;

	GtkWidget *lblTextLiturgicalCalendar;
	GtkWidget *lblTextFeast;

	// level bars
	GtkWidget *lblTextProgressTitle;
	GtkWidget *levelBar_decade;
	GtkWidget *levelBar_mystery;
} app_widgets;

typedef struct displayFeastVariables_struct {
	int feastID;
	char feastName[40];
	int feastDay;
	int feastMonth;
	char monthName[40];
} displayFeastVariables_t;

/*
 * Prototypes
 * */

void initializeLabelPointers( GtkBuilder *builder, GtkWidget *window, app_widgets *widgets, char *userDefinedFeast );
int initialMystery( int weekdayNo );
void update_widgets_labels( rosary_db_t *rosary_db_struct, app_widgets *widgets );
void updateFeastDisplayStruct( feast_db_t *feast_db_struct, displayFeastVariables_t *queryFeastViewStruct, int todayDay, int todayMonth );

#endif
