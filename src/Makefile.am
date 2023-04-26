# $Id: Makefile.am,v 1.100 2022/09/16 02:32:08 sarrazip Exp $

# The dot forces CMOC to be compiled before processing the stdlib and float
# subdirectories, whose processing requires CMOC itself.
#
SUBDIRS = usim-0.91-cmoc . stdlib float

bin_SCRIPTS = install-coco-boot-loader

bin_PROGRAMS = cmoc

if BUILD_WRITECOCOFILE
bin_PROGRAMS += writecocofile
endif

cmoc_SOURCES = \
	TypeDesc.cpp \
	TypeDesc.h \
	TypeManager.cpp \
	TypeManager.h \
	DeclarationSpecifierList.cpp \
	DeclarationSpecifierList.h \
	util.cpp \
	util.h \
	Tree.cpp \
	Tree.h \
	ASMText.cpp \
	ASMText.h \
	Pseudo6809.h \
	parser.yy \
	lexer.ll \
	Declarator.cpp \
	Declarator.h \
	DeclarationSequence.cpp \
	DeclarationSequence.h \
	Declaration.cpp \
	Declaration.h \
	InitializerCodeEmitter.cpp \
	InitializerCodeEmitter.h \
	BinaryOpExpr.cpp \
	BinaryOpExpr.h \
	UnaryOpExpr.cpp \
	UnaryOpExpr.h \
	CastExpr.cpp \
	CastExpr.h \
	IfStmt.cpp \
	IfStmt.h \
	SwitchStmt.cpp \
	SwitchStmt.h \
	LabeledStmt.cpp \
	LabeledStmt.h \
	WhileStmt.cpp \
	WhileStmt.h \
	ForStmt.cpp \
	ForStmt.h \
	JumpStmt.cpp \
	JumpStmt.h \
	StringLiteralExpr.cpp \
	StringLiteralExpr.h \
	Scope.cpp \
	Scope.h \
	FunctionDef.cpp \
	FunctionDef.h \
	SemanticsChecker.cpp \
	SemanticsChecker.h \
	AncestorFunctor.cpp \
	AncestorFunctor.h \
	ExpressionTypeSetter.cpp \
	ExpressionTypeSetter.h \
	TranslationUnit.cpp \
	TranslationUnit.h \
	TreeSequence.cpp \
	TreeSequence.h \
	CommaExpr.cpp \
	CommaExpr.h \
	FunctionCallExpr.cpp \
	FunctionCallExpr.h \
	IdentifierExpr.cpp \
	IdentifierExpr.h \
	VariableExpr.cpp \
	VariableExpr.h \
	WordConstantExpr.cpp \
	WordConstantExpr.h \
	DWordConstantExpr.cpp \
	DWordConstantExpr.h \
	RealConstantExpr.cpp \
	RealConstantExpr.h \
	CompoundStmt.h \
	CodeStatus.cpp \
	CodeStatus.h \
	FormalParameter.cpp \
	FormalParameter.h \
	FormalParamList.cpp \
	FormalParamList.h \
	FunctionPointerCast.h \
	AssemblerStmt.cpp \
	AssemblerStmt.h \
	ObjectMemberExpr.cpp \
	ObjectMemberExpr.h \
	ClassDef.cpp \
	ClassDef.h \
	ConditionalExpr.cpp \
	ConditionalExpr.h \
	ScopeCreator.cpp \
	ScopeCreator.h \
	Pragma.cpp \
	Pragma.h \
	main.cpp

AM_YFLAGS = -d -Wno-conflicts-sr
# -d produces a .h file
# -Wno-conflicts-sr silences a shift/reduce warning.

cmoc_CXXFLAGS = -DPKGDATADIR=\"$(pkgdatadir)\"


if BUILD_WRITECOCOFILE

writecocofile_SOURCES = writecocofile.cpp

endif


LOCAL_CMOC = $(ENV) PATH="$(srcdir):$$PATH" CMOCFLOATLIBDIR=float ./cmoc -I $(srcdir)/stdlib/ -Lstdlib -Lfloat

# Pass STOPONFAIL="--stop --nocleanup" on the command-line
# to force the unit testing to stop at the first failed test.
# Example: make STOPONFAIL="--stop --nocleanup" check
# The --nocleanup option avoids deleting the tested program
# (,check-prog.c) and the .s, etc. files after a failure.
#
STOPONFAIL =

