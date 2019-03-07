# printf-time

C syntax which calculates Easter day and Paschal Full Moon. (gcc)

version: ```0.1.1```

#### Description:

A C program which uses C syntax and the GCC compiler to calculate the date of the Paschal Full Moon (PMF) and the date of Easter Day.

This app is a C refresher as well as an exercise in using the CLI to debug in GDB. I deliberately omitted the ```string.h``` library to force myself to manually perform C string manipulations.

#### Feature algorithms:

* Gauss Easter Algorithm
* Anonymous Easter Algorithm
* Meeus Easter Algorithm
* Paschal Full Moon (PFM) -- *Just the full moon day*

---

#### Example CLI Input:
```bash
## Verbose PFM for 2019

./main -v 2019
```

#### Example CLI Output:

```
------------------------
Basic PMF Output Render:
------------------------

The next Paschal Full Moon:
	This year
	In 44.151701 days
	On Thursday 18 April 2019


Verbose PMF and Easter Output Render:
----------------------------------------
Easter 2019 Dates:
----------------------------------------

Gauss Output:
	Sunday 21, April 2019 -- Gregorian Calendar, mixed var array

Anonymous Output:
	Sunday 21, April 2019 -- Gregorian Calendar, mixed var array

Meeus Output:
	 15, April 2019 -- Julian Calendar, mixed var array

Paschal Full Moon (PFM) Output:
	Thursday 18, April 2019 -- Gregorian Calendar, mixed var array

PFM output as a single char array value:
	String array: 20190418

----------------------------------------
Demo Array Illustration through printf():
----------------------------------------

Char String Array:
[0][1][2][3][4][5][6][7][\0]
 2  0  1  9  0  4  1  8

Index 	 Hex Address 	 Char 	 Hex / Dec 	 Byte
0	 0x55bcb49d99c0	 2	 32 / 50	 110010
1	 0x55bcb49d99c2	 0	 30 / 48	 110000
2	 0x55bcb49d99c4	 1	 31 / 49	 110001
3	 0x55bcb49d99c6	 9	 39 / 57	 111001
4	 0x55bcb49d99c8	 0	 30 / 48	 110000
5	 0x55bcb49d99ca	 4	 34 / 52	 110100
6	 0x55bcb49d99cc	 1	 31 / 49	 110001
7	 0x55bcb49d99ce	 8	 38 / 56	 111000
8	 0x55bcb49d99d0	 \0	  0 / 0		 (null)

------------------------
This next last line will be used as a string to input into Bash for any further POSIX date calculations.

20190418

```

---

### Developer Rant:

This is (way way way) too bloated for what it is.

The quick and dirty would have just been a ~10 liner with a ```return date char```, but I felt like making an embellished personal C refresher.

### MinGW & MSYS

GCC and G++ is just GNU. [Windows GNU](https://osdn.net/projects/mingw/releases/)

### C and POSIX References

[ISO/IEC 9899:1999 - n1256.pdf](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1256.pdf) - www.open-std.org

[ISO/IEC 9899 - Programming languages - C](http://www.open-std.org/JTC1/SC22/WG14/www/projects#9899) -  Standard C libraries PDF

POSIX Documentation [Single UNIX® Specification, Version 4, 2018 Edition](https://publications.opengroup.org/standards/unix/t101) - Misc POSIX Reffs
