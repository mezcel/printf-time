/*
 * mainGtk.c
 */

#ifdef _WIN32 // MinGW
	#include <windows.h>
	#include <stdio.h>
	#include <tchar.h>
#endif

#ifdef linux // Linux GCC v6+
	#include <stdlib.h>		// calloc()/realloc()/malloc(), system(), free()
	#include <stdio.h>
	#include <string.h>
	#include <sys/ioctl.h>	// ioctl(), TIOCGWINSZ
	#include <unistd.h> 	// STDOUT_FILENO

	/*
	 * sudo apt install libgtk2.0-dev
	 * gcc mainGtk.c `pkg-config --cflags --libs gtk+-2.0`
	 * */
	#include <gtk/gtk.h>
#endif

#include <time.h>				// time_t
#include "my-csv-parser.h"		// my own homework CSV parse functions & structs

// Prototypes //
void clearScreen(int isLinux);
void borderCharPrintF(char *charSymbol, int borderWidth);
void splashCoverPager(int weekdayNo, int isLinux);
void multiLinePrintF(char *labelChars, char *strIn, int desiredLineLength);
int returnDayOfWeekFlag();
int initialMystery(int weekdayNo);
int pressKeyContinue(int navigtionPosition, int isLinux);
void outputDisplay(char *mysteryName, char *decadeName, char *mesageText, char *decadeInfo, char *scriptureText, char *prayerText, char *beadType, int rosaryPositionID, int loopBody, int decadeNo, int smallbeadPercent, int mysteryPercent, int mysteryNo, int desiredDispLen);
void makeGtkWindow(int argc, char *argv[], char *mysteryName, char *decadeName, char *mesageText, char *decadeInfo, char *scriptureText, char *prayerText, char *beadType, int rosaryPositionID, int loopBody, int decadeNo, int smallbeadPercent, int mysteryPercent, int mysteryNo);

// Functions //
void clearScreen(int isLinux) {
	//system("@cls||clear");
	if (isLinux == 1) {
		system("clear"); // linux
	} else {
		system("@cls"); // win
	}
}

void borderCharPrintF(char *charSymbol, int borderWidth) {
	for (int i = 0; i < borderWidth; i++) {
		printf("%s", charSymbol);
	}
}

void splashCoverPage(int weekdayNo, int isLinux) {

	char * weekday[] = { "Sunday", "Monday", "Tuesday", "Wednesday",
							"Thursday", "Friday", "Saturday" };

	char * weekdayMystery[] = { "Glorious", "Joyful", "Sorrowful", "Glorious",
									"Luminous", "Sorrowful", "Joyful" };

	char *aboutString ="This is a scriptural rosary for the command line interface (CLI). This app reads from CSV text files arranged as ER database. It uses .h libraries which are default on most gcc installation. I made an additional library which will parse CSV text into an array of structs for ER db queries. Scriptural readings are quoted from The New American Bible, while additional included readings were curated from a variety of different rosary prayer guides.";

	clearScreen(isLinux); // clear cli

	char *titleLabel = " C/CSV Rosary ";
	int titleLabelLength = (int)strlen(titleLabel);
	borderCharPrintF("+", 100);
	printf("\n");
	borderCharPrintF("+", 3);
	printf(titleLabel);
	borderCharPrintF("+", (100 - (titleLabelLength + 3 )) );
	printf("\n");
	borderCharPrintF("+", 100);
	printf("\n");

	multiLinePrintF("\n About:\n\n\t", aboutString, 60);

	printf("\n\n Display:\n\n\tOptimal Terminal Display: (+25 rows) x (+100 cols) to Full Screen.\n");
	printf("\n User Controls:\n\n\t Press [b] to step 1 back");
	printf("\n\t Press [enter] to step 1 forward");
	printf("\n\t Press [q] to quit the app");
	printf("\n\n\n Today is a %s, therefore today's mystery is the %s Mystery.", weekday[weekdayNo], weekdayMystery[weekdayNo]);
	printf("\n press [enter] to continue");

	getchar(); // pause for char input
	clearScreen(isLinux); // clear cli
}

