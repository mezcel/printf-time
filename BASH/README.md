# bashPFMday.bash

Shell script will gcc compile, build, execute the C program.

The program output will be saved into bash variables and its contents will be parsed

The desired parced output is the PFM date. (last printf line output)

The PFM date string will be further converted by Bash into a detailed date time format.

### Example Input:
```bash
## Compile/build the C code using gcc and make the main executable
gcc -o easter-algorithm main.c -lm

## Store printf output to bash var
printfcapture=$(./easter-algorithm)

## parse only the last output line
lastline=$(echo "$printfcapture" | tail -n1)

## use printf string to generate a Bash date
date --date=$lastline
```

### Example Output:

```bash
Thu Apr 18 00:00:00 EDT 2019

```
