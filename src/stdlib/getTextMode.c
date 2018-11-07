#include "coco.h"


byte getTextMode()
{
    if (isCoCo3)
    {
        byte hrWidth = * (byte *) 0x00E7;
        if (hrWidth == 1)
            return 40;
        if (hrWidth == 2)
            return 80;
    }
    return 32;
}
