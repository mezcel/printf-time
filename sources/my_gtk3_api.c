/*
 * my_glade_api.c
 * */

#include "../sources/my_calendar.c"
#include "../headers/my_gtk3_api.h"

/*
 * Local Scope
 * */

// ER Database Structs
// I made them global for easy access between OOP Gtk, and Procedural main.c
// since its source data is from an external CSV file, its security is good enough

rosaryBead_t *rosaryBead_record_field = NULL;
bead_t *bead_record_field = NULL;
book_t *book_record_field = NULL;
decade_t *decade_record_field = NULL;
message_t *message_record_field = NULL;
mystery_t *mystery_record_field = NULL;
prayer_t *prayer_record_field = NULL;
scripture_t *scripture_record_field = NULL;

rosaryBead_t rosaryBead_dbArray[317];
bead_t bead_dbArray[9];
book_t book_dbArray[17];
decade_t decade_dbArray[22];
message_t message_dbArray[22];
mystery_t mystery_dbArray[7];
prayer_t prayer_dbArray[11];
scripture_t scripture_dbArray[202];

 /*
 * Header API Scope Functions
 * */

void initializeLabelPointers(GtkBuilder *builder, GtkWidget *window, app_widgets *widgets) {
	struct MyDateStruct todaysDate = setTodaysDateStruct();

	// labels
	widgets -> lblTextDate = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextDate"));

	widgets -> lblTextMystery = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextMystery"));
	widgets -> lblTextDecade = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextDecade"));
	widgets -> lblTextDecadeMessage = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextDecadeMessage"));
	widgets -> lblTextBackground = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextBackground"));
	widgets -> lblTextScripture = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextScripture"));
	widgets -> lblTextPrayer = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextPrayer"));
	widgets -> lblTextBeadType = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextBeadType"));
	widgets -> lblTextBeadNo = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextBeadNo"));
	widgets -> lblTextLiturgicalCalendar = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextLiturgicalCalendar"));
	widgets -> lblTextFeast = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextFeast"));

	widgets -> lblTextDecadeProgress = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextDecadeProgress"));
	widgets -> lblTextDecadePercent = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextDecadePercent"));
	widgets -> lblTextMysteryProgress = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextMysteryProgress"));
	widgets -> lblTextMysteryPercent = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextMysteryPercent"));

	widgets -> lblTextLiturgicalCalendar = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextLiturgicalCalendar"));
	widgets -> lblTextFeast = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextFeast"));
	widgets -> lblTextLiturgicalCalendar = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextLiturgicalCalendar"));
	widgets -> lblTextFeast = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextFeast"));

	widgets -> lblTextLiturgicalCalendar = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextLiturgicalCalendar"));
	widgets -> lblTextFeast = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextFeast"));

	// progressbars / levelbar
	widgets -> levelBar_decade = GTK_WIDGET(gtk_builder_get_object(builder, "levelBar_decade"));
	widgets -> levelBar_mystery = GTK_WIDGET(gtk_builder_get_object(builder, "levelBar_mystery"));

    gtk_label_set_text(GTK_LABEL(widgets->lblTextDate), todaysDate.weekdayName);
}

int initialMystery(int weekdayNo) {
	int navigtionPosition[] = {237, 0, 158, 237, 79, 158, 0};

	if ( (weekdayNo > 6) || (weekdayNo < 0) ) {
		weekdayNo = 0;
	}

	return navigtionPosition[weekdayNo];
}

