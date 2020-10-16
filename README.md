<!-- pandoc formatting
title: 'printf-time'
subtitle: 'A scripture Rosary written in C for Win10's VS'
author: 'Mezcel'
date: 'Jan 1, 2019'
description: 'Scripture rosary using English and Latin Bible text.'
lang: en-US
-->

# printf-time

branch: ```visual-studio```
* This branch will not be merged into ```master```.
    * It is just a workaround for the Visual Studio 2019 C++ IDE.
* This branch contains from the ```master``` branch which are unused in this branch.

## About

A **( Latin / English )** scripture **Rosary** written in C/GCC for TTY. It uses CSV database. The CSV contains NAB quotes in English.

## Visual Studio 2019 IDE

The ```visual-studio``` branch is a Win10 fork of the Linux compatible ```master``` branch.

* Project file: ```printf-time.vcxproj```
* The GTK or the JSON features available in the Linux compatible ```master``` branch are commented out.
* Warnings regarding time.h function calls are suppressed because C++ prefers alternative functions over the C compatible functions used in this program.

### Unused resources

* ```database/json/*```
* ```sources/my_gtk3.api.c```, ```my_json_structs.c```, ```my_tty_ui_posix.c```
* ```headers/my_gtk3_api.h```
* ```Makefile```, ```*.bat```, ```*.ps1```
* ```mainTTY.c```, ```mainGtk3.c```

### Dependencies

Minimal Requirements:
- Desktop Development with C++ from the Visual Studio Installer.

