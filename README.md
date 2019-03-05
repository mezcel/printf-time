# printf-time

C syntax which calculates Easter day and Paschal Full Moon. 

version: ```0.1```

#### Description:

A C program which uses C syntax and the GCC compiler to caculate the date of the Paschal Full Moon (PMF) and the date of Easter Day. Dveloped on a Mint, tested on a Debian and an Arch.

This app is a C refresher as well as an exercise to learn the how to use the CLI as an IDE, debug in GDB, and inspecting assembly code in the desktop environment.

Output Modes:

* This Year Date
* Upcoming Year Date
* Any Year ( 1900AD ~ 3000AD )

#### Feature algorithms:

* Gauss Easter Algorithm
* Annonomous Easter Algorithm
* Meeus Easter Algorithm
* Paschal Full Moon (PFM) -- *Just the full moon day*

---

#### Example CLI Output:

```
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
	String array: 2019-04-18

----------------------------------------
Demo Array Illustration through printf():
----------------------------------------

Char String Array:
[0][1][2][3][4][5][6][7][8][9][\0]
 2  0  1  9  -  0  4  -  1  8 

Index 	 Hex Address 	 Char 	 Hex / Dec 	 Byte
0	 0x5557307599c0	 2	 32 / 50	 110010 
1	 0x5557307599c2	 0	 30 / 48	 110000 
2	 0x5557307599c4	 1	 31 / 49	 110001 
3	 0x5557307599c6	 9	 39 / 57	 111001 
4	 0x5557307599c8	 -	 2d / 45	 101101 
5	 0x5557307599ca	 0	 30 / 48	 110000 
6	 0x5557307599cc	 4	 34 / 52	 110100 
7	 0x5557307599ce	 -	 2d / 45	 101101 
8	 0x5557307599d0	 1	 31 / 49	 110001 
9	 0x5557307599d2	 8	 38 / 56	 111000 
10	 0x5557307599d4	 \0	  0 / 0		 (null) 

2019-04-18

------------------------

Basic PMF Output Render:

The next Paschal Ful Moon:
	This year
	In 44.178079 days
	On Thursday 18 April 2019

```

---

### Developer Rant:

This is (way way way) too bloated for what it is.

The quick and dirty would have just been a ~10 liner with a ```return date char```, but I felt like making an embellished personal C refresher.

### MinGW & MSYS

GCC and G++ is just GNU. [Windows GNU](https://osdn.net/projects/mingw/releases/)
