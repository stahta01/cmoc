unpackSingleAndConvertToASCII_hook IMPORT

        SECTION constructors


        IFDEF _CMOC_MS_FLOAT_
unpackSingleAndConvertToASCII IMPORT
        leax    unpackSingleAndConvertToASCII,PCR               ; PCR in caps b/c ref to code
        stx     unpackSingleAndConvertToASCII_hook,pcr
        ENDC


        ENDSECTION