# We use perl -e 'print "foo\n"' to print a string that uses escape sequences (e.g., \n)
# because the system's echo command may not support echo -n -e (especially -e).
#
PERLEXEC = $(PERL) -e

CREATE_TEST_PROG = $(PERLEXEC) 'print "int main() { return 0; }\n"' >,check-prog.c

USIM = usim-0.91-cmoc/usim
HD = $(HEXDUMP) -C
MKDIR = mkdir
RMDIR = rmdir

check-base:
	./cmoc --version >/dev/null
	./cmoc --help >/dev/null
	rm -f ,check-prog.c ,check-prog.s ,check-prog.asm ,check-prog.i ,check-prog.lst ,check-prog.hex ,check-prog.bin
	$(PERLEXEC) 'print "char g; int main() { return 0; }\n"' >,check-prog.c
	$(LOCAL_CMOC) -o ,check-prog.xyz ,check-prog.c
	test ! -f ,check-prog.bin  # fail if -o not applied
	rm ,check-prog.xyz  # fail if file not there
	$(LOCAL_CMOC) --lwasm=`which lwasm` --lwlink=`which lwlink` ,check-prog.c
	rm ,check-prog.bin  # fail if file not there

check-srec:
	$(CREATE_TEST_PROG)
	$(LOCAL_CMOC) --srec --verbose ,check-prog.c | $(GREP) ",check-prog.srec"
	$(GREP) -q ^S1 ,check-prog.srec  # data record
	test `$(GREP) -c ^S9 ,check-prog.srec` = 1  # starting address record (only one)
	test `$(GREP) -c ^: ,check-prog.srec` = 0  # not Intel HEX format

# Check that a raw format executable for DECB starts with LDD #-1024 and an LBSR instruction,
# as emitted by TranslationUnit::emitAssembler().
#
check-raw:
	$(CREATE_TEST_PROG)
	$(LOCAL_CMOC) --raw --verbose ,check-prog.c | $(GREP) ",check-prog.raw"
	$(HD) ",check-prog.raw" | $(HEAD) -1 | $(GREP) -q '^00000000  cc fc 00 17'

check-org:
	$(CREATE_TEST_PROG)
	$(LOCAL_CMOC) --org=4321 --data=6000 --intermediate --verbose ,check-prog.c 2>&1
	$(GREP) -q "Symbol: program_start (,check-prog.o) = 4321" ,check-prog.map
	$(GREP) -q "Section: rwdata .* load at 6000," ,check-prog.map
	$(LOCAL_CMOC) --org=2800 --limit=2810 ,check-prog.c 2>&1 | $(GREP) -q "program_end exceeds it"

check-dos:
	$(CREATE_TEST_PROG)
	$(LOCAL_CMOC) --dos ,check-prog.c
	$(HD) ,check-prog.bin | $(HEAD) -1 | $(GREP) -q '^00000000  00 .. .. 26 00 4f 53'
	rm -f ,check-prog

check-long:
	$(LOCAL_CMOC) --usim -DPART0 -DPART1 -DPART2 -O2 -Lstdlib -Lfloat --org=1600 $(srcdir)/check-long.c 2>&1 >/dev/null
	$(USIM) check-long.srec | $(PERL) -pe '/\bSUCCESS\b/ and $$s = 1; END { exit !$$s }'
	rm -f check-long.srec

check-float: check-coco-float check-dragon-float
	$(PERLEXEC) 'print "int main() { return 18.44f == 0; }\n"' >,check-prog.c
	$(LOCAL_CMOC) --decb -c --intermediate -O0 ,check-prog.c
	$(GREP) -q 'FCB.$$85,$$13,$$85,$$1E,$$B8$$' ,check-prog.s
	$(LOCAL_CMOC) --dragon -c --intermediate -O0 ,check-prog.c
	$(GREP) -q 'FCB.$$85,$$13,$$85,$$1E,$$B8$$' ,check-prog.s
	$(LOCAL_CMOC) --os9 -c --intermediate -O0 ,check-prog.c
	$(GREP) -q 'FCB.$$13,$$85,$$1E,$$85$$' ,check-prog.s
	rm -f ,check-prog.*

