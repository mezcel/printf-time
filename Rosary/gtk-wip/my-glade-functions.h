int weekdayNo = 0;
int navigtionPosition = 0;
int beadNo = 0; // position accumulator

// ER Database Structs
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

// Widget Pointer Struct
typedef struct {
	int navigtionPosition; // accumulator

	GtkWidget *lblTextMystery;
	GtkWidget *lblTextDecade;
	GtkWidget *lblTextDecadeMessage;
	GtkWidget *lblTextBackground;
	GtkWidget *lblTextScripture;
	GtkWidget *lblTextPrayer;
	GtkWidget *lblTextBeadType;
	GtkWidget *lblTextDecadeProgress;
	GtkWidget *lblTextMysteryProgress;
	GtkWidget *lblTextBeadNo;
	GtkWidget *lblTextLiturgicalCalendar;
	GtkWidget *lblTextFeast;
} app_widgets;

// void initializeLabelPointers(GtkBuilder *builder, GtkWidget *window, app_widgets *widgets);
void initializeLabelPointers(GtkBuilder *builder, GtkWidget *window, app_widgets *widgets) {

	widgets -> lblTextMystery = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextMystery"));
	widgets -> lblTextDecade = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextDecade"));
	widgets -> lblTextDecadeMessage = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextDecadeMessage"));
	widgets -> lblTextBackground = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextBackground"));
	widgets -> lblTextScripture = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextScripture"));
	widgets -> lblTextPrayer = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextPrayer"));
	widgets -> lblTextBeadType = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextBeadType"));
	widgets -> lblTextDecadeProgress = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextDecadeProgress"));
	widgets -> lblTextMysteryProgress = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextMysteryProgress"));
	widgets -> lblTextBeadNo = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextBeadNo"));
	widgets -> lblTextLiturgicalCalendar = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextLiturgicalCalendar"));
	widgets -> lblTextFeast = GTK_WIDGET(gtk_builder_get_object(builder, "lblTextFeast"));
}

int returnDayOfWeekFlag() {
	time_t rawtime;
	struct tm *timeinfo;

	int year = 2019; // i need to come back to this, use system clock instead
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	timeinfo->tm_year = year - 1900;

	/* call mktime: timeinfo->tm_wday will be set */
	mktime ( timeinfo );

	return timeinfo->tm_wday;
}

int initialMystery(int weekdayNo) {

	int navigtionPosition = 0;

	switch (weekdayNo) {
		case 1: // mon joyful
			navigtionPosition = 0;
			break;

		case 2: // tues sorrowful
			navigtionPosition = 158;
			break;

		case 3: // wed glorious
			navigtionPosition = 237;
			break;

		case 4: // thurs Luminous
			navigtionPosition = 79;
			break;

		case 5: // fri sorrowful
			navigtionPosition = 158;
			break;

		case 6: // sat joyful
			navigtionPosition = 0;
			break;

		case 0: // sun glorious
			navigtionPosition = 237;
			break;

		default:
			navigtionPosition = 0;
	}

	return navigtionPosition;
}

void update_widgets_labels(app_widgets *widgets) {
	int navigtionPosition = widgets->navigtionPosition;

	// ER Query

	int rosaryPositionID = rosaryBead_dbArray[navigtionPosition].rosaryBeadID;
	int beadFK = rosaryBead_dbArray[navigtionPosition].beadIndex;
	int decadeFK = rosaryBead_dbArray[navigtionPosition].decadeIndex;
	int messageFK = rosaryBead_dbArray[navigtionPosition].messageIndex;
	int mysteryFK = rosaryBead_dbArray[navigtionPosition].mysteryIndex;
	int prayerFK = rosaryBead_dbArray[navigtionPosition].prayerIndex;
	int scriptureFK = rosaryBead_dbArray[navigtionPosition].scriptureIndex;
	int loopBody = rosaryBead_dbArray[navigtionPosition].loopBody;
	int smallbeadPercent = rosaryBead_dbArray[navigtionPosition].smallbeadPercent;
	int mysteryPercent = rosaryBead_dbArray[navigtionPosition].mysteryPercent;

	char *beadType = bead_dbArray[beadFK].beadType;
	char *decadeName = decade_dbArray[decadeFK].decadeName;
	char *decadeInfo = decade_dbArray[decadeFK].decadeInfo;
	char *mesageText = message_dbArray[messageFK].mesageText;
	char *mysteryName = mystery_dbArray[mysteryFK].mysteryName;
	char *scriptureText = scripture_dbArray[scriptureFK].scriptureText;
	char *prayerText = prayer_dbArray[prayerFK].prayerText;
	int decadeNo = decade_dbArray[decadeFK].decadeNo;
	int mysteryNo = mystery_dbArray[mysteryFK].mysteryNo;

	// Update Label Strings

	gtk_label_set_text(GTK_LABEL(widgets->lblTextMystery), mysteryName);
	gtk_label_set_text(GTK_LABEL(widgets->lblTextDecade), decadeName);
	gtk_label_set_text(GTK_LABEL(widgets->lblTextDecadeMessage), mesageText);
	gtk_label_set_text(GTK_LABEL(widgets->lblTextBackground), decadeInfo);
	gtk_label_set_text(GTK_LABEL(widgets->lblTextScripture), scriptureText);
	gtk_label_set_text(GTK_LABEL(widgets->lblTextPrayer), prayerText);
	gtk_label_set_text(GTK_LABEL(widgets->lblTextBeadType), beadType);

	gchar *str_smallbeadPercent = g_strdup_printf("%d / 10", smallbeadPercent);
	gtk_label_set_text(GTK_LABEL(widgets->lblTextDecadeProgress), str_smallbeadPercent);

	gchar *str_mysteryPercent = g_strdup_printf("%d / 50", mysteryPercent);
	gtk_label_set_text(GTK_LABEL(widgets->lblTextMysteryProgress), str_mysteryPercent);

	gchar *str_rosaryPositionID = g_strdup_printf("%d", rosaryPositionID);
	gtk_label_set_text(GTK_LABEL(widgets->lblTextBeadNo), str_rosaryPositionID);

	gtk_label_set_text(GTK_LABEL(widgets->lblTextLiturgicalCalendar), "u/c");
	gtk_label_set_text(GTK_LABEL(widgets->lblTextFeast), "u/c");

	g_free(str_smallbeadPercent);
	g_free(str_mysteryPercent);
	g_free(str_rosaryPositionID);
}

