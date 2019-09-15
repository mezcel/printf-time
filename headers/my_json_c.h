/*
 * my_json_c.h
 * */

#ifndef MY_JSON_C
#define MY_JSON_C

size_t returnFileSize(char *filePath);

char *queryAttrString(struct json_object *inputObject, char *attrName, int idx);
int queryAttrInteger(struct json_object *inputObject, char *attrName, int idx);
int returnScreenWidth(int isLinux);
int pressKeyContinue(int navigtionPosition, int isLinux);
void clearScreen(int isLinux);
void borderCharPrintF(char *charSymbol, int borderWidth);
void multiLinePrintF(char *labelChars, char *strIn, int desiredLineLength);
void displayProgress(int rosaryBeadID, int loopBody, int smallbeadPercent, int mysteryPercent, int mysteryNo, int prayerFK);

#endif
