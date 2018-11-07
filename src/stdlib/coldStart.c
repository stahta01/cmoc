#include "coco.h"


void coldStart()
{
    asm("CLR", "$71");    // POKE 113,0
    asm("JMP", "$A027");  // EXEC 40999
}
