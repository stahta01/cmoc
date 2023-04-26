	INCLUDE float.inc

	SECTION code

initSingleFromUnsignedDWord     EXPORT

initSingleFromDWord	        IMPORT


initSingleFromUnsignedDWord
        andcc   #1
        lbra    initSingleFromDWord


	ENDSECTION
