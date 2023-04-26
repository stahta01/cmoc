	INCLUDE float.inc

	SECTION code

divSingleSingle	EXPORT

divByZeroSingle_singleDividend IMPORT
unpackXToFPA1AndDiv     IMPORT
binOpSingleSingle       IMPORT

; Divides two numbers and writes the result at a third location.
; Synopsis:
;	pshs	rightOpAddr
;	pshs	leftOpAddr
;	leax	result,PCR
;	lbsr	divSingleSingle
;	leas	4,s
; Preserves X.
;
divSingleSingle
	tst	[4,s]		; check exponent of right operand (divisor)
        lbeq    divByZeroSingle_singleDividend
	pshs	u,y,x
	leau    unpackXToFPA1AndDiv,PCR		; uppercase PCR b/c ref to code
	lbsr	binOpSingleSingle
	puls	x,y,u,pc


	ENDSECTION
