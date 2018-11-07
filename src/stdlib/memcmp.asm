	SECTION code

_memcmp	EXPORT


* int memcmp(void *s1, void *s2, size_t n)
*
* Returns 0, 1 or $FF in B. Leaves A undefined.
*
_memcmp
	pshs	u,y
	ldy	10,s		number of bytes to compare
	beq	_memcmp_equal
	ldx	6,s		1st string
	ldu	8,s		2nd string

_memcmp_loop
	lda	,x+		byte from 1st string
	cmpa	,u+		compare with byte from 2nd
	bne	_memcmp_diff	if bytes different

	leay	-1,y		one byte done
	bne	_memcmp_loop	if more to do

_memcmp_equal
	clrb			return 0: regions are equal
	bra	_memcmp_end

_memcmp_diff
	cmpa	-1,u
	bhi	_memcmp_ret1	return +1: 1st string comes after

	ldb	#$FF		return -1: 1st string comes before
	bra	_memcmp_end

_memcmp_ret1
	ldb	#1

_memcmp_end
	sex			return int
	puls	y,u,pc




	ENDSECTION
