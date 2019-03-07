#!/bin/bash

## cd into the repo's source code dir
cd ../c/

## Compile/build the C code using gcc and make the main executable
gcc -o easter-algorithm main.c -lm

## Store printf output to bash var
printfcapture=$(./easter-algorithm)

## parse only the last output line
lastline=$(echo "$printfcapture" | tail -n1)

## use printf string to generate a Bash date
date --date=$lastline
