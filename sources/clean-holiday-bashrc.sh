#!/bin/sh

uname -a | grep "GNU" &>/dev/null
isDebian=$?

if [ $isDebian -eq 0 ]; then
    command -v bash &>/dev/null
    isBash=$?

    if [ $isBash -eq 0 ]; then
        origianlBashrc=~/.bashrc
        backupBashrc=$origianlBashrc.backup_$(date +%d%b%Y%H%S)
        tempBashrc=$origianlBashrc.temp

        echo -e "#\tUpdate ~/.bashrc ..."

        ## make safety backups
        cp $origianlBashrc $backupBashrc
        cp $origianlBashrc $tempBashrc

        ## rm previous ttyBashrc calls
        sed -i "/## Special holiday bash text/d" $tempBashrc
        sed -i "/ttyBashrc/d" $tempBashrc

        ## rm empty lines
        sed -i "/^$/d" $tempBashrc

        mv $tempBashrc $origianlBashrc
        echo -e "#\tRemoved $(pwd)/ttyBashrc from ~/.bashrc ..."

        ## remove misc aliases and bin copies
        if [ -f man/printf-time ]; then rm man/printf-time; fi
        if [ -f /usr/bin/printf-time ]; then sudo rm /usr/bin/printf-time; fi
        if [ -f /usr/bin/ttyRosary ]; then sudo rm /usr/bin/ttyRosary; fi
        if [ -f /usr/bin/gtkRosary ]; then sudo rm /usr/bin/gtkRosary; fi

        if [ -f /usr/bin/ttyBashrc ]; then sudo rm /usr/bin/ttyBashrc; fi
        if [ -f /bin/ttyBashrc ]; then sudo rm /bin/ttyBashrc; fi

        echo -e "#\tRemoved misc aliases and bin copies ..."

    fi


fi