check-os9: check-array-section check-add-os9-stack-space check-os9-no-float
	$(CREATE_TEST_PROG)
	$(LOCAL_CMOC) --os9 --intermediate -nodefaultlibs ,check-prog.c  # works b/c main() calls nothing
	$(LOCAL_CMOC) --os9 --intermediate ,check-prog.c
	rm ,check-prog
	$(GREP) -q OS9PREP ,check-prog.s
	$(GREP) -q OS9PREP ,check-prog.lst
	$(GREP) -q OS9PREP ,check-prog.map
	$(GREP) -q 'section start load d' ,check-prog.link
	$(PERLEXEC) 'print "void putchar(int c); int main() { putchar(42); return 0; }\n"' >,check-prog.c
	$(LOCAL_CMOC) --os9 --intermediate -nodefaultlibs ,check-prog.c | grep -q '_putchar not found'
	rm -f ,check-prog.s
	$(LOCAL_CMOC) --os9 -i ,check-prog.c
	$(GREP) -q _stkcheck ,check-prog.s
	$(LOCAL_CMOC) --os9 --intermediate --function-stack=9876 ,check-prog.c
	$(GREP) -q -w 9876 ,check-prog.s
	$(LOCAL_CMOC) --os9 --intermediate --function-stack=0 ,check-prog.c
	test `$(GREP) -c _stkcheck ,check-prog.s` = 0
	rm -f ,check-prog.* ,check-prog

# Check OS-9 option --add-os9-stack-space.
# The expected "01 50" is the word affected by that option.
# It is the Permanent Storage Size, at offset 11 of the executable.
#
check-add-os9-stack-space:
	$(CREATE_TEST_PROG)
	$(LOCAL_CMOC) --os9 --intermediate --add-os9-stack-space=300 ,check-prog.c
	$(HD) ,check-prog | $(EGREP) -q '^00000000  .* 00 0d 01 50 '
	rm -f ,check-prog.* ,check-prog

# Check that an OS-9 executable does not contain the float constructor.
#
check-os9-no-float:
	$(CREATE_TEST_PROG)
	$(LOCAL_CMOC) --os9 --intermediate ,check-prog.c
	test `$(GREP) -c float ,check-prog.map` = 0
	rm -f ,check-prog.* ,check-prog

# Check that a DECB executable contain the float constructor.
#
check-coco-float:
	$(CREATE_TEST_PROG)
	$(LOCAL_CMOC) --coco --intermediate ,check-prog.c
	test `$(GREP) -c float ,check-prog.map` = 2
	rm -f ,check-prog.*

# Check that a Dragon executable contain the float constructor.
#
check-dragon-float:
	$(CREATE_TEST_PROG)
	$(LOCAL_CMOC) --dragon --intermediate ,check-prog.c
	test `$(GREP) -c float ,check-prog.map` = 2
	rm -f ,check-prog.*

# Check that the right Dragon file type is created when using --dragon
# with --raw or --srec or neither.
#
check-dragon:
	rm -f ,check-prog.* ,check-prog
	$(CREATE_TEST_PROG)
	$(LOCAL_CMOC) --dragon ,check-prog.c
	rm ,check-prog.bin
	$(LOCAL_CMOC) --dragon --raw ,check-prog.c
	rm ,check-prog.raw
	$(LOCAL_CMOC) --dragon --srec ,check-prog.c
	rm ,check-prog.srec
	rm -f ,check-prog.* ,check-prog

# Checks that both the C file that defines a constant array and the C file that
# imports it via "extern" see the array as part of the read-only data section.
# Under OS-9, this means using ,PCR to refer to the array, while ,Y is used to
# refer to writable data.
#
check-array-section:
	$(PERLEXEC) 'print "const int ro[] = { 1000 }; int w[] = { 2000 };\n"' >,array.c
	$(PERLEXEC) 'print "extern const int ro[]; extern int w[]; int main() { return ro[0] + w[0]; }\n"' >,main.c
	$(LOCAL_CMOC) --os9 -O0 --intermediate ,main.c ,array.c
	$(EGREP) -q 'LDD.*_ro\+0,PCR' ,main.s
	$(EGREP) -q 'LDD.*_w\+0,Y' ,main.s
	rm -f ,main ,main.* ,array.*

