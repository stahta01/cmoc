#!/usr/bin/perl -w

use strict;
use Getopt::Long;
use File::Basename;


my $cFilename = ",check-prog.c";
my $useLWASM = 0;  # default is FrankASM, i.e., as6809
my $numDebuggingLines = 0;


my @testCaseList =
(


{
title => q{Empty source file},
program => q!!,
expected => [ qq!$cFilename:1: error: syntax error:! ]
},


{
title => q{Using a variable before declaring it},
program => q!
    int main()
    {
        a = 1;
        int a;
        return 0;
    }
!,
expected => [
    qq!$cFilename:4: __error__: undeclared identifier `a'!,
    qq!$cFilename:4: __error__: lvalue required as left operand of assignment!,
    ]
},


{
title => q{Non-void not returning a value},
program => q!
    int main() { return 0; }
    int f() {}
    int g() { f(); }
    void h() { return 42; }
    int i() { return; }
    !,
expected => [ qq!,check-prog.c:3: __error__: function 'f' is not void but does not have any return statement!,
              qq!,check-prog.c:4: __error__: function 'g' is not void but does not have any return statement!,
              qq!,check-prog.c:5: __error__: returning expression of type int, which differs from function's return type (void)!,
              qq!,check-prog.c:6: __error__: return without argument in a non-void function!,
            ]
},


{
title => q{Initializing pointer from non-zero constant},
program => q!
    int main() 
    { 
        char *p0 = -42; 
        char *p1 = 42;
        char *p2 = f();
        return 0; 
    }
    int f() { return 0; }
!,
expected => [
    qq!,check-prog.c:4: __warning__: initializing pointer 'p0' from negative constant!,
    qq!,check-prog.c:6: __warning__: initializing pointer 'p2' from integer expression!,
    qq!,check-prog.c:6: __error__: calling undeclared function f()!,
    ]
},


{
title => q{Declaring a variable with a name that is already used},
program => q!
    int foo;
    int foo;
    int main()
    {
        char a;
        int a;
        return 0;
    }
    void f0(int n)
    {
        int n = 42;  // fails b/c C views function param as part of function scope, not separate scope
    }
    void f1(int n)
    {
        {
            int n = 42;  // OK b/c inner braces create separate scope
        }
    }
    !,
expected => [ qq!,check-prog.c:3: __error__: global variable `foo' already declared at global scope at ,check-prog.c:2!,
              qq!,check-prog.c:7: __error__: variable `a' already declared in this scope at ,check-prog.c:6!,
              qq!,check-prog.c:12: __error__: variable `n' already declared in this scope at ,check-prog.c:10!,
            ]
},


{
title => q{Detect invalid subtractions},
program => q!
    void f(int x) {}
    int main()
    {
        char *p;
        f((int) (4 - p));
        return 0;
    }
    !,
expected => [ qq!,check-prog.c:6: __error__: subtraction of pointer or array from integral! ]
},


{
title => q{Illegal array operations},
program => q!
    int main()
    {
        int w[2];
        w = 0;
        w += 0;
        ++w;
        w--;
        *w = 0;
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:5: __error__: cannot assign to array name!,
    qq!,check-prog.c:6: __error__: cannot assign to array name!,
    qq!,check-prog.c:7: __error__: cannot increment array name!,
    qq!,check-prog.c:8: __error__: cannot decrement array name!,
    ]
},


{
title => q{Forbidden to pass structs by value to functions},
program => q!
    struct Foobar { char b; };
    void f(struct Foobar s)
    {
    }
    void f1(struct Foobar)
    {
    }
    void f2(struct Undefined)
    {
    }
    int main()
    {
        struct Foobar s;
        f(s);
        f1(s);
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:3: __error__: argument 1 of f() receives `struct Foobar' by value!,
    qq!,check-prog.c:6: __error__: argument 1 of f1() receives `struct Foobar' by value!,
    qq!,check-prog.c:9: __error__: argument 1 of f2() receives `struct Undefined' by value!,
    qq!,check-prog.c:15: __error__: argument 1 of call to function f() is of type struct Foobar (cannot pass struct by value)!,
    qq!,check-prog.c:16: __error__: argument 1 of call to function f1() is of type struct Foobar (cannot pass struct by value)!,
    ]
},


{
title => q{Forbid requesting a struct by value from va_arg(). Detect use of unknown struct name},
program => q!

    #include <stdarg.h>

    struct S { char b; };
    void f(char *a, ...)
    {
        va_list ap;
        va_start(ap, a);  // ok
        va_arg(ap, struct S);  // passes but will not work
        va_arg(ap, struct S *);  // ok
        va_arg(ap, struct Unknown *);  // ok because sizeof gives 2, regard of unknown struct name
        va_arg(ap, void);  // error
        va_arg(ap, char);  // ok
        va_arg(ap, char *);  // ok
        va_arg(ap, char **);  // ok
        va_arg(ap, char *****);  // ok
        va_end(ap);
    }
    int main()
    {
        f(0);
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:13: __error__: indirection of a pointer to void!,
    qq!,check-prog.c:13: __error__: cannot take sizeof(void)!,
    ]
},


{
title => q{Do-while lacks terminating semi-colon..},
program => q!
    void f()
    {
        do {} while (1)
    }
    int main()
    {
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:5: __error__: syntax error: }!,
    ]
},


{
title => q{Global variable too large},
program => q!
    int w[50000];
    int main()
    {
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:2: __error__: invalid dimensions for array w!,
    ]
},


{
title => q{Local variable too large},
program => q!
    int main()
    {
        char b[40000];
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:4: __error__: invalid dimensions for array b!,
    ]
},


{
title => q{Number of arguments of built-in functions},
program => q!
    #include <cmoc.h>
    int main()
    {
        putstr("foo");
        int w;
        toupper(w);
        char *s0;
        strchr(s0, 256 + 'f');
        printf();
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:5: __error__: call to putstr() passes 1 argument(s) but function expects 2!,
    qq!,check-prog.c:10: __error__: call to printf() passes 0 argument(s) but function expects at least 1!,
    ]
},


{
title => q{Detect change in signedness when passing an argument to a function},
program => q!
    #include <cmoc.h>
    void fsb(char x) {}
    void fsw(int x) {}
    void fub(unsigned char x) {}
    void fuw(unsigned x) {}
    int main()
    {
        char sb;
        int sw;
        unsigned char ub;
        unsigned uw;
        fsb(ub);
        fsw(uw);
        fub(sb);
        fuw(sw);
        memset((unsigned char *) 0, sb, sw);
        fsw(sw + ub);  // no warning because sum is signed int (see ExpressionTypeSetter::processBinOp())
        return 0;
    }
    !,
expected => [
    #qq!,check-prog.c:14: __warning__: passing unsigned argument as signed parameter 1 of function fsw()!,
    #qq!,check-prog.c:16: __warning__: passing signed argument as unsigned parameter 1 of function fuw()!,
    #qq!,check-prog.c:17: __warning__: passing signed argument as unsigned parameter 3 of function memset()!,
    ]
},


{
title => q{Return value type vs. function's return type},
program => q!
    unsigned char *b1()     { return 1; }
    unsigned char *bm1()    { return -1; }
    unsigned char *b1000()  { return 1000; }
    unsigned char *bm1000() { return -1000; }
    unsigned *w1()     { return 1; }
    unsigned *wm1()    { return -1; }
    unsigned *w1000()  { return 1000; }
    unsigned *wm1000() { return -1000; }
    int main()
    {
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:2: __error__: returning expression of type int, which differs from function's return type (unsigned char *)!,
    qq!,check-prog.c:3: __error__: returning expression of type int, which differs from function's return type (unsigned char *)!,
    qq!,check-prog.c:4: __error__: returning expression of type int, which differs from function's return type (unsigned char *)!,
    qq!,check-prog.c:5: __error__: returning expression of type int, which differs from function's return type (unsigned char *)!,
    qq!,check-prog.c:6: __error__: returning expression of type int, which differs from function's return type (unsigned int *)!,
    qq!,check-prog.c:7: __error__: returning expression of type int, which differs from function's return type (unsigned int *)!,
    qq!,check-prog.c:8: __error__: returning expression of type int, which differs from function's return type (unsigned int *)!,
    qq!,check-prog.c:9: __error__: returning expression of type int, which differs from function's return type (unsigned int *)!,
    ]
},


{
title => q{Return type of main() must be int},
program => q!
    void main()
    {
    }
    !,
expected => [
    qq!,check-prog.c:2: __error__: return type of main() must be int!,
    ]
},


{
title => q{printf() format warnings},
program => q!
    #include <cmoc.h>
    int main()
    {
        int sw;
        unsigned uw;
        char sb;
        unsigned char ub;
        unsigned char *bp;
        printf("%u %d %5u %% %d %u %3d %p\n", sw, uw, sb, ub, bp, bp);
        printf("%");
        printf("foo %123");
        printf("%u %u", 1, 2, 3);
        printf("");
        obligatory_error;
        printf("%d", -1);  // no warning expected
        printf("%u", 1);   // no warning expected
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:15: __error__: undeclared identifier `obligatory_error'!,
    qq!,check-prog.c:10: __warning__: not enough arguments to printf() to match its format string!,
    qq!,check-prog.c:11: __warning__: no letter follows last % in printf() format string!,
    qq!,check-prog.c:12: __warning__: no letter follows last % in printf() format string!,
    qq!,check-prog.c:13: __warning__: too many arguments for printf() format string!,
    ]
},


{
title => q{Declaration type vs. initializer type},
program => q!
    int main()
    {
        unsigned w = 1844;
        unsigned *pw0 = &w;
        unsigned *pw1 = &pw0;  // unsigned ** assigned to unsigned *
        char b0 = -129;
        char b1 = -128;
        char b2 = 255;
        char b3 = 256;
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:6: __error__: initializing unsigned int * with expression of type unsigned int **!,
    qq!,check-prog.c:7: __error__: initializing byte variable with word value!,
    qq!,check-prog.c:10: __error__: initializing byte variable with word value!,
    ]
},


{
title => q{Byte array initialized with non-byte expressions},
program => q!
    char strings[] = { "foo", "bar", "baz" };
    int main()
    {
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:2: __error__: initializing char with expression of type char[]!,
    qq!,check-prog.c:2: __error__: initializing char with expression of type char[]!,
    qq!,check-prog.c:2: __error__: initializing char with expression of type char[]!,
    ]
},


{
title => q{Array whose initializer contains expressions of types that do not match the element type},
program => q!
    struct A { char byteField; };
    struct A structArray[3] = { { 42 }, "foo", { 44 } };
    int v0[4] = "foo";
    int v1[] = { 9999 };
    int v2[] = &v1;
    int main()
    {
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:6: __error__: unexpected type of array initializer!,
    qq!,check-prog.c:3: __error__: initializer for struct A is of type `char[]': must be list, or struct of same type!,
    qq!,check-prog.c:4: __error__: initializer for array `v0' is invalid!,
    ]
},


{
title => q{Re: Declaration::checkClassInitializer()},
program => q!
    struct A
    {
        char b;
    }; 
    struct A a = { "foo" };
    struct B
    {
        struct A aMember;
    };
    struct B b = { { "bar" } };
    struct C
    {
        struct A aMemberArray[2];
    };
    struct C c = { {
                    { "baz"  },
                    { "quux" }
                 } };
    int main()
    {
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:6: __error__: initializing char with expression of type char[]!,
    qq!,check-prog.c:11: __error__: initializing char with expression of type char[]!,
    qq!,check-prog.c:17: __error__: initializing char with expression of type char[]!,
    qq!,check-prog.c:18: __error__: initializing char with expression of type char[]!,
    ]
},


{
title => q{var_decl containing a type_specifier but no declarator_list, unless it defines a struct},
program => q!
    struct S { char b; };  // ok
    unsigned n = 42;  // ok
    unsigned x;  // ok: declarator without initializer
    unsigned;  // fail
    int main()
    {
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:5: __error__: declaration specifies a type but no variable name!,
    ]
},


{
title => q{Reject returning an array from an int function},
program => q!
    int i = 0;
    int f(int *p)
    {
        return p;
    }
    int g(int p[][3])
    {
        return p[i];
    }
    int h(int p[][3][3])
    {
        return p[i][i];
    }
    int h2(int p[][3][3])
    {
        return p[i];
    }
    int main()
    {
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:5: __error__: returning expression of type int *, which differs from function's return type (int)!,
    qq!,check-prog.c:9: __error__: returning expression of type int[], which differs from function's return type (int)!,
    qq!,check-prog.c:13: __error__: returning expression of type int[], which differs from function's return type (int)!,
    qq!,check-prog.c:17: __error__: returning expression of type int[][], which differs from function's return type (int)!,
    ]
},


{
title => q{Calling an undeclared function, mismatching function prototype, wrong number of parameters, etc.},
program => q!
    void f2();
    void f3(int n);
    void f3();
    void f4();
    int main()
    {
        f0();
        f1();
        f2(5);
        f3();
        return 0;
    }
    void f1()
    {
    }
    void f4(int n)
    {
    }
    void f5(int a);
    void f5(int a, ...);
    !,
expected => [
    qq!,check-prog.c:4: __error__: formal parameters for f3() are different from previously declared at ,check-prog.c:3!,
    qq!,check-prog.c:17: __error__: formal parameters for f4() are different from previously declared at ,check-prog.c:5!,
    qq!,check-prog.c:21: __error__: formal parameters for f5() are different from previously declared at ,check-prog.c:20!,
    qq!,check-prog.c:8: __error__: undeclared identifier `f0'!,
    qq!,check-prog.c:10: __error__: call to f2() passes 1 argument(s) but function expects 0!,
    qq!,check-prog.c:11: __error__: call to f3() passes 0 argument(s) but function expects 1!,
    qq!,check-prog.c:8: __error__: calling undeclared function f0()!,
    qq!,check-prog.c:9: __error__: calling undeclared function f1()!,
    qq!,check-prog.c:2: __error__: function f2() declared and called but not defined!,
    qq!,check-prog.c:4: __error__: function f3() declared and called but not defined!,
    ]
},


{
title => q{Unknown member of a struct},
program => q!
    struct S0
    {
        int a;
    };    
    int main()
    {
        struct S0 s0;
        s0.b = 1;
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:9: __error__: struct S0 has no member named b!,
    ]
},


{
title => q{Warnings on dubious function calls},
program => q!
    void f() {}
    int main()
    {
        int f;
        f();
        int pf = f;
        pf();
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:6: __warning__: calling 'f', which is both a variable and a function name!,
    qq!,check-prog.c:8: __warning__: variable 'pf' used as function pointer without being of type void *!,
    ]
},


{
title => q{switch()},
program => q!
    int f() { return 99; }
    int main()
    {
        switch (1) return 42;
        switch (1) { case f(): return 0; }
        switch (1) { return 1; case 5: return 0; }
        char c = 1;
        switch (c) { case 500: return 1; }
        unsigned char uc = 1;
        switch (uc) { case 500: return 1; }
        switch (1) { default: break; case 5: break; default: ; } 
        switch (1) { case 5: continue; }
        switch (1)
        {
            case 3:
                ;
            case 3:  // duplicate case value
                ;
        }
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:5: __error__: switch() statement has no `case' or `default' statement!,
    qq!,check-prog.c:6: __error__: case statement has a variable expression!,
    qq!,check-prog.c:7: __error__: statement in switch precedes first `case' or `default' statement!,
    qq!,check-prog.c:9: __warning__: switch expression is signed char but case value is not in range -128..127!,
    qq!,check-prog.c:11: __warning__: switch expression is unsigned char but case value is not in range 0..255!,
    qq!,check-prog.c:12: __error__: more than one default statement in switch!,
    qq!,check-prog.c:18: __error__: duplicate case value (first used at ,check-prog.c:16)!,
    ]
},


{
title => q{Continue in a switch (not supported)},
program => q!
    int f() { return 42; }
    int main()
    {
        switch (1) { case 1: continue; }  // error
        switch (1) { case 1: while (1) continue; }  // ok
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:5: __error__: continue statement is not supported in a switch!,
    ]
},



{
title => q{Using both "#pragma org" and --org},
options => "--org=0x5555",
program => q!
    #pragma org 0x1234
    int main()
    {
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:2: __warning__: #pragma org and --org (or --dos) both used!,
    ]
},


{
title => q{Invalid usage of "#pragma org"},
program => q!
    #pragma org pizza
    int main()
    {
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:2: __error__: invalid pragma directive: org pizza!,
    ]
},


{
title => q{Passing a wrong type to a function expecting a non-void pointer},
program => q!
    struct S {};
    void f(struct S *p) {}
    struct T {}; union U {};
    int main()
    {
        f(0);  // OK: null pointer
        f(3);  // OK: was an error (required cast) before version 0.1.21
        f(-4);  // warning: negative constant passed for pointer parameter
        int n;
        f(&n);  // error: wrong type of pointer
        struct T t;
        f(&t);  // error: ditto
        struct S s;
        f(&s);  // OK
        union U u;
        f(&u);
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:9: __warning__: passing negative constant as parameter 1 of function f(), which is struct S *!,
    qq!,check-prog.c:11: __error__: pointer type mismatch: passing int * as parameter 1 of function f(), which is a struct S *!,
    qq!,check-prog.c:13: __error__: pointer type mismatch: passing struct T * as parameter 1 of function f(), which is a struct S *!,
    qq!,check-prog.c:17: __error__: pointer type mismatch: passing union U * as parameter 1 of function f(), which is a struct S *!,
    ]
},


{
title => q{#pragma const_data},
program => q!
    int f() { return 42; }
    #pragma const_data start
    int lacksInitializer;
    int nonConstInitializer = f();
    int ok = 6809;
    #pragma const_data end
    int main()
    {
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:4: __error__: global variable 'lacksInitializer' declared in const_data section but has no initializer!,
    qq!,check-prog.c:5: __error__: global variable 'nonConstInitializer' declared in const_data section but has a run-time initializer!,
    ]
},


{
title => q{Referring to a member of an undefined struct},
program => q!
    int main()
    {
        struct S *p = 0;
        p->n = 42;
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:5: __error__: reference to member `n' of undefined class `S'!,
    ]
},


{
title => q{Indirection of a pointer to a struct used as an r-value},
program => q!
    struct S { int field; };
    struct T { struct S *ps; };
    int main()
    {
        struct S *ps = (struct S *) 100;
        if (*ps)  // bad
            ;
        if ((*ps).field == 0)  // ok
            ;
        struct T *pt = (struct T *) 200;
        if (*(*pt).ps)  // bad
            ;
        if ((*(*pt).ps).field)  // ok
            ;
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:7: __error__: indirection of struct as an r-value not supported: use '->' operator instead!,
    qq!,check-prog.c:12: __error__: indirection of struct as an r-value not supported: use '->' operator instead!,
    ]
},


{
title => q{Initializing from incompatible pointer type},
program => q!
    int a[5][7][13];
    char n;
    int main()
    {
        int *p0 = a;
        p0 = a;
        int *p1 = a + n;
        p1 = a + n;
        int *p2 = a + 1;
        p2 = a + 1;
        int *p2 = n;
        p0 = n;
        p0 = -1;
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:12: __error__: variable `p2' already declared in this scope at ,check-prog.c:10!,
    qq!,check-prog.c:7: __warning__: assigning pointer to int with incompatible int[][][]!,
    qq!,check-prog.c:9: __warning__: assigning pointer to int with incompatible int[][][]!,
    qq!,check-prog.c:11: __warning__: assigning pointer to int with incompatible int[][][]!,
    qq!,check-prog.c:13: __warning__: assigning pointer with integer expression!,
    qq!,check-prog.c:14: __warning__: assigning pointer with negative constant!,
    qq!,check-prog.c:6: __warning__: initializing pointer to int 'p0' from incompatible int[][][]!,
    qq!,check-prog.c:8: __warning__: initializing pointer to int 'p1' from incompatible int[][][]!,
    qq!,check-prog.c:10: __warning__: initializing pointer to int 'p2' from incompatible int[][][]!,
    qq!,check-prog.c:12: __warning__: initializing pointer 'p2' from integer expression!,
    ]
},


{
title => q{Assembly-only function containing non-asm statement},
program => q!
    int asm f()
    {
        int foo;  // only asm{} allowed in asm function
        asm {}
    }
    int asm g()
    {
        asm {}
        return 42;  // only asm{} allowed in asm function
    }
    int asm h(int m, char n, char *s)
    {
        asm {
            ldb n
        }
        asm {
            ldb s[12]
            ldd m
            ldb n
            ldd m
            tfr s,x     // OK: s refers to register, not to C variable
        }
        asm("clr", n);
    }
    int global0 = 42;
    void q()
    {
        asm("ldd", global0);  // OK: variable is global
        asm {
            ldd global0  // ditto
        }
    }
    int main()
    {
        int z;
        asm { nop }  // OK: no 'asm' modifier on this function
        asm("clr", z);  // ditto
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:4: __error__: body of function f() contains statement(s) other than inline assembly!,
    qq!,check-prog.c:10: __error__: body of function g() contains statement(s) other than inline assembly!,
    qq!,check-prog.c:16: __error__: assembly-only function refers to local C variable `n'!,
    qq!,check-prog.c:23: __error__: assembly-only function refers to local C variables `m', `n', `s'!,
    qq!,check-prog.c:24: __error__: assembly-only function refers to local C variable `n'!,
    ]
},


{
title => q{asm modifier used on non-function declarations},
program => q!
    int asm globalVar0;  // modifier only legal on a function 

    typedef int asm Bad; 
    int main()
    {
        int asm localVar;
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:2: error: illegal modifier used on declaration of variable `globalVar0'!,
    qq!,check-prog.c:4: error: illegal modifier used on typedef!,
    qq!,check-prog.c:7: error: illegal modifier used on declaration of variable `localVar'!,
    ]
},


{
title => q{interrupt modifier},
program => q!
    int interrupt globalVar1;
    interrupt void isr() {} 
    int main()
    {
        int interrupt localVar;
        isr();
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:2: __error__: illegal modifier used on declaration of variable `globalVar1'!,
    qq!,check-prog.c:6: __error__: illegal modifier used on declaration of variable `localVar'!,
    qq!,check-prog.c:7: __error__: calling function isr() is forbidden because it is an interrupt service routine!,
    ]
},


{
title => q{Union},
program => q!
    union U
    {
        int i;
    };
    struct S
    {
        int i;
    };
    struct Cell;
    struct List
    {
        struct Cell *a, *b;
    };
    union UndefUnion;
    struct Cell fc();
    void fc1(struct Cell c);
    void fc2(struct Cell c) {}
    int main()
    {
        struct U u;
        union S s;
        struct Cell c;
        union UndefUnion uu;
        struct Cell *pc;  // OK
        union UndefUnion *puu;  // OK
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:16: __error__: declaring `fc' of undefined type struct `Cell'!,
    qq!,check-prog.c:21: __error__: referring to U as a struct, but it is a union!,
    qq!,check-prog.c:22: __error__: referring to S as a union, but it is a struct!,
    qq!,check-prog.c:23: __error__: declaring `c' of undefined type struct `Cell'!,
    qq!,check-prog.c:24: __error__: declaring `uu' of undefined type struct `UndefUnion'!,
    qq!,check-prog.c:17: __error__: argument 1 of fc1() receives `struct Cell' by value!,
    qq!,check-prog.c:18: __error__: argument 1 of fc2() receives `struct Cell' by value!,
    ]
},


{
title => q{Forbid --org when targeting Vectrex},
target => "vectrex",
options => "--org=0x300",
program => q!
    #pragma org  0x100
    #pragma data 0x200
    int main()
    {
        return 0;
    }
    !,
expected => [
    qq!cmoc: --org is not permitted for Vectrex!,
    ]
},


{
title => q{Forbid code and data positioning pragmas when targeting Vectrex},
target => "vectrex",
options => "",
program => q!
    #pragma org  0x100
    #pragma data 0x200
    int main()
    {
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:2: __error__: #pragma org is not permitted for Vectrex!,
    qq!,check-prog.c:3: __error__: #pragma data is not permitted for Vectrex!,
    ]
},


{
title => q{Function prototype local to a function body},
program => q!
    void f() {}
    int g()
    {
        char *f();
        return 1;  // check that this JumpStmt is seen as inside g()
    }
    int main()
    {
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:5: __error__: invalid declaration!,
    ]
},


{
title => q{Correct line number in error message when using function address to initialize char},
program => q!
    char f() { return 42; }
    int main()
    {
        char b = f;
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:5: __error__: initializing char with expression of type void *!,
    ]
},


{
title => q{sizeof on an unknown struct name},
program => q!
    struct S {}; 
    unsigned g0 = sizeof(struct Foo);
    unsigned g1 = sizeof(struct S);
    int main()
    {
        unsigned a = sizeof(struct Foo);
        unsigned b;
        b = sizeof(struct Foo);
        b = sizeof(struct S);
        b = sizeof(struct Bar);
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:3: __error__: cannot take sizeof unknown struct or union 'Foo'!,
    qq!,check-prog.c:7: __error__: cannot take sizeof unknown struct or union 'Foo'!,
    qq!,check-prog.c:9: __error__: cannot take sizeof unknown struct or union 'Foo'!,
    qq!,check-prog.c:11: __error__: cannot take sizeof unknown struct or union 'Bar'!,
    ]
},


{
title => q{sizeof on an unknown array name, used twice in a binary expression},
program => q!
    int main()
    {
        unsigned n = sizeof(a) / sizeof(a[0]);
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:4: __error__: undeclared identifier `a'!,
    qq!,check-prog.c:4: __error__: undeclared identifier `a'!,
    qq!,check-prog.c:4: __error__: array reference on non array or pointer!,
    qq!,check-prog.c:4: __error__: cannot take sizeof(void)!,
    qq!,check-prog.c:4: __error__: cannot take sizeof(void)!,
    qq!,check-prog.c:4: __error__: lvalue required as left operand of array reference!,
    ]
},


{
title => q{Passing integer for pointer parameter},
program => q!
    int g() { return 42; }
    void f(int *p) {}
    int main()
    {
        f(g());
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:6: __warning__: passing non-pointer/array (int) as parameter 1 of function f(), which is int *!,
    ]
},


{
title => q{Invalid numerical constant},
program => q!
    int f0() { return 0777777; }
    int f1() { return 0xFFFFF; }
    int f2() { return 99999; }
    int f3() { return -99999; }
    int main()
    {
        return f0() + f1() + f2() + f3();
    }
    !,
expected => [
    qq!,check-prog.c:2: __error__: invalid numerical constant 262143.000000 (must be 16-bit integer)!,
    qq!,check-prog.c:3: __error__: invalid numerical constant 1048575.000000 (must be 16-bit integer)!,
    qq!,check-prog.c:4: __error__: invalid numerical constant 99999.000000 (must be 16-bit integer)!,
    qq!,check-prog.c:5: __error__: invalid numerical constant 99999.000000 (must be 16-bit integer)!,
    ]
},


{
title => q{Dereferencing a void pointer},
program => q!
    void g(int n) {}
    void f(void *p)
    {
        g(*p);
    }
    int main()
    {
        f(0);
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:5: __error__: indirection of a pointer to void!,
    ]
},


{
title => q{Use of a struct as an r-value},
program => q`
    struct Inner { int n; };
    struct Outer { struct Inner i; };
    int main()
    {
        struct Outer obj;
        if (obj)
            return 1;
        if (obj.i)
            return 2;
        if (!obj.i)
            return 3;
        return 0;
    }
    `,
expected => [
    qq!,check-prog.c:7: __error__: cannot use variable `obj', of type struct `Outer', as an r-value!,
    qq!,check-prog.c:9: __error__: cannot use member `i' of struct `Outer' as an r-value!,
    qq!,check-prog.c:11: __error__: cannot use member `i' of struct `Outer' as an r-value!,
    ]
},


{
title => q{Unsupported type keywords},
program => q!
    int main()
    {
        long l;
        float f;
        double d;
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:4: __error__: unsupported type keyword `long'!,
    qq!,check-prog.c:5: __error__: unsupported type keyword `float'!,
    qq!,check-prog.c:6: __error__: unsupported type keyword `double'!,
    ]
},


{
title => q{Anonymous struct},
program => q!
    struct { int n; } a;
    int main()
    {
        int *pi = &a;
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:5: __error__: initializing int * with expression of type struct AnonStruct_,check-prog.c:2 *!,
    ]
},


{
title => q{goto and ID-labeled statements},
program => q!
    void f()
    {
    foo: ; // ok
    bar: ;
    }
    int main()
    {
    foo:
    foo:
        f();
        goto bar;
        goto imaginary;
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:10: __error__: label `foo' already defined at ,check-prog.c:9!,
    qq!,check-prog.c:12: __error__: goto targets label `bar' which is unknown to function main()!,
    qq!,check-prog.c:13: __error__: goto targets label `imaginary' which is unknown to function main()!,
    ]
},


{
title => q{Conditional with incompatible types},
program => q!
    int f() { return 42; }
    void g(int) {}
    int main()
    {
        char *p;
        int i;
        g(i > 0 ? p : i);
        g(i > 0 ? (char) 0x12 : i);
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:8: __error__: true and false expressions of conditional are of incompatible types (char * vs int)!,
    qq!,check-prog.c:9: __warning__: true and false expressions of conditional are not of the same type (char vs int); result is of type int!,
    ]
},


{
title => q{Automatic type conversions},
program => q!
    unsigned char returnByte(unsigned char b)
    {
        return b;
    }
    int main()
    {
        int i = 1000;
        char c;
        c = i;
        c = 2000;
        unsigned u = 1001;
        unsigned char uc;
        uc = u;
        uc = 2001; 

        u = 100;
        u = (u > 99 ? 50 : u);
        unsigned char b = 12;
        u = (u > 66 ? u : returnByte(b));
        u = 999;
        u = (u < 2000 ? u : returnByte(b));
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:10: __warning__: assigning to `char' from larger type `int'!,
    qq!,check-prog.c:11: __warning__: assigning to `char' from larger constant of type `int'!,
    qq!,check-prog.c:14: __warning__: assigning to `unsigned char' from larger type `unsigned int'!,
    qq!,check-prog.c:15: __warning__: assigning to `unsigned char' from larger constant of type `int'!,
    qq!,check-prog.c:18: __warning__: true and false expressions of conditional are not of the same type (int vs unsigned int); result is of type int!,
    qq!,check-prog.c:20: __warning__: true and false expressions of conditional are not of the same type (unsigned int vs unsigned char); result is of type unsigned int!,
    qq!,check-prog.c:22: __warning__: true and false expressions of conditional are not of the same type (unsigned int vs unsigned char); result is of type unsigned int!,
    ]
},


{
title => q{Wrong use of assignment operator with structs},
program => q!
    struct S { int i; };
    struct Other {} other;
    void f(char *, ...) {}
    int main()
    {
        struct S s, t;
        int i;
        s = 'x';
        s = i;
        s = &i;
        i = s;
        s += t;
        f("", s = t);
        struct S u = 42;
        struct S v = other;
        struct S w = &other;
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:9: __error__: cannot assign `char' to `struct S'!,
    qq!,check-prog.c:10: __error__: cannot assign `int' to `struct S'!,
    qq!,check-prog.c:11: __error__: cannot assign `int *' to `struct S'!,
    qq!,check-prog.c:12: __error__: cannot assign `struct S' to `int'!,
    qq!,check-prog.c:13: __error__: invalid use of an operator on a struct!,
    qq!,check-prog.c:14: __error__: argument 2 of call to function f() is of type struct S (cannot pass struct by value)!,
    qq!,check-prog.c:15: __error__: initializer for struct S is of type `int': must be list, or struct of same type!,
    qq!,check-prog.c:16: __error__: initializer for struct S is of type `struct Other': must be list, or struct of same type!,
    qq!,check-prog.c:17: __error__: initializer for struct S is of type `struct Other *': must be list, or struct of same type!,
    ]
},


{
title => q{Static keyword},
program => q!
    static int g0;  // equivalent to "int g0;"
    int g0;  // duplicates previous declaration
    int g1;
    static int g1;  // duplicates previous declaration
    static int g2;
    extern int g2;  // no problem: entire line is ignored
    int main()
    {
        extern int g3;  // ignored
        static int g4;  // local static not supported
        g4 = 1;
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:3: __error__: global variable `g0' already declared at global scope at ,check-prog.c:2!,
    qq!,check-prog.c:5: __error__: global variable `g1' already declared at global scope at ,check-prog.c:4!,
    qq!,check-prog.c:11: __error__: local static variables are not supported!,
    ]
},


{
title => q{More than one formal parameter with same name},
program => q!
    void f1(int a, int b, int a);
    void f2(int a, int b, int a) {}
    void f3(int a, int, char a) {}
    void f4(int, int, char);  // OK
    int main()
    {
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:2: __error__: function f1() has more than one formal parameter named 'a'!,
    qq!,check-prog.c:3: __error__: function f2() has more than one formal parameter named 'a'!,
    qq!,check-prog.c:4: __error__: function f3() has more than one formal parameter named 'a'!,
    ]
},


{
title => q{Returning wrong struct pointer type},
program => q{
    struct A {};
    struct B {} b;
    struct A *f()
    {
        return &b;
    }
    int main()
    {
        return f() != 0;
    }
    },
expected => [
    qq!,check-prog.c:6: __error__: returning expression of type struct B *, which differs from function's return type (struct A *)!,
    ]
},


{
title => q{Bad type specifier combinations},
program => q!
    int main()
    {
        int char x;
        signed void p;
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:4: __error__: combining type specifiers is not supported!,
    qq!,check-prog.c:5: __error__: signed and unsigned modifiers can only be applied to integral type!,
    ]
},


{
title => q{Typedef local to a function},
suspended => 1,  # This test is suspended because the compiler does not detect this error.
program => q!
    int main()
    {
        typedef int Integer;
        Integer n = 42;
        return n;
    }
    !,
expected => [
    qq!!,
    ]
},


{
title => q{enum},
program => q!
    enum A { A0 };
    enum A { A1 };  // error: 'A' already used

    enum B { DuplicateEnumeratedName };


    void f0(enum { EnumNameInFunctionParam } e) {}  // error: enumerator in formal param not supported
    void f5(enum { OtherEnumNameInFunctionParam } e);  // error: same, but on prototype

    enum { EnumNameInReturnType } f1() { return 0; }  // error: enumerator in return type
    enum { OtherEnumNameInReturnType } f2();  // error: same, but on prototype

    enum D { D0 };
    enum D f3() { return D0; }  // ok
    enum D f4();  // ok

    signed enum F { F0 } f0;
    
    void funcTakingA(enum A a) {}

    int main()
    {
        enum { X } localEnumVar;
        enum E { E0 } otherLocalEnumVar;
        funcTakingA(A0);  // ok
        funcTakingA(5);   // error: 5 not member of enum A
        funcTakingA(D0);  // error: D0 not member of enum A
        return 0;
    }
    enum C { DuplicateEnumeratedName };  // error re: enum B
    !,
expected => [
    qq!,check-prog.c:3: __error__: enum `A' already defined at ,check-prog.c:2!,
    qq!,check-prog.c:8: __error__: enum with enumerated names is not supported in a function's formal parameter!,
    qq!,check-prog.c:9: __error__: enum with enumerated names is not supported in a function's formal parameter!,
    qq!,check-prog.c:11: __error__: enum with enumerated names is not supported in a function's return type!,
    qq!,check-prog.c:12: __error__: enum with enumerated names is not supported in a function prototype's return type!,
    qq!,check-prog.c:18: __error__: signed and unsigned modifiers cannot be applied to an enum!,
    qq!,check-prog.c:31: __error__: enumerated name `DuplicateEnumeratedName' already defined at ,check-prog.c:5!,
    qq!,check-prog.c:27: __error__: parameter 1 of function funcTakingA() must be a member of enum A!,
    qq!,check-prog.c:28: __error__: `D0' used as parameter 1 of function funcTakingA() but is not a member of enum A!,
    qq!,check-prog.c:24: __error__: non-global enum not supported!,
    qq!,check-prog.c:25: __error__: non-global enum not supported!,
    ]
},


{
title => q{Declaring an enum variable without the enum keyword},
program => q!
    enum E { E0 };
    E e;  // error
    int main()
    {
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:3: __error__: syntax error: E!,
    ]
},


{
title => q{String numerical escape sequence out of range},
program => q!
    int main()
    {
        char *s0 = "\x80bomber";  // error: $80b > 255
        char *s1 = "zzz\0777zzz";  // error: 0777 > 255
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:4: __warning__: hex escape sequence out of range!,
    qq!,check-prog.c:5: __warning__: octal escape sequence out of range!,
    ]
},


{
title => q{Named argument required before ellipsis of variadic function},
program => q!
    void functionWithNoNamedArg(...) {}
    void prototypeWithNoNamedArg(...);
    int main()
    {
        void (*fp)(...);
        functionWithNoNamedArg(1, 2, 3);
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:6: __error__: named argument is required before `...'!,
    qq!,check-prog.c:2: __error__: function functionWithNoNamedArg() uses `...' but has no named argument before it!,
    qq!,check-prog.c:3: __error__: prototype prototypeWithNoNamedArg() uses `...' but has no named argument before it!,
    ]
},


{
title => q{l-value required for some operators},
program => q!
    void f(unsigned *n) {}
    char g() { return 1; }
    int *h() { return 0; }
    int main()
    {
        unsigned n = 891;
        f(&(n >> 1));
        ++(n >> 1);
        --(n >> 1);
        (n >> 1)++;
        (n >> 1)--;
        char a, b;
        (g() ? a : b) = 42;  // OK because both alternatives are l-values
        (g() ? a : 99) = 42;
        (g() ? 99 : b) = 42;
        h()[0] = 0;  // OK
        *h() = 0;  // OK
        ((int *) 0x400)[32] = 0;  // OK
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:8: __error__: lvalue required as operand of address-of!,
    qq!,check-prog.c:9: __error__: lvalue required as operand of pre-increment!,
    qq!,check-prog.c:10: __error__: lvalue required as operand of pre-decrement!,
    qq!,check-prog.c:11: __error__: lvalue required as operand of post-increment!,
    qq!,check-prog.c:12: __error__: lvalue required as operand of post-decrement!,
    qq!,check-prog.c:15: __error__: lvalue required as left operand of assignment!,
    qq!,check-prog.c:16: __error__: lvalue required as left operand of assignment!,
    ]
},


{
title => q{Various array errors},
program => q!
    int main()
    {
        int a0[];
        int a1[5][];
        int a3["foo"];
        int n = 5;
        int a4[n];
        return 0;
    }
    !,
expected => [
    qq!,check-prog.c:4: __error__: array a0: no size of first dimension, no initialization expression!,
    qq!,check-prog.c:5: __error__: array a1: dimension other than first one is unspecified!,
    qq!,check-prog.c:6: __error__: pointer or array expression used for size of array 'a3'!,
    qq!,check-prog.c:8: __error__: invalid size expression for dimension 1 array 'a4'!,
    ]
},


#{
#title => q{Sample test},
#program => q!
#    int main()
#    {
#        return 0;
#    }
#    !,
#expected => [
#    qq!!,
#    ]
#},


);


###############################################################################


my $program = basename($0);
my $version = "0.0.0";
my $numErrors = 0;
my $numWarnings = 0;

my $srcdir;
my $assemblerFilename;
my @includeDirList;
my $stopOnFail = 0;


sub usage
{
    my ($exitStatus) = @_;

    print <<__EOF__;
Usage: $program [options]

--nocleanup       Do not delete the intermediate files after running.
--only=NUM        Only run test #NUM, with no clean up.
--last            Only run the last test.
--stop-on-fail    Stop right after a test has failed instead of continuing
                  to the end of the test list. 
--titles[=STR]    Dump to test titles (with numbers) to standard output.
                  If STR specified, only dumps titles that contain STR.
--lwasm           Use LWASM instead of FrankASM (as6809).
                  Requires LWASM >= 4.11.

__EOF__

    exit($exitStatus);
}


sub errmsg
{
    print "$program: ERROR: ";
    printf @_;
    print "\n";

    ++$numErrors;
}


sub warnmsg
{
    print "$program: Warning: ";
    printf @_;
    print "\n";

    ++$numWarnings;
}


sub indexi
{
    my ($haystack, $needle) = @_;
    
    return index(lc($haystack), lc($needle));
}


sub compileProgram
{
    my ($program, $extraCompilerOptions, $target) = @_;

    $target = $target || "usim"; 

    my $cFile;
    if (!open($cFile, "> $cFilename"))
    {
        print "$0: ERROR: failed to create source file $cFilename: $!\n";
        return undef;
    }

    print $cFile $program;
    if (!close($cFile))
    {
        print "$0: ERROR: failed to close source file $cFilename: $!\n";
        return undef;
    }

    my $compCmd = "./cmoc --$target --a09='$assemblerFilename'";
    for my $includeDir (@includeDirList)
    {
        $compCmd .= " -I '$includeDir'";
    }
    if (defined $extraCompilerOptions)
    {
        $compCmd .= " $extraCompilerOptions";
    }
    if ($useLWASM)
    {
        $compCmd .= " --lwasm";
    }
    $compCmd .= " $cFilename";  # compile for usim
    print "--- Compilation command: $compCmd\n";
    print "--- Actual compilation errors:\n";
    my $fh;
    if (!open($fh, "$compCmd 2>&1 |"))
    {
        print "$0: ERROR: failed to start compilation command $compCmd: $!\n";
        return undef;
    }
    
    # Accumulate compiler output lines in a list.
    #
    my @compOutput;
    my $line;
    while ($line = <$fh>)
    {
        $line =~ s/\s+$//s;
        
        if ($line =~ /^#/)  # ignore debugging output lines
        {
            $numDebuggingLines++;
            next;
        }

        # Mask errors and warnings to keep auto build system from complaining.
        $line =~ s/: error:/: __error__:/gi;
        $line =~ s/: warning:/: __warning__:/g;

        push @compOutput, $line;
        printf("%6u  %s\n", scalar(@compOutput), $line);
    }

    if (!close($fh) && $!)  # close() expected to fail because compiler gave errors;
                            # real close() error is when $! non null.
    {
        print "$0: ERROR: failed to close pipe to command $compCmd: $!\n";
        return undef;
    }

    return \@compOutput;
}


sub runTestNumber
{
    my ($i) = @_;

    if ($i < 0 || $i >= @testCaseList)
    {
        print "$0: ERROR: no test case #$i\n";
        return 0;
    }
    my $rhTestCase = $testCaseList[$i];
    die unless defined $rhTestCase;

    print "\n";
    print "-" x 80, "\n";
    print "--- Program # $i: ", $rhTestCase->{title}, "\n";
    my $lineNum = 0;
    for my $line (split /\n/, $rhTestCase->{program})
    {
        printf("%3u%5s%s\n", ++$lineNum, "", $line);
    }

    if (defined $rhTestCase->{suspended})
    {
        print "\n";
        print "This test is suspended.\n";
        print "\n";
        return 1;
    }

    my $raActualOutput = compileProgram($rhTestCase->{program}, $rhTestCase->{options}, $rhTestCase->{target});

    my $raExpected = $rhTestCase->{expected};
    if (defined $raExpected)
    {
        print "--- Expected compilation errors:\n";
        my $ctr = 0;
        for my $exp (@$raExpected)
        {
            $exp =~ s/: error:/: __error__:/gi;  # mask error b/c not real error
            $exp =~ s/: warning:/: __warning__:/g;
            printf("%6u  %s\n", ++$ctr, $exp);
        }
    }
    else
    {
        print "$0: ERROR: test #$i does not specify the expected compilation errors\n";
        return 0;
    }

    if (!defined $raActualOutput)
    {
        print "$0: ERROR: program #$i: no output\n";
        return 0;
    }

    if (@$raActualOutput != @$raExpected)
    {
        print "$0: ERROR: program #$i: actual output differs from expected output\n";
        return 0;
    }

    # Compare each line.
    #
    for (my $j = 0; $j < @$raActualOutput; ++$j)
    {
        my $act = $raActualOutput->[$j];
        my $exp = $raExpected->[$j];
        if ($act ne $exp)
        {
            print "$0: ERROR: program #$i: actual output differs at line ",
                    $j + 1, " from expected output\n";
            return 0;
        }
    }

    return 1;
}


# Searches the {title} field in @testCaseList.
#
sub findMatchingTestNumbers
{
    my ($testSubName) = @_;

    my @matchingNumbers;
    my $testNum = 0;
    for my $rhTestCase (@testCaseList)
    {
        my $title = $rhTestCase->{title} or die;
        if (indexi($title, $testSubName) != -1)
        {
            push @matchingNumbers, { num => $testNum, title => $title };
        }
        ++$testNum;
    }
    return \@matchingNumbers;
}


###############################################################################


my $showUsage = 0;
my $noCleanUp = 0;
my $onlyArg;
my $onlyLast;
my $titleDumpWanted;

if (!GetOptions(
    "help" => \$showUsage,
    "only=s" => \$onlyArg,
    "last" => \$onlyLast,
    "nocleanup" => \$noCleanUp,
    "stop-on-fail" => \$stopOnFail,
    "titles:s" => \$titleDumpWanted,  # the ':' means argument is optional
    "lwasm" => \$useLWASM,
    ))
{
    exit 1;
}

usage(0) if $showUsage;

$| = 1;  # no buffering on STDOUT

if (defined $titleDumpWanted)
{
    my $testIndex = 0;
    for my $rhTest (@testCaseList)
    {
        my $title = $rhTest->{title};
        die unless defined $title;
        if (indexi($title, $titleDumpWanted) != -1)  # if title contains --titles argument (empty string matches all)
        {
            printf("%6u\t%s\n", $testIndex, $title);
        }
        ++$testIndex;
    }
    exit 0;
}

$srcdir = shift || ".";
$assemblerFilename = "$srcdir/a09";
@includeDirList = ("$srcdir/support");

my $cleanUp = !$noCleanUp && !defined $onlyArg && !defined $onlyLast && !$stopOnFail;

my @testNumbers = 0 .. $#testCaseList;  # numbers of the tests to be run
if (defined $onlyArg)
{
    @testNumbers = split /,/, $onlyArg;
    for my $n (@testNumbers)
    {
        unless ($n =~ /^\d+$/)
        {
            # $n may be a substring that matches parts of test titles.
            my $raMatches = findMatchingTestNumbers($n);
            if (@$raMatches == 0)
            {
                print "Invalid test number '$n'\n\n";
                usage(1);
            }

            # If $n matches more than one test title, list matches and fail.
            if (@$raMatches > 1)
            {
                print "Ambiguous test name '$n':\n";
                for my $match (@$raMatches)
                {
                    printf("%4u  %s\n", $match->{num}, $match->{title});
                }
                print "\n";
                usage(1);
            }

            # Only one match: take the test number and continue.
            $n = $raMatches->[0]->{num};
        }
    }
}
elsif (defined $onlyLast)  # --last
{
    @testNumbers = $#testCaseList;
}

$ENV{PATH} = $srcdir . ":" . $ENV{PATH};  # allows a09 to find intelhex2cocobin

my @failedTestNumbers = ();

for my $i (@testNumbers)
{
    if (!runTestNumber($i))
    {
        push @failedTestNumbers, $i;
        last if $stopOnFail;
    }
    print "### ls ,check-prog.*:\n";
    system("ls ,check-prog.*");
    print "###\n";
}

if ($cleanUp)
{
    print "\n";
    print "Cleaning up:\n";
    my $success = 1;
    for my $ext (qw(c asm i lst hex bin))
    {
        my $fn = ",check-prog.$ext";
        if (-f $fn)
        {
            print "  erasing $fn\n";
            if (!unlink($fn))
            {
                print "$0: ERROR: failed to delete temporary file $fn: $!\n";
                $success = 0;
            }
        }
    }
    exit 1 unless $success;
}

print "\n";

if (@failedTestNumbers > 0)
{
    print "$0: ", scalar(@failedTestNumbers), " tests (#",
          join(", #", @failedTestNumbers),
          ") failed out of ", scalar(@testNumbers), "\n";
    exit 1;
}

print "$0: ALL ", scalar(@testNumbers), " tests PASSED\n";

print <<__EOF__;

         ###   #   #   ###    ###   #####   ###    ###
        #   #  #   #  #   #  #   #  #      #   #  #   #
        #      #   #  #      #      #      #      #
         ###   #   #  #      #      ###     ###    ###
            #  #   #  #      #      #          #      #
        #   #  #   #  #   #  #   #  #      #   #  #   #
         ###    ###    ###    ###   #####   ###    ###

__EOF__

if ($numDebuggingLines > 0)
{
    warnmsg("ignored %u debugging output lines", $numDebuggingLines);
}

print "$program: $numErrors error(s), $numWarnings warnings(s).\n";
exit($numErrors > 0);