void multiLinePrintF(char *labelChars, char *strIn, int desiredLineLength) {
	int lineLength = (int)strlen(strIn);
	printf("%s", labelChars);

	if ( lineLength <= desiredLineLength) {
		printf("%s\n\t\t", strIn);

	} else {
		int inputLength = (int)strlen(strIn);
		char stringInput[inputLength]; // temp copy of string to manipulate
			strcpy(stringInput, strIn);
		char *delim = " ";
		char *parsedStringArray = strtok(stringInput, delim);
		int desiredLengthCounter = 0;
		int wordLength = 0;

		while (parsedStringArray != NULL) {
			wordLength = (int)strlen(parsedStringArray);
			desiredLengthCounter = desiredLengthCounter + wordLength;

			if (desiredLengthCounter < desiredLineLength) {
				printf("%s ", parsedStringArray);
			} else {
				printf("\n\t\t%s ", parsedStringArray);
				desiredLengthCounter = 0;
			}

			parsedStringArray = strtok(NULL, delim);
		}
	}
}

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

int pressKeyContinue(int navigtionPosition, int isLinux) {
	int c = getc(stdin);
	for (;;) {
		switch (c) {
			case '\n': // [enter] navigate 1 step forward
				clearScreen(isLinux);
				if (navigtionPosition < 315) {
					navigtionPosition++;
				} else {
					navigtionPosition = 0;
				}
				return navigtionPosition;
				break;

			case 'b': // navigate 1 step back
				if (navigtionPosition > 1) {
					navigtionPosition = navigtionPosition - 2;
				} else {
					navigtionPosition = 315;
				}
				return navigtionPosition;
				break;

			case 'q':
				printf("\n Quit App \n");
				return 316; //retun an integer greater than 315
				break;

			default: // no nav change
				return navigtionPosition - 1;

		}
	}
}

void outputDisplay(char *mysteryName, char *decadeName, char *mesageText, char *decadeInfo, char *scriptureText, char *prayerText, char *beadType, int rosaryPositionID, int loopBody, int decadeNo, int smallbeadPercent, int mysteryPercent, int mysteryNo, int desiredDispLen) {

	// header
	char *titleLabel = " C/CSV Rosary ";
	int titleLabelLength = (int)strlen(titleLabel);
	borderCharPrintF("+", 3);
	printf(titleLabel);
	borderCharPrintF("+", desiredDispLen + 30);

	// body
	printf("\n\n Mystery:\t%s", mysteryName);
	printf("\n Decade:\t%s", decadeName);
	multiLinePrintF("\n\t\t", mesageText, desiredDispLen);
	multiLinePrintF("\n Background:\t", decadeInfo, desiredDispLen);
	multiLinePrintF("\n\n Scripture:\t", scriptureText, desiredDispLen);
	multiLinePrintF("\n Prayer:\t", prayerText, desiredDispLen);
	printf("\n Bead Type:\t%s\n", beadType);

	// footer
	char *footerLabel = " Rosary Progress ";
	int footerLabelLength = (int)strlen(footerLabel);
	int diffLabelLength = desiredDispLen - (footerLabelLength - titleLabelLength);
	borderCharPrintF("+", 3);
	printf(footerLabel);
	borderCharPrintF("+", diffLabelLength + 30);
	printf("\n\n position:\t   %d / 315", rosaryPositionID);

	if (loopBody == 1) {
		printf("\n Decade Progress:    %d / 10\t\t Decade:    %d / 5", smallbeadPercent, decadeNo);
	} else {
		printf("\n Decade Progress:    %d / introduction", smallbeadPercent);
	}

	printf("\n Mystery Progress:   %d / 50\t\t Mystery:   %d / 4", mysteryPercent, mysteryNo);
	printf("\n:");
}

// Gtk prototypes

static int count = 0;

void closeApp(GtkWidget *button, gpointer data);
void changeLabel(GtkWidget *button, gpointer data[10]);
void populateGtk();
void updateGtkLabels();

// Gtk Functions

void closeApp(GtkWidget *button, gpointer data) {
	gtk_main_quit();
}