check-flex:
	$(CREATE_TEST_PROG)
	$(LOCAL_CMOC) --flex --intermediate -nodefaultlibs ,check-prog.c  # works b/c main() calls nothing
	$(LOCAL_CMOC) --flex --intermediate ,check-prog.c
	rm ,check-prog.cmd
	$(GREP) -q -w FLEXCL ,check-prog.map  # FLEX-specific command line parsing routine
	rm -f ,check-prog.*

check-deps:
	$(CREATE_TEST_PROG)
	$(LOCAL_CMOC) -c ,check-prog.c
	test ! -f ,check-prog.d 
	$(LOCAL_CMOC) -c --deps ,check-prog.c
	$(GREP) -q '\.d : ' ,check-prog.d
	test -f ,check-prog.o 
	rm -f ,check-prog.d ,check-prog.o
	$(LOCAL_CMOC) --deps-only ,check-prog.c
	$(GREP) -q '\.d : ' ,check-prog.d
	test ! -f ,check-prog.o 
	rm -f ,check-prog.d

check-only-deps-arg:
	mkdir ,subdir
	$(CREATE_TEST_PROG)
	mv ,check-prog.c ,subdir
	$(LOCAL_CMOC) --deps-only=,subdir/,other-name.d ,subdir/,check-prog.c
	test ! -f ,other-name.d
	$(GREP) -q ',check-prog.o ,subdir/,other-name.d : ,subdir/,check-prog.c' ,subdir/,other-name.d
	rm ,subdir/,other-name.d ,subdir/,check-prog.c
	rmdir ,subdir
	mkdir ,subdir
	$(CREATE_TEST_PROG)
	mv ,check-prog.c ,subdir
	$(LOCAL_CMOC) --deps-only=,subdir/,other-name.d -o ,subdir/,check-prog.o ,subdir/,check-prog.c
	test ! -f ,other-name.d
	test ! -f ,other-name.o
	$(GREP) -q ',subdir/,check-prog.o ,subdir/,other-name.d : ,subdir/,check-prog.c' ,subdir/,other-name.d
	rm ,subdir/,other-name.d ,subdir/,check-prog.c
	rmdir ,subdir

check-vectrex:
	$(PERLEXEC) 'print "#include <vectrex/bios.h>\n#include <vectrex/stdlib.h>\nint main() { move(0, 0); wait_retrace(); return 0; }\n"' >,check-prog.c
	rm -f ,check-prog.bin
	$(LOCAL_CMOC) --vectrex --intermediate ,check-prog.c
	test -f ,check-prog.bin
	$(STRINGS) ,check-prog.bin | $(GREP) -q 'g GCE 2015'
	$(GREP) -q -w '^_move' ,check-prog.s
	$(GREP) -q -w '^_wait_retrace' ,check-prog.s

check-void-target:
	$(PERLEXEC) 'print "int main() { return 0; }\n"' >,check-prog.c
	rm -f ,check-prog.srec ,check-prog.bin
	$(LOCAL_CMOC) --void-target ,check-prog.c
	test -f ,check-prog.srec
	test ! -f ,check-prog.bin

check-intdir:
	rm -f ,check-prog.{s,lst,o,map,link,bin} ,check-prog-out.{map,link,bin}
	$(CREATE_TEST_PROG)
	$(LOCAL_CMOC) -i -c ,check-prog.c
	test -f ,check-prog.s
	test -f ,check-prog.lst
	test -f ,check-prog.o
	rm ,check-prog.{s,lst,o}
	$(LOCAL_CMOC) -i ,check-prog.c
	test -f ,check-prog.s
	test -f ,check-prog.lst
	test -f ,check-prog.o
	test -f ,check-prog.map
	test -f ,check-prog.link
	test -f ,check-prog.bin
	rm ,check-prog.{s,lst,o,map,link,bin}
	$(MKDIR) ,int
	$(LOCAL_CMOC) -i -c --intdir=,int ,check-prog.c
	test -f ,int/,check-prog.s
	test -f ,int/,check-prog.lst
	test -f ,int/,check-prog.o
	rm ,int/,check-prog.{s,lst,o}
	$(LOCAL_CMOC) -i -c --intdir=,int -o ,check-prog.o ,check-prog.c
	test -f ,int/,check-prog.s
	test -f ,int/,check-prog.lst
	test -f ,check-prog.o
	rm ,int/,check-prog.{s,lst} ,check-prog.o
	$(LOCAL_CMOC) -i -c --intdir=,int -o ./,check-prog.o ,check-prog.c
	test -f ,int/,check-prog.s
	test -f ,int/,check-prog.lst
	test -f ,check-prog.o
	rm ,int/,check-prog.{s,lst} ,check-prog.o
	$(LOCAL_CMOC) -i --intdir=,int -o ./,check-prog-out.bin ,check-prog.c
	test -f ,int/,check-prog.s
	test -f ,int/,check-prog.lst
	test -f ,int/,check-prog.o
	test -f ,check-prog-out.map
	test -f ,check-prog-out.link
	test -f ,check-prog-out.bin
	rm ,int/,check-prog.{s,lst,o}
	rm ,check-prog-out.{map,link,bin}
	$(RMDIR) ,int

