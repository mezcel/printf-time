:: Makefile_win.bat

:: Manual compile on Win10:
:: This will compile and build the cli terminal app on Win10.
:: This script must be run within Visual Studio's Developer CommandPrompt.

:: silence terminal while the script loads
@echo off
::@cls

:: Input external arguments, global var
SET userinput=%1

::::::::::::::::::: main menu function :::::::::::::::::::

:about
    IF "%userinput%"=="clean" GOTO menuOptions
    IF %userinput%=="build" GOTO menuOptions
    IF %userinput%=="run" GOTO menuOptions

    :: splash screen and instructions
    ECHO.
    ECHO ---------------------------------------------------
    ECHO Compile and build a CLI scripture Rosary on Win10.
    ECHO.
    ECHO About:
    ECHO        This script is a DIY Makefile. Select from the following option.
    ECHO        clean, build, run
    ECHO.
    ECHO    Important:
    ECHO        This script must run within: Developer CommandPrompt for VS 2019+
    ECHO        The executable will be mainTTY.exe
    ECHO.
    ECHO    Options:
    ECHO        clean:
    ECHO            clear previous builds
    ECHO        build:
    ECHO            clear previous builds
    ECHO            compile and build
    ECHO        run:
    ECHO            clear previous builds
    ECHO            compile and build
    ECHO            run the compile executable 'mainTTY.exe'
    ECHO        quit:
    ECHO            do nothing, abort script
    ECHO ---------------------------------------------------
    ECHO.

    SET /P userinput= Type selection option [ clean, build, run ] :

:menuOptions
    IF "%userinput%"=="quit" (
		GOTO EOF
	)
    IF "%userinput%"=="clean" (
        CALL :makeClean EOF
    )
    IF "%userinput%"=="build" (
        CALL :makeClean EOF
        CALL :makeBuild EOF
    )
    IF "%userinput%"=="run" (
        CALL :makeClean EOF
        CALL :makeBuild EOF
        CALL :makeRun EOF
    )

    :: Terminate script
    EXIT /B 0

::::::::::::::::::::: menu functions :::::::::::::::::::::

:makeClean
    ECHO Cleaning ...
    :: clean previous builds
    IF EXIST *.obj DEL /F *.obj
    IF EXIST *.exe DEL /F *.exe
    ::EXIT /B 0
    GOTO %~1

:makeBuild
    ECHO Building ...
    :: Compile and build object modules
    cl /c sources\my_calendar.c
    cl /c sources\my_csv_structs.c
    cl /c sources\my_tty_ui.c

    :: Build the executable file
    cl mainTTY.c my_calendar.obj my_csv_structs.obj my_tty_ui.obj
    ::EXIT /B 0
    GOTO %~1

:makeRun
    ECHO Running ...
    :: Run
    IF EXIST .\mainTTY.exe CALL .\mainTTY.exe
    ::EXIT /B 0
    GOTO %~1


@echo on
:EOF
    :: End of file marker
    ECHO Done.
