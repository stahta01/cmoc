# $Id: Makefile.am,v 1.23 2018/09/02 04:56:19 sarrazip Exp $

# N.B.: CMOC must already have been compiled before this directory can be processed.

# CAUTION: In this library, references to data must be specified with lowercase ",pcr",
#          while references to code must be specified with uppercase ",PCR".
#          This is for the benefit of OS-9, where ",pcr" gets converted to ",Y".

# The linker mode header files go in /usr/share/cmoc/include,
# while the legacy monolith mode header files go in /usr/share/cmoc.
#
cmocincdir = $(pkgdatadir)/include
cmocinc_HEADERS = \
	assert.h \
	cmoc.h \
	coco.h \
	disk.h \
	stdarg.h \
	vectrex.h

vectrexincdir = $(cmocincdir)/vectrex
vectrexinc_HEADERS = \
	vectrex/stdlib.h \
	vectrex/bios.h

# The ecb, usim, os9 and vec keywords in these library names
# are specified in invokeLinker() [main.cpp].
#
cmoclibdir = $(pkgdatadir)/lib
cmoclib_DATA = \
	libcmoc-crt-ecb.a \
	libcmoc-crt-usim.a \
	libcmoc-crt-os9.a \
	libcmoc-crt-vec.a \
	libcmoc-std-ecb.a \
	libcmoc-std-usim.a \
	libcmoc-std-os9.a \
	libcmoc-std-vec.a

CRT_ASM = \
	crt.asm \
	addDWordDWord.asm \
	addDWordInt.asm \
	addDWordUnsignedInt.asm \
	adddww.asm \
	addIntDWord.asm \
	addUnsignedIntDWord.asm \
	andDWordDWord.asm \
	andDWordWord.asm \
	cmpDWordDWord.asm \
	cmpDWordSignedInt.asm \
	cmpDWordUnsignedInt.asm \
	cmpdww.asm \
	cmpSignedIntDWord.asm \
	cmpUnsignedIntDWord.asm \
	copyDWord.asm \
	copyDWordFromXToD.asm \
	copyMem.asm \
	copyWordToDWord.asm \
	decrementDWord.asm \
	DIV16.asm \
	DIV16BY10.asm \
	DIV32.asm \
	DIV8.asm \
	DIV8BY7.asm \
	divdwb.asm \
	divDWordDWord.asm \
	divDWordUnsignedInt.asm \
	divdww.asm \
	divModDWordDWord.asm \
	divModDWordUnsignedInt.asm \
	divModUnsignedIntDWord.asm \
	divUnsignedIntDWord.asm \
	incrementDWord.asm \
	initByteFromDWord.asm \
	initDWordFromSignedWord.asm \
	initDWordFromUnsignedWord.asm \
	initSingleFromSingle.asm \
	initWordFromDWord.asm \
	isDWordZero.asm \
	jumpTableSwitch.asm \
	leftShiftDWord.asm \
	leftShiftDWordAtXByB.asm \
	modDWordDWord.asm \
	modDWordUnsignedInt.asm \
	modUnsignedIntDWord.asm \
	MUL168_TO24.asm \
	MUL168_TO32.asm \
	MUL16.asm \
	MUL32.asm \
	mulDWordDWord.asm \
	mulDWordInt.asm \
	mulDWordUnsignedInt.asm \
	mulIntDWord.asm \
	mulUnsignedIntDWord.asm \
	negateDWord.asm \
	orDWordDWord.asm \
	orDWordWord.asm \
	push4ByteStruct.asm \
	push5ByteStruct.asm \
	pushStruct.asm \
	rightShiftDWord.asm \
	rightShiftDWordAtXByB.asm \
	SDIV16.asm \
	SDIV8.asm \
	shiftByteLeft.asm \
	shiftByteRightSigned.asm \
	shiftByteRightUnsigned.asm \
	shiftLeft.asm \
	shiftRightSigned.asm \
	shiftRightUnsigned.asm \
	signedDivDWordDWord.asm \
	signExtWordToDWord.asm \
	sub32.asm \
	sub32xu.asm \
	subDWordDWord.asm \
	subDWordInt.asm \
	subDWordUnsignedInt.asm \
	subdww.asm \
	subIntDWord.asm \
	subUnsignedIntDWord.asm \
	testAndRemoveSignOnDWord.asm \
	testAndRemoveSignOnWord.asm \
	xorDWordDWord.asm \
	xorDWordWord.asm

STD_ASM = \
	atoi.asm \
	atoui.asm \
	ATOW.asm \
	checknull.asm \
	checkstack.asm \
	delay.asm \
	dwtoa.asm \
	LINBUF.asm \
	memcmp.asm \
	memcpy.asm \
	memset.asm \
	printf.asm \
	putchar_a.asm \
	putstr.asm \
	readline.asm \
	readword.asm \
	sbrk.asm \
	sbrkmax.asm \
	seed.asm \
	setConsoleOutHook.asm \
	sprintf.asm \
	strcat.asm \
	strchr.asm \
	strcmp.asm \
	strcpy.asm \
	strlen.asm \
	strlwr.asm \
	strncpy.asm \
	strtoul.asm \
	strupr.asm \
	tolower.asm \
	toupper.asm \
	zerodw.asm

