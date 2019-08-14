### GDB Notes

##### Compile and launch

* compile .c code using -g flag
    * gcc mycode.c -g
    * note: ```a.out``` is the default ```-o```

* launch gdb with an optional terminal user interface (TUI)
    * ```gdbtui a.out``` or ```gdb a.out -tui```

### gdb commands

| text command | result |
| --- | --- |
| help <command> | get help using a command |
| ```r``` or ```run``` | run the prgm |
| ```b`` or ```break``` | set a break point at a line number or function name |
| ```s``` or ```step``` | step to the next line in the code sequence |
| ```n``` or ```next``` | step to the next step opver a subroutine/function |
| ```p``` or ```print``` | print variable value |

## GDB Background

[manual](https://www.gnu.org/software/gdb/documentation/) - gnu.org

If you dont use GDB on the CLI or a traditional IDE, you can uses this Atom.io package, [dbg-gdb](https://atom.io/packages/dbg-gdb)

### The neat thing is ...

The compiler can re-render the code more efficiently than the programmer/user. (every case varies)

Sometime the ASM will illustrate this, but ultimately the optimizations will be in the executable binary.
