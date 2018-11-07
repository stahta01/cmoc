/*  coco.h - Utility functions for interface with CoCo Disk Basic

    By Pierre Sarrazin <http://sarrazip.com/>.
    This file is in the public domain.
*/

#ifndef _coco3_h_
#define _coco3_h_

#include <cmoc.h>


enum { FALSE, TRUE };

#ifndef _CMOC_BASIC_TYPES_
#define _CMOC_BASIC_TYPES_

typedef unsigned char byte;
typedef signed char   sbyte;
typedef unsigned int  word;
typedef signed int    sword;

#endif

typedef unsigned char uint8_t;
typedef signed char   int8_t;
typedef unsigned int  uint16_t;
typedef signed int    int16_t;


#ifdef _COCO_BASIC_


/*  Registers U and Y must be saved in the stack
    while calling CoCo BASIC routines.
*/

byte isCoCo3 = FALSE;


// May be called more than once.
//
void initCoCoSupport()
{
    word irqServiceRoutineAddress = * (word *) 0xFFF8;
    isCoCo3 = (irqServiceRoutineAddress == 0xFEF7);
}


void setHighSpeed(byte fast)
{
    asm
    {
        ldx     #65494
        tst     fast
        beq     setHighSpeed_010
        leax    1,x
setHighSpeed_010:
        tst     isCoCo3
        beq     setHighSpeed_020
        leax    2,x
setHighSpeed_020:
        clr     ,x
    }
}


byte resetPalette(byte isRGB)
{
    if (!isCoCo3)
        return FALSE;

    // Fix bug in CoCo 3 BASIC's RGB and CMP commands.
    if (* (byte *) 0xE649 == 15)
        * (byte *) 0xE649 = 16;

    // Jump to RGB or CMP routine.
    asm("PSHS", "U,Y");  // protect against BASIC routine
    if (isRGB)
        asm("JSR", "$E5FA");
    else
        asm("JSR", "$E606");
    asm("PULS", "Y,U");
    return TRUE;  // success
}


// slot: 0..15.
// color: 0..63.
// Returns true for success, false if args are invalid.
// See also paletteRGB().
//
byte palette(byte slot, byte color)
{
    if (!isCoCo3)
        return FALSE;
    if (slot > 15)
        return FALSE;
    if (color > 63)
        return FALSE;
    byte *palette = (byte *) 0xFFB0;
    palette[slot] = color;
    return TRUE;
}


// Easier interface when assuming an RGB monitor.
// slot: 0..15.
// red, green, blue: 0..3.
//
void paletteRGB(byte slot, byte red, byte green, byte blue)
{
    if (!isCoCo3)
        return;
    if (slot > 15)
        return;
    * (((byte *) 0xFFB0) + slot) = ((red   & 2) << 4)
                                   | ((red   & 1) << 2)
                                   | ((green & 2) << 3)
                                   | ((green & 1) << 1)
                                   | ((blue  & 2) << 2)
                                   |  (blue  & 1);
}


// Sets the given 6-bit color code as the border color
// for the 40 and 80 column modes.
//
byte setBorderColor(byte color)
{
    if (!isCoCo3)
        return FALSE;

    * (byte *) 0xFF9A = color;
    return TRUE;
}


byte textScreenWidth  = 32;
byte textScreenHeight = 16;


// Returns true for success, false if arg is invalid.
//
byte width(byte columns)
{
    if (!isCoCo3)
        return FALSE;

    if (columns != 32 && columns != 40 && columns != 80)
        return FALSE;

    asm("PSHS", "U,Y");  // protect against BASIC routine
    asm("LDB", columns);
    asm("JSR", "$F643");  // inside the WIDTH command
    asm("PULS", "Y,U");

    textScreenWidth = columns;
    textScreenHeight = (columns == 32 ? 16 : 24);

    return TRUE;
}


// Returns 32, 40 or 80.
//
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


// color: Argument that would be passed to BASIC's CLS command.
//        Pass 255 to signify no argument.
//
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


