# $Id: Makefile.am,v 1.29 2016/07/26 01:18:52 sarrazip Exp $

SUBDIRS = support usim-0.91-cmoc

localedir = $(datadir)/locale

bin_SCRIPTS = intelhex2cocobin intelhex2srec install-coco-boot-loader

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
	ExpressionTypeSetter.cpp \
	ExpressionTypeSetter.h \
	TranslationUnit.cpp \
	TranslationUnit.h \
	TreeSequence.cpp \
	TreeSequence.h \
	FunctionCallExpr.cpp \
	FunctionCallExpr.h \
	IdentifierExpr.cpp \
	IdentifierExpr.h \
	VariableExpr.cpp \
	VariableExpr.h \
	WordConstantExpr.cpp \
	WordConstantExpr.h \
	CompoundStmt.h \
	CodeStatus.cpp \
	CodeStatus.h \
	FormalParameter.cpp \
	FormalParameter.h \
	FormalParamList.h \
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

AM_YFLAGS = -d
# -d produces a .h file

cmoc_CXXFLAGS = \
	-DPKGDATADIR=\"$(pkgdatadir)\" \
	-DLOCALEDIR=\"$(localedir)\" \
	-DHAVE_AS6809=\"$(HAVE_AS6809)\" \
	-DHAVE_LWASM=\"$(HAVE_LWASM)\" \
	-I../intl -I$(top_srcdir)/intl

cmoc_LDADD = \
	$(INTLLIBS)


if BUILD_WRITECOCOFILE

writecocofile_SOURCES = writecocofile.cpp

writecocofile_CXXFLAGS = \
	-DLOCALEDIR=\"$(localedir)\" \
	-I../intl -I$(top_srcdir)/intl

endif


pkgdata_SCRIPTS = a09

LOCAL_CMOC = $(ENV) PATH="$(srcdir):$$PATH" ./cmoc -I$(srcdir)/support --a09='$(srcdir)/a09'
HEXDUMP = od -tx1

# Pass STOPONFAIL="--stop --nocleanup" on the command-line
# to force the unit testing to stop at the first failed test.
# Example: make STOPONFAIL="--stop --nocleanup" check
# The --nocleanup option avoids deleting the tested program
# (,check-prog.c) and the .asm, etc. files after a failure.
#
STOPONFAIL =

check: check-writecocofile
	$(PERL) -cw $(srcdir)/a09
	$(PERL) -cw $(srcdir)/intelhex2cocobin
	$(PERL) -cw $(srcdir)/intelhex2srec
	$(srcdir)/a09 --version >/dev/null
	$(srcdir)/a09 --help >/dev/null
	test -x $(srcdir)/intelhex2cocobin
	test "`$(srcdir)/intelhex2cocobin </dev/null`" = ""
	test "`echo -ne ":02BEEF004F4B00\n:00000001FF\n" | $(srcdir)/intelhex2cocobin | od -tx1 | head -1`" = \
		"0000000 00 00 02 be ef 4f 4b ff 00 00 be ef"
	test "`echo -ne ":02BEEF004F4B00\n:00000001ff\n" | $(srcdir)/intelhex2cocobin --entry=1234 | od -tx1 | head -1`" = \
		"0000000 00 00 02 be ef 4f 4b ff 00 00 12 34"
	test -x $(srcdir)/intelhex2srec
	test "`$(srcdir)/intelhex2srec </dev/null`" = ""
	test "`echo -ne ":02BEEF004F4B00\n" | $(srcdir)/intelhex2srec`" = "S105BEEF4F4BB3"
	test "`echo -ne ":02BEEF004F4B00\n:00000001FF\n" | $(srcdir)/intelhex2srec --entry=ABCD | tail -1`" = \
		"S903ABCD84"
	test "`echo ":0D00000048656C6C6F2C20576F726C640A00" | $(srcdir)/intelhex2srec`" = "S110000048656C6C6F2C20576F726C640A9D"
	./cmoc --version >/dev/null
	./cmoc --help >/dev/null
	echo "int main() { return 0; }" >,check-prog.c
	$(LOCAL_CMOC) --srec --usim --verbose ,check-prog.c | $(GREP) "Generating SREC"
	$(GREP) -q ^S1 ,check-prog.srec  # data record
	test `$(GREP) -c ^S9 ,check-prog.srec` = 1  # starting address record (only one)
	test `$(GREP) -c ^: ,check-prog.srec` = 0  # not Intel HEX format
	$(LOCAL_CMOC) --org=4321 --verbose ,check-prog.c 2>&1 | $(GREP) -q "program_start             .4321"
	$(LOCAL_CMOC) --org=2800 --limit=2810 ,check-prog.c 2>&1 | $(GREP) -q "program_end exceeds it"
	$(LOCAL_CMOC) --dos ,check-prog.c
	od -tx1 ,check-prog.bin | head -1 | $(GREP) -q '^0000000 00 .. .. 26 00'
	$(LOCAL_CMOC) --os9 ,check-prog.c
	$(GREP) -rwq mod ,check-prog.asm
	test -f ,check-prog
	rm -f ,check-prog
	echo -ne "#pragma limit 0x2810\nint main() { return 0; }\n" >,check-prog.c
	$(LOCAL_CMOC) --org=2800 ,check-prog.c 2>&1 | $(GREP) -q "program_end exceeds it"
	rm -f ,check-prog.*
	$(PERL) -cw $(srcdir)/test-program-output.pl
	$(PERL) -cw $(srcdir)/test-bad-programs.pl
	$(PERL) $(srcdir)/test-program-output.pl $(STOPONFAIL) $(srcdir)
	$(PERL) $(srcdir)/test-bad-programs.pl $(STOPONFAIL) $(srcdir)


check-writecocofile:
if BUILD_WRITECOCOFILE
	./writecocofile --version >/dev/null
	./writecocofile --help >/dev/null
	$(PERL) -e 'print chr(255) x (35*18*256)' > ,check.dsk
	./writecocofile -d ,check.dsk | grep -q '68 granule.s. free'
	echo FOOBAR > ,check.dat
	./writecocofile --verbose ,check.dsk ,check.dat | grep -q 'Writing native file ,check.dat'
	./writecocofile -d ,check.dsk | grep -q '67 granule.s. free'
	./writecocofile -d ,check.dsk | grep -q ',CHECK  .DAT  data     binary'
	./writecocofile -s ,check.dsk ,check.dat | grep -q 'FOOBAR'
	./writecocofile --verbose -k ,check.dsk ,check.dat | grep -q 'Freeing granule'
	./writecocofile -d ,check.dsk | grep -q '68 granule.s. free'
	rm -f ,check.dsk ,check.dat
endif


EXTRA_DIST = $(bin_SCRIPTS) $(pkgdata_DATA) $(pkgdata_SCRIPTS) \
             test-program-output.pl test-bad-programs.pl 

CLEANFILES = parser.cc parser.h lexer.cc

MAINTAINERCLEANFILES = Makefile.in