void changeLabel(GtkWidget *button, gpointer data[10]) {
	count = count + 1;

	char countChar[sizeof(count)]; // x86/c64: 4 bytes
	sprintf(countChar, "%d", count); // int to string

	gtk_label_set_text(data[0], "Changed Label Text 0");
	gtk_label_set_text(data[1], "Changed Label Text 1");
	gtk_label_set_text(data[2], "Changed Label Text 2");
	gtk_label_set_text(data[3], "Changed Label Text 3");
	gtk_label_set_text(data[4], "Changed Label Text 4");
	gtk_label_set_text(data[5], "Changed Label Text 5");
	gtk_label_set_text(data[6], "Changed Label Text 6");
	gtk_label_set_text(data[7], countChar );
	gtk_label_set_text(data[8], "Changed Label Text 8");
	gtk_label_set_text(data[9], "Changed Label Text 9");

	printf("\n button pressed %lu \n", sizeof(count)); // terminal update
}

void populateGtk() {

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

	GtkWidget *lblTextMystery = gtk_label_new("");
	GtkWidget *lblTextDecade = gtk_label_new("");
	GtkWidget *lblTextDecadeMessage = gtk_label_new("");
	GtkWidget *lblTextBackground = gtk_label_new("");
	GtkWidget *lblTextScripture = gtk_label_new("");
	GtkWidget *lblTextPrayer = gtk_label_new("");
	GtkWidget *lblTextBeadType = gtk_label_new("");
	GtkWidget *lblTextBeadNo = gtk_label_new("0");
	GtkWidget *lblTextDecadeProgress = gtk_label_new("0/10");
	GtkWidget *lblTextMysteryProgress = gtk_label_new("0/50");
	GtkWidget *labelTextArray[10] = {lblTextMystery, lblTextDecade, lblTextDecadeMessage, lblTextBackground, lblTextScripture, lblTextPrayer, lblTextBeadType, lblTextBeadNo, lblTextDecadeProgress, lblTextMysteryProgress};

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
	gtk_box_pack_start( GTK_BOX(vboxTextColumn), lblTextMystery, FALSE, FALSE, 2 );
	gtk_box_pack_start( GTK_BOX(vboxTextColumn), lblTextDecade, FALSE, FALSE, 2 );
	gtk_box_pack_start( GTK_BOX(vboxTextColumn), lblTextDecadeMessage, FALSE, FALSE, 2 );
	gtk_box_pack_start( GTK_BOX(vboxTextColumn), lblTextBackground, FALSE, FALSE, 2 );
	gtk_box_pack_start( GTK_BOX(vboxTextColumn), lblTextScripture, FALSE, FALSE, 2 );
	gtk_box_pack_start( GTK_BOX(vboxTextColumn), lblTextPrayer, FALSE, FALSE, 2 );
	gtk_box_pack_start( GTK_BOX(vboxTextColumn), lblTextBeadType, FALSE, FALSE, 2 );

	// Progress Row
	gtk_box_pack_start( GTK_BOX(hboxProgressRow), vboxDecadeProgressColumn, TRUE, TRUE, 10 );
		gtk_box_pack_start( GTK_BOX(vboxDecadeProgressColumn), lblTextDecadeProgress, TRUE, TRUE, 2 );
	gtk_box_pack_start( GTK_BOX(hboxProgressRow), vboxMysteryProgressColumn, TRUE, TRUE, 10 );
		gtk_box_pack_start( GTK_BOX(vboxMysteryProgressColumn), lblTextMysteryProgress, TRUE, TRUE, 2 );

	// Button Row
	gtk_box_pack_start( GTK_BOX(hboxButtonRow), vboxLeftButtonColumn, FALSE, FALSE, 10 );
		gtk_box_pack_start( GTK_BOX(vboxLeftButtonColumn), backButton, FALSE, FALSE, 2 );
	gtk_box_pack_start( GTK_BOX(hboxButtonRow), vboxBeadCounterColumn, TRUE, TRUE, 10 );
		gtk_box_pack_start( GTK_BOX(vboxBeadCounterColumn), lblTextBeadNo, TRUE, TRUE, 2 );
		gtk_box_pack_start( GTK_BOX(vboxBeadCounterColumn), lblTextBeadType, TRUE, TRUE, 2 );
	gtk_box_pack_start( GTK_BOX(hboxButtonRow), vboxRightButtonColumn, FALSE, FALSE, 10 );
		gtk_box_pack_start( GTK_BOX(vboxRightButtonColumn), nextButton, FALSE, FALSE, 2 );

	g_signal_connect( GTK_OBJECT(backButton), "clicked", GTK_SIGNAL_FUNC(closeApp), NULL);
	g_signal_connect( GTK_OBJECT(nextButton), "clicked", GTK_SIGNAL_FUNC(changeLabel), labelTextArray );

	// Package objects in a col
	gtk_box_pack_start( GTK_BOX(hboxTopContainerColumn), hboxReadingRow, FALSE, FALSE, 10 );
	gtk_box_pack_start( GTK_BOX(hboxTopContainerColumn), hboxProgressRow, FALSE, FALSE, 10 );
	gtk_box_pack_start( GTK_BOX(hboxTopContainerColumn), hboxButtonRow, FALSE, FALSE, 10 );

	// attach everything into the window
	gtk_container_add( GTK_CONTAINER(window), hboxTopContainerColumn );
	gtk_widget_show_all(window);
	gtk_main();
}

