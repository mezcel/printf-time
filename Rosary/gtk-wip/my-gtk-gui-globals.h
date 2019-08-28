/*
 * my-gtk-gui-globals.h (UI trial ane error testing)
 * dependancies: ../my-csv-parser.h
 * called by: mainGtk-globals.c
 * */

typedef struct displayVariables_struct {
	int rosaryPositionID;
	int beadFK;
	int decadeFK;
	int messageFK;
	int mysteryFK;
	int prayerFK;
	int scriptureFK;
	int loopBody;
	int smallbeadPercent;
	int mysteryPercent;

	char beadType[40];
	char decadeName[800];
	char decadeInfo[800];
	char mesageText[150];
	char mysteryName[100];
	char scriptureText[500];
	char prayerText[1250];

	int decadeNo;
	int mysteryNo;

	// gtk objects
	GtkWidget *lblTextMystery;
	GtkWidget *lblTextDecade;
	GtkWidget *lblTextDecadeMessage;
	GtkWidget *lblTextBackground;
	GtkWidget *lblTextScripture;
	GtkWidget *lblTextPrayer;
	GtkWidget *lblTextBeadType;
	GtkWidget *lblTextBeadNo;
	GtkWidget *lblTextDecadeProgress;
	GtkWidget *lblTextMysteryProgress;

} displayVariables_t;

int weekdayNo = 0;
int navigtionPosition = 0;

// Name my strtuct variables
rosaryBead_t *rosaryBead_record_field = NULL;
rosaryBead_t rosaryBead_dbArray[317];

bead_t *bead_record_field = NULL;
bead_t bead_dbArray[9];

book_t *book_record_field = NULL;
book_t book_dbArray[17];

decade_t *decade_record_field = NULL;
decade_t decade_dbArray[22];

message_t *message_record_field = NULL;
message_t message_dbArray[22];

mystery_t *mystery_record_field = NULL;
mystery_t mystery_dbArray[7];

prayer_t *prayer_record_field = NULL;
prayer_t prayer_dbArray[11];

scripture_t *scripture_record_field = NULL;
scripture_t scripture_dbArray[202];

//struct displayVariables_struct displayVariables_t;
displayVariables_t queryViewStruct;

// Gtk prototypes
int returnDayOfWeekFlag();
int initialMystery(int weekdayNo);
void updateDisplayVariablesStruct( displayVariables_t *queryViewStruct, int navigtionPosition);

// Callbacks
void closeApp(GtkWidget *button, gpointer data);
void changeLabel(GtkWidget *button, displayVariables_t *queryViewStruct);
void initGtkWindow(displayVariables_t queryViewStruct);

//

