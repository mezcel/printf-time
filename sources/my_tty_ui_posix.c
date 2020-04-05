/* my_tty_ui_posix.c
 *
 * For use on Debian Linux POSIX terminal environments.
 * */

#ifdef __unix__
    #include <sys/ioctl.h>	// ioctl(), TIOCGWINSZ, struct winsize
	#include <unistd.h> 	// STDOUT_FILENO
#endif

#include "../headers/my_tty_ui.h"

int returnScreenWidth( int isLinux ) {
	// return a number which represents how long/wide the screen text should be
	int col_length = 95;	// 85 chars wide

	if( isLinux == 1 ) {
		struct winsize w;						// terminal tty info
		ioctl( STDOUT_FILENO, TIOCGWINSZ, &w );	// tty col/row
		col_length =  w.ws_col;
	}
	return col_length;
}

void deactivateEcho( int isLinux ) {
	if( isLinux == 1 ) {
		system( "stty -echo" );
		system( "stty cbreak" );
	}
}

void activateEcho( int isLinux ) {
	if( isLinux == 1 ) {
		system( "stty echo" ); // Make echo work
		system( "stty -cbreak" );// go to COOKED mode
	}
}
