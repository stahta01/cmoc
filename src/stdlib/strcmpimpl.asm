        SECTION code

strcmpimpl     EXPORT


; Routine that compares two strings and returns -1, 0 or +1
; (like strcmp()) in D depending on the result.
; Preserves U and may trash X.
;
; Input: two string pointers on the stack;
;        X => character transform routine.
;             That routine may change registers A and B, which will contain
;             characters from the two strings.
;             The routine may change CC.
;             It must preserve the other registers.
;
strcmpimpl
        pshs    u,x
; Stack map here:
; 0,S = address of transform routine;
; 2,S = saved U;
; 4,S = return address;
; 6,S = address of first string;
; 8,S = address of second string.
        ldx     6,s             ; 1st string
        ldu     8,s             ; 2nd string

_strcmp_050
        ldb     ,u+
        lda     ,x+
        bne     _strcmp_010
        tstb
        beq     _strcmp_900     ; return 0 (in B)

* a zero but b non zero, so 1st string comes before
_strcmp_040
        ldb     #$ff
        bra     _strcmp_900

_strcmp_010     equ     *
        tstb
        bne     _strcmp_020

* a non zero but b zero, so 1st string comes after
_strcmp_030     equ     *
        ldb     #1
        bra     _strcmp_900

_strcmp_020     equ     *
* a and b non zero.
        jsr     [,s]            ; call routine to transform A and B
        pshs    b
        cmpa    ,s+
        bhi     _strcmp_030     ; return +1
        blo     _strcmp_040     ; return -1
        bra     _strcmp_050

_strcmp_900
        sex
        puls    x,u,pc


        ENDSECTION
