#include <coco.h>


extern byte _CMOC_pmodeNo;
extern byte *_CMOC_pmodeScreenBuffer;


// Sets _CMOC_pmodeNo and _CMOC_pmodeScreenBuffer.
//
BOOL
pmode(byte mode, byte *screenBuffer)
{
    if (mode > 4 || ((word) screenBuffer & 511) != 0)
        return FALSE;
    _CMOC_pmodeNo = mode;
    _CMOC_pmodeScreenBuffer = screenBuffer;
    byte *pia1bData = (byte *) 0xff22;
    *pia1bData = *pia1bData & 7 | ((mode + 3) << 4);
    return TRUE;
}
