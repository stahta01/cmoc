#include "coco.h"


byte waitkey(byte blinkCursor)
{
    byte key;
    if (blinkCursor)
    {
        asm
        {
            jsr $A1B1  // blink cursor while waiting for a keystroke
            sta key
        }
        return key;
    }

    for (;;)
    {
        key = inkey();
        if (key)
            return key;
    }
}
