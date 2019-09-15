#include <stdio.h>
#include <json-c/json.h>
#include <sys/stat.h> // used for file size

#ifdef linux // Linux GCC v6+
	#include <stdlib.h>		// calloc(), realloc(), malloc(), system(), free()
	#include <stdio.h>
	#include <string.h>
	#include <sys/ioctl.h>	// ioctl(), TIOCGWINSZ, struct winsize
	#include <unistd.h> 	// STDOUT_FILENO

	#define IS_LINUX 1		// os flag
#endif

#include "../headers/my_json_c.h"

char *queryAttrString(struct json_object *inputObject, char *attrName, int idx) {
	struct json_object *er_class;
	er_class = json_object_array_get_idx(inputObject, idx);

	struct json_object *attr;
	json_object_object_get_ex(er_class, attrName, &attr);

	return (char *)json_object_get_string(attr);
}

int queryAttrInteger(struct json_object *inputObject, char *attrName, int idx) {
	struct json_object *er_class;
	er_class = json_object_array_get_idx(inputObject, idx);

	struct json_object *attr;
	json_object_object_get_ex(er_class, attrName, &attr);

	return json_object_get_int(attr);
}

size_t returnFileSize(char *filePath) {
	// Get the size of a json file
	struct stat st;
	stat(filePath, &st);
	size_t size = st.st_size; // size in bytes

	return size;
}

/////////////////////////

int returnScreenWidth(int isLinux) {
	// return a number which represents how long/wide the screen text should be
	int col_length = 85;	// 85 chars wide

	if(isLinux) {
		struct winsize w;						// terminal tty info
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);	// tty col/row
		col_length =  w.ws_col;
	}
	return col_length;
}

int pressKeyContinue(int navigtionPosition, int isLinux) {
	// Increment or decrement the next desired position in the rosary sequence

	char c[32] = {0};
	fgets(c, 32, stdin); //fgets(c, sizeof(c), stdin);

	switch (c[0]) {
		case 'n':	// [n key] navigates 1 step forward
		case '\n':	// [enter key] navigates 1 step forward
			if (navigtionPosition < 315) {
				navigtionPosition++;
			} else {
				navigtionPosition = 0; // loop to the beginning
			}
			break;

		case 'b':	// [b key] navigates 1 step back
			if (navigtionPosition > 1) {
				navigtionPosition--;
			} else {
				navigtionPosition = 315; // loop back to the end
			}
			break;

		case 'q':	// [q key] quits the app
			printf("\n Quit App \n");
			navigtionPosition = 316; // any integer greater than 315
			break;

		default: // other key entries
			navigtionPosition -= 0; // cancel navigation accumulation
	}

	return navigtionPosition;
}

void clearScreen(int isLinux) {
	// system("@cls||clear");
	if (isLinux == 1) {
		system("clear");	// linux
	} else {
		system("@cls");		// win
	}
}

void borderCharPrintF(char *charSymbol, int borderWidth) {
	// print a sequence of chars which act as a visual border/divider
	for (int i = 0; i < borderWidth; i++) {
		printf("%s", charSymbol);
	}
}

void multiLinePrintF(char *labelChars, char *strIn, int desiredLineLength) {
	int screenWidth = desiredLineLength;	// max chars per screen line width
	int inputLength = (int)strlen(strIn);	// number of chars contained in input string
	int labelColChars = 17;					// chars used in the label col
	int max_line_chars = screenWidth - labelColChars;

	printf("%s", labelChars); // print the content label, initial printf

	if ( inputLength < max_line_chars ) { // short enough to be 1 line
		printf("%s\n\t\t", strIn);
	} else { // longer than one line
		// input string to an array of words
		char tmpStringArray[inputLength];
		strcpy(tmpStringArray, strIn);
		char *delimiter = " ";
		char *token = strtok(tmpStringArray, delimiter); // array of words

		// init counters
		int chars_in_a_word = 0;
		int potential_line_length = 0;
		int charCounter = 0;

		// parse each word in the long sentence
		while (token != NULL) {
			chars_in_a_word = (int)strlen(token);
			potential_line_length = chars_in_a_word + charCounter;

			if(potential_line_length < max_line_chars) {
				charCounter += chars_in_a_word + 1;
				printf("%s ", token);
			} else {
				charCounter = chars_in_a_word;
				printf("\n\t\t%s ", token); // start new line indent
			}

			token = strtok(NULL, delimiter); // get the next word
		}
		printf("\n");
	}
}

void displayProgress(int rosaryBeadID, int loopBody, int smallbeadPercent, int mysteryPercent, int mysteryNo, int prayerFK) {
	char *rosaray_region_string;
	int segment_whole, segment_part;

	if (loopBody == 1) {
		rosaray_region_string = "rosary body";
		segment_whole = 10;
		segment_part = smallbeadPercent;
	} else {
		if ( (prayerFK == 7) || (prayerFK == 8) ) {
			rosaray_region_string = "conclusion prayers";
			segment_whole = 2;
			segment_part = smallbeadPercent / 5;
		} else {
			rosaray_region_string = "introduction prayers";
			segment_whole = 7;
			segment_part = smallbeadPercent;
		}
	}
	printf("\n\n position:\t\t%d / %d", rosaryBeadID, 315);
	printf("\n Decade Progress:\t%d / %d\t\t%s", segment_part, segment_whole, rosaray_region_string);
	printf("\n Mystery Progress:\t%d / 50\t\tMystery:   %d / 4", mysteryPercent, mysteryNo);
	printf("\n:");
}