# Check that 8x8 multiply uses MUL instruction, and that 16x8 uses MUL16 routine.
# 
check-mul:
	$(PERLEXEC) 'print "unsigned f(unsigned char a, unsigned char b) { return a * b; }\n"' >,check-prog.c
	$(LOCAL_CMOC) -c -i -O0 ,check-prog.c
	$(PERL) -ne '/^\s+MUL\b/ and $$f=1; END {exit !$$f}' ,check-prog.s

	$(PERLEXEC) 'print "unsigned f(unsigned char a, unsigned b) { return a * b; }\n"' >,check-prog.c
	$(LOCAL_CMOC) -c -i -O0 ,check-prog.c
	$(PERL) -ne '/^\s+LBSR\s+MUL16\b/ and $$f=1; END {exit !$$f}' ,check-prog.s

	$(PERLEXEC) 'print "unsigned f(unsigned a, unsigned char b) { return a * b; }\n"' >,check-prog.c
	$(LOCAL_CMOC) -c -i -O0 ,check-prog.c
	$(PERL) -ne '/^\s+LBSR\s+MUL16\b/ and $$f=1; END {exit !$$f}' ,check-prog.s

	rm -f ,check-prog.*

# Test the -Wlocal-var-hiding option.
# After calling cmoc, use a Perl command to invert cmoc's exit status: we want cmoc to fail.
#
check-local-var-hiding:
	echo 'void f() { int v; if (1) { int v; } }' >,check-prog.c
	$(LOCAL_CMOC) -c -Wlocal-var-hiding -Werror ,check-prog.c >/dev/null; $(PERLEXEC) 'exit !$$ARGV[0]' $$?
	rm -f ,check-prog.*

check-misc: check-base check-srec check-raw check-org check-long check-float check-os9 check-flex \
				check-deps check-only-deps-arg check-vectrex check-stack-space check-linking check-nbsp \
				check-local-var-hiding check-void-target check-call-graph check-func-import check-no-hole
	rm -f ,check-prog.*

check-self-tests:
	$(PERL) -cw $(srcdir)/test-program-output.pl
	$(PERL) -cw $(srcdir)/test-bad-programs.pl
	$(PERL) $(srcdir)/test-program-output.pl $(STOPONFAIL) $(srcdir)
	$(PERL) $(srcdir)/test-bad-programs.pl $(STOPONFAIL) $(srcdir)

# Stack space must be specified when compiling the .c file that defines main().
check-stack-space:
	$(PERLEXEC) 'print qq[#include <cmoc.h>\nint main() { printf("\%u\\n", sbrkmax()); return 0; }\n]' >,check-prog.c
	$(LOCAL_CMOC) --usim -c -I $(srcdir)/stdlib ,check-prog.c
	$(LOCAL_CMOC) --usim --org=0 ,check-prog.o
	test `$(USIM) ,check-prog.srec` -ge 60000
	$(LOCAL_CMOC) --usim -c -I $(srcdir)/stdlib --stack-space=30000 ,check-prog.c
	$(LOCAL_CMOC) --usim --org=0 ,check-prog.o
	test `$(USIM) ,check-prog.srec` -lt 34000
	$(PERLEXEC) 'print qq[#pragma stack_space 15000\n#include <cmoc.h>\nint main() { printf("\%u\\n", sbrkmax()); return 0; }\n]' >,check-prog.c
	$(LOCAL_CMOC) --usim -c -I $(srcdir)/stdlib ,check-prog.c
	$(LOCAL_CMOC) --usim --org=0 ,check-prog.o
	test `$(USIM) ,check-prog.srec` -ge 48000
	test `$(USIM) ,check-prog.srec` -lt 49000
	rm -f ,check-prog.c ,check-prog.o ,check-prog.srec

