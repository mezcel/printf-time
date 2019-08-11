## README

#### work/play in progress

## Notes:
I made my own csv parser. It is tailored to the C files I plan to use in my app.
I could have just read from csv, but I wanted to make something more embeleshed that used C in a way you would not use C in a C++ app.

* [my-csv-parser.h](./my-csv-parser.h)

```c
// splitting a string by some delimiter
char* token = strtok( my_char_array_variable , ";");
```

I made a failsafe script to use the csv itself as memory storage.

* [plain-csv-reading.c](./my-csv-parser.h)

