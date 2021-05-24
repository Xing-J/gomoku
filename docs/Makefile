.POSIX:

.SUFFIXES: .ms .ps .pdf .html

all:
	@echo 'Run make against a groff document'

.ms.ps:
	groff -ms $< > $@

.ms.html:
	groff -ms -Thtml $< > $@

.ps.pdf:
	ps2pdf $<

clean:
	rm -f *.pdf *.ps *.html

.PHONY: all clean
