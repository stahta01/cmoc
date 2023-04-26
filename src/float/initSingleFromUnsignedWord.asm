	INCLUDE float.inc

	SECTION code

initSingleFromUnsignedWord	EXPORT

loadUnsignedDInFPA0             IMPORT


; Initializes the single-precision float at X with the unsigned word in D.
;
initSingleFromUnsignedWord
	pshs	u,y,x
	lbsr	loadUnsignedDInFPA0	; load D (unsigned) into FPA0
	puls	x
	flt_packFPA0ToX
	puls	y,u,pc

	ENDSECTION
