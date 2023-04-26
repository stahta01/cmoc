// Source: http://forum.43oh.com/topic/10095-fast-sqrt-for-16-bit-integers/
//
unsigned char
sqrt16(unsigned short value)
{
    unsigned char i;
    unsigned short rem, root;
    #if 0
    rem  = 0;
    root = 0;

    // loop over the eight bits in the root
    for ( i = 0; i < 8; i++ ) {
        // shift the root up by one bit
        root <<= 1;

        // move next two bits from the input into the remainder
        rem = ((rem << 2) + (value >> 14));
        value <<= 2;

        // test root is (2n + 1)
        ++root;

        if ( root <= rem ) {
            // root not more than the remainder, so the new bit is one
            rem -= root;
            ++root;
        } else {
            // root is greater than the remainder, so the new bit is zero
            --root;
        }
    }
    return (root >> 1);
    #else
    asm
    {
        ldb     #8              ; number of loop iterations
        stb     :i
        clra
        clrb
        std     :rem
        std     :root
; for i=0..7:
@loop:
; Move next two bits from the input ('value') into the remainder.
        lsl     :value[1]       ; LSB of 'value'
        rol     :value          ; MSB
        rol     :rem[1]
        rol     :rem
        lsl     :value[1]
        rol     :value
        rol     :rem[1]
        rol     :rem
; ++root (D contains 'root' at this point).
        lslb
        rola
        addd    #1
        std     :root
; if:
        cmpd    :rem
        bhi     @else
        ldd     :rem
        subd    :root
        std     :rem
        ldd     :root
        addd    #1
        bra     @endif
@else:
        ldd     :root
        subd    #1
@endif:
        std     :root
; Increment 'i'.
        dec     :i
        bne     @loop           ; D contains 'root' at this point
; root >> 1:
        lsra
        rorb
        std     :root
    }
    return (unsigned char) root;
    #endif
}
