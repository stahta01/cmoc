<head>
<title>CMOC Implementation Guide</title>
</head>
<body style="margin-left: 50px; margin-right: 50px; margin-top: 30px; margin-bottom: 30px;">

CMOC Implementation Guide
=========================

**By Pierre Sarrazin**

`sarrazip@sarrazip.com`

Copyright &copy; 2003-2016

<http://sarrazip.com/dev/cmoc.html>

Distributed under the **GNU General Public License**,
**version 3 or later** (see the License section).

Date of this manual: 2016-05-19


Introduction
------------

This guide describes the implementation of the CMOC compiler. To
learn how to use it, refer to the CMOC Manual, distributed with
CMOC as cmoc-manual.markdown.

CMOC is written in C++, GNU Bison and GNU Flex.


Compiler structure
------------------

The main phases of this compiler are the following:

1. Lexical analysis.
1. Syntactic analysis.
1. Semantic checking.
1. Code generation.
1. Low-level optimization.


### Lexical analysis

This phase reads a file of characters and produces a stream of tokens.
The file `lexer.ll` is a GNU Flex source file that gets converted
into a C++ file named `lexer.cc`. The list of all token names
(e.g., INT, CHAR, etc.) is defined with `%token` directives in the
parser.yy, which defines the syntactic analyzer.


### Syntactic analysis

This phase reads the tokens produced by the lexical analyzer and
checks that those tokens conform to a grammar that is close to that
of a large subset of the C language. This grammar is defined in
`parser.yy`, which is a GNU Bison source file that gets converted
into a C++ file named `parser.cc` that defines a function called
yyparse().

For each grammar rule in `parser.yy`, there is a code segment in
curly braces that builds a syntax tree. When the input program is
considered valid by this parser, the end result is a single syntax
tree whose subtrees are mostly function definitions and global
variable declarations.

The main() function of the compiler calls yyparse(). If any errors
occurred, they have been counted by the global integer `numErrors`,
defined in parser.yy. If that number is zero, the compiler continues
with the subsequent phases.


### Semantic checking

This phase is implemented by TranslationUnit::checkSemantics(),
which is called by main() some time after having called yyparse()
successfully.

A major part of this phase is implemented by the SemanticsChecker
class, which is functor that gets called on most nodes of the
syntax tree. In particular, this triggers calls to the checkSemantics()
method of each defined FunctionDef object, i.e., on each C function
defined in the input program.

The main job of FunctionDef::checkSemantics() is to call the
ExpressionTypeSetter functor on all nodes in the function's body.
This functor examines each expression and sub-expression and
determines its type.

A type (like `char`, `int`, a struct, a pointer to another type, etc.)
is represented by a `TypeDesc` object.

#### Type representation

`BasicType` is an enumeration that represents the elementary types
supported by the compiler: `VOID_TYPE`, `BYTE_TYPE`, `WORD_TYPE`,
`POINTER_TYPE`, `ARRAY_TYPE`, `CLASS_TYPE` and the internal
`SIZELESS_TYPE`.

The `TypeDesc` class represents more complex types. It contains
a BasicType, a boolean indicating if the type is signed or unsigned
(when applicable), the pointed type (when the type itself is pointer),
the class name (when the type is a struct), and a boolean indicating
if the struct is actually a union. (A union is just a struct whose
members are all at offset zero.)

A pointer to a signed int is represented by two TypeDesc objects.
The first one represents the signed int type, using the `WORD_TYPE`
as its basic type. The second one uses `POINTER_TYPE` as its basic
type and pointers to the first TypeDesc as its pointed type.

The compiler only creates one instance of TypeDesc to represent
the `int` type. The same goes for all basic C types (signed int,
unsigned int, signed char, unsigned char and void).

The `TypeManager` class is there to make sure that those basic
types are represented by one instance of TypeDesc each. In fact,
TypeManager is the only class that is allowed to create TypeDesc
objects. The rest of the compiler calls public methods of TypeManager
to obtain a pointer to the TypeDesc object that corresponds to the
type described.

