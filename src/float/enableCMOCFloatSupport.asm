        INCLUDE float.inc

        SECTION code

_enableCMOCFloatSupport EXPORT

unpackSingleAndConvertToASCII IMPORT
unpackSingleAndConvertToASCII_hook IMPORT

; void enableCMOCFloatSupport(void);
;
; For a program that uses the native float support, the reference to
; unpackSingleAndConvertToASCII will involve references to _floatable_unpack
; and _floatable_toDecimal, which will cause the linker to bring in additional
; object files to provide the needed code.
;
; A program that does not use floats should omit using enableCMOCFloatSupport(),
; so that this .asm file does not get brought into the program, and thus
; no reference to unpackSingleAndConvertToASCII is made, and no native float
; support code gets brought in.
;
; unpackSingleAndConvertToASCII_hook gets initialized by "constructor" code
; that gets run before main(). See float-ctor.asm.
;
_enableCMOCFloatSupport
        leax    unpackSingleAndConvertToASCII,PCR       ; PCR in caps b/c ref to code
        stx     unpackSingleAndConvertToASCII_hook,pcr
        rts


	ENDSECTION
