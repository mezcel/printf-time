## source files

functional libraries

| calendar | database | tty | Gtk |

| --- | --- | --- | --- |
| dependency: my_calendar.h | dependency: my_calendar.h | dependency: my_calendar.h |
| - | - | dependency: my_csv_structs.h | dependency: my_csv_structs.h |
|| dependency: my_csv_structs.h | dependency: my_tty_ui.h | dependency: my_gtk3_api.h |
| about: calculates feast days | about: converts csv files into an ER Schema, the de is stored in a single struct| about: tty ui | about: gtk ui|
