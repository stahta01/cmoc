#include "coco.h"


asm const byte *readJoystickPositions()
{
    asm
    {
        pshs    u,y     ; protect against Color Basic
        jsr     $A9DE   ; GETJOY
        jsr     $A976   ; turn audio back on (GETJOY turns it off)
        puls    y,u
        ldd     #$015A  ; return POTVAL
    }
}
