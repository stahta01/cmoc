	INCLUDE float.inc

	SECTION code

loadUnsignedDInFPA0	EXPORT


; Trashes D, X.
;
loadUnsignedDInFPA0
	flt_clrVALTYP
	std	FP0MAN		; store in upper mantissa of FPA0
	ldb	#128+16 	; 16 = exponent required
	stb	FP0EXP      ; save exponent
	clra
	clrb
	std	FP0MAN+2    ; clear lower mantissa of FPA0
	flt_clrFPSBYT
	sta	FP0SGN
	orcc	#1		; set carry so value seen as non-negative
	flt_normalizeFPA0
	rts


	ENDSECTION
