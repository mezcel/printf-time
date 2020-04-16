/*
 * my_tty_ui.h
 */

#ifndef MY_FEAST
#define MY_FEAST

typedef struct displayFeastVariables_struct {
	int feastID;
	char feastName[40];
	int feastDay;
	int feastMonth;
	char monthName[40];
} displayFeastVariables_t;

void updateFeastDisplayStruct( feast_db_t *feast_db_struct, displayFeastVariables_t *queryFeastViewStruct, int todayDay, int todayMonth );

#endif