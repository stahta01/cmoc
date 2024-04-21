// On a CoCo, reads test cases from FTOATEST.DAT.
// This is is generated by support/write-ftoa-test-cases.c.

// CAUTION: A float/*.c file of the CMOC sources, like this one, that invokes
//          the MC6839 must NOT do it from inline asm.
//          It must do it from a .asm file, so that this .asm file gets
//          fixed up by os9fixup.pl (see float/Makefile.am).

#include "mc6839-cmoc.h"

#include <assert.h>


enum
{
    #ifndef _CMOC_HAVE_FALSE_TRUE_
    FALSE = 0,
    TRUE = 1,
    #endif
};


#ifndef _CMOC_BASIC_TYPES_
typedef unsigned char byte;
#endif

#ifndef _CMOC_HAVE_BOOL_
typedef unsigned char BOOL;
#endif


#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))


#ifdef DUMP_BCD
static void
dumpBCD(const mc6839_bcd *bcd)
{
    printf("BCD: S=$%02x FD=%u ", bcd->fraction_sign, bcd->fraction_digits);
    printf("EXP: $%02x ", bcd->exp_sign);
    for (byte j = 0; j < MAX_EXP_LENGTH; ++j)
        printf("%u", bcd->exp[j]);
    printf("\n     ");
    for (byte j = 0; j < MAX_FRACTION_LENGTH; ++j)
        printf("%u", bcd->fraction[j]);
    printf("\n");
    //printf("     0123456789ABCDEF012\n");
}
#endif


// Rounds the mantissa to maxOutputDigits.
//
static void
roundMantissa(unsigned char fraction[MAX_FRACTION_LENGTH], byte maxOutputDigits)
{
    byte i = 0;
    while (i < MAX_FRACTION_LENGTH && fraction[i] == 0)
        ++i;
    if (i == MAX_FRACTION_LENGTH)
        return;  // nothing to do: only zeroes
    byte j = i + maxOutputDigits;
    if (j >= MAX_FRACTION_LENGTH)
        return;  // not enough digits to warrant rounding
    BOOL roundDown = (fraction[j] < 5);
    memset(fraction + j, 0, MAX_FRACTION_LENGTH - j);
    if (roundDown)
        return;

    for (byte *d = &fraction[j]; ; )
    {
        *d = 0;
        --d;
        if (d == fraction)
        {
            memset(fraction, 9, maxOutputDigits);
            return;
        }
        if (*d < 9)
        {
            ++*d;
            return;
        }
        *d = 0;
    }
}


