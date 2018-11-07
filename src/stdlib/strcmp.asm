	SECTION code

_strcmp	EXPORT


* int strcmp(char *, char *);
*
_strcmp
	pshs	u,x
	ldx	6,s		1st string
	ldu	8,s		2nd string

_strcmp_050
	ldb	,u+
	lda	,x+
	bne	_strcmp_010
	tstb
	beq	_strcmp_900	return 0 (in B)

* a zero but b non zero, so 1st string comes before
_strcmp_040
	ldb	#$ff
	bra	_strcmp_900

_strcmp_010	equ	*
	tstb
	bne	_strcmp_020

* a non zero but b zero, so 1st string comes after
_strcmp_030	equ	*
	ldb	#1
	bra	_strcmp_900

_strcmp_020	equ	*
* a and b non zero.
	cmpa	-1,u
	bhi	_strcmp_030	return +1
	blo	_strcmp_040	return -1
	bra	_strcmp_050

_strcmp_900
	sex
	puls	x,u,pc




	ENDSECTION
