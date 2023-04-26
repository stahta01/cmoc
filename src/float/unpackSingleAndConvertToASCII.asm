        INCLUDE float.inc

        SECTION code

unpackSingleAndConvertToASCII EXPORT


; Input: X => Packed single-precision float.
; Trashes B, X.
; Preserves U.
;
unpackSingleAndConvertToASCII
	flt_unpackFromXToFPA0
	flt_convertFPA0ToASCII
        rts


	ENDSECTION
