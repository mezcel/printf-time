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
void updateDisplayVariablesStruct(rosaryBead_t rosaryBead_dbArray[317], bead_t bead_dbArray[9], book_t book_dbArray[17], decade_t decade_dbArray[22], message_t message_dbArray[22], mystery_t mystery_dbArray[7], prayer_t prayer_dbArray[11], scripture_t scripture_dbArray[202], displayVariables_t *queryViewStruct, int navigtionPosition);
void outputTtyDisplay( displayVariables_t queryViewStruct, int desiredDispLen);

#endif
