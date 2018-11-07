# $Id: Makefile.am,v 1.4 2018/05/09 23:00:30 sarrazip Exp $

cmoclibdir = $(pkgdatadir)/lib
cmoclib_DATA = \
	libcmoc-float-ecb.a \
	libcmoc-float-usim.a

ASM = \
	addFPA0FPA1.asm \
	addIntSingle.asm \
	addSignedDWordSingle.asm \
	addSingleInt.asm \
	addSingleSignedDWord.asm \
	addSingleSingle.asm \
	addSingleUnsignedDWord.asm \
	addSingleUnsignedInt.asm \
	addUnsignedDWordSingle.asm \
	addUnsignedIntSingle.asm \
	binOpSingleSingle.asm \
	cmpSignedIntSingle.asm \
	cmpSingleSignedInt.asm \
	cmpSingleSingle.asm \
	cmpSingleUnsignedInt.asm \
	cmpUnsignedIntSingle.asm \
	copySingle.asm \
	decrementSingle.asm \
	divByZeroSingle.asm \
	divIntSingle.asm \
	divSignedDWordSingle.asm \
	divSingleInt.asm \
	divSingleSignedDWord.asm \
	divSingleSingle.asm \
	divSingleUnsignedDWord.asm \
	divSingleUnsignedInt.asm \
	divUnsignedDWordSingle.asm \
	divUnsignedIntSingle.asm \
	ftoa.asm \
	incrementSingle.asm \
	initDWordFromSingle.asm \
	initSignedByteFromSingle.asm \
	initSignedWordFromSingle.asm \
	initSingleFromDWord.asm \
	initSingleFromSignedWord.asm \
	initSingleFromUnsignedWord.asm \
	initUnsignedByteFromSingle.asm \
	initUnsignedWordFromSingle.asm \
	isDWordZeroSpecial.asm \
	isSingleZero.asm \
	loadSignedDWordInFPA0.asm \
	loadUnsignedDInFPA0.asm \
	loadUnsignedDWordInFPA0.asm \
	mulIntSingle.asm \
	mulSignedDWordSingle.asm \
	mulSingleInt.asm \
	mulSingleSignedDWord.asm \
	mulSingleSingle.asm \
	mulSingleUnsignedDWord.asm \
	mulSingleUnsignedInt.asm \
	mulUnsignedDWordSingle.asm \
	mulUnsignedIntSingle.asm \
	negateSingle.asm \
	strtof.asm \
	subIntSingle.asm \
	subSignedDWordSingle.asm \
	subSingle_common.asm \
	subSingleInt.asm \
	subSingleSignedDWord.asm \
	subSingleSingle.asm \
	subSingleUnsignedDWord.asm \
	subSingleUnsignedInt.asm \
	subUnsignedDWordSingle.asm \
	subUnsignedIntSingle.asm \
	unpackXToFPA0AndDiv.asm \
	unpackXtoFPA0AndPrep.asm \
	unpackXToFPA1AndMul.asm

ECB_OBJ  = $(ASM:asm=ecb_o)
USIM_OBJ = $(ASM:asm=usim_o)

libcmoc-float-ecb.a: $(ECB_OBJ)
	$(LWAR) -c $@ $(ECB_OBJ)
libcmoc-float-usim.a: $(USIM_OBJ)
	$(LWAR) -c $@ $(USIM_OBJ)

.asm.ecb_o:
	$(LWASM) -fobj -D_COCO_BASIC_ --output=$@ $<
.asm.usim_o:
	$(LWASM) -fobj -DUSIM --output=$@ $<

CLEANFILES = $(cmoclib_DATA) \
        $(ECB_OBJ) $(USIM_OBJ) \
	$(ECB_OBJ:.ecb_o=.s) \
        $(ECB_OBJ:.ecb_o=.lst)

EXTRA_DIST = float.inc $(ASM)
