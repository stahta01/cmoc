; N.B.: Not used when using --mc6839. See mc6839-strtof.c instead.

	INCLUDE float.inc

	SECTION code

_strtof	EXPORT


; float strtof(char *nptr, char **endptr);
;
; The string must have at most 255 characters (before the null terminator).
; Caution: Passing an excessive value will make Basic fail with an OV ERROR.
;
_strtof

        IFDEF _CMOC_MS_FLOAT_
GETCCH	EQU	$00A5           ; routine: get current char
CHARAD	EQU	$00A6		; interpreter's input pointer

	pshs	u,y             ; protect CMOC registers against Basic

	ldd	CHARAD		; save interpreter's input pointer
	pshs	b,a
	ldx	10,s		; nptr: string to parse
	stx	CHARAD		; point interpreter to caller's string

	jsr	GETCCH		; get current char in A; set carry iff A is numeric char
	jsr	convertStrToFlt ; convert string at X into FPA0; trashes FPA1

	ldx	8,s		; address of returned float (hidden parameter)
	flt_packFPA0ToX

	ldd	CHARAD		; get address in nptr where parsing stopped
	std	[12,s]		; store at *endptr

	puls	a,b
	std	CHARAD		; restore interpreter's input pointer

	puls	y,u,pc

        ENDC                    ; _CMOC_MS_FLOAT_


        IFDEF _CMOC_NATIVE_FLOAT_

_floatable_fromDecimal  IMPORT
_floatable_pack         IMPORT

        pshs    u               ; save frame pointer
        leau    ,s
        leas    -6,s            ; UFloat40 (unpacked float)
; Arguments: 4,u = address of float to return; 6,u = nptr; 8,u = endptr.

; Call byte floatable_fromDecimal(UFloat40 *dest, const char *decimal, char **endptr);
        ldx     8,u             ; endptr
        ldd     6,u             ; nptr
        pshs    x,d
        leax    -6,u            ; address of unpacked float to fill
        pshs    x
        lbsr    _floatable_fromDecimal
        leas    6,s
;        tstb
;        beq     @success
; Overflow. TODO: errno = ERANGE;
; Pack the +/- HUGE_VALF just received into the returned float.
@success
; Call floatable_pack(PFloat40 *dest, const UFloat40 *src);
        leax    -6,u            ; unpacked float just filled
        ldd     4,u             ; packed float to be filled
        pshs    x,d
        lbsr    _floatable_pack
        leas    4,s
; TODO: errno = 0;
@return
        leas    ,u
        puls    u,pc

        ENDC                    ; _CMOC_NATIVE_FLOAT_


	ENDSECTION
