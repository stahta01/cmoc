/*  stdarg.h - Support for variable argument functions

    By Pierre Sarrazin <http://sarrazip.com/>.
    This file is in the public domain.
*/

#ifndef _stdarg_h_
#define _stdarg_h_


typedef unsigned int *va_list;

asm char *__va_arg(va_list *app, unsigned int sizeInBytes)
{
#if 0  // Code on which the following asm{} is based.
    char *origAddr;
    origAddr = (char *) *app;
    *app = (va_list) (origAddr + 2);  // always 2 bytes per argument, because char gets promoted to int
    if (sizeInBytes == 1)  // if char requested
        ++origAddr;  // pass MSB of argument in stack; point to LSB
    return origAddr;
#else
    asm
    {
        ldx     2,s     // get 'app'
        ldd     ,x      // init 'origAddr'
        pshs    b,a     // keep copy
        addd    #2      // pass current argument in stack
        std     ,x      // update caller's va_list
        ldd     6,s     // get 'sizeInBytes'
        cmpd    #1      // if char requested
        puls    a,b     // restore 'origAddr' in D (does not affect CC)
        bne     __va_arg_010    // branch if request is not for char
        addd    #1      // pass MSB of argument in stack; point to LSB
__va_arg_010:
        // return origAddr in D
    }
#endif
}

#define va_start(ap, lastFixed) do { (ap) = ((unsigned *) &(lastFixed)) + 1; } while (0)
#define va_arg(ap, type) (* (type *) __va_arg(&(ap), sizeof(type)))
#define va_end(ap) do {} while (0)


#endif  /* _stdarg_h_ */
