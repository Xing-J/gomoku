.POSIX:

.SUFFIXES: .ms .ps .pdf .html

DOCS=requirements.pdf requirements.html

all: ${DOCS}

${DOCS}:

.ms.ps:
	groff -ms $< > $@

.ms.html:
	groff -ms -Thtml $< > $@

.ps.pdf:
	ps2pdf $<

clean:
	rm -f *.ps *.pdf *.html

.PHONY: all clean