For example, `getIntType(WORD_TYPE, true)` returns the instance
of TypeDesc that corresponds to `int`. To obtain a TypeDesc
representing `int *`, one would pass the previous TypeDesc pointer
to getPointerTo().

The `TypeManager` class also registers and handles typedefs.


### Code generation

This phase creates an ASMText object (in the main() function)
and passes it to TranslationUnit::emitAssembler(), which writes
6809 instructions and assembler directives (e.g., `ORG`) to the
ASMText object.

An ASMText object is a vector of "elements," each element being an
instruction, a label, an inline assembly block, a text comment, a
separator comment, an include directive, a C function start marker
or a C function end marker.

Most classes that are part of the syntax tree have an emitCode()
method. It receives a reference to an ASMText object and a boolean
that indicates if the method must evaluate an _l-value_ or not
(an _r-value_).

An l-value is a value that is suitable to be used at the left of
an assignment operator, hence the _l_. An l-value must have an
address, and it is this address that must be computed, and left
in the X register.

If an r-value must be computed, it must be left in the D register
(if the type of the expression has 16 bits) or in B (in the 8-bit
case). An r-value does not have to have an address. Numerical
constants like 42 for example have no address and can only be used
as r-values, i.e., on the right side of assignments.

When emitting an assignment like `foo = bar`, the emitCode()
method will be called with the `lValue` parameter equal to false
in the case of `bar`, then equal to true in the case of `foo`. In
the general case, after the first call to emitCode(), a `PSHS B,A`
instruction is emitted to preserve the value of `bar`. Then the
second call to emitCode() will evaluate the address of `foo` and
leave it in register X. In the general case, this call is free to use
D for intermediate values, hence the PSHS instruction just before.
After this second call, the compiler emits instructions that pop
D off the stack (the value of `bar`) and store it at the address
contained in X (the address of `foo`).

The following pseudo-code summarizes this process:

    [evaluate right side of assignment in D]
    PSHS B,A
    [evaluate address of destination in X, possibly trashing D]
    PULS A,B
    STD ,X


### Low-level optimization

After having called TranslationUnit::emitAssembler(), the main()
function calls ASMText::peepholeOptimize(), unless the user has
requested no optimizations. This method applies a series of ad
hoc optimizations directly on the assembly code, with the aim of
improving naive instruction sequences, therefore making the program
shorter and/or faster.

After this phase, the main() function tells the ASMText object
to write its contents to an actual .asm file on disk.


Self tests
----------

### Compiled and run unit tests

The Perl script `test-program-output.pl` contains many small C programs
that run assert statements and write results to the terminal.
Each of these programs is a unit test that is run by the USim 6809
simulator. No assert is expected to fail. The output of a program
is checked against the expected output.

Each unit test is a reference to a hash that contains a single-line
_title_ field, a multi-line _program_ field and an _expected_ field
that indicates what output is expected of the program through its
printf() statements, if any.  The _expected_ field usese \n to
represent a newline.

An optional _compilerOptions_ field can be used to pass additional
options to the compiler.

The `--help` option lists several command-line switches. The most
useful during development are `--last`, `--only=`_X_ and `--stop`.


### Error and warning unit tests

The Perl script `test-bad-programs.pl` is similar to
`test-program-output.pl`, but its goal is not to run programs, it is
to check that the compiler issues the error and warning messages that
are expected when making several types of mistakes in a C program.

The _expected_ field of a unit test in this script is a reference
to an array of compiler messages. In these messages, the `error` and
`warning` keywords are preceded and followed by two underscores so
as to avoid having these lines be picked up by an automatic build
system's error detection facilities.


Documentation
-------------

The documentation is written in Markdown format in files found in
the `doc` subdirectory. This subdirectory contains a Perl script
named `toc.pl` that adds a table of contents to the HTML produced
by the `markdown` command from a Markdown source file. That Perl
script is run by the makefile in the `doc` subdirectory.


License
-------

See the CMOC Manual.


</body>