check-linking:
	$(PERLEXEC) 'print "int main() { return 0; }\n"' > ,mod0.c
	echo "static void in() {}  void ex() { void (*pf)() = in; }" > ,mod1.c
	$(LOCAL_CMOC) ,mod0.c ,mod1.c
	rm -f ,mod0.c ,mod1.c ,mod0.bin

check-writecocofile:
if BUILD_WRITECOCOFILE
	./writecocofile --version >/dev/null
	./writecocofile --help >/dev/null
	$(PERL) -e 'print chr(255) x (35*18*256)' > ,check.dsk
	./writecocofile -d ,check.dsk | $(GREP) -q '68 granule.s. free'
	echo FOOBAR > ,check.dat
	./writecocofile --verbose ,check.dsk ,check.dat > ,check.log
	$(GREP) -q 'Writing native file ,check.dat' ,check.log
	./writecocofile -d ,check.dsk | $(GREP) -q '67 granule.s. free'
	./writecocofile -d ,check.dsk | $(GREP) -q ',CHECK  .DAT  data     binary'
	./writecocofile -s ,check.dsk ,check.dat | $(GREP) -q 'FOOBAR'
	./writecocofile --verbose -k ,check.dsk ,check.dat | $(GREP) -q 'Freeing granule'
	./writecocofile -d ,check.dsk | $(GREP) -q '68 granule.s. free'
	rm -f ,check.dsk ,check.dat ,check.log
endif

# This checks that an initializer that involves 'f' is seen as a use of f(),
# which avoids the warning about a static function not being called.
# This test compiles with -c and without a main() function.
#
check-call-graph:
	echo "static void f(void) {}  void (*pf)(void) = f;" > ,check-prog.c
	$(LOCAL_CMOC) --usim -c ,check-prog.c
	rm -f ,check-prog.*

# Checks if some files contain non-breakable spaces (character 160).
# The statement in the 'continue' clause resets the line counter ($.)
# at the end of each processed file.
#
check-nbsp:
	cd $(srcdir) && $(PERL) -e 'while (<>) { if (/\xA0/) { print "Non-breakable space at $$ARGV:$$.\n"; exit 1 } } continue { close ARGV if eof }' \
		$(cmoc_SOURCES) test-program-output.pl test-bad-programs.pl check-long.c $(bin_SCRIPTS) Makefile.am

# Check that a non-static function prototype generates an IMPORT directive
# in the asm file.
#
check-func-import:
	echo "int f(char); int main() { int (*pf)(char) = f; return pf(0); }" > ,check-prog.c
	$(LOCAL_CMOC) --usim -c ,check-prog.c
	rm -f ,check-prog.*

# Check that a DECB program that has something in its BSS section gives a .bin file
# containing single contiguous block.
# The Perl script reads the entire .bin file, gets the length of the first .bin block,
# and checks that this block is 10 bytes less than the whole file.
# A single-block .bin file has a 5-byte header, the contents, then the 5-byte footer.
# The dollar signs in the Perl script are doubled so that make passes a single
# dollar sign to the Perl command.
#
check-no-hole:
	echo "char bssArray[9]; int main() { return 0; }" > ,check-prog.c
	rm -f ,check-prog.bin
	$(LOCAL_CMOC) --coco ,check-prog.c
	$(PERL) -e '$$/ = undef; $$bin = <>; ($$z, $$blkLen) = unpack("Cn", $$bin); die unless $$blkLen == length($$bin) - 10' ,check-prog.bin
	rm -f ,check-prog.*

check: check-writecocofile check-misc check-self-tests


EXTRA_DIST = $(bin_SCRIPTS) $(pkgdata_DATA) $(pkgdata_SCRIPTS) \
             test-program-output.pl test-bad-programs.pl check-long.c

.PHONY: cleanlib
cleanlib:
	$(MAKE) -C stdlib clean
	$(MAKE) -C float clean

CLEANFILES = parser.cc parser.h lexer.cc

MAINTAINERCLEANFILES = Makefile.in
