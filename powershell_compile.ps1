## Manual compile on Win10:
## This will compile and build the cli terminal app on Win10 using Powershell.
## Must have Visual Studio installed with C++ in order to compile.

## External arument inputs
param( $inputArgs )

## Store the file name of this script
$scriptName = $MyInvocation.MyCommand.Name

function makeClean {
    Write-Host "Cleaning ...
    "
    ## clean previous builds
    if (Test-Path *.obj) {
        Write-Host "Removing the following:"
        Get-ChildItem *.obj
        Remove-Item *.obj
    }

    if (Test-Path *.exe) {
        Write-Host ""
        Write-Host "Removing the following:"
        Get-ChildItem *.exe
        Remove-Item *.exe
    }
    Write-Host "Done Cleaning.
    "
}

function makeBuild {
    Write-Host "Building ...
    "
    ## Compile and build object modules
    cl /c sources\my_calendar.c
    cl /c sources\my_csv_structs.c
    cl /c sources\my_tty_ui.c

    ## Build the executable file
    cl mainTTY.c my_calendar.obj my_csv_structs.obj my_tty_ui.obj
    Write-Host "Done Building.
    "
}

function makeRun {
    Write-Host "Running ...
    "
    ## Run
    .\mainTTY.exe
    Write-Host "Done Running.
    "
}

function menu {
    Write-Host ""
    Write-Host "$scriptName"
    Write-Host "
    About:
        This script is a DIY Makefile. Select from the following option.
        clean, build, run
        
    Important: 
        This script must run within: Developer Powershell for VS 2019+
        
    Run from terminal:
        .\$scriptName clean
        .\$scriptName build
        .\$scriptName run

    Options:
        clean:
            clear previous builds
        build:
            clear previous builds
            compile and build
        run:
            clear previous builds
            compile and build
            run the compile executable 'mainTTY.exe'
    "
    $userinput = Read-Host -Prompt "Type selection option [ clean, build, run ] "

    if ( $userinput -eq "clean" ) {
        Write-Host "You entered: $userinput"
        makeClean
    } elseif ( $userinput -eq "build" ) {
        Write-Host "You entered $userinput"
        makeClean
        makeBuild
    } elseif ( $userinput -eq "run" ) {
        Write-Host "You entered: $userinput"
        makeClean
        makeBuild
        makeRun
    } else {
        Write-Host "You entered: $userinput"
        Write-Host "    !!! bad input !!!
            Input only one of the following: 'clean', 'build', or 'run'.
        Try Again.
        "
        Write-Host "Done.
        "
    }

}

## main

switch ( $inputArgs ) {
    "clean" { makeClean }
    "build" { makeClean; makeBuild }
    "run"   { makeClean; makeBuild; makeRun }
    default { menu }
}
