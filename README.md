## printf-time

version: ```v0.2.1```

#### About:

Yet another installment in my rosary app series. This version is a CLI desktop application written in C (gcc).

* This app uses a CLI display interface.
* Text is rendered from pre-formatted char variables passed through printf() statements
	* it's not pretty, but it has a symetrical and justified layout
	* i deliberately avoided cuses to encourage easier cross-app portability
* libraries:
	* <stdio.h>	// standard default C library
	* <stdlib.h>	// calloc()/realloc()/malloc(), system(), free()
	* <string.h>	// workhorse header for CLI string manipulation
	* <time.h>
	* "my-csv-parser.h"	// my own homebrew CSV parse header

#### Apps Contained in the Repo:

1. __PFM-Calculator__:
	* Calculate Easter Day from the Paschal Full Moon date
	* a lot of extra/optional output display related bloat (just for jollies)
	* intended as a standalone or portable app
	* [asciinema demo video link](https://asciinema.org/a/232779)

2. __Rosary__:
	* A basic CLI Rosary using (CSV to Struct Array) array db.
	* Intended as a standalone app
	* Main features are working and complete
	* Display UI works but ```beautification``` is under construction
	* [quick demo recording](https://asciinema.org/a/262232)  **Not the latest version.**

### Future Development:

* UI display beautification for the Rosary
	* kinda hard since it is just printf(), but so far the word wrap is functional.
* Integrate PFM into the Rosary in order to make it more like the rosary apps I made using the other programming languages.
	* so far, only the weekday flags are up and running
