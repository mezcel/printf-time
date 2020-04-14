/* my_tty_ui_posix.c
 *
 * For use on Debian Linux POSIX terminal environments.
 * */

#include <sys/ioctl.h>	// ioctl(), TIOCGWINSZ, struct winsize
#include <unistd.h> 	// STDOUT_FILENO

#include "../headers/my_tty_ui.h"

void clearScreen() {
	// system( "@cls||clear" );
	system( "clear" );								// linux
}

int returnScreenWidth() {
	// return a number which represents how long/wide the screen text should be
	int col_length = 95;	// Estimate and proximate ( 85 - 120 ) chars screen width

	struct winsize w;								// terminal tty info
	ioctl( STDOUT_FILENO, TIOCGWINSZ, &w );			// tty col/row
	col_length =  w.ws_col;

	return col_length;
}

void deactivateEcho() {
	system( "stty -echo" );
	system( "stty cbreak" );
}

void activateEcho() {
	system( "stty echo" );							// Make echo work
	system( "stty -cbreak" );						// read one key without pressing enter
}

int pressKeyContinue( queryFeastViewStruct, int navigtionPosition, int weekdayNo, int desiredDispLen ) {
	// Increment or decrement the next desired position in the rosary sequence
	// uses traditional vim or "retro game" navigation keys

	char ch = getchar();

	switch ( ch ) {
		// help screen
		case 65:									// ASCII up arrow
		case 66:									// ASCII down arrow
			printf( "\n" );
		case 'w':
		case 's':
		case 'j':
		case 'k':
			clearScreen();
			infoPage( queryFeastViewStruct, weekdayNo, desiredDispLen, " Instructions: " );
			break;

		// Navigate forward
		case 67:									// ASCII right arrow
			printf( "\n" );
		case 10:									// ASCII enter key
		case 'n':									// [ n key ] navigates 1 step forward
		case 'l':									// vim input
		case 'd':									// game input
			if ( navigtionPosition < 315 ) {
				navigtionPosition++;
			} else {
				navigtionPosition = 0;				// loop to the beginning
			}
			break;

		// Navigate backward
		case 68:									// ASCII left arrow
			printf( "\n" );
		case 32:									// ASCII space bar
		case 'h':									// vim input
		case 'a':									// game input
		case 'b':									// [ b key ] navigates 1 step back
			if ( navigtionPosition > 1 ) {
				navigtionPosition--;
			} else {
				navigtionPosition = 315;			// loop back to the end
			}
			break;

		// Jump to a mystery
		case '0':									// Mystery of the day
			navigtionPosition = initialMystery( weekdayNo );
			break;
		case '1':									// Joyful
			navigtionPosition = 0;
			break;
		case '2':									// Luminous
			navigtionPosition = 79;
			break;
		case '3':									// Sorrowful
			navigtionPosition = 158;
			break;
		case '4':									// Glorius
			navigtionPosition = 237;
			break;

		// Exit Application
		//case 27:									// ASCII esc key
		case 'q':									// [ q key ] quits the app
			printf( "\n\n Quit App \n", ch );
			navigtionPosition = 316;				// any integer greater than 315
			break;

		// Non-mapped keys
		default:									// other key entries
			//printf( "%d", ch );
			printf( "\n" );
			break;
	}

	return navigtionPosition;
}
