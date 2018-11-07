#include "coco.h"


byte setBorderColor(byte color)
{
    if (!isCoCo3)
        return FALSE;

    * (byte *) 0xFF9A = color;
    return TRUE;
}
