	INCLUDE float.inc

	SECTION code

initSingleFromSignedWord	EXPORT


; Initializes the single-precision float at X with the signed word in D.
;
initSingleFromSignedWord
	pshs	u,y,x
	flt_loadSignedDIntoFPA0
	puls	x
	flt_packFPA0ToX
	puls	y,u,pc

	ENDSECTION
