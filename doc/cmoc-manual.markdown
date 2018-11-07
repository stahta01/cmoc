<head>
<title>The CMOC C-like 6809-targeting cross-compiler</title>
</head>
<body style="margin-left: 50px; margin-right: 50px; margin-top: 30px; margin-bottom: 30px;">

The CMOC C-like 6809-targeting cross-compiler
=============================================

**By Pierre Sarrazin**

`sarrazip@sarrazip.com`

Copyright &copy; 2003-2016

<http://sarrazip.com/dev/cmoc.html>

Distributed under the **GNU General Public License**,
**version 3 or later** (see the License section).

Version of CMOC covered by this manual: **0.1.32**

Date of this manual: 2016-09-17


Introduction
------------

CMOC is a [Unix](https://en.wikipedia.org/wiki/Unix)-based program that
compiles a [C](https://en.wikipedia.org/wiki/C_%28programming_language%29)-like
language, generates [Motorola 6809](https://en.wikipedia.org/wiki/Motorola_6809)
assembly language programs and assembles them into executables for the
[Color Computer](https://en.wikipedia.org/wiki/TRS-80_Color_Computer)'s
Disk Basic environment.  (As of version 0.1.18, targeting the
[Vectrex](https://en.wikipedia.org/wiki/Vectrex) video game console
is also supported.)

CMOC is not meant to be able to compile existing C programs.
It is a tool to develop new programs for the Color Computer (CoCo).

The efficiency of the generated machine language is modest,
but the resulting machine language will be faster
than the equivalent interpreted
[Color Basic](https://en.wikipedia.org/wiki/Color_BASIC) program.
This was the initial goal of the CMOC project.

The main features missing from C are longs, floats, const and
separate compilation.

CMOC itself is written in [C++](https://en.wikipedia.org/wiki/C%2B%2B)
for a Unix-like system.  The C++ source code is somewhat complicated
because of the anarchic development process that gave rise to CMOC.
Years ago, development was able to take off because having a working
product had higher priority than having a clean but theoretical design.


Features
--------

### Unsupported features

- [Floating-point](https://en.wikipedia.org/wiki/Floating_point) arithmetic
  (no float or double types).

- 32-bit arithmetic (no long type). Type char is 8 bits and short and int are 16 bits.

- The const keyword.

- Separate compilation (i.e., compiling several source files
  to several object files that get linked together).

- Bit fields.

- Type-safe function pointers.
  (The address of a function has type `void *`
  and the return type of a call through a pointer is assumed to be int.)

- Typedefs local to a function (global typedefs are supported).

- Structs local to a function (global structs are supported).

- Indirection of a pointer to a *struct* used as an r-value (e.g., `*ptr` alone).
  The l-value case is supported, e.g., `(*ptr).field`.

- Passing a struct by value to a function.

- Comma expressions (e.g., x = 1, y = 2, z = 3;).

- register, extern, static, volatile. The register keyword is accepted but ignored.

- [K&R](https://en.wikipedia.org/wiki/C_%28programming_language%29#K.26R_C)
  function definitions, i.e., f() int a; { ... }

- A continue statement in a switch() body.

- Implementing [Duff's device](https://en.wikipedia.org/wiki/Duff%27s_device)
  in a switch().

- Function-local [function prototypes](https://en.wikipedia.org/wiki/Function_prototype).
  All prototypes must be declared at global scope.

- Zero-element arrays.

### Supported C and C99 features

- Pointers, including pointers to pointers, etc.

- Structs, including a struct in a struct. Struct initializers.
  A struct must be declared at the global level.
  A reference to an undefined struct is accepted if the declaration
  or statement only refers to a pointer to such a struct.

- Anonymous structs.

- Assigning a struct value to another (e.g., `struct S a, b; a = b;`).
  Initializing a struct from another one is also supported (e.g.,
  `struct S a; struct S b = a;`).

- char (8 bits), int (16 bits), signed, unsigned, typedef (global only).
  A function's return type can be void.

- Declaring a variable in the middle of a function, as in
  [C99](https://en.wikipedia.org/wiki/C99).

- while, do, for, switch, continue, break.

- Declaring a for() loop's control variable in the for() itself as in C99,
  i.e., for (int i = 0; ...) {}.

- Declaring more than one variable on the same line, i.e., int a = 0, b = 1;

- [Variadic functions](https://en.wikipedia.org/wiki/Variadic_function),
  i.e., void foo(const char \*format, ...). There must be at least one named
  argument before the ellipsis (...), as in ISO C.

- Ending an initializer list with a comma.

- Use of the [C preprocessor](https://en.wikipedia.org/wiki/C_preprocessor)
  (the system's cpp is invoked): #include, #define, #ifdef, etc.
  (Use #includes instead of separating the program in more than one .c file.)

- Unions (since version 0.1.12).

- Enumerations (since version 0.1.29).

- Generating [OS-9](https://en.wikipedia.org/wiki/OS-9) executables (since
  version 0.1.15, using the `--os9` command-line option).

- [Goto](https://en.wikipedia.org/wiki/Goto) and non-case labeled statements.


Differences with C
------------------

CMOC is sometimes more strict than C on some points.
For instance, it is an error to call an undeclared function.

If a large discrepancy exists between C and CMOC,
a bug report should be filed.


Installing CMOC
---------------

The following instructions assume a Unix-like system.
A C++ compiler is necessary to compile CMOC.

### The compiler

Deploy the .tar.gz source archive in a directory, go to this directory,
read the generic installation instructions in the INSTALL file, then (typically)
give these commands:

> tar -xzf cmoc-0.1.XX.tar.gz

> cd cmoc-0.1.XX

> ./configure --prefix=/some/installation/dir

> make

> make install

The sudo prefix may be needed to do a `make install`
to a system directory like /usr/local/bin.

The "check" makefile target runs several unit tests.

The compiler executable is called "cmoc".

To generate the HTML documentation (this document), do `make html`, which
will create the file `doc/cmoc-manual.html`.


Running CMOC
------------

### Compiling a C program

The following must be in the path:

- A C preprocessor callable by the name "cpp".

- The [LWTOOLS](http://lwtools.projects.l-w.ca/) lwasm assembler.

To compile a program written in the file foo.c, run this command:

> cmoc foo.c

By default, the resulting .bin file will load at address $2800 on a CoCo
(see the `#pragma org` directive elsewhere in this manual).
The generated machine language is position-independent, so the .bin file
can be loaded with an offset, by passing a second argument to Disk Basic's
LOADM command.

Pass `--help` to cmoc to see the available options.

CMOC comes with a `writecocofile` command that can copy a .bin file
to a 35-track Disk Basic diskette image file. For example:

> writecocofile testing.dsk foo.bin

Pass `--help` to writecocofile for more options.

For more information on running a CoCo emulator on a GNU/Linux system, see
<http://sarrazip.com/emul-coco.html>.

### Disabling some optimizations

By default, all peephole optimizations are enabled.

The [peephole optimizer](https://en.wikipedia.org/wiki/Peephole_optimization)
can be disabled by passing the `-O0` option to the compiler.
This can be useful when one suspects that the compiler may have generated
invalid code.

Several peephole optimizations were contributed by Jamie Cho in early 2016
for version 0.1.20. They can be disabled by passing `-O1`.

Option `-O2` is equivalent to using the default (full) optimization level.

### Generated files

From the .c file passed to `cmoc`, the compiler generates these files:

- **.asm**: The assembler file written by CMOC. It contains `#include`
  statements that refer to stdlib.inc and stdlib-data.inc, which are
  typically installed in /usr/share/cmoc, or elsewhere depending
  on the installation prefix given to the `configure` script.

- **.i**: The .asm file as processed by the C preprocessor (cpp), using
  the include directories and defines passed to the `a09` assembler script.
  This file contains pure assembly, without #include statements or comments.

- **.lst**: The listing generated by the 6809 assembler (lwasm).
  This is useful to see exactly where the code and data end up in memory.

- **.hex**: The executable program in
  [Intel HEX format](http://en.wikipedia.org/wiki/Intel_HEX).
  This format is understood by the usim 6809 simulator that is used
  by the `make check` test suite.

- **.bin**: The executable in Disk Basic .bin format. This can be
  transfered to a CoCo or emulator and loaded with the LOADM command.
  (If compiling for OS-9&mdash;with the `--os9` command-line switch&mdash;the
  executable has the name of the C file without the extension.)

When distributing the .bin file to CoCo users, it is not
necessary or useful to accompany it with the other generated files.

### The Motorola S-record (SREC) format

Pass the `--srec` option to cmoc to make
it generate an executable in
[Motorola S-record format](https://en.wikipedia.org/wiki/SREC_%28file_format%29).
The additional file will have the .srec extension.

### The Vectrex video game console

The doc subdirectory of the source distribution contains
cmoc-vectrex.markdown, which gives Vectrex-specific instructions.
Giving the `make html` command will generate cmoc-vectrex.html,
which can be viewed in a browser.

Note that questions regarding Vectrex-specific issues should be
addressed to **Johan Van den Brande** at `johan@vandenbrande.com`.


Programming for CMOC
--------------------

### Signedness of integers

The compiler generally produces more efficient code for unsigned
arithmetic. Therefore, types `unsigned` and `unsigned char` should
be preferred to `int` and `char` where possible.

CMOC considers that the signedness of an additive of multiplicative
operation is the signedness of the left operand.

### Pre-increment vs. post-increment

The pre-increment (++i) typically generates one instruction less
than the post-increment (i++). This is because the post-increment
must yield the *initial* value of the variable. When this initial
value is not needed, it is advisable to use the pre-increment.

The same situation holds for the decrement operators.

### Origin address

To specify the origin address of the program, start your program with a
`#pragma org` directive. For example:

> \#pragma org 0x5C00

By default, the origin address is 0x2800. (Under Disk Basic, the
Basic program normally starts at 0x2601, because four PMODE pages
are reserved by default.)

### End address and length of the executable

To determine the effective start and end address of the executable
(assuming no relocation by LOADM), one can look up the `program_start`
and `program_end` symbols in the .lst listing file generated by the
assembler.

`program_end` is useful to check that the executable fits in the
available RAM. On a 32k CoCo, the RAM ends at $8000. By defaut,
Color Basic reserves 200 bytes for Basic strings, and before that,
the system stack should be given 512 bytes for a typical C program.
These assumptions mean that an executable should not go beyond $7D38.

**If a program crashes the CoCo just by getting loaded**, it could
be because it is too long and overwrites the system stack. The
`parse-coco-bin` Perl script, available on the CMOC home page,
can be useful to confirm that.

The following example program prints the start and end of the memory
it uses initially:

    #include <cmoc.h>
    int main()
    {
        char *s, *e;
        asm
        {
            leax    program_start,pcr
            stx     s
            leax    program_end,pcr
            stx     e
        }
        printf("START AT %p, END AT %p.\n", s, e);
        return 0;
    }

Note that the label addresses are taken relatively to the
program counter (`,pcr`), so that this program will report
the correct addresses even if the program is loaded at an
address other than the one specified in the .bin file.
(This can be done by passing a second argument to Disk Basic's
LOADM command.)

This section assumes that the code and data sections form a single
block.  When using the `#pragma data` directive (see elsewhere
in this manual), the *writable* globals will not be between
`program_start` and `program_end`.

As of version 0.1.20, CMOC automatically displays the program start
and end addresses, as well as the start and end of the writable data
section, when the `--verbose` option is passed.  In the following
example, `#pragma org` and `data` have been used to position the
code and data separately:

    Notable addresses:
      program_start             $C000
      program_end               $DC39
      writable_globals_start    $3800
      writable_globals_end      $3B7A

### Enforcing a limit address on the end of the program

As of version 0.1.20, CMOC accepts the `--limit=X` option.  When it
is passed, CMOC will fail if the end of the program, as indicated
by the `program_end` listing symbol, exceeds address X (specified
in hexadecimal).

For example, `--limit=7800` will keep the program from finishing
too close to the system stack under Disk Basic, which is not far
below $8000. A limit at $7800 leaves two kilobytes for the stack
and for Basic's string space.

It is not necessary to pass the `--verbose` option to use the
`--limit` option.

### Position-independent code

All 6809 code generated by CMOC is position-independent, i.e.,
it can be loaded at any address and will still work.

### Targeting CoCo Disk Basic or the USim 6809 simulator

By default, the compiler defines the `_COCO_BASIC_` preprocessor
identifier.  This identifier can be used to adapt a program to
make it use alternative code depending on whether it will run under
Disk Extended Color Basic or not.

By passing the `--usim` option, the compiler will target the USim
6809 simulator, which comes with CMOC.  No .bin file is produced
in this case.  The .hex file can be executed by passing its name to
`src/usim-0.91-cmoc/usim`.

### The standard library

CMOC's standard library is small. The program must `#include <cmoc.h>`
to use functions like printf(). See that file for a list of implemented C functions.
Most are standard C functions while others are CMOC extensions.

dwtoa(), meaning "double word to ASCII", is not a standard C function.
It takes an 11-character buffer and two
unsigned integers. It converts the 32-bit value formed by these integers into
an ASCII decimal represented stored in the buffer. The address of the first
character of this decimal string is returned. For example, this code returns a pointer
to a string equal to "65536".

    char buf[11];
    char *p = dwtoa(buf, 1, 0);

readline() acts like Basic's LINE INPUT command and returns the address of
the string entered.

Each assembly program generated by CMOC includes stdlib.inc, which assembles
to about 2000 bytes of machine code. In the future, a mechanism could be implemented
in the compiler to reduce this overhead. In the mean time, one can remove the
unneeded parts of this file, if memory is at a premium.

#### Size of the standard library

As of version 0.1.9, the standard library takes up almost 2048
bytes when all of its functions are called by the program.

But as of that version, only the standard library functions that
are actually called are included in the final assembly program.

A program that calls none of these functions will shed about 2000
of those bytes.

#### printf()

CMOC's printf() function supports %u, %d, %x, %X, %p, %s,
%c and %%. Specifying a field width is allowed, but
a left justification is only supported for strings, i.e.,
`%-15s` will work, but `%-6u` will not.
Zero padding for a number is supported (e.g., `%04x`).

%p always precedes the hexadecimal digits with `$`, as per
the CoCo assembly language notation. %x and %X do not generate
such a prefix. %p, %x and %X always print letter digits as
capital letters (A to F, not a to f).

printf(), like putchar() and putstr(), sends its output one
character at a time to Color Basic's PUTCHR routine, whose
address is taken from $A002.

#### Redirecting the output of printf()

The standard library's printf() writes the characters of the formatted
string by calling the routine whose address is stored in the library's
CHROUT global variable (not to be confused with Color Basic's CHROUT
vector at $A002).
The same applies to functions sprintf(), putchar() and putstr().

By default, under Color Basic,
that routine is the one found in that $A002 vector.
To designate a C function as the new character output routine,
first define the new routine:

    void newOutputRoutine()
    {
        char ch;
        asm
        {
            pshs    x,b  // preserve registers used by this routine
            sta     ch
        }
        
        // Insert C statements that print or otherwise process 'ch'.

        asm
        {
            puls    b,x
        }
    }

This routine will receive the character to be printed in register A.
It **must** preserve registers B, X, Y and U.
It does not have to preserve A.

Install it at the appropriate time with this call:

    void *oldCHROOT;

    oldCHROOT = setConsoleOutHook(newOutputRoutine).

To restore the original output routine, do this:

    setConsoleOutHook(oldCHROOT);

#### sprintf()

This function is like printf(), but it writes into a memory buffer
whose address is passed as the first argument, before the format string.
For example:

    char greeting[32];
    void f(char *name)
    {
        sprintf(greeting, "Hello, %s.", name);
    }

Calling f("Lonnie") will write "Hello, Lonnie." in the greeting[] array,
including a terminating '\0' character. A total of 15 bytes
get written to the start of that array. 

The **caller is responsible for providing a buffer long enough** to
receive all the text resulting from the format string and its arguments,
*including the terminating '\0' character*.

In this example, the longest "name" that can be safely passed to f()
would be a 23-character name.

The standard C language offers snprintf(), which is safer because it requires
passing the length of the destination buffer. But checking for
this limit would have a performance hit that is not necessarily
acceptable on a CoCo. If such a function is needed, it can be
implemented using the technique described in the previous section.

#### Redefining a standard library function

Defining a function using the name of a standard library function
is allowed.  For example, a program could redefine `rand()` and
`srand()` to implement an alternative random number generator.
In the final assembly program, such functions replace the ones
provided by the standard library.

#### Dynamic memory allocation with sbrk()

sbrk() is a function that dynamically allocates a region of memory
of the size (in bytes) passed to it as an argument. It returns a
void pointer. If the quantity of memory requested is not available,
sbrk() returns `(void *) -1`. For example:

    void *p = sbrk(100);
    if (p != (void *) -1)
        memset(p, 'X', 100);

The name of the function comes from the notion of a "program break",
which is the current end of the memory allocated to the program.
The memory after that is presumed to be free for dynamic allocation.

In the case of the CoCo, the assumption is that the program is loaded
after the Basic program and variables. This means the space that
sbrk() can allocate from goes from there to the top of the stack,
which is around $3F00 on a 16K CoCo and $7F00 on a 32K-or-more CoCo.

To determine how much of that memory is available for sbrk(),
call sbrkmax(), which returns the number of bytes as a size\_t
(unsigned). CMOC ends the region available to sbrk() about 1024 bytes
before the stack pointer, leaving those bytes to program calls and
local variables.

sbrkmax() returns 0 if the program is loaded after the stack space.

Be careful when using both sbrk() and #pragma const\_data (see
previous section). If the data is not positioned correctly, sbrk()
calls may end up allocating memory that is used by some global
variables.


### Inline assembly

Inline assembly text can be specified by surrouding it with `asm {`
and `}`. In the text, one can refer to C variables (global, local
and parameters) as well as functions.
Labels can be used
for branch instructions, but a label must either be unique to the whole program
or comply with what lwasm considers a "local" label.
Prefixing a global label with the name of the current C function is a
good way to help prevent clashes. A label must appear at the
very beginning of the line, without spaces or tabs in front of it.

One way of using lwasm **local labels** is to prefix the label name with
the @ character. Such a label will be local to the current block, which
will begin at the previous blank line (or start of the `asm` block) and
end at the next blank line (or end of the `asm` block). Refer to the
[LWASM manual about its symbols](http://lwtools.projects.l-w.ca/manual/manual.html#AEN237)
for details on using local labels.

The following example fills array `out` with `n` copies of character `ch`,
then returns the address that follows the region written to:

    #include <cmoc.h>

    char *f(char *out, char ch, unsigned char n)
    {
        char *end;
        asm
        {
            ldx     out         /* comments must be C style */
            lda     ch          // or C++ style
            ldb     n
    f_loop:
            sta     ,x+
            decb
            bne     f_loop
            stx     end
        }
        return end;
    }

    int main()
    {
        char a[10];
        a[9] = '\0';
        char *p = f(a, 'X', (unsigned char) sizeof(a) - 1);
        printf("a='%s', %p, %p\n", a, a, p);
        return 0;
    }

Since version 0.1.21, when referring to a C function, the function
name is replaced with its assembly label, possibly followed by the
`,pcr` suffix.  This suffix is omitted if the instruction is BSR,
LBSR or JSR, because these instructions do not support the `,pcr` suffix and
they do not need it anyway.  The following example calls the same C
function three different ways:

    asm
    {
        jsr     someCFunction
        lbsr    someCFunction
        leax    someCFunction
        jsr     ,x
    }

Note that CMOC always generates position independent code. This rule
should be maintained in inline assembly if the resulting program is to
be relocatable.

The BSR instruction is not recommended because it is a short branch
and if the called function is too far from the call, the assembly
step will fail.


#### Preprocessor identifiers in inline assembly

The GNU C preprocessor can add spaces in surprising ways, which makes its
use slightly problematic in inline assembly. For example:

    #define PIA0 0xFF00

    asm
    {
        stb     PIA0+2
    }

One would expect this code to generate an `stb 0xFF02` instruction,
but cpp will actually expand this to `stb 0xFF00 +2`, because it
apparently adds a space after the expansion of the PIA0 identifier.

lwasm takes this space as the start of the comment, so it ignores
the +2 and assembles `stb $FF00`.

A workaround appears to be reverse the addition and write `stb 2+PIA0`.
No space gets added before the identifier.

Therefore, preprocessor identifiers should be used with caution in
inline assembly.


#### Referring to variables whose name is that of a register

Before version 0.1.31, bad assembly language text could be emitted
if inline assembly referred to a C variable that has the name of a
register. To help resolve this ambiguity, version 0.1.31 introduced
a _C variable escape character_, which is a colon that is put in
front of the C variable name.

For example:

    char b;
    asm
    {
        inc     :b
        ldb     :b
        leax    b,x
    }

Here, `:b` refers to variable _b_ of the C program, while the _b_
in _b,x_ refers to the register.

This change may break inline assembly code in programs that were
written for versions of CMOC preceding 0.1.31. Adding a colon at
the right places will resolve the issue.

Note that the escape character is not necessary on variable names
that are not also register names.


#### Assembly-only functions

When a function is written entirely in assembly language for
performance reasons, the stack frame may not be necessary.
CMOC will not generate a stack frame for a function defined
with the `asm` modifier, as in this example:

    asm int f(int m, int n)
    {
        // U not pushed, so 1st argument is at 2,s
        asm
        {
            ldd 2,s     // load m
            addd 4,s    // add n, leave return value in D
        }
    }

Only `asm { ... }` statements are allowed in such a function.
Typically, only one is needed. Local variables cannot be defined
in that function and the function's parameters cannot be accessed
by name.  The assembly code is allowed to refer to global
variables however.

CMOC still ends the function with the RTS instruction
(or RTI if the function is declared with the `interrupt` modifier.)

See the *Calling convention* section elsewhere in this manual
for the rules to observe. In particular, note that byte arguments
are promoted to words, which are pushed onto the stack in the big
endian byte ordering.

#### Functions that are only called by assembly code

Normally, CMOC does not emit code for a function that is never
called and whose address is never taken. But such a function
could still be called by inline assembly. This can lead to an
assembler error that complains that the LBSR or JSR argument
is not defined.

CMOC can be forced to emit all functions by passing it the
`--emit-uncalled` option.


### Interrupt Service Routines

CMOC supports the `interrupt` function modifier, which tells the
compiler to end the function with an RTI instruction instead of
an RTS. For example:

    interrupt void newCoCoIRQRoutine()
    {
        asm
        {
            lda     $FF03           // check for 60 Hz interrupt
            bpl     irqISR_end      // return if 63.5 us interrupt
            lda     $FF02           // reset PIA0, port B interrupt flag
        }

        // Do something in C.

        asm
        {
    irqISR_end:
        }
        // Nothing here, so that next instruction is RTI.
    }


### Function pointers

The address of a function can be taken and stored in order to be
called through that pointer later. However, unlike in the C language,
a CMOC function pointer expression always has type `void *`.

This means that function pointers are not type-safe with CMOC.

The following example shows that the two syntaxes used in C to call
a function through a pointer are supported by CMOC:

    unsigned char f(int a, char b) { ... }
    int main()
    {
        void *pf = f;
        unsigned char c0 = (unsigned char) (*pf)(1000, 'x');
        unsigned char c1 = (unsigned char) pf(1001, 'y');
        return 0;
    }

Because CMOC does not know the return type of such a call, it is
important to cast it to the exact type returned by the function
that is actually called.

A member of a struct can point to a function. For example:

    struct S
    {
        void *fp;
    };
    void g() { ... }
    int main()
    {
        struct S s = { g };  // member 'fp' points to g()
        s.fp();  // call g()
        return 0;
    }

Since version 0.1.28, CMOC supports the full function pointer
notation, e.g., `int (*pf)(char, int *, char[])`, but the
effective type of such a pointer is still `void *`. This full
notation can be used to declare a variable but also a function
parameter.


### Array initializers

#### Local vs. global array

When only a single function needs to use a read-only array of
integers, this array could be defined locally to that function,
but it is more efficient, as of CMOC 0.1.10 to define the array as
global. This is because the global array will be emitted as a
sequence of FCB or FDB directives, while a local array will be
initialized with a series of load and store instructions.

In the following example, array `g` will be initialized more
efficiently than array `l`:

    int g[] = { 55, 66, 77 };
    void f()
    {
        int l[] = { 22, 33, 44 };
        /* ... */
    }


#### Execution of global array initializers

A global array initializer containing only integer values (not
string literals) is treated specially. It is initialized
at compile-time, not at run-time. This means that if the program
modifies the array, quits, and then is reexecuted, the modified
contents will still appear as is. The array will not be reinitialized
to the values in the initializer.

For example:

    int a[2] = { 13, 17 };
    int main() { a[0]++; printf("%d\n", a[0]); }

The first time this program is executed, a[0] starts at 13,
it is incremented to 14, which is the number that is printed.

The second time this program is executed, a[0] starts at 14
because array `a` is _not_ reinitialized upon entry.

This is meant to save memory by not including a second copy
of the initializer just for run-time initialization purposes.


### Enumerations (enum)

Enumerations are supported, with the restriction that an enum must
be declared at the global scope. In particular, an enum with an
enumerator list (e.g., `enum { A, B }`) cannot be used in the formal
parameter of a function, nor as its return type.

An enum can be anonymous (e.g., `enum { A, B }`) or be given a name
(e.g., `enum E { A, B }`).

Each enumerated name can have a specified value, e.g.,
`enum { SCREEN = 0x0400, BIT5 = 1 << 5 }`. Such a value must be
a constant expression.


### Compiling a ROM image for a cartridge

To help support the ROM cartridge format, CMOC supports directives
that allow telling it to assemble the code, the string literals
and the read-only global variables at the typical cartridge ROM
address of $C000, while mapping the writable global variables
at a RAM address like $3800.

This is achieved by using the four #pragma directives that
appear in this example:

    #pragma org $C000
    #pragma data $3800

    int f() { return 42; }
    int writableGlobal = f();

    #pragma const_data start
    int readOnlyGlobal = 100;
    unsigned char byteArray[3] = { 11, 22, 33 };
    char text[] = "hello";
    #pragma const_data end

    int anotherWritableGlobal;

    int main()
    {
        anotherWritableGlobal = 99;
        return 0;
    }

Note that `writableGlobal` is allowed to have a run-time initializer
because it is writable.

`readOnlyGlobal`, `byteArray` and `text` are read-only because they appear
between the `const_data` directives. More than one such section can
appear in the same program.

In the case of `text`, the use of the empty brackets is necessary:
declaring text as `char *text` would be rejected by CMOC.
This is because `text` would then be a pointer whose initialization
would have to be at run-time, because the address of a string literal
depends on where the program is loaded by the user.

`anotherWritableGlobal` is writable because it is not in a `const_data`
section. It is allowed to have no initializer because it is writable.

Using sbrk() can be dangerous depending on where in memory the
writable data section is positioned.

After compiling the program, the .bin file normally contains
a single contiguous block of code. Extract this block with
this Perl command:

    perl -e 'sysread(STDIN,$h,5)==5 or die;
             sysread(STDIN,$rom,0xFFFF)>0 or die;
             print substr($rom,0,length($rom)-5)' <foo.bin >foo.rom

This ROM image can be tested in the XRoar emulator this way:

    xroar -machine cocous -cart-autorun -cart color8.rom

Note that XRoar requires the image file to have the .rom extension.

Note that in a program written as above, the IRQ interrupt is
not enabled, so Basic's TIMER counter (at $0112) does not get
incremented. To enable the IRQ in your catridge-based program,
put this at the beginning of the main() function:

    asm
    {
        // We come here from a JMP $C000 in Color Basic (normally at $A10A in v1.2).
        // At this point, the 60 Hz interrupt has not been enabled yet, so enable it.
        lda     $ff03   // get control register of PIA0, port B
        ora     #1
        sta     $ff03   // enable 60 Hz interrupt

        // Unmask interrupts to allow the timer IRQ to be processed.
        andcc   #$af
    }


### Detecting null pointer accesses at run time

Accessing a value through a null pointer is a common bug.
To help detect such accesses, CMOC has the --check-null command-line
option, which adds run-time checks before every use of a pointer and
every array element access.

By default, the handler that is invoked when a null pointer access
is detected is a no-op. The program should start by calling the
`set_null_ptr_handler()` function to set up a handler that will
receive the address of the failed check as an argument. For example:

    #include <cmoc.h>

    struct S { int n; };

    void nullPointerHandler(char *addressOfFailedCheck)
    {
        printf("[FAIL: %p]\n", addressOfFailedCheck);
        exit(1);
    }

    int main()
    {
        set_null_ptr_handler(nullPointerHandler);
        struct S *p = 0;
        p->n = 42;
        return 0;
    }

This program will fail and display an address.  One can then look up
this address in the .lst listing file generated by CMOC to determine
in which function that null pointer was detected.

Using this option incurs a performance cost, so it is only recommended
during debugging. An alternative is to define an `assert()` macro that
expands to nothing when `NDEBUG` is defined.


### Detecting stack overflows at run time

Runaway recursion or excessively long local arrays can cause corruption
that is difficult to investigate. To help detect stack overflows,
CMOC has the --check-stack command-line option, which adds run-time checks
at the beginning of each function body.

When passing --check-stack to CMOC, the program should start with
a call to `set_stack_overflow_handler()` that installs a handler.
This handler receives two arguments: the address of the failed check
and the out-of-range stack pointer. The handler must not return.
For example:

    void stackOverflowHandler(char *addressOfFailedCheck, char *stackRegister)
    {
        printf("[FAIL: %p, %p]\n", addressOfFailedCheck, stackRegister);
        exit(1);
    }
    void recurse() { recurse(); }
    int main()
    {
        set_stack_overflow_handler(stackOverflowHandler);
        recurse();
        return 0;
    }

This program will fail and display two addresses. One can look up
the first one in the .lst listing file generated by CMOC to determine
in which function that stack overflow was detected.

Using this option incurs a performance cost, so it is only recommended
during debugging.

CMOC allocates 1024 bytes for the stack. In a program that is compiled
with the default layout, the stack is preceded by the memory managed
by sbrk() (see elsewhere in this manual).


### Single-execution programs

If a program is intended to be executable only once, i.e., that
reloading it or rebooting the CoCo is required to run it again,
then the code that initializes the writable global variables is
not needed upon entry to function main().

This routine is assembled at the very end of the code section.
When the program specifies `#pragma exec_once`, then the "program
break" used by sbrk() (see the previous section) is placed at
the start of the routine. This makes the memory of that routine
available to be allocated by sbrk().


### Calling convention

CMOC follows the C convention of passing the parameters in the stack
in the reverse order.

The caller pops them off the stack after the call.

An argument of type `char`, which is signed, is promoted to `int`.

An argument of type `unsigned char` is promoted to `unsigned int`.

When the return value is requested to be an r-value, is expected in
the B register for a byte-size type or D for a word-size type. For
an l-value, the return value must be left in X.

The body of a function must preserve registers U and S. It is
allowed to modify A, B, X and CC. 

**Under OS-9, CMOC uses Y to refer to the data section** of the current
process. Any code that needs to use Y must preserve its value and
restore it when finished.

The called function does not have to return any particular condition
codes.

Register DP is not used or modified by CMOC-generated code.

A CMOC-generated function uses a stack frame if the function receives
one or more parameters or has local variables, and is not defined
with the `asm` keyword (see the *Assembly-only functions* section
elsewhere in this manual).
Register U is used as the stack frame
pointer. Such a function starts with these instructions:

        PSHS    U       
        LEAU    ,S

an ends with these:

        LEAS    ,U
        PULS    U,PC    


### Compiling a program executable by the DOS command

Disk Basic 1.1 has a DOS command that loads track 34 at $2600
and if the contents start with the bytes 'O' and 'S', the interpreter
jumps at $2602.

CMOC can accommodate this with its --dos option. It implies --coco,
it uses $2600 as the code origin, and it generates the "OS" marker
at that address.

The output is still a .bin file. CMOC comes with a command-line tool
called `install-coco-boot-loader` that takes this file and copies
it to track 34 of a DECB disk image. For example:

    cmoc --dos prog.c
    install-coco-boot-loader foo.dsk prog.bin

This tool will fail if track 34 is already occupied. It has a `--force`
option that will install the boot leader despite that.

To uninstall the boot loader, use the `--uninstall` option:

    install-coco-boot-loader --uninstall foo.dsk


### Unused functions

A C function that is not called and whose address is not taken will
not have assembly language generated for it by CMOC.

This means that a library can be implemented as a header file
containing several functions, without having to worry about bloating
an executable that would only use some of those functions.


License
-------

**EXCEPT FOR THE FILES UNDER src/usim-0.91-cmoc in the CMOC source archive,
CMOC is distributed under the following license:**

This program is free software: you can redistribute it and/or modify
it under the terms of the **GNU General Public License** as published by
the Free Software Foundation, **either version 3 of the License, or
(at your option) any later version.**

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

</body>
