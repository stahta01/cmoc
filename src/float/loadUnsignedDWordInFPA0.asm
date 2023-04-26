	INCLUDE float.inc

	SECTION code

loadUnsignedDWordInFPA0	EXPORT


; Input: X => unsigned dword.
;
loadUnsignedDWordInFPA0
	flt_clrVALTYP
	ldd	,x
	std	FP0MAN		; store in upper mantissa of FPA0
	ldd	2,x
	std	FP0MAN+2	; store in upper mantissa of FPA0
	ldb	#128+32 	; 32 = exponent required
	stb	FP0EXP
	flt_clrFPSBYT
	clr	FP0SGN
	orcc	#1		; set carry so value seen as non-negative
	flt_normalizeFPA0
	rts



	ENDSECTION
