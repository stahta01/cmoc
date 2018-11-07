#include "coco.h"


byte isCoCo3;
byte textScreenWidth;
byte textScreenHeight;


void initCoCoSupport()
{
    word irqServiceRoutineAddress = * (word *) 0xFFF8;
    isCoCo3 = (irqServiceRoutineAddress == 0xFEF7);
    textScreenWidth  = 32;
    textScreenHeight = 16;
}
