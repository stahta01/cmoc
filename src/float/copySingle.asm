	SECTION code

copySingle	EXPORT


; Copies a packed single-precision number.
; Input: D = address of source number.
;        X = address of destination number.
; Preserves X. Trashes D.
;
copySingle
	pshs	u
	tfr     d,u	; address of source number
	ldd	,u
	std	,x
	ldd	2,u
	std	2,x
        IFNDEF _CMOC_MC6839_
	ldb	4,u
	stb	4,x
        ENDC
	puls	u,pc


	ENDSECTION
