/* my_tty_ui_win.c
 *
 * Counterpart to ../sources/posixFunctions.c
 * For use on non-linux & non-posix terminal environments.
 * Visual Studio's compiler returns errors if non-comliant
 * libraries and functions are mentioned in the code algorithm.
 * */

#include "../headers/my_tty_ui.h"

int returnScreenWidth(int isLinux) {
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

void make_struct_db_json(rosary_db_t *rosary_db_struct, char *filePath) {
	/*
	 * This is a place holder just to make the Win10 VS compiler happy.
	 * The real function, by the same name, was designed for use on a
	 * Debian Linux using the json-c library. This dummy function was
	 * likely called by a non-linux OS, like Win10.
	*/
	return 0;
}

void deactivateEcho(int isLinux) {
	/*
	 * n/a
	 * On a POSIX terminal it would turn off "echo" on key press
	 * */
	return 0;
}

void activateEcho(int isLinux) {
	/*
	 * n/a
	 * On a POSIX terminal it would restore "echo" on key press
	 * */
	return 0;
}
