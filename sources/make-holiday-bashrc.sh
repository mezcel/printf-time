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

        echo -e "\n## Special holiday bash text" >> $tempBashrc
        projectRoot=$(pwd)

        echo -e "currentDir=\$(pwd); cd $projectRoot; ./ttyBashrc; cd \$currentDir" >> $tempBashrc

        mv $tempBashrc $origianlBashrc
        echo -e "#\tAppended $(pwd)/ttyBashrc to ~/.bashrc ..."
    fi
fi