int returnDayOfWeekFlag() {
	time_t rawtime;
	struct tm *timeinfo;

	int year = 2019;
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

void updateDisplayVariablesStruct(displayVariables_t *queryViewStruct, int navigtionPosition) {

	int rosaryPositionID = 0, beadFK = 0, decadeFK = 0, messageFK = 0, mysteryFK = 0, prayerFK = 0;
	int scriptureFK = 0, loopBody = 0, smallbeadPercent = 0, mysteryPercent = 0;
	int decadeNo = 0, mysteryNo = 0;

	char *beadType, *decadeName, *decadeInfo, *mesageText, *mysteryName;
	char *scriptureText, *prayerText;

	rosaryPositionID = rosaryBead_dbArray[navigtionPosition].rosaryBeadID;
	beadFK = rosaryBead_dbArray[navigtionPosition].beadIndex;
	decadeFK = rosaryBead_dbArray[navigtionPosition].decadeIndex;
	messageFK = rosaryBead_dbArray[navigtionPosition].messageIndex;
	mysteryFK = rosaryBead_dbArray[navigtionPosition].mysteryIndex;
	prayerFK = rosaryBead_dbArray[navigtionPosition].prayerIndex;
	scriptureFK = rosaryBead_dbArray[navigtionPosition].scriptureIndex;
	loopBody = rosaryBead_dbArray[navigtionPosition].loopBody;
	smallbeadPercent = rosaryBead_dbArray[navigtionPosition].smallbeadPercent;
	mysteryPercent = rosaryBead_dbArray[navigtionPosition].mysteryPercent;

	beadType = bead_dbArray[beadFK].beadType;
	decadeName = decade_dbArray[decadeFK].decadeName;
	decadeInfo = decade_dbArray[decadeFK].decadeInfo;
	mesageText = message_dbArray[messageFK].mesageText;
	mysteryName = mystery_dbArray[mysteryFK].mysteryName;
	scriptureText = scripture_dbArray[scriptureFK].scriptureText;
	prayerText = prayer_dbArray[prayerFK].prayerText;

	decadeNo = decade_dbArray[decadeFK].decadeNo;
	mysteryNo = mystery_dbArray[mysteryFK].mysteryNo;

	queryViewStruct -> rosaryPositionID = rosaryPositionID;
	queryViewStruct -> beadFK = beadFK;
	queryViewStruct -> decadeFK = decadeFK;
	queryViewStruct -> messageFK = messageFK;
	queryViewStruct -> mysteryFK = mysteryFK;
	queryViewStruct -> prayerFK = prayerFK;
	queryViewStruct -> scriptureFK = scriptureFK;
	queryViewStruct -> loopBody = loopBody;
	queryViewStruct -> smallbeadPercent = smallbeadPercent;
	queryViewStruct -> mysteryPercent = mysteryPercent;

	// struct strings
	strcpy( queryViewStruct -> beadType, beadType);
	strcpy( queryViewStruct -> decadeName, decadeName);
	strcpy( queryViewStruct -> decadeInfo, decadeInfo);
	strcpy( queryViewStruct -> mesageText, mesageText);
	strcpy( queryViewStruct -> mysteryName, mysteryName);
	strcpy( queryViewStruct -> scriptureText, scriptureText);
	strcpy( queryViewStruct -> prayerText, prayerText);

	queryViewStruct -> decadeNo = decadeNo;
	queryViewStruct -> mysteryNo = mysteryNo;

}

// Gtk Callbacks

void closeApp(GtkWidget *button, gpointer data) {
	gtk_main_quit();
}

void changeLabel(GtkWidget *button, displayVariables_t *queryViewStruct) {
	navigtionPosition++;
	updateDisplayVariablesStruct(queryViewStruct, navigtionPosition);

	int rosaryPositionID = queryViewStruct->rosaryPositionID;
	int smallbeadPercent = queryViewStruct->smallbeadPercent;
	int mysteryPercent = queryViewStruct->mysteryPercent;

	char rosaryPositionIDChar[sizeof(rosaryPositionID)];
	char smallbeadPercentChar[sizeof(smallbeadPercent)];
	char mysteryPercentChar[sizeof(mysteryPercent)];

	sprintf(rosaryPositionIDChar, "%d", rosaryPositionID);
	sprintf(smallbeadPercentChar, "%d", smallbeadPercent);
	sprintf(mysteryPercentChar, "%d", mysteryPercent);

	gtk_label_set_text(GTK_LABEL(queryViewStruct->lblTextMystery), queryViewStruct->mysteryName);
	gtk_label_set_text(GTK_LABEL(queryViewStruct->lblTextDecade), queryViewStruct->decadeName);
	gtk_label_set_text(GTK_LABEL(queryViewStruct->lblTextDecadeMessage), queryViewStruct->decadeInfo);
	gtk_label_set_text(GTK_LABEL(queryViewStruct->lblTextBackground), queryViewStruct->mesageText);
	gtk_label_set_text(GTK_LABEL(queryViewStruct->lblTextScripture), queryViewStruct->scriptureText);
	gtk_label_set_text(GTK_LABEL(queryViewStruct->lblTextPrayer), queryViewStruct->prayerText);
	gtk_label_set_text(GTK_LABEL(queryViewStruct->lblTextBeadType), queryViewStruct->beadType); // bead type
	gtk_label_set_text(GTK_LABEL(queryViewStruct->lblTextBeadNo), rosaryPositionIDChar);
	gtk_label_set_text(GTK_LABEL(queryViewStruct->lblTextDecadeProgress), smallbeadPercentChar);
	gtk_label_set_text(GTK_LABEL(queryViewStruct->lblTextMysteryProgress), mysteryPercentChar);



}

void initGtkWindow(displayVariables_t queryViewStruct) {

	// GtkWidget boxes
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *hboxTopContainerColumn = gtk_vbox_new(FALSE, 1);

	// body
	GtkWidget *hboxReadingRow = gtk_hbox_new(FALSE, 1);
	GtkWidget *vboxLabelColumn = gtk_vbox_new(FALSE, 1);
	GtkWidget *vboxTextColumn = gtk_vbox_new(FALSE, 1);

	// progress
	GtkWidget *hboxProgressRow = gtk_hbox_new(FALSE, 1);
	GtkWidget *vboxDecadeProgressColumn = gtk_vbox_new(TRUE, 1);
	GtkWidget *vboxMysteryProgressColumn = gtk_vbox_new(TRUE, 1);

	// buttons
	GtkWidget *hboxButtonRow = gtk_hbox_new(FALSE, 1);
	GtkWidget *vboxLeftButtonColumn = gtk_vbox_new(FALSE, 1);
	GtkWidget *vboxBeadCounterColumn = gtk_vbox_new(FALSE, 1);
	GtkWidget *vboxRightButtonColumn = gtk_vbox_new(FALSE, 1);

	// window
	gtk_window_set_title(GTK_WINDOW(window), "C/CSV Rosary");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	//gtk_window_set_default_size(GTK_WINDOW(window), 1000,800);

	GdkGeometry gdkGeometry;
    gdkGeometry.min_width = 60;
    gdkGeometry.min_height = 60;
    gtk_window_set_geometry_hints (GTK_WINDOW (window), window, &gdkGeometry, GDK_HINT_MIN_SIZE);

	// Define Labels
	GtkWidget *lblNameMystery = gtk_label_new("Mystery:");
	GtkWidget *lblNameDecade = gtk_label_new("Decade:");
	GtkWidget *lblNameDecadeMessage = gtk_label_new("Decade Message:");
	GtkWidget *lblNameBackground = gtk_label_new("Background:");
	GtkWidget *lblNameScripture = gtk_label_new("Scripture:");
	GtkWidget *lblNamePrayer = gtk_label_new("Prayer:");
	GtkWidget *lblNameBeadType = gtk_label_new("Bead Type:");
	/*GtkWidget *lblNameBeadNo = gtk_label_new("Bead No:");
	GtkWidget *lblNameDecadeProgress = gtk_label_new("Decade Progress:");
	GtkWidget *lblNameMysteryProgress = gtk_label_new("Mystery Progress:");*/

	// left justify lables
	gtk_misc_set_alignment(GTK_MISC(lblNameMystery), 0.0f, 0.0f);
	gtk_misc_set_alignment(GTK_MISC(lblNameDecade), 0.0f, 0.0f);
	gtk_misc_set_alignment(GTK_MISC(lblNameDecadeMessage), 0.0f, 0.0f);
	gtk_misc_set_alignment(GTK_MISC(lblNameBackground), 0.0f, 0.0f);
	gtk_misc_set_alignment(GTK_MISC(lblNameScripture), 0.0f, 0.0f);
	gtk_misc_set_alignment(GTK_MISC(lblNamePrayer), 0.0f, 0.0f);
	gtk_misc_set_alignment(GTK_MISC(lblNameBeadType), 0.0f, 0.0f);

	queryViewStruct.lblTextMystery = gtk_label_new(" "); //gtk_label_set_line_wrap(GTK_LABEL(queryViewStruct.lblTextMystery), TRUE);
	queryViewStruct.lblTextDecade = gtk_label_new(" "); //gtk_label_set_line_wrap(GTK_LABEL(queryViewStruct.lblTextDecade), TRUE);
	queryViewStruct.lblTextDecadeMessage = gtk_label_new(" "); //gtk_label_set_line_wrap(GTK_LABEL(queryViewStruct.lblTextDecadeMessage), TRUE);
	queryViewStruct.lblTextBackground = gtk_label_new(" "); //gtk_label_set_line_wrap(GTK_LABEL(queryViewStruct.lblTextBackground), TRUE);
	queryViewStruct.lblTextScripture = gtk_label_new(" "); //gtk_label_set_line_wrap(GTK_LABEL(queryViewStruct.lblTextScripture), TRUE);
	queryViewStruct.lblTextPrayer = gtk_label_new(" "); //gtk_label_set_line_wrap(GTK_LABEL(queryViewStruct.lblTextPrayer), TRUE);

		gtk_misc_set_alignment (GTK_MISC (queryViewStruct.lblTextPrayer), 0, 0);
		gtk_label_set_line_wrap (GTK_LABEL (queryViewStruct.lblTextPrayer), TRUE);
		gtk_label_set_use_markup (GTK_LABEL (queryViewStruct.lblTextPrayer), TRUE);
		gtk_container_set_border_width (GTK_CONTAINER (queryViewStruct.lblTextPrayer), 100);

	queryViewStruct.lblTextBeadType = gtk_label_new(" ");
	queryViewStruct.lblTextBeadNo = gtk_label_new(" ");
	queryViewStruct.lblTextDecadeProgress = gtk_label_new("0/10");
	queryViewStruct.lblTextMysteryProgress = gtk_label_new("0/50");

	// Define Buttons
	GtkWidget *backButton = gtk_button_new_with_label("backButton / close");
	GtkWidget *nextButton = gtk_button_new_with_label("nextButton / change text");

	// Header Col
	gtk_box_pack_start( GTK_BOX(hboxReadingRow), vboxLabelColumn, FALSE, FALSE, 10 );
	gtk_box_pack_start( GTK_BOX(vboxLabelColumn), lblNameMystery, FALSE, FALSE, 2 );
	gtk_box_pack_start( GTK_BOX(vboxLabelColumn), lblNameDecade, FALSE, FALSE, 2 );
	gtk_box_pack_start( GTK_BOX(vboxLabelColumn), lblNameDecadeMessage, FALSE, FALSE, 2 );
	gtk_box_pack_start( GTK_BOX(vboxLabelColumn), lblNameBackground, FALSE, FALSE, 2 );
	gtk_box_pack_start( GTK_BOX(vboxLabelColumn), lblNameScripture, FALSE, FALSE, 2 );
	gtk_box_pack_start( GTK_BOX(vboxLabelColumn), lblNamePrayer, FALSE, FALSE, 2 );
	gtk_box_pack_start( GTK_BOX(vboxLabelColumn), lblNameBeadType, FALSE, FALSE, 2 );

	// Text Col

	gtk_box_pack_start( GTK_BOX(hboxReadingRow), vboxTextColumn, FALSE, FALSE, 10 );
	gtk_box_pack_start( GTK_BOX(vboxTextColumn), queryViewStruct.lblTextMystery, FALSE, FALSE, 2 );
	gtk_box_pack_start( GTK_BOX(vboxTextColumn), queryViewStruct.lblTextDecade, FALSE, FALSE, 2 );
	gtk_box_pack_start( GTK_BOX(vboxTextColumn), queryViewStruct.lblTextDecadeMessage, FALSE, FALSE, 2 );
	gtk_box_pack_start( GTK_BOX(vboxTextColumn), queryViewStruct.lblTextBackground, FALSE, FALSE, 2 );
	gtk_box_pack_start( GTK_BOX(vboxTextColumn), queryViewStruct.lblTextScripture, FALSE, FALSE, 2 );
	gtk_box_pack_start( GTK_BOX(vboxTextColumn), queryViewStruct.lblTextPrayer, FALSE, FALSE, 2 );
	gtk_box_pack_start( GTK_BOX(vboxTextColumn), queryViewStruct.lblTextBeadType, FALSE, FALSE, 2 );

	// Progress Row
	gtk_box_pack_start( GTK_BOX(hboxProgressRow), vboxDecadeProgressColumn, TRUE, TRUE, 10 );
		gtk_box_pack_start( GTK_BOX(vboxDecadeProgressColumn), queryViewStruct.lblTextDecadeProgress, TRUE, TRUE, 2 );
	gtk_box_pack_start( GTK_BOX(hboxProgressRow), vboxMysteryProgressColumn, TRUE, TRUE, 10 );
		gtk_box_pack_start( GTK_BOX(vboxMysteryProgressColumn), queryViewStruct.lblTextMysteryProgress, TRUE, TRUE, 2 );

	// Button Row
	gtk_box_pack_start( GTK_BOX(hboxButtonRow), vboxLeftButtonColumn, FALSE, FALSE, 10 );
		gtk_box_pack_start( GTK_BOX(vboxLeftButtonColumn), backButton, FALSE, FALSE, 2 );
	gtk_box_pack_start( GTK_BOX(hboxButtonRow), vboxBeadCounterColumn, TRUE, TRUE, 10 );
		gtk_box_pack_start( GTK_BOX(vboxBeadCounterColumn), queryViewStruct.lblTextBeadNo, TRUE, TRUE, 2 );
		gtk_box_pack_start( GTK_BOX(vboxBeadCounterColumn), queryViewStruct.lblTextBeadType, TRUE, TRUE, 2 );
	gtk_box_pack_start( GTK_BOX(hboxButtonRow), vboxRightButtonColumn, FALSE, FALSE, 10 );
		gtk_box_pack_start( GTK_BOX(vboxRightButtonColumn), nextButton, FALSE, FALSE, 2 );

	g_signal_connect( GTK_OBJECT(backButton), "clicked", GTK_SIGNAL_FUNC(closeApp), NULL);
	g_signal_connect( GTK_OBJECT(nextButton), "clicked", GTK_SIGNAL_FUNC(changeLabel), (gpointer*)&queryViewStruct );

	// Package objects in a col
	gtk_box_pack_start( GTK_BOX(hboxTopContainerColumn), hboxReadingRow, FALSE, FALSE, 10 );
	gtk_box_pack_start( GTK_BOX(hboxTopContainerColumn), hboxProgressRow, FALSE, FALSE, 10 );
	gtk_box_pack_start( GTK_BOX(hboxTopContainerColumn), hboxButtonRow, FALSE, FALSE, 10 );

	// attach everything into the window
	gtk_container_add( GTK_CONTAINER(window), hboxTopContainerColumn );
	gtk_widget_show_all(window);
	gtk_main();
}
