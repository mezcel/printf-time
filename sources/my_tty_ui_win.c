/* my_tty_ui_win.c
 * USECASE: Supliment the my_tty_ui.c source code.
 *
 * Counterpart to ../sources/my_tty_ui_posix.c
 * For use on non-linux & non-posix terminal environments.
 * Visual Studio's compiler returns errors if non-comliant
 * libraries and functions are mentioned in the code algorithm.
 * */

//#include <stdlib.h>   // system()
#include <windows.h>    // Win10 GetConsoleScreenBufferInfo()
#include <conio.h>      // getch() Win10 only

#include "../headers/my_file_to_struct.h"
#include "../headers/my_tty_ui.h"

void clearScreen() {
    // WIN10, Powershell or Command Terminal
    // system( "@cls||clear" );
    system( "@cls" );
}

int returnScreenWidth() {
    /*
    * On a POSIX terminal I would use the following headers
    *   #include <sys/ioctl.h>  // ioctl(), TIOCGWINSZ, struct winsize
    *   #include <unistd.h>     // STDOUT_FILENO
    *
    * On Win10 I use #include <windows.h>
    *   #include <windows.h>    // GetConsoleScreenBufferInfo()
    * batch script to get console width:
    * for /F "usebackq tokens=2* delims=: " %%W in (`mode con ^| findstr Columns`) do echo %%W
    * */

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;

    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    //int rows;
    //rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return columns;     // For comfortable readability, aim for an int greater than 95;
}

void deactivateEcho() {
    /*
     * n/a
     * used to deactivate echo on posix compliant terminals
     * */
    return;
}

void activateEcho() {
    /*
     * n/a
     * used to reactivate echo on posix compliant terminals
     * */
    return;
}

void make_struct_rosary_db_json( rosary_db_t *rosary_db_struct, char *jsonFilePath ) {
    /*
     * n/a
     * This is a place holder just to make the Win10 VS compiler happy.
     * The real function, by the same name, was designed for use on a
     * Debian Linux using the json-c library. This dummy function was
     * likely to be called by a non-linux OS, like Win10.
     *
     * this is based on my_json_structs.c which was not loaded
     * */
    return;
}

int pressKeyContinue( displayFeastVariables_t queryFeastViewStruct,
        int navigtionPosition, int weekdayNo, int desiredDispLen ) {
    /*
     * User keyboard input on win10
     * Increment or decrement the next desired position in the rosary sequence
     * Uses traditional vim or "retro game" navigation keys
     * https://www.alt-codes.net/arrow_alt_codes.php
     * */

    char ch = getch();  // input keyboard key without the enter key on Win10

    switch ( ch ) {

        // help screen
        case 72:                                    // ASCII up arrow
        case 80:                                    // ASCII down arrow
        case 'w':
        case 's':
        case 'j':
        case 'k':
            clearScreen();
            infoPage( queryFeastViewStruct, weekdayNo, desiredDispLen, " Instructions: " );
            break;

        // Navigate forward
        case 77:                                    // ASCII right arrow
        case '\r':                                  // [ enter ] key
        case 'n':                                   // [ n key ] navigates 1 step forward
        case 'l':                                   // vim input
        case 'd':                                   // game input
            if ( navigtionPosition < 315 ) {
                navigtionPosition++;
            } else {
                navigtionPosition = 0;              // loop to the beginning
            }
            break;

        // Navigate backward
        case 75:                                    // ASCII left arrow
        case 32:                                    // ASCII space bar
        case 'h':                                   // vim input
        case 'a':                                   // game input
        case 'b':                                   // [ b key ] navigates 1 step back
            if ( navigtionPosition > 1 ) {
                navigtionPosition--;
            } else {
                navigtionPosition = 315;            // loop back to the end
            }
            break;

        // Jump to a mystery
        case '0':                                   // Mystery of the day
            navigtionPosition = initialMystery( weekdayNo );
            break;
        case '1':                                   // Joyful
            navigtionPosition = 0;
            break;
        case '2':                                   // Luminous
            navigtionPosition = 79;
            break;
        case '3':                                   // Sorrowful
            navigtionPosition = 158;
            break;
        case '4':                                   // Glorius
            navigtionPosition = 237;
            break;

        // Exit Application
        //case 27:                                  // ASCII esc key
        case 'q':                                   // [ q key ] quits the app
            printf( "\n\n Quit App \n", ch );
            navigtionPosition = 316;                // any integer greater than 315
            break;

        // Non-mapped keys
        default:                                    // other key entries
            break;
    }

    return navigtionPosition;
}
