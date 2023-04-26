float
fabsf(float num)
{
    asm  // This routine also works if num == 0, i.e., all zero bytes.
    {
        leax    :num            ; point to packed float 'num'
        ldb     1,x             ; get sign/mantissa byte
        andb    #$7F            ; set sign to 0 (positive)
        stb     1,x
    }
    return num;
}