# Also part of 'std' library:
C_COMMON = \
	atol.c \
	atoul.c \
	strtol.c \
	stdarg.c \
        sqrt16.c \
        divmod16.c \
        divmod8.c \
        rand.c

# Also part of 'std' library, but only under Color Basic:
C_COCO_BASIC = \
	atoff.c \
	showLowResTextAddress.c \
	showPmode4.c \
	showGraphicsAddress.c \
	pcls.c \
	setSAMRegisters.c \
	sleep.c \
	setOutputDevice.c \
	sound.c \
	readJoystickButtons.c \
	readJoystickPositions.c \
	isKeyPressed.c \
	waitkey.c \
	inkey.c \
	coldStart.c \
	setCaseFlag.c \
	hset.c \
	hscreen.c \
	locate.c \
	attr.c \
	cls.c \
	getTextMode.c \
	width.c \
	setBorderColor.c \
	paletteRGB.c \
	palette.c \
	resetPalette.c \
	setHighSpeed.c \
	initCoCoSupport.c \
	disk.c

# Also part of 'std' library, but only for the Vectrex:
C_VECTREX = vectrex_bios.c

CRT_ECB_OBJ  = $(CRT_ASM:.asm=.ecb_o)
CRT_USIM_OBJ = $(CRT_ASM:.asm=.usim_o)
CRT_OS9_OBJ  = $(CRT_ASM:.asm=.os9_o)
CRT_VECTREX_OBJ  = $(CRT_ASM:.asm=.vec_o)

libcmoc-crt-ecb.a: $(CRT_ECB_OBJ)
	$(LWAR) -c $@ $(CRT_ECB_OBJ)
libcmoc-crt-usim.a: $(CRT_USIM_OBJ)
	$(LWAR) -c $@ $(CRT_USIM_OBJ)
libcmoc-crt-os9.a: $(CRT_OS9_OBJ)
	$(LWAR) -c $@ $(CRT_OS9_OBJ)
libcmoc-crt-vec.a: $(CRT_VECTREX_OBJ)
	$(LWAR) -c $@ $(CRT_VECTREX_OBJ)

STD_ECB_OBJ  = $(STD_ASM:.asm=.ecb_o)  $(C_COMMON:.c=.ecb_o) $(C_COCO_BASIC:.c=.ecb_o)
STD_USIM_OBJ = $(STD_ASM:.asm=.usim_o) $(C_COMMON:.c=.usim_o)
STD_OS9_OBJ  = $(STD_ASM:.asm=.os9_o)  $(C_COMMON:.c=.os9_o)
STD_VECTREX_OBJ = $(STD_ASM:.asm=.vec_o) $(C_COMMON:.c=.os9_o) $(C_VECTREX:.c=.vec_o)

libcmoc-std-ecb.a: $(STD_ECB_OBJ)
	$(LWAR) -c $@ $(STD_ECB_OBJ)
libcmoc-std-usim.a: $(STD_USIM_OBJ)
	$(LWAR) -c $@ $(STD_USIM_OBJ)
libcmoc-std-os9.a: $(STD_OS9_OBJ)
	$(LWAR) -c $@ $(STD_OS9_OBJ)
libcmoc-std-vec.a: $(STD_VECTREX_OBJ)
	$(LWAR) -c $@ $(STD_VECTREX_OBJ)

.asm.ecb_o:
	$(LWASM) -fobj -D_COCO_BASIC_ --output=$@ $<
.asm.usim_o:
	$(LWASM) -fobj -DUSIM --output=$@ $<
OS9TEMP = $(notdir $<.os9asm)
.asm.os9_o:
	$(PERL) $(srcdir)/os9fixup.pl < $< > $(OS9TEMP)
	$(LWASM) -fobj -DOS9 -I$(srcdir) --pragma=dollarnotlocal --output=$@ $(OS9TEMP)
	rm $(OS9TEMP)
# OS9: dollarnotlocal is necessary to avoid errors on identifiers like "F$Exit".
.asm.vec_o:
	$(LWASM) -fobj -DVECTREX --output=$@ $<

CMOC_LIB_FLAGS = -O2 -DNDEBUG -nostdinc -I $(srcdir)

.c.ecb_o:
	../cmoc -c $(CMOC_LIB_FLAGS) -o $@ $<
.c.usim_o:
	../cmoc -c $(CMOC_LIB_FLAGS) --usim -o $@ $<
.c.os9_o:
	../cmoc -c $(CMOC_LIB_FLAGS) --os9 -o $@ $<
.c.vec_o:
	../cmoc -c $(CMOC_LIB_FLAGS) --vectrex -DSTD_INC_PATH='$(srcdir)/std.inc' -o $@ $<

CLEANFILES = $(cmoclib_DATA) \
        $(CRT_ECB_OBJ) $(CRT_USIM_OBJ) $(CRT_OS9_OBJ) $(CRT_VECTREX_OBJ) \
        $(STD_ECB_OBJ) $(STD_USIM_OBJ) $(STD_OS9_OBJ) $(STD_VECTREX_OBJ)

EXTRA_DIST = std.inc os9fixup.pl $(CRT_ASM) $(STD_ASM) $(C_COMMON) $(C_COCO_BASIC) $(C_VECTREX)
