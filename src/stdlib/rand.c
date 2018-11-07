static unsigned _RandomSeed = 0;


asm void
srand(unsigned newSeed)
{
    asm
    {
        ldd     2,s             ; newSeed
        std     :_RandomSeed
    }
}


asm int
rand()
{
    //_RandomSeed = _RandomSeed * (256 + 128 + 1) + 1;
    //return (int) (_RandomSeed & 0x7FFF);
    asm
    {
	LDD	:_RandomSeed
	PSHS	B,A	SEED
	TFR	B,A
	CLRB
	PSHS	B,A	SEED * 256
	LSRA
	RORB
	PSHS	B
	LSLA
	LDB	:_RandomSeed	MSB of SEED
	LSRB
	RORA
	PULS	B	D = SEED * 128
	ADDD	,S++	D = SEED * (256 + 128)
	ADDD	,S++	D = SEED * (256 + 128 + 1)
	ADDD	#1
        EORB    #$40            ; improves distribution of this bit 
	STD	:_RandomSeed
	ANDA	#$7F	15-bit result
    }
}