// Main //
int main(int argc, char *argv[]) {

	int isLinux = 1;
	int rosaryPositionID = 0, beadFK = 0, decadeFK = 0, messageFK = 0, mysteryFK = 0, prayerFK = 0;
	int scriptureFK = 0, loopBody = 0, smallbeadPercent = 0, mysteryPercent = 0;
	int decadeNo = 0, mysteryNo = 0;
	int weekdayNo = 0;
	int navigtionPosition = 0, desiredDispLen = 80;

	char *beadType, *decadeName, *decadeInfo, *mesageText, *mysteryName;
	char *scriptureText, *prayerText;

	#ifdef linux
		isLinux = 1;
		weekdayNo = returnDayOfWeekFlag(); // 0=sun, 1=mon
		navigtionPosition = initialMystery(weekdayNo); // starting position
		struct winsize w; // terminal tty info
	#endif

	#ifdef _WIN32
		isLinux = 0;
	#endif

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

	/*
	 * Populate my struct arrays
	 * (single_struct, struct_array, max_chars_per_line, csv_file_path)
	 * */

	csvToStruct_rosaryBead(rosaryBead_record_field, rosaryBead_dbArray, 300, "csv/rosaryBead.csv");
	csvToStruct_bead(bead_record_field, bead_dbArray, 40, "csv/bead.csv");
	csvToStruct_book(book_record_field, book_dbArray, 300, "csv/book.csv");
	csvToStruct_decade(decade_record_field, decade_dbArray, 800, "csv/decade.csv");
	csvToStruct_message(message_record_field, message_dbArray, 150, "csv/message.csv");
	csvToStruct_mystery(mystery_record_field, mystery_dbArray, 100, "csv/mystery.csv");
	csvToStruct_prayer(prayer_record_field, prayer_dbArray, 1250, "csv/prayer.csv");
	csvToStruct_scripture(scripture_record_field, scripture_dbArray, 500, "csv/scripture.csv");

	splashCoverPage(weekdayNo, isLinux); // intro, coverpage, splash text

	// Launch Gtk

	gtk_init(&argc, &argv);
	populateGtk();

    while (navigtionPosition <= 315) {

		// linux tty/posix display dimentions
        if(isLinux == 1) {
			ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); // tty col/row
			desiredDispLen = (w.ws_col / 2) + (w.ws_col / 5);
        }

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

		// Render output tty display
		outputDisplay(mysteryName, decadeName, mesageText, decadeInfo, scriptureText, prayerText, beadType, rosaryPositionID, loopBody, decadeNo, smallbeadPercent, mysteryPercent, mysteryNo, desiredDispLen);

		// Navigation Input
		navigtionPosition = pressKeyContinue(navigtionPosition, isLinux);
		// getchar(); // pause for char input
	}

	return 0;
}
