# main.c

## compile & build

```bash
## -lm links the math.h lib

## standard system executable
gcc -o myExec main.c -lm


## ASM (optional for jollies)

gcc -S myExec main.c -lm
```

## run

```bash
./myExec		## this year's or upcoming year(as needed)

./myExec 2020	## output date for 2020

./myExec -v 2020	## verbose output date for 2020

./myExec -v 2020 -f ~/Downloads/mytextfile.txt	## verbose output date for 2020 && pmf date to file

```

---

## Dependencies for my headers

general-header.h | easter-algorithms.h | pmf-tables.h | runFunctions.h
--- | --- | --- | ---
stdlib.h | stdio.h | stdlib.h | all included headers
stdio.h | stdlib.h | stdio.h | ...
math.h | math.h | math.h | ...
time.h | general-header.h | general-header.h | ...

---

## My Functions

function | function description
--- | ---
```static int inspectMainInputs( int argc, const char *argv[] );``` | returns 1 if program inputs are valid, 0 if not
```void simpleDisplay(int yearInt);``` | printf POSIX Bash Calendar date of this years PFM
```void verboseDisplay(int yearInt);``` |  printf POSIX Bash Calendar date with Easter dates and illustration of Char memory allocation
```int daysUntillPFM(int yearInt);``` | return number of days from today until the next PFM
```void nextPFM();``` | printf date of the next upcoming pfm
```int returnYear();``` | returns current year from system clock
```int noOfChars(char *inputString);``` | returns the number of chars in a a string
```char *myConcat(char *str1, char *str2);``` | concatenate string2 to string 1
```char *itoa(int n);``` | convert integer to string
```struct EasterDay anonymous_Gregorian_algorithm(int yearInt);``` | returns Easter day Gregorian calendar date
```struct EasterDay gauss_Easter_algorithm(int yearInt);``` | returns Easter day Gregorian calendar date
```struct EasterDay meeus_Julian_algorithm(int yearInt);``` | returns Easter day Julian calendar date
```struct EasterDay pfm_algorithm(int yearInt);``` | returns PFM day Gregorian calendar date
