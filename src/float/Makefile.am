# $Id: Makefile.am,v 1.24 2022/09/16 02:32:08 sarrazip Exp $
#
# ecb = Extended Color Basic.
# dgn = Dragon.
# native = CMOC's own floating-point library (experimental, slow and bloated).

cmoclibdir = $(pkgdatadir)/lib
cmoclib_DATA = \
	float-ctor.ecb_o \
	float-ctor.dgn_o \
	libcmoc-float-ecb.a \
	libcmoc-float-dgn.a

if DISTRIBUTE_FLOATABLE

cmoclib_DATA += \
	float-ctor.native_o \
	libcmoc-float-native.a

endif

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
	divByZeroSingle_singleDividend.asm \
	divIntSingle.asm \
	divSignedDWordSingle.asm \
	divSingleInt.asm \
	divSingleSignedDWord.asm \
	divSingleSingle.asm \
	divSingleUnsignedDWord.asm \
	divSingleUnsignedInt.asm \
	divUnsignedDWordSingle.asm \
	divUnsignedIntSingle.asm \
	enableCMOCFloatSupport.asm \
	ftoa.asm \
	incrementSingle.asm \
	initDWordFromSingle.asm \
	initSignedDWordFromSingle.asm \
	initUnsignedDWordFromSingle.asm \
	initSignedByteFromSingle.asm \
	initSignedWordFromSingle.asm \
	initSingleFromDWord.asm \
	initSingleFromSignedWord.asm \
	initSingleFromUnsignedWord.asm \
	initSingleFromSignedDWord.asm \
	initSingleFromUnsignedDWord.asm \
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
	unpackSingleAndConvertToASCII.asm \
	unpackXToFPA0AndDiv.asm \
	unpackXtoFPA0AndPrep.asm \
	unpackXToFPA1AndMul.asm

C_FILES = \
	atoff.c

ECB_OBJ  = $(ASM:asm=ecb_o) $(C_FILES:.c=.ecb_o)
DGN_OBJ  = $(ASM:asm=dgn_o) $(C_FILES:.c=.dgn_o)
NATIVE_OBJ = $(ASM:asm=native_o) $(C_FILES:.c=.native_o) native-data.native_o

libcmoc-float-ecb.a: $(ECB_OBJ)
	$(LWAR) -c $@ $(ECB_OBJ)

libcmoc-float-dgn.a: $(DGN_OBJ)
	$(LWAR) -c $@ $(DGN_OBJ)

if DISTRIBUTE_FLOATABLE

NATIVE_OTHER = native-data.asm native/floatable.h native/floatable-private.h

# CMOC-independent 40-bit floating-point library.
FLOATABLE_ASM = \
	native/floatable.asm
FLOATABLE_C = \
	native/addUFloat40.c \
	native/assert.c \
	native/cmpUFloat40.c \
	native/compareAccWithDivisor.c \
	native/div40by32.c \
	native/fdiv.c \
	native/fmul.c \
	native/fromDecimal.c \
	native/normalizeUFloat40.c \
	native/pack.c \
	native/print.c \
	native/setUFloat40ToSignedInt.c \
	native/setUFloat40ToZero.c \
	native/shift5BytesLeft1Bit.c \
	native/subtract32From40.c \
	native/subUFloat40.c \
	native/toDecimal.c \
	native/unpack.c
FLOATABLE_OBJ = \
	$(FLOATABLE_ASM:.asm=.native_o) \
	$(FLOATABLE_C:.c=.native_o)

# Library that contains Floatable and CMOC-specific glue code.
libcmoc-float-native.a: $(NATIVE_OBJ) $(FLOATABLE_OBJ)
	$(LWAR) -c $@ $(NATIVE_OBJ) $(FLOATABLE_OBJ)

endif


%.ecb_o: %.asm float.inc
	$(LWASM) -fobj -D_COCO_BASIC_ -D_CMOC_MS_FLOAT_ --output=$@ $<

%.dgn_o: %.asm float.inc
	$(LWASM) -fobj -DDRAGON -D_CMOC_DGN_FLOAT_ -D_CMOC_MS_FLOAT_ --output=$@ $<

%.native_o: %.asm float.inc
	$(LWASM) -fobj -D_CMOC_NATIVE_FLOAT_ --output=$@ $<

INTERMEDIATE = #-i
CMOC_LIB_FLAGS = -O2 -DNDEBUG -nostdinc -I $(srcdir)/../stdlib -I $(srcdir) -Werror $(INTERMEDIATE)

%.ecb_o: %.c float.inc
	../cmoc --coco -c $(CMOC_LIB_FLAGS) -D_CMOC_MS_FLOAT_ -o $@ $<

%.dgn_o: %.c float.inc
	../cmoc --dragon -c $(CMOC_LIB_FLAGS) -D_CMOC_DGN_FLOAT_ -D_CMOC_MS_FLOAT_ -o $@ $<

%.native_o: %.c float.inc native/floatable.h native/floatable-private.h
	../cmoc -c $(CMOC_LIB_FLAGS) -D_CMOC_NATIVE_FLOAT_ -o $@ $<

# Checks if some files contain non-breakable spaces (character 160).
# The statement in the 'continue' clause resets the line counter ($.)
# at the end of each processed file.
#
check:
	$(PERL) -e 'while (<>) { if (/\xA0/) { print "Non-breakable space at $$ARGV:$$.\n"; exit 1 } } continue { close ARGV if eof }' \
		$(ASM) $(C_FILES) Makefile.am

CLEANFILES = $(cmoclib_DATA) \
	$(ECB_OBJ) $(ECB_OBJ:.ecb_o=.s) $(ECB_OBJ:.ecb_o=.lst) \
	$(DGN_OBJ) $(DGN_OBJ:.dgn_o=.s) $(DGN_OBJ:.dgn_o=.lst) \
	$(NATIVE_OBJ) $(NATIVE_OBJ:.native_o=.s) $(NATIVE_OBJ:.native_o=.lst) $(FLOATABLE_OBJ)

EXTRA_DIST = \
    float.inc float-ctor.asm $(ASM) $(C_FILES) \
    $(NATIVE_OTHER) \
    $(FLOATABLE_ASM) $(FLOATABLE_C)
