#include "coco.h"


void cls(byte color)
{
    asm("PSHS", "U,Y");  // protect against BASIC routine
    byte hrwidth;
    if (isCoCo3)
        hrwidth = * (byte *) 0x00E7;
    else
        hrwidth = 0;

    if (hrwidth != 0)
    {
        if (color > 8)
            color = 1;
        // This is the hi-res CLS routine,
        // which must not be called in 32 column mode.
        asm("LDB", color);
        asm("JSR", "$F6B8");
    }
    else if (color > 8)
    {
        asm("JSR", "$A928");
    }
    else
    {
        asm("LDB", color);
        asm("JSR", "$A91C");
    }
    asm("PULS", "Y,U");
}
