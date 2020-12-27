% PRINTF-TIME(1)
% Mezcel
% 2019

# NAME

printf-time - an English & Latin scripture Rosary for TTY and GTK

# SYNOPSIS

**ttyRosary** [**options**] -v tag

**gtkRosary** [**options**] -v tag

**ttyBashrc**

**manpage**

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

**./ttyBashrc**
: This display today's liturgical season, feast day information, and display a season appropriate scripture quote from the rosary database. It's intended usecase is to display a header text on each new instance a virtual terminal is launched.

# PRIMARY UI KEY BINDINGS (ROSARY)

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

# BASHRC

**Using ./ttyBashrc with ~/.bashrc**
: Run the ./ttyBashrc executable from wherever it was compiled from. The following is an example of how the ~/.bashrc should be appended.

**Assuming: git clone https://github.com/mezcel/printf-time.git ~/github/mezcel/printf-time.git**
: currentDir=$(pwd); cd /home/$(whoami)/github/mezcel/printf-time.git; ./ttyBashrc; cd $currentDir

# MAN PAGE

Render a man page from a markdown. Must have pandoc installed.

**Debian External Prerequisites:**
: sudo apt install -y man-db groff pandoc

**Usecase Example:**
: Global Manpage: pandoc ./man/manpage.md -s -t man > /usr/bin/printf-time
: Local Manpage: pandoc ./man/manpage.md -s -t man > ./man/printf-time

# GIT

**github:**
: https://github.com/mezcel/printf-time.git
