/*
 * my_tty_ui.h
 */

#ifndef MY_TTY_UI
#define MY_TTY_UI

/*
 * Data Structures
 * */

/* A sturct serving as an ER View class for displaying the scripture rosary */
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

/* A sturct serving as an ER View class for displaying feast day information */
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

/* Returns a full file path of a child directory of the current working directory */
char *returnDefaultDbDir( char *childPath);

/* Set variable flags based on the programs input arguments
 * The file database directory path and language translation flag will be set. */
void SetTranslationDatabase( int argc, char **argv, char **database, int *translationFlag);

/* Manually concatenate 2 strings. */
void myConcatenate( char *first, char *second );

/* Manually copy chars from one variable into another. */
void myCopyString( char *new, char *original );

/* Set the full file path of a resource file. */
void setResourcePath (char *pathVariable, char *parentPath, char *childPath);

/* Replace substring sequence within a string. */
char *stringReplace(char *original, char *pattern, char *replacement);

/* Parse out pre-defined char patters from a string. */
char *cleanQuote( char * original );

/* Return 0 if no input argument, return 1 otherwise. Used to initialize NAB or Vulgate readings.*/
int returnLaunchArgument( int argc, char *argv );

/* Return the number of columns wide the current terminal display is. */
int returnScreenWidth();

/* Inputs a week day 0-6 number Sun-Sat. Return starting position Rosary Bead Position PK */
int initialMystery( int weekdayNo );

/* Increments rosary bead position. Function typically called when specific keyboard keys are pressed. */
int pressKeyContinue(
    displayFeastVariables_t queryFeastViewStruct,
    int navigtionPosition, int weekdayNo, int desiredDispLen );

/* Pause and prompt user to press enter. */
void pressEnter();

/* Deactivate terminal echo. Use to decorate the terminal UX. */
void deactivateEcho();

/* Restore terminal echo. Used just before the rosary application is terminated. */
void activateEcho();

/* printf an emboldened string to terminal */
void boldString( char *inStr );

/* Clear tty screen */
void clearScreen();

/* printf a row sequence of chars which act as a visual border/divider */
void borderCharPrintF( char *charSymbol, int borderWidth );

/* Automatically wrap string arrays that are longer than 1 terminal row */
void multiLinePrintF( char *labelChars, char *strIn, int desiredLineLength, int minRows );

/* printf a string centered in terminal. horizontal center. */
void centerString( char *strIn, int desiredLineLength, int boldFlag );

/* Display a formatted splash screen welcome screen */
void splashPage( int desiredDispLen, char *verboseDate );

/* Display a formatted screen explain what this program does and basic UI controls. */
void infoPage(
    displayFeastVariables_t queryFeastViewStruct,
    int weekdayNo, int desiredDispLen, char *titleLabel );

/* Display a warning and instruction if program was launch with an invalid argument. */
void badArgMsg( int desiredDispLen );

/* Display a formatted screen with information about the next upcoming mystery. */
void mysteryCoverPage( displayVariables_t queryViewStruct, int navigtionPosition, int desiredDispLen );

/* Populate the ER view class struct "displayVariables_struct" */
void updateDisplayVariablesStruct(
    rosary_db_t *rosary_db_struct, displayVariables_t *queryViewStruct,
    int navigtionPosition );

/* Populate the ER view class struct "displayFeastVariables_struct" */
void updateFeastDisplayStruct(
    feast_db_t *feast_db_struct, displayFeastVariables_t *queryFeastViewStruct,
    int todayDay, int todayMonth, int recordCount );

/* Render liturgical season theme in bash prompt */
void bashrcHolidayDisplay( rosary_db_t *rosary_db_struct, displayFeastVariables_t queryFeastViewStruct,
    displayVariables_t queryViewStruct, char *verboseDate, int desiredDispLen );


/* Render scripture rosary text to terminal. Primary UI and content display. */
void renderRosaryDisplay(
    displayVariables_t queryViewStruct,
    int desiredDispLen, char *titleLabel );

#endif
