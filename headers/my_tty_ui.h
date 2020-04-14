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

typedef struct displayFeastVariables_struct {
	int feastID;
	char feastName[40];
	int feastDay;
	int feastMonth;
	char monthName[40];
} displayFeastVariables_t;

/*
 * Prototypes
 * */

int returnScreenWidth();
int initialMystery( int weekdayNo );
int pressKeyContinue( int navigtionPosition, int weekdayNo, int desiredDispLen );

void deactivateEcho();
void activateEcho();

void clearScreen();
void borderCharPrintF( char *charSymbol, int borderWidth );
void multiLinePrintF( char *labelChars, char *strIn, int desiredLineLength, int minRows );

void splashPage( int desiredDispLen, char *verboseDate );
void infoPage( int weekdayNo, int desiredDispLen, char *titleLabel );

void updateDisplayVariablesStruct( rosary_db_t *rosary_db_struct, displayVariables_t *queryViewStruct, int navigtionPosition );
void updateFeastDisplayVariablesStruct( feast_db_t *feast_db_struct, displayFeastVariables_t *queryFeastViewStruct, int navigtionPosition );

void printStaticFeastArray( displayFeastVariables_t queryFeastViewStruct, int todayDay, int todayMonth );
void outputTtyDisplay( displayVariables_t queryViewStruct, int desiredDispLen, char *titleLabel );

#endif