// Bits 0-2: background color (0-7)
// Bits 3-5: foreground color (0-7)
// Bits 6: underline if set.
// Bits 7: blink if set.
//
byte attr(byte foreColor, byte backColor, byte blink, byte underline)
{
    if (!isCoCo3)
        return FALSE;

    asm
    {
        ldb     foreColor
        lslb
        lslb
        lslb
        orb     backColor
        tst     blink
        beq     attr_no_b
        orb     #$80
attr_no_b:
        tst     underline
        beq     attr_no_u
        orb     #$40
attr_no_u:
        stb     $FE08
    }

    return TRUE;
}


byte locate(byte column, byte row)
{
    byte hrwidth;
    if (isCoCo3)
        hrwidth = * (byte *) 0x00E7;
    else
        hrwidth = 0;

    if (hrwidth == 0)  // if 32 col mode
    {
        if (column >= 32)
            return FALSE;
        if (row >= 16)
            return FALSE;
        * (word *) 0x0088 = 1024 + (((word) row) << 5) + column;
    }
    else
    {
        if (column >= 80)
            return FALSE;
        if (row >= 24)
            return FALSE;
        if (hrwidth == 1)  // if 40 col mode
            if (column >= 40)
                return FALSE;
        asm("PSHS", "U,Y");  // protect against BASIC routine
        asm("LDA", column);
        asm("LDB", row);
        asm("JSR", "$F8F7");  // inside the LOCATE command
        asm("PULS", "Y,U");
    }
    return TRUE;
}


byte hscreen(byte mode)
{
    if (!isCoCo3)
        return FALSE;

    if (mode > 4)
        return FALSE;
    asm("PSHS", "U,Y");  // protect against BASIC routine
    asm("LDB", mode);
    asm("JSR", "$E69C");
    asm("PULS", "Y,U");
    return TRUE;
}


byte hset(word x, word y, byte color)
{
    if (x >= 640 || y >= 192 || color >= 16)
        return FALSE;
    byte hrmode = * (byte *) 0x00E6;
    if (hrmode == 0)
        return FALSE;  // hi-res mode not enabled
    if (hrmode <= 2)
        if (x >= 320)
            return FALSE;
    * (byte *) 0x00C2 = 1;  // SETFLG: 1 = HSET, 0 = HRESET
    * (word *) 0x00BD = x;  // HORBEG
    * (word *) 0x00BF = y;  // VERBEG
    asm("PSHS", "U,Y");  // protect against BASIC routine
    asm("LDB", color);
    asm("JSR", "$E73B");  // save the working color
    asm("JSR", "$E785");  // put the pixel on the screen
    asm("PULS", "Y,U");
    return TRUE;
}


void setCaseFlag(byte upperCase)
{
    if (upperCase != 0)
        upperCase = 0xFF;
    * (byte *) 0x11a = upperCase;
}


#if 0  // Untested.

// Calls BASIC's NEW command.
//
void newBasicProgram()
{
    asm("PSHS", "U,Y");  // protect against BASIC routine
    asm("JSR", "$AD19");
    asm("PULS", "Y,U");
}


void warmStart()
{
    asm("JMP", "$A027");  // EXEC 40999
}

#endif  // Untested


void coldStart()
{
    asm("CLR", "$71");    // POKE 113,0
    asm("JMP", "$A027");  // EXEC 40999
}


// Returns 0 if no key is currently pressed.
//
byte asm inkey()
{
    asm
    {
        jsr     [$A000]     // POLCAT
        tfr     a,b         // byte return value goes in B
    }
}


// Waits for a key to be pressed and returns its code.
//
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


// Same arguments as Color Basic's SOUND command.
//
void sound(byte tone, byte duration)
{
    asm("PSHS", "U");  // protect U from Color Basic code
    * (byte *) 0x8C = tone;
    * (word *) 0x8D = ((word) duration) << 2;
    asm("JSR", "$A956");
    asm("PULS", "U");
}


