## README

#### A working work in progress

### Background:

I made my own csv parser. It is tailored to the C files I plan to use in my app.

I could have just read from csv, but I wanted to make something more embellished that used C in a way you would not use C in a C++ app. But since it is C, it "should" work as-is in a C++ app.

* Deliminator Workaround: I changed ";" to "<semicolon>". The ```;``` char appeared in long text strings and it was cutting the string into segments.
	* the objective at the moment is retrieving, displaying, and navigating
	* i will work on beautification and formatting later


### Files:

* [my-csv-parser.h](./my-csv-parser.h)
	* parse csv into dynamic array structs
* [main.c](./main.c)
	* bare bones basic rosary
	* [enter key] navigates forward
	* [b] and [enter] navigates back

I made a failsafe script to demo the use the csv itself as memory storage.

* [plain-csv-reading.c](./my-csv-parser.h)

---

### Dev Environment

* Developed on WLS for convenient migration into MinGw.
