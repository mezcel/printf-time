#!/bin/sh

#uname -v | grep "Debian" &>/dev/null
#isDebian=$?

command -v bash &>/dev/null
isBash=$?

if [ $isBash -eq 0 ]; then
    echo "Make a bashrc alias"
else
    echo "canceled bashrc alias"
fi
