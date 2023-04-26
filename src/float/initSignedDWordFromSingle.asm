        INCLUDE float.inc

	SECTION code

initSignedDWordFromSingle     EXPORT

initDWordFromSingle	IMPORT


initSignedDWordFromSingle
        orcc    #1
        lbra    initDWordFromSingle


	ENDSECTION
