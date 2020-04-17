/*
 * my_gtk3_api.h
 * */

#ifndef MY_GTK3_API
#define MY_GTK3_API

/*
 * Data Structures
 * */

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
	char feastName[80];
	int feastDay;
	int feastMonth;
	char monthName[40];
} displayFeastVariables_t;

/*
 * Prototypes
 * */

int initialMystery( int weekdayNo );
int returnIndexCount ( char *jsonFilePath  );

void initializeLabelPointers( GtkBuilder *builder, GtkWidget *window, app_widgets *widgets, char *userDefinedFeast );
void update_widgets_labels( rosary_db_t *rosary_db_struct, app_widgets *widgets );
void updateFeastDisplayStruct( feast_db_t *feast_db_struct, displayFeastVariables_t *queryFeastViewStruct, int todayDay, int todayMonth, int recordCount );

#endif
