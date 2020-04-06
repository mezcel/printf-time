/* my_tty_ui_win.c
 *
 * Counterpart to ../sources/my_tty_ui_posix.c
 * For use on non-linux & non-posix terminal environments.
 * Visual Studio's compiler returns errors if non-comliant
 * libraries and functions are mentioned in the code algorithm.
 * */

#include <conio.h>		// getch() win10
#include "../headers/my_file_to_struct.h"
#include "../headers/my_tty_ui.h"

void clearScreen() {
	// system( "@cls||clear" );
	system( "@cls" );	// win os
}

int returnScreenWidth() {
	/*
	 * On a POSIX terminal I would use the following to determine
	 * how many columns wide the terminal is.
	 * 	#include <sys/ioctl.h>	// ioctl(), TIOCGWINSZ, struct winsize
	 * 	#include <unistd.h> 	// STDOUT_FILENO
	 * Since Win10 Visual Studio does not support this, I will just set
	 * the terminal's column width.
	*/
	return 94; // number of chars wide
}

void make_struct_db_json( rosary_db_t *rosary_db_struct, char *jsonFilePath ) {
	/*
	 * n/a
	 * This is a place holder just to make the Win10 VS compiler happy.
	 * The real function, by the same name, was designed for use on a
	 * Debian Linux using the json-c library. This dummy function was
	 * likely called by a non-linux OS, like Win10.
	 *
	 * this is based on my_json_structs.c which was not loaded
	*/
	return;
}

int pressKeyContinue( int navigtionPosition, int weekdayNo, int desiredDispLen ) {
	// user keyboard input for win10
	// Increment or decrement the next desired position in the rosary sequence
	// uses traditional vim or "retro game" navigation keys
	// https://www.alt-codes.net/arrow_alt_codes.php

	char ch = getch();	// input keyboard key without the enter key

	switch ( ch ) {

		// help screen

		case 72:	// ASCII up arrow
		case 80:	// ASCII down arrow
		case 'w':
		case 's':
		case 'j':
		case 'k':
			clearScreen();
			infoPage( weekdayNo, desiredDispLen, " Instructions: " );
			break;

		// Navigate forward

		case 77:	// ASCII right arrow
		case 'n':	// [ n key ] navigates 1 step forward
		case 'l':	// vim input
		case 'd':	// game input
			if ( navigtionPosition < 315 ) {
				navigtionPosition++;
			} else {
				navigtionPosition = 0; // loop to the beginning
			}
			break;

		// Navigate backward

		case 75:	// ASCII left arrow
		case 32:	// ASCII spacebar
		case 'h':	// vim input
		case 'a':	// game input
		case 'b':	// [ b key ] navigates 1 step back
			if ( navigtionPosition > 1 ) {
				navigtionPosition--;
			} else {
				navigtionPosition = 315; // loop back to the end
			}
			break;

		// Exit Application

		//case 27:	// ASCII esc key
		case 'q':	// [ q key ] quits the app
			printf( "\n\n Quit App \n", ch );
			navigtionPosition = 316; // any integer greater than 315
			break;

		// Non-mapped keys

		default:	// other key entries
			break;
	}

	return navigtionPosition;
}
