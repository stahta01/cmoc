	INCLUDE float.inc

	SECTION code

initSingleFromDWord	EXPORT


; Initializes the single-precision float at X with the dword whose address is in D.
; The carry must be the signedness flag (0 for unsigned dword, non-zero for signed).
;
initSingleFromDWord
	pshs	u,y,x,cc
	flt_clrVALTYP
	tfr	d,x			; X => dword
	ldd	2,x			; copy dword to mantissa
	std	FP0MAN+2
	ldd	,x
	std	FP0MAN
; A is now high byte of mantissa, as expected by $BC84
	ldb	#128+32			; exponent: 32
	stb	FP0EXP
	flt_clrFPSBYT
	clr	FP0SGN
	puls	cc			; test signedness flag
	bcc	@unsigned
	suba	#$80			; set carry if non-negative mantissa
	bra	@normalize
@unsigned
	orcc	#1			; consider mantissa non-negative
@normalize
	flt_normalizeFPA0
	puls	x
	flt_packFPA0ToX
	puls	y,u,pc			; not implemented




	ENDSECTION
