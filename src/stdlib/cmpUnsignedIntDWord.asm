	SECTION code

cmpUnsignedIntDWord	EXPORT

cmpDWordDWord           IMPORT


cmpUnsignedIntDWord
	pshs	u,x
	ldu	8,s		; address of dword
	ldd	6,s		; signed int
	pshs	b,a		; create temp dword in stack
	clr	,-s
	clr	,-s		; pushed dword version of int
	leau	,s		; point to dword (left side)
	pshs	u,x
	lbsr	cmpDWordDWord
	leas	8,s		; clean up pushed U and X, and temp long
	puls	x,u,pc




	ENDSECTION
