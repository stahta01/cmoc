// _FinishIntegerToASCII.c - CMOC's standard library functions.
//
// By Pierre Sarrazin <http://sarrazip.com/>.
// This file is in the public domain.

#include <cmoc.h>


char *
_FinishIntegerToASCII(char *firstDigit, char *endOfString, char *returnValue)
{
    #if 0  /* Original C code. */

    *endOfString = '\0';

    // Invert characters from 'firstDigit' to before 'endOfString'.
    for (--endOfString; firstDigit < endOfString; ++firstDigit, --endOfString)
    {
        char tmp = *firstDigit;
        *firstDigit = *endOfString;
        *endOfString = tmp;
    }

    #else

    asm
    {
        pshs    y                   ; preserve CMOC globals pointer
        ldx     :firstDigit
        ldy     :endOfString        ; cannot refer to globals now
        clr     ,y
        leay    -1,y
        bra     @loopCond
@loopBody
; Swap *firstDigit and *endOfString.
        lda     ,x
        ldb     ,y
        sta     ,y
        stb     ,x+                 ; also increment firstDigit
        leay    -1,y                ; --endOfString
@loopCond
        sty     :endOfString        ; store for comparison
        cmpx    :endOfString        ; firstDigit < endOfString ?
        blo     @loopBody
        puls    y
    }

    #endif

    return returnValue;
}
