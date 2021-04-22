#!/bin/bash

uname -a | grep "GNU" &>/dev/null
isDebian=$?

uname -a | grep "CYGWIN" &>/dev/null
isCygwin=$?

isUnixPass=1

if [ $isDebian -eq 0 ]; then
    ## Debian Linux or WSL Debian
    echo -e "#\tDebian detected ..."
    isUnixPass=0
elif [ $isCygwin -eq 0 ]; then
    ## CYGWIN Gnu
    echo -e "#\tCygwin detected ..."
    isUnixPass=0
else
    echo "#\tDebian and Cygwin is not detected."
fi

if [ $isUnixPass -eq 0 ]; then
    command -v bash &>/dev/null
    isBash=$?

    if [ $isBash -eq 0 ]; then
        echo -e "#\tBash Detected ..."

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

        #echo -e "currentDir=\$(pwd); cd $projectRoot; ./ttyBashrc; cd \$currentDir" >> $tempBashrc
        #echo -e "exec $(pwd)/ttyBashrc -d $(pwd)/" >> $tempBashrc
        #echo -e "ttyBashrc -d $(pwd)/database/" >> $tempBashrc
		
		if [ $isCygwin -eq 0 ]; then
	        echo -e "alias ttyBashrc.exe=\"ttyBashrc -d $(pwd)/database/\"\nttyBashrc.exe" >> $tempBashrc
		else
	        echo -e "alias ttyBashrc=\"ttyBashrc -d $(pwd)/database/\"\nttyBashrc" >> $tempBashrc
		fi

        mv $tempBashrc $origianlBashrc
        echo -e "#\tAppended $(pwd)/ttyBashrc to ~/.bashrc ..."


        #sudo ln -s ttyBashrc /usr/bin/ttyBashrc
		
		command -v sudo &>/dev/null
		isSudo=$?
		if [ $isSudo -eq 0 ]; then
			sudo cp ttyBashrc /usr/bin/
        else
            cp ttyBashrc /usr/bin/
		fi

		echo -e "#\tMade global user /usr/bin/ttyBashrc copy..."

    fi
fi
