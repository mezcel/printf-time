/*
 * my_glade_api.h
 * dependaency: ../my-csv-parser.h
 * */

#ifndef MY_GLADE_API
#define MY_GLADE_API

/*
 * Data Structures
 * */

// Widget Pointer Struct
typedef struct {
	int navigtionPosition; // accumulator

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
	GtkWidget *lblTextLiturgicalCalendar;
	GtkWidget *lblTextFeast;

	GtkWidget *lblTextDecadePercent;
	GtkWidget *lblTextDecadeProgress;
	GtkWidget *lblTextMysteryPercent;
	GtkWidget *lblTextMysteryProgress;

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
