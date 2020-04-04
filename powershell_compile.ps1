<#
    Manual compile on Win10:
        This will compile and build the cli terminal app on Win10 using Powershell.
        Must have Visual Studio installed with C++ in order to compile.
#>

## clean previous builds
del *.obj
del *.exe

## Compile and build object modules
cl sources\my_calendar.c
cl sources\my_csv_structs.c
cl sources\my_tty_ui.c

## Build the executable file
cl mainTTY.c my_calendar.obj my_csv_structs.obj my_tty_ui.obj

## Run
.\mainTTY.exe