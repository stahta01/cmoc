        SECTION code

_stricmp	EXPORT

convertABToUpperCase    IMPORT
strcmpimpl				IMPORT


* int strcmp(char *, char *);
*
_stricmp
	leax	convertABToUpperCase,PCR
	lbra	strcmpimpl


        ENDSECTION
