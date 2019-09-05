/*
 * my_gtk3_api.h
 * */

#ifndef MY_GLADE_API
#define MY_GLADE_API

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
	GtkWidget *levelBar_decade;
	GtkWidget *levelBar_mystery;
} app_widgets;

/*
 * Prototypes
 * */

void initializeLabelPointers(GtkBuilder *builder, GtkWidget *window, app_widgets *widgets);
int initialMystery(int weekdayNo);
void update_widgets_labels(app_widgets *widgets);

#endif
