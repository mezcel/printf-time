#!/bin/sh

uname -v | grep "Debian" &>/dev/null
isDebian=$?

if [ $isDebian -eq 0 ]; then
    command -v bash &>/dev/null
    isBash=$?

    if [ $isBash -eq 0 ]; then

        origianlBashrc=~/.bashrc
        backupBashrc=$origianlBashrc.backup_$(date +%d%b%Y%H%S)
        tempBashrc=$origianlBashrc.temp

        echo "Update ~/.bashrc ..."

        cp $origianlBashrc $backupBashrc
        cp $origianlBashrc $tempBashrc

        sed -i "/## Special holiday bash text/d" $tempBashrc
        sed -i "/ttyBashrc/d" $tempBashrc

        echo "Appended $(pwd)/ttyBashrc to ~/.bashrc ..."
        echo -e "\n## Special holiday bash text" >> $tempBashrc
        echo -e "$(pwd)/ttyBashrc" >> $tempBashrc

        sudo mv $tempBashrc $origianlBashrc
    fi
fi
