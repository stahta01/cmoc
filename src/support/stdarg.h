/*  stdarg.h - Support for variable argument functions

    By Pierre Sarrazin <http://sarrazip.com/>.
    This file is in the public domain.
*/

#ifndef _stdarg_h_
#define _stdarg_h_


typedef unsigned int *va_list;

char *__va_arg(va_list *app, unsigned int sizeInBytes)
{
    char *origAddr;
#if 0  // Code on which the following asm{} is based.
    origAddr = (char *) *app;
    *app = (va_list) (origAddr + 2);  // always 2 bytes per argument, because char gets promoted to int
    if (sizeInBytes == 1)  // if char requested
        ++origAddr;  // pass MSB of argument in stack; point to LSB
#else
    asm
    {
        ldx     4,u     // get 'app'
        ldd     ,x      // init 'origAddr'
        tfr     d,y     // keep copy
        addd    #2      // pass current argument in stack
        std     ,x      // update caller's va_list
        ldd     6,u     // get 'sizeInBytes'
        cmpd    #1      // if char requested
        tfr     y,d     // restore 'origAddr' in D (does not affect CC)
        bne     __va_arg_010    // branch if request is not for char
        addd    #1      // pass MSB of argument in stack; point to LSB
__va_arg_010:
        std     origAddr    // return origAddr
    }
#endif
    return origAddr;
}

#define va_start(ap, lastFixed) do { (ap) = ((unsigned *) &(lastFixed)) + 1; } while (0)
#define va_arg(ap, type) (* (type *) __va_arg(&(ap), sizeof(type)))
#define va_end(ap) do {} while (0)


#endif  /* _stdarg_h_ */