void update_widgets_labels(app_widgets *widgets) {
	int navigtionPosition = widgets->navigtionPosition;

	/*
	 * ER Query
	 * */

	int rosaryPositionID = rosaryBead_dbArray[navigtionPosition].rosaryBeadID;
	int beadFK = rosaryBead_dbArray[navigtionPosition].beadIndex;
	int decadeFK = rosaryBead_dbArray[navigtionPosition].decadeIndex;
	int messageFK = rosaryBead_dbArray[navigtionPosition].messageIndex;
	int mysteryFK = rosaryBead_dbArray[navigtionPosition].mysteryIndex;
	int prayerFK = rosaryBead_dbArray[navigtionPosition].prayerIndex;
	int scriptureFK = rosaryBead_dbArray[navigtionPosition].scriptureIndex;
	//int loopBody = rosaryBead_dbArray[navigtionPosition].loopBody;
	int smallbeadPercent = rosaryBead_dbArray[navigtionPosition].smallbeadPercent;
	int mysteryPercent = rosaryBead_dbArray[navigtionPosition].mysteryPercent;

	char *beadType = bead_dbArray[beadFK].beadType;
	char *decadeName = decade_dbArray[decadeFK].decadeName;
	char *decadeInfo = decade_dbArray[decadeFK].decadeInfo;
	char *mesageText = message_dbArray[messageFK].mesageText;
	char *mysteryName = mystery_dbArray[mysteryFK].mysteryName;
	char *scriptureText = scripture_dbArray[scriptureFK].scriptureText;
	char *prayerText = prayer_dbArray[prayerFK].prayerText;
	/*int decadeNo = decade_dbArray[decadeFK].decadeNo;
	int mysteryNo = mystery_dbArray[mysteryFK].mysteryNo;*/

	/*
	 * Calculate percentages
	 * */

	double smallbeadDouble = (double)smallbeadPercent / 10.0;
	double smallbeadPercentDouble = smallbeadDouble * 100.0;

	double mysteryDouble = (double)mysteryPercent / 50.0;
	double mysteryPercentDouble = mysteryDouble * 100.0;

	/*
	 * Update Label Strings
	 * */

	// Readings
	gtk_label_set_text(GTK_LABEL(widgets->lblTextMystery), mysteryName);
	gtk_label_set_text(GTK_LABEL(widgets->lblTextDecade), decadeName);
	gtk_label_set_text(GTK_LABEL(widgets->lblTextDecadeMessage), mesageText);
	gtk_label_set_text(GTK_LABEL(widgets->lblTextBackground), decadeInfo);
	gtk_label_set_text(GTK_LABEL(widgets->lblTextScripture), scriptureText);
	gtk_label_set_text(GTK_LABEL(widgets->lblTextPrayer), prayerText);
	gtk_label_set_text(GTK_LABEL(widgets->lblTextBeadType), beadType);

	// Decade
	gchar *str_smallbeadPercentDouble = g_strdup_printf("%.1f %%", smallbeadPercentDouble); // 1 decimal place
	gtk_label_set_text(GTK_LABEL(widgets->lblTextDecadePercent), str_smallbeadPercentDouble);

	gchar *str_smallbeadPercent = g_strdup_printf("%d / 10", smallbeadPercent);
	gtk_label_set_text(GTK_LABEL(widgets->lblTextDecadeProgress), str_smallbeadPercent);

	// Mystery
	gchar *str_mysteryPercentDouble = g_strdup_printf("%.1f %%", mysteryPercentDouble); // 1 decimal place
	gtk_label_set_text(GTK_LABEL(widgets->lblTextMysteryPercent), str_mysteryPercentDouble);

	gchar *str_mysteryPercent = g_strdup_printf("%d / 50", mysteryPercent);
	gtk_label_set_text(GTK_LABEL(widgets->lblTextMysteryProgress), str_mysteryPercent);

	// Position
	gchar *str_rosaryPositionID = g_strdup_printf("%d / 315", rosaryPositionID);
	gtk_label_set_text(GTK_LABEL(widgets->lblTextBeadNo), str_rosaryPositionID);

	// Calendar
	gtk_label_set_text(GTK_LABEL(widgets->lblTextLiturgicalCalendar), "u/c");
	gtk_label_set_text(GTK_LABEL(widgets->lblTextFeast), "u/c");

	// clear tmp char allocations
	g_free(str_smallbeadPercentDouble);
	g_free(str_smallbeadPercent);
	g_free(str_mysteryPercentDouble);
	g_free(str_mysteryPercent);
	g_free(str_rosaryPositionID);

	/*
	 * Update Level Bar
	 * */

	gtk_level_bar_set_value(GTK_LEVEL_BAR(widgets->levelBar_decade), smallbeadDouble);
	gtk_level_bar_set_value(GTK_LEVEL_BAR(widgets->levelBar_mystery), mysteryDouble);

}
