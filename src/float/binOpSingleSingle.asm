        INCLUDE float.inc

        SECTION code

binOpSingleSingle       EXPORT


; Does a binary operation on two numbers and writes the result at a third location.
; Synopsis (based on pattern generated by CMOC):
;       pshs    rightOpAddr
;       pshs    leftOpAddr
;       leax    result,pcr
;       lbsr    addSingleSingle         ; for example
;       leas    4,s
;   [...]
; addSingleSingle
;       pshs    u,y,x
;       ldu     #colorBasicRoutine      ; routine uses FPA0 & FPA1, result in FPA0
;       lbsr    binOpSingleSingle
;       puls    u,x,y,pc
;
binOpSingleSingle
;
; Stack at this point:
;    0,S: Return address in caller of binOpSingleSingle (e.g., addSingleSingle).
;    2,S: Caller's X: Result address.
;    4,S: Caller's Y.
;    6,S: Caller's U: Routine that reads the number at X, may unpack it to FPA1, then does FPA0 = op(FPA0, the number at X).
;    8,S: Return address of caller of (e.g.) addSingleSingle.
;   10,S: Address of left operand.
;   12,S: Address of right operand.
;
        ldx     12,s            ; rightOpAddr
        flt_unpackFromXToFPA0
        ldx     10,s            ; leftOpAddr
        jsr     ,u
        ldx     2,s             ; result address
        flt_packFPA0ToX
        rts


        ENDSECTION
