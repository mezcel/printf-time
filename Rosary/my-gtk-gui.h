/*
 * my-gtk-gui.h
 * dependancies: my-csv-parser.h
 * called by: main.c
 * compile: gcc -Wall -o "mainGtk" "mainGtk.c" `pkg-config --cflags --libs gtk+-2.0`
 * */

// Gtk prototypes
static int count = 0;

void closeApp(GtkWidget *button, gpointer data);
void changeLabel(GtkWidget *button, displayVariables_t *queryViewStruct);
void initGtkWindow(displayVariables_t queryViewStruct);

// Gtk Functions

void closeApp(GtkWidget *button, gpointer data) {
	gtk_main_quit();
}

void changeLabel(GtkWidget *button, displayVariables_t *queryViewStruct) {

	int rosaryPositionID = queryViewStruct->rosaryPositionID;
	int smallbeadPercent = queryViewStruct->smallbeadPercent;
	int mysteryPercent = queryViewStruct->mysteryPercent;

	char rosaryPositionIDChar[sizeof(count)];
	char smallbeadPercentChar[sizeof(count)];
	char mysteryPercentChar[sizeof(count)];

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
	gtk_window_set_default_size(GTK_WINDOW(window), 1000,800);

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

	queryViewStruct.lblTextMystery = gtk_label_new(" ");
	queryViewStruct.lblTextDecade = gtk_label_new(" ");
	queryViewStruct.lblTextDecadeMessage = gtk_label_new(" ");
	queryViewStruct.lblTextBackground = gtk_label_new(" ");
	queryViewStruct.lblTextScripture = gtk_label_new(" ");
	queryViewStruct.lblTextPrayer = gtk_label_new(" ");
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
