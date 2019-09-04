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

void splashCoverPager(int weekdayNo, int isLinux);
void multiLinePrintF(char *labelChars, char *strIn, int desiredLineLength);
int pressKeyContinue(int navigtionPosition, int isLinux);
void updateDisplayVariablesStruct( rosary_db_t *rosary_db_struct, displayVariables_t *queryViewStruct, int navigtionPosition);
void outputTtyDisplay( displayVariables_t queryViewStruct, int desiredDispLen);

#endif
