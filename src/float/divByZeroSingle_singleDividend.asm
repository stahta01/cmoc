	INCLUDE float.inc

	SECTION code

divByZeroSingle_singleDividend  EXPORT

divByZeroSingle                 IMPORT


; Input: X => Destination packed single.
;        0,s (before call): Address of a packed single containing the dividend of the operation.
; Output: Calls divByZeroSingle with the sign of a single in bit 7 of A.
; Trashes A. Preserves X, U.
;
divByZeroSingle_singleDividend
        pshs    u
        ldu     4,s             ; point to single (left operand)
        lda     1,u             ; get 1st byte of mantissa (bit 7 is sign of single)
        lbsr    divByZeroSingle
        puls    u,pc
