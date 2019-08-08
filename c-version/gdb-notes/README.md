### GEB Notes

* compile .c code using -g flag
    * gcc mycode.c -g
    * note: a.out is the default -o
* launch gdb with an optional terminal user interface (TUI)
    * ```gdbtui a.out``` or ```gdb a.out -tui```

### gdb commands

| text command | result |
| --- | --- |
| help <command> | get help using a command |
| ```r``` or ```run``` | run the prgm |
| ```b`` or ```break``` | set a break point at a line number or function name |
| ```s``` or ```step``` | step to the next line in the code sequence |
| ```n``` or ```next``` | step to the next step opver a subroutine/function