#define DEV_SCREEN     0
#define DEV_CASSETTE (-1)
#define DEV_SERIAL   (-2)
#define DEV_PRINTER  DEV_SERIAL

void asm setOutputDevice(sbyte deviceNum)
{
    asm
    {
        ldb     3,s     // deviceNum
        stb     $6F     // Color Basic's DEVNUM
    }
}


// newValue: word value.
//
#define setTimer(newValue) (* (word *) 0x112 = (newValue))

// Returns a word.
//
#define getTimer() (* (word *) 0x112)


// seconds: 0..1092.
//
void sleep(int seconds)
{
    if (!seconds)
        return;
    unsigned limit = 60 * (unsigned) seconds; 
    setTimer(0);
    while (getTimer() < limit)
        ;
}


// samAddr: Base address to write to (0xFFC0 for screen mode,
//          0xFFC6 for graphics page address).
// value:   Value to write.
// numBits: Number of bits to write to samAddr. (Refers to the
//          least significant bits of 'value'.)
// 
void setSAMRegisters(byte *samAddr, byte value, byte numBits)
{
    while (numBits)
    {
        // Write at even address to send a 0, odd to send a 1.
        //
        *(samAddr + (value & 1)) = 0;

        value = value >> 1;

        --numBits;

        // Next SAM bit is two addresses further.
        //
        samAddr += 2;
    }
}


// Writes the given byte in the 6k PMODE 4 screen buffer (0x1800 bytes long)
// starting at the address given by 'textScreenBuffer'.
//
void pcls(byte *buffer, byte byteToClearWith)
{
    word *end = (word *) (buffer + 0x1800);

    asm {
        lda     byteToClearWith
        tfr     a,b
        ldx     buffer
pcls_loop:
        std     ,x++
        std     ,x++
        std     ,x++
        std     ,x++
        std     ,x++
        std     ,x++
        std     ,x++
        std     ,x++
        std     ,x++
        std     ,x++
        std     ,x++
        std     ,x++
        std     ,x++
        std     ,x++
        std     ,x++
        std     ,x++
        cmpx    end
        bne     pcls_loop
    }
}


// pageNum: 512-byte page index in 0..127.
// Sets the SAM registers to show the PMODE 4 graphics
// at address pageNum * 512.
//
void showGraphicsAddress(byte pageNum)
{
    setSAMRegisters((byte *) 0xFFC6, pageNum, 7);
    setSAMRegisters((byte *) 0xFFC0, 6, 3);
}


// Set "PMODE 4 : SCREEN 1,colorset", where colorset is 0 (green/black)
// or 1 (white/black).
//
void showPmode4(byte colorset)
{
    byte *pia1bData = (byte *) 0xff22;
    byte b = *pia1bData & 7 | 0xf0;
    if (colorset)
         b |= 8;
    *pia1bData = b;
}


// Select the 32x16 text mode and position the screen buffer at address 1024.
//
void showLowResTextAddress()
{
    setSAMRegisters((byte *) 0xFFC6, 2, 7);  // 2 == 0x0400 / 512
    setSAMRegisters((byte *) 0xFFC0, 0, 3);  // 0 == 32x16 mode
}


// Show the text mode.
//
void asm showPmode0()
{
    asm
    {
        ldb     $FF22
        andb    #7
        stb     $FF22
    }
}


#else  /* !defined _COCO_BASIC_ */


byte textScreenWidth  = 80;
byte textScreenHeight = 24;


void coldStart()
{
    asm { sync }  // stops usim
}


byte asm inkey()
{
    asm
    {
        ldb $ff00   // assumed a properly modified usim 6809 simulator
    }
}


// Waits for a key to be pressed and returns its code.
//
byte waitkey(byte blinkCursor)
{
    byte key;
    for (;;)
    {
        key = inkey();
        if (key)
        {
            if (key != '\n')
                while (inkey() != '\n')  //PATCH: need cbreak mode
                    ;
            return key;
        }
    }
}


#endif  /* !defined _COCO_BASIC_ */


#endif  /* _coco3_h_ */
