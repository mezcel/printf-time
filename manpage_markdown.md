% PRINTF-TIME(1)
% Mezcel
% 2019

# NAME

printf-time - an English & Latin scripture Rosary for TTY and GTK

# SYNOPSIS

**ttyRosary** [**options**] -v tag

**gtkRosary** [**options**] -v tag

# DESCRIPTION

printf-time is a  scripture rosary written in C/GCC for the GTK and the TTY. It uses both a CSV and a JSON Database. The CSV contains NAB quotes in English and the JSON contains Vulgate quotes in Latin.

# RESOURCES

This manual contains instruction on how to use printf-time.

# OPTIONS

**-v**
:   Vulgate Latin translation flag.

USECASE EXAMPLE:

**./ttyRosary -v**
: Use latin biblical readings from the St. Jerome's Vulgate. The Vulgate is stored on a JSON database file.

**./ttyRosary**
: Use English biblical readings from the USCCB's New American Bible (NAB). The NAB is stored on a CSV database file.

# KEY BINDINGS

**q**
: quit app

**a, h, b, back arrow, spacebar**
: navigate backwards

**d, l, n, right arrow, enter**
: navigate forwards

**w, s, j, k, up arrow, down arrow**
: show information about using printf-time

# SEE ALSO

gcc, printf, make, tty, gtk3, pandoc, c-json

# MAN PAGE

Render a man page from a markdown. Must have pandoc installed.

**Example:**
: pandoc .manpage_markdown.md -s -t man > /usr/bin/printf_time

# GIT

**github:**
: https://github.com/mezcel/printf-time.git