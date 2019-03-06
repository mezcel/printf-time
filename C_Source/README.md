# main.c

## compile

```bash
## -lm links the math.h lib

## executable
gcc -o myExec main.c -lm

```

## run

```bash
./myExec		## this year's or upcoming year(as needed)

./myExec 2030	## output date for 2030

```

---

## my headers

### general-header.h

char counter, int to char conversion, define struct

display simulated array information

 * #include <stdlib.h>
 * #include <stdio.h>
 * #include <math.h>
 * #include <time.h>

### easter-algorithms.h

Algorithms taken from: https://en.wikipedia.org/wiki/Computus

 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <math.h>
 * #include "general-header.h"

### pmf-tables.h

Algorithms and Tables taken from: https://www.assa.org.au/edm

 * #include <stdlib.h>
 * #include <stdio.h>
 * #include <math.h>
 * #include "general-header.h"

---

## system headers

 * #include <stdlib.h>
 * #include <stdio.h>

---

## non standard headers
 
 * #include <stdlib.h>
 * #include <stdio.h>
 * #include <math.h>
