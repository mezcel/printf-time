## source files

functional libraries

* A struct ER Database
	* reads csv file data and converts it into an in-app app ER DB accesed via structs
* calculate feast day calendar dates
	* uses time.h to calculate the date of a variety of feast day calendar dates
* user interfaces
	* A UI for the CLI
	* A UI for a window desktop

|| my_calendar.c | my_csv_structs.c | my_tty_ui.c | my_gtk3_api.c |
|| --- | --- | --- | --- |
| __about:__| calculates feast days using time.h | converts csv files into an ER Schema, the de is stored in a single struct| command line terminal interface GUI | Gtk3 desktop window application GUI|
| __dependency:__ | my_calendar.h | - | my_calendar.h | my_calendar.h |
|| - | my_csv_structs.h | my_csv_structs.h | my_csv_structs.h |
|| - | - | my_tty_ui.h | my_gtk3_api.h |

