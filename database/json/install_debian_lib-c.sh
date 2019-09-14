#!/bin/bash

## https://packages.debian.org/search?searchon=sourcenames&keywords=json-c
## https://packages.debian.org/source/stretch/json-c

## build dependency
sudo apt install autotools-dev debhelper dh-autoreconf dh-exec

## stretch (libs): 0.12.1-1.1
sudo apt install libjson-c-dev libjson-c-doc libjson-c3
