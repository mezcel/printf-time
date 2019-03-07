/* Easter Day Calculations (general-header.h)
 *
 * char counter, into to char conversion, define struct
 * */

/*
 * #include <stdlib.h>
 * #include <stdio.h>
 * #include <math.h>
 * #include <time.h>
 * */

/* Vars */

struct EasterDay {
   char *weekday, *month;
   int day, year;
};

/* Function Prototypes */

int returnYear();
int noOfChars(char *inputString);
char *myConcat(char *str1, char *str2);
char *itoa(int n);

long decimalToBinary(long n);
char *stringTocharArray(char *inputString);
char *outputDate2OutputString(struct EasterDay outputDate);
void dispDemoArray (char *inputString);
int binary2hex(char *inputString);
struct tm defineTMstruct(int yearInput, int monthInput, int dayInput);

int compareStrings(char input[],char check[]);

/* Function Definition */

int returnYear() {
	int yearInt;
	char yearChar[5];

	time_t now;
	if ( time(&now) != (time_t)(-1) ) {
		struct tm *mytime = localtime(&now);
		if ( mytime ) {
			if ( strftime(yearChar, sizeof yearChar, "%Y", mytime) ) {
				yearInt = atoi(yearChar);
			}
		}
	}

	return yearInt;
}

int noOfChars(char *inputString) {
	int count=0;

	while ( inputString[count]!='\0' ) {
		count++;
	}

	return count;
}

char *myConcat(char *str1, char *str2) {
	char *outputString = "\0";
	int count1 = 0, count2 = 0;
	int str1Len = 0, str2Len = 0, combinedLen = 0;

	str1Len = noOfChars(str1);
	str2Len = noOfChars(str2);
	combinedLen = str1Len + str2Len;

	outputString = malloc( combinedLen );

	while ( count1 < str1Len ) {
		outputString[count1] = str1[count1];
		count1++;
	}

	while ( count2 < str2Len ) {
		outputString[count1+count2] = str2[count2];
		count2++;
	}

	outputString[count1+count2] = '\0'; //termination char

	return outputString;
}

char *itoa(int n) {
	/* Int to Char conversion
	 * DIY itoa
	 * 	char *  itoa ( int value, char * str, int base );
	 * 	is non-standard function
	 * 	https://stackoverflow.com/a/13361077
	 * */

	int len = n==0 ? 1 : floor(log10l(labs(n)))+1;
	if (n<0) len++; // room for negative sign '-'

	char *buf = calloc(sizeof(char), len+1); // +1 for null
	//snprintf(buf, len+1, "%ld", n);
	snprintf(buf, len+1, "%d", n);

	return   buf;
}

long decimalToBinary(long n) {
    int remainder;
 long binary = 0, i = 1;

    while(n != 0) {
        remainder = n%2;
        n = n/2;
        binary= binary + (remainder*i);
        i = i*10;
    }
    return binary;
}

char *stringTocharArray(char *inputString) {

	static char *outputString;
	static int count1 = 0, count2 = 0;
	static int str1Len = 0, str2Len = 0, combinedLen = 0;

	str1Len = noOfChars(inputString);
	str2Len = (str1Len * 3);// each 1 char has  '[],'
	combinedLen = str1Len + str2Len;

	outputString = malloc( combinedLen );

	while ( count1 < str1Len ) {
		outputString[count2]='[';
		count2++;

		outputString[count2] = inputString[count1];
		count1++;

		count2++;
		outputString[count2]=']';

		if ( count1 < str1Len ) {
			count2++;
			outputString[count2]=',';
			count2++;
		}

	}


	count2++;
	outputString[count2] = '\0'; //termination char

	return outputString;
}

char *outputDate2OutputString(struct EasterDay outputDate) {

	char *yearNo, *monthNo, *dayNo, *str1, *str2;
	
		//if ( outputDate.month == "March" ) {
    char *monthCharStr = outputDate.month;
    int isMarch = compareStrings( monthCharStr, "March");
    if ( isMarch ) {
		monthNo = "03";
	} else {
		monthNo = "04";
	}
	
	yearNo = itoa(outputDate.year);
	str1 = myConcat( yearNo , monthNo );
	
	dayNo =  itoa(outputDate.day);
	str2 = myConcat( str1 , dayNo );

	return str2;
}

void dispDemoArray (char *inputString) {
	printf("\n----------------------------------------\n"
			"Demo Array Illustration through printf():"
			"\n----------------------------------------\n");
	
	int count = 0;

	/* char string array */
	char *charStr = inputString;
	printf("\nChar String Array:\n");
	count=0;
	while (*charStr) {
		printf("[%d]", count);
		count++;
		charStr++;
	}
	printf("[\\0]\n");
	charStr = inputString;
	while (*charStr) {
		printf(" %c ", *charStr);
		charStr++;
	}
	printf("\n");
	
	/* char address pointer */
	printf("\nIndex \t Hex Address \t Char \t Hex / Dec \t Byte\n");
	char *ptrChar = inputString;
	count=0;
	while (*ptrChar) {
		printf("%d\t %p\t %c\t %x / %u\t %ld \n", 
			count, &ptrChar[count], *ptrChar, *ptrChar, *ptrChar, decimalToBinary(*ptrChar));
		ptrChar++;
		count++;
	}
	// manually display known the null terminator char value
	printf("%d\t %p\t \\0\t  %x / %x\t\t %ld \n", 
		count, &ptrChar[count],  *ptrChar, *ptrChar, decimalToBinary(*ptrChar));
		

}

int binary2hex(char *inputChar) {

	int binaryval, hexadecimalval = 0, i = 1, remainder;
	binaryval = decimalToBinary(*inputChar);
	while (binaryval != 0) {
		remainder = binaryval % 10;
		hexadecimalval = hexadecimalval + remainder * i;
		i = i * 2;
		binaryval = binaryval / 10;
		//printf("[%ld],", binaryval);
	}
	///printf("\nEquivalent hexadecimal value: %lX\n", hexadecimalval);

	return hexadecimalval;
}

struct tm defineTMstruct(int yearInput, int monthInput, int dayInput) {
	
	struct tm myTMstruct;

	myTMstruct.tm_mday = dayInput;
	myTMstruct.tm_mon = monthInput - 1;
	myTMstruct.tm_year = yearInput - 1900;

	myTMstruct.tm_hour = 0;
	myTMstruct.tm_min = 0;
	myTMstruct.tm_sec = 1;
	myTMstruct.tm_isdst = 0;
	
	return myTMstruct;
	
}

int compareStrings(char input[],char check[]) {
    int i,result=1;
    for(i=0; input[i]!='\0' || check[i]!='\0'; i++) {
        if(input[i] != check[i]) {
            result=0;
            break;
        }
    }
    return result;
}
