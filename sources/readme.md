## source files

functional libraries

* A struct ER Database
	* reads csv file data and converts it into an in-app app ER DB accesed via structs
* calculate feast day calendar dates
	* uses time.h to calculate the date of a variety of feast day calendar dates
* user interfaces
	* A UI for the CLI
	* A UI for a window desktop

With the exception of the UI's, the calendar and db were designed arround standard gcc libraries. The UI's required extra data formatting and OOP interacing.

Dependency Matrix:

| - | my_calendar.c | my_csv_structs.c | my_json_structs.c | my_tty_ui.c | my_gtk3_api.c |
| - | --- | --- | --- | --- | --- |
| __about:__ | calculates feast days using time.h | converts csv files into an ER Schema, the DB is stored in a single struct | json to struct using [libjson-c](https://github.com/json-c/json-c) | command line terminal interface GUI | Gtk3 desktop window application GUI|
| __dependency:__ | my_calendar.h | n/a | n/a| my_calendar.h | my_calendar.h |
| __dependency:__ | n/a | my_file_to_struct.h |my_file_to_struct.h | my_file_to_struct.h | my_file_to_struct.h |
| __dependency:__ | n/a | n/a | n/a | my_tty_ui.h | my_gtk3_api.h |
