#include "coco.h"


void sound(byte tone, byte duration)
{
    asm("PSHS", "U");  // protect U from Color Basic code
    * (byte *) 0x8C = tone;
    * (word *) 0x8D = ((word) duration) << 2;
    asm("JSR", "$A956");
    asm("PULS", "U");
}
