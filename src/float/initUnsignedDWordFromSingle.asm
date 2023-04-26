        INCLUDE float.inc

	SECTION code

initUnsignedDWordFromSingle     EXPORT

initDWordFromSingle	IMPORT


initUnsignedDWordFromSingle
        andcc   #1
        lbra    initDWordFromSingle


	ENDSECTION
