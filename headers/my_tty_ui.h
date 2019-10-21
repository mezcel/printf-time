/*
 * my_tty_ui.h
 */

#ifndef MY_TTY_UI
#define MY_TTY_UI

/*
 * Data Structures
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

} displayVariables_t;

/*
 * Prototypes
 * */

int returnScreenWidth(int isLinux);
int initialMystery(int weekdayNo);
int pressKeyContinue(int navigtionPosition, int isLinux, int weekdayNo, int desiredDispLen);

void clearScreen(int isLinux);
void borderCharPrintF(char *charSymbol, int borderWidth);
void multiLinePrintF(char *labelChars, char *strIn, int desiredLineLength, int minRows);
void splashCoverPage(int weekdayNo, int desiredDispLen, char *titleLabel);
void updateDisplayVariablesStruct( rosary_db_t *rosary_db_struct, displayVariables_t *queryViewStruct, int navigtionPosition);
void outputTtyDisplay( displayVariables_t queryViewStruct, int desiredDispLen, char *titleLabel);

#endif