// This function has external linkage to facilitate automated testing.
// This function is likely to be inefficient, as of Feb. 2024.
// Trashes *bcd.
//
char *
_CMOC_convertBCDToASCIIDecimal(char out[MAX_ASCII_OUTPUT_LENGTH], mc6839_bcd *bcd, unsigned char maxOutputDigits)
{
    #ifdef DUMP_BCD
    printf("convertBCDToASCIIDecimal(%u):\n", maxOutputDigits);
    dumpBCD(bcd);
    #endif

    switch (bcd->exp_sign)
    {
        case 0x00:  // non-negative number
        case 0x0F:  // negative number
            break;  // continue conversion
        case 0x0A: return strcpy(out, "+INF");  // positive infinity
        case 0x0B: return strcpy(out, "-INF");  // negative infinity
        case 0x0C: return strcpy(out, "NAN");   // not a number
        default:   return strcpy(out, "?");
    }

    roundMantissa(bcd->fraction, maxOutputDigits);

    #ifdef DUMP_BCD
    printf("AFTER ROUNDMANTISSA:\n");
    dumpBCD(bcd);
    #endif

    char *writer = out;
    const unsigned char *fraction = bcd->fraction;

    // Find the first non-zero digit.
    //
    byte i;
    for (i = 0; i < MAX_FRACTION_LENGTH; ++i)
        if (fraction[i] != 0)
            break;
    if (i == MAX_FRACTION_LENGTH)  // if only zeroes
    {
        *writer++ = '0';
        *writer = '\0';
        return out;
    }

    const int firstNonZeroIndex = i;
    //printf("#FNZI=%d\n", firstNonZeroIndex);

    char *limit = out + MAX_ASCII_OUTPUT_LENGTH - 1;  // leave room for terminating '\0'

    if (bcd->fraction_sign != 0)
        *writer++ = '-';
    
    const unsigned char *bcdExp = bcd->exp;

    int exp = (((unsigned) bcdExp[0] * 125u) << 3) + (int) bcdExp[1] * 100u + bcdExp[2] * 10u + bcdExp[3];
    if (bcd->exp_sign != 0)
        exp = -exp;
    //printf("#EXP=%d\n", exp);

    // Place the decimal point.
    // pointIndex is the index of the digit in bcd->fraction[]
    // AFTER which the point goes.
    //
    const int pointIndex = MAX_FRACTION_LENGTH - 1 - (int) bcd->fraction_digits + exp;
    //printf("#PI=%d\n", pointIndex);

    // Find the last non-zero digit.
    //
    for (i = MAX_FRACTION_LENGTH; i--; )
        if (fraction[i] != 0)
            break;
    assert(i < MAX_FRACTION_LENGTH);  // there has to be a non-zero digit
    assert(firstNonZeroIndex <= i);

    const int lastNonZeroIndex = i;
    //printf("#LNZI=%d\n", lastNonZeroIndex);

    const int numMantissaDigits = lastNonZeroIndex - firstNonZeroIndex + 1;
    //printf("#numMantissaDigits=%d, maxOutputDigits=%u\n", numMantissaDigits, maxOutputDigits);

    BOOL useSci = FALSE;
    if (firstNonZeroIndex - pointIndex >= 3)
    {
        //printf("#USESCI: CASE A: %d\n", firstNonZeroIndex - pointIndex);
        useSci = TRUE;  // .001 should be 1E-03, .01 should be .001
    }
    else if (pointIndex - firstNonZeroIndex > 7)
    {
        //printf("#USESCI: CASE B: %d\n", pointIndex - firstNonZeroIndex);
        useSci = TRUE;  // avoid excessively large numbers; prefer 3.1416E+09 to 3141600000
    }

    //printf("#USESCI=%d\n", useSci);

    if (useSci)
    {
        // Write the mantissa digits, including any decimal point.
        int numDigitsToWrite = min(numMantissaDigits, (int) maxOutputDigits);
        //printf("#numDigitsToWrite=%d\n", numDigitsToWrite);
        int numCharsNeeded = numDigitsToWrite;
        if (numCharsNeeded > 1)
            ++numCharsNeeded;  // decimal point will be written
        //printf("#numCharsNeeded=%d\n", numCharsNeeded);
        if (limit - writer < numCharsNeeded)
            return NULL;  // no room
        *writer++ = '0' + fraction[firstNonZeroIndex];
        if (numCharsNeeded > 1)
        {
            *writer++ = '.';
            int startIndex = firstNonZeroIndex + 1;
            int numDecimalToWrite = numDigitsToWrite - 1;
            for (int j = 0; j < numDecimalToWrite; ++j)
                *writer++ = '0' + fraction[startIndex + j];
        }

        // Figure out the exponent.
        // Example: The BCD string says 123.987 * 10^6 (to mean 123987000).
        //          We want to write 1.23987 * 10^8.
        //          We have moved the point 2 places to the left, so x = 6 + 2.
        //          The 6 is 'exp'. The 2 is 'delta':
        //
        const int delta = (MAX_FRACTION_LENGTH - 1 - (int) bcd->fraction_digits) - firstNonZeroIndex;
        const int sciExp = exp + delta;
        //printf("#exp=%d, delta=%d, sciExp=%d\n", exp, delta, sciExp);
        if (sciExp == 0)
            *writer = '\0';
        else
        {
            const int absSciExp = (sciExp < 0 ? -sciExp : sciExp);
            char asciiExp[12];
            itoa10(absSciExp, asciiExp);  // absolute value in ASCII
            const byte numExpDigits = (absSciExp < 100 ? 2u : (byte) strlen(asciiExp));  // at least 2 digits for exp
            if (limit - writer < 2 + numExpDigits)  // if no room for 'E', sign and abs. value
                return NULL;
            *writer++ = 'E';
            *writer++ = (sciExp < 0 ? '-' : '+');
            if (absSciExp < 10)
                *writer++ = '0';
            strcpy(writer, asciiExp);  // finishes with a '\0'
        }
    }
    else  // not using scientific notation
    {
        // First useful digit index.
        // For 0000000001234560000 with pointIndex = 11, it's min(11, 9) = 9 (the '1') (123.456).
        // For 0000000001234560000 with pointIndex =  6, it's min( 6, 9) = 6 (.00123456).
        //
        const byte firstUsefulIndex = (byte) max(min(pointIndex, firstNonZeroIndex), 0);
        //printf("#FUI=%d\n", firstUsefulIndex);
        assert(firstUsefulIndex >= 0 && firstUsefulIndex < MAX_FRACTION_LENGTH);

        // If there is no integer part:
        if (pointIndex < firstUsefulIndex || fraction[firstUsefulIndex] == 0)
        {
            //printf("#NO INTEGER PART\n");

            // Last useful digit index.
            // For 0000000001234560000 with pointIndex = 18, it's max(18, 14) = 18 (last '0') (1234560000).
            // For 0000000001234560000 with pointIndex = 11, it's max(12, 14) = 14 (the '6') (123.456).
            //
            const byte lastUsefulIndex = (byte) min(max(pointIndex, lastNonZeroIndex), MAX_FRACTION_LENGTH - 1);
            //printf("#LUI=%d\n", lastUsefulIndex);
            assert(lastUsefulIndex >= 0 && lastUsefulIndex < MAX_FRACTION_LENGTH);
            assert(lastUsefulIndex == lastNonZeroIndex);  // trailing zeroes discarded

            // Fail if no room for decimal point, the following zeroes,
            // and the significant digits.
            // Room needed: firstUsefulIndex - pointIndex + (lastUsefulIndex - firstUsefulIndex + 1)
            //
            if (limit - writer < 1 - pointIndex + lastUsefulIndex)
                return NULL;
            *writer++ = '.';
            int j;
            for (j = pointIndex + 1; j < firstUsefulIndex; ++j)
                *writer++ = '0';
            for ( ; j <= lastUsefulIndex; ++j)
                *writer++ = '0' + fraction[j];
        }
        else
        {
            //printf("#INTEGER PART\n");
            // There is an integer part. Write it.
            const int m = min(MAX_FRACTION_LENGTH - 1, pointIndex);
            //printf("#M=%d, NEED %d\n", m, m - firstUsefulIndex + 1);
            byte numDigitsIntPart = (byte) (m - firstUsefulIndex + 1);
            if (limit - writer < numDigitsIntPart)
                return NULL;  // no room for integer part
            int j;
            for (j = firstUsefulIndex; j <= m; ++j)
                *writer++ = '0' + fraction[j];
            if (j <= pointIndex)  // if integer part has zeroes beyond bcd->fraction[], they must be written
            {
                numDigitsIntPart += (byte) (pointIndex - j + 1);
                for ( ; j <= pointIndex; ++j)
                    *writer++ = '0';
            }

            // Write the fractional part if any.
            if (j <= lastNonZeroIndex)
            {
                byte numDigitsFracPart = (byte) (lastNonZeroIndex - j + 1);
                if (numDigitsIntPart + numDigitsFracPart > maxOutputDigits)
                {
                    if (numDigitsIntPart >= maxOutputDigits)  // should not happen, should have used sci. not.
                        numDigitsFracPart = 1;
                    else
                        numDigitsFracPart = maxOutputDigits - numDigitsIntPart;
                }
                if (limit - writer < 1 + numDigitsFracPart)  // allow room for point
                    return NULL;
                *writer++ = '.';
                for (byte p = 0; p < numDigitsFracPart; ++p, ++j)
                    *writer++ = '0' + fraction[j];
            }
        }
        *writer = '\0';
    }
    return out;
}


// Returns NULL if the decimal representation does not fit the given array.
//
char *
ftoa(char out[MAX_ASCII_OUTPUT_LENGTH], float f)
{
    //printf("#ftoa(out=@%p %p, f=@%p %08lx)\n", &out, out, &f, * (unsigned long *) &f);
    mc6839_bcd bcd;
    _CMOC_callMC6839BinDec(&bcd, &f);
    return _CMOC_convertBCDToASCIIDecimal(out, &bcd, DEFAULT_MAX_OUTPUT_DIGITS);
}
