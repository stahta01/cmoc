	INCLUDE float.inc

	SECTION code

unpackXtoFPA0AndPrep	EXPORT
unpackXtoFPA1AndPrep    EXPORT

; Output: A = FPA1 exponent, B = FPA0 exponent, Z = 1 if FPA0 exponent is zero.
;
unpackXtoFPA0AndPrep
	flt_unpackFromXToFPA0
	bra	prepBinFloatOp

unpackXtoFPA1AndPrep
	flt_unpackFromXToFPA1

prepBinFloatOp
        flt_computeResultSign

        lda     FP1EXP
        ldb     FP0EXP          ; sets N and Z
	rts




	ENDSECTION
