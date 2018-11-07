# For help on the Markdown syntax: see
# http://daringfireball.net/projects/markdown/syntax

man_MANS = $(PACKAGE).1

MARKDOWN = markdown

HTML_DOC_FILES = $(PACKAGE)-manual.html $(PACKAGE)-implementation.html $(PACKAGE)-vectrex.html

html-local: $(HTML_DOC_FILES)

$(PACKAGE)-manual.html: $(PACKAGE)-manual.markdown toc.pl
	$(MARKDOWN) $(PACKAGE)-manual.markdown > $(PACKAGE)-manual.html
	$(PERL) -i toc.pl $(PACKAGE)-manual.html  # add table of contents in place
	grep '<H2>Table of Contents' $(PACKAGE)-manual.html  # check that it worked

$(PACKAGE)-implementation.html: $(PACKAGE)-implementation.markdown toc.pl
	$(MARKDOWN) $(PACKAGE)-implementation.markdown > $(PACKAGE)-implementation.html
	$(PERL) -i toc.pl $(PACKAGE)-implementation.html  # add table of contents in place
	grep '<H2>Table of Contents' $(PACKAGE)-implementation.html  # check that it worked

$(PACKAGE)-vectrex.html: $(PACKAGE)-vectrex.markdown
	$(MARKDOWN) $(PACKAGE)-vectrex.markdown > $(PACKAGE)-vectrex.html

CLEANFILES = $(HTML_DOC_FILES)

EXTRA_DIST = \
	$(PACKAGE)-manual.markdown \
	$(PACKAGE)-implementation.markdown \
	$(PACKAGE)-vectrex.markdown \
	toc.pl
