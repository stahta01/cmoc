	SECTION code

negateSingle	EXPORT


; Negates the packed single-precision float at X.
; Preserves X.
;
negateSingle
        tst     ,x              ; check exponent: is number zero?
        beq     @done           ; if yes, nothing to do
	ldb	1,x
	eorb	#$80
	stb	1,x
@done
	rts




	ENDSECTION
