/*
 * my_gtk3_api.h
 * */

#ifndef MY_GTK3_API
#define MY_GTK3_API

/*
 * Data Structures
 * */

/* Global struct variables used to populate GTK widgets */
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

/* Struct containing feast day information */
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

/* Inputs a week day 0-6 number Sun-Sat. Return starting position Rosary Bead Position PK */
int initialMystery( int weekdayNo );

/* Return the number of index keys contained within a JSON DB file. Used for the Fast Day JSON db */
int returnIndexCount ( char *jsonFilePath  );

/* Initial Gtk widget values */
void initializeLabelPointers( GtkBuilder *builder, GtkWidget *window, app_widgets *widgets, char *userDefinedFeast );

/* Update variable values contained in the "app_widgets" struct */
void update_widgets_labels( rosary_db_t *rosary_db_struct, app_widgets *widgets );

/* Render updated text value displayed in the GTK Window UI */
void updateFeastDisplayStruct(
    feast_db_t *feast_db_struct,
    displayFeastVariables_t *queryFeastViewStruct,
    int todayDay, int todayMonth, int recordCount );

#endif
