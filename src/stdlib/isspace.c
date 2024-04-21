#include <cmoc.h>


asm int
isspace(int c)
{
    asm
    {
        ldd     2,s         ; argument 'c'
        cmpd    #9
        blo     @notSpace
        cmpd    #13
        bls     @space
        cmpd    #32
        beq     @space
@notSpace
        clrb
        clra
        rts
@space
        ldb     #1
@return
        clra
    }
}
