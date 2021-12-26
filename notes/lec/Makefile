MARPARGS=--theme default -katex
EMACSARGS=--batch  -l export.el
LATEXMKARGS= -xelatex -shell-escape -outdir=.
marp-install:
	npm install --save @marp-team/marp-cli@latest

lec-%-slides.org: lec-%.org
	../scripts/make-slides $< $@

lec-%-notes.org: lec-%.org
	../scripts/make-notes $< $@

lec-%-notes.tex: lec-%-notes.org
	emacs $< $(EMACSARGS) -f org-latex-export-to-latex

lec-%-notes.pdf: lec-%-notes.tex
	latexmk $(LATEXMKARGS) $<

lec-%-notes.html: lec-%-notes.org
	emacs $< $(EMACSARGS) -f org-html-export-to-html

lec-%-slides.md: lec-%-slides.org
	emacs $< $(EMACSARGS) -f org-md-export-to-markdown

lec-%-slides.html: lec-%-slides.md
	../scripts/make-slides $< $@
	npx marp --html $(MARPARGS) --allow-local-files $< -o $@

lec-%-slides.html lec-%-slides.pdf: lec-%-slides.md
	npx marp --html $(MARPARGS) --allow-local-files $< -o $@

# collect stuff
lec-en-notes.org: lec-en.org $(wildcard lec-*-en.org)
	emacs $< $(EMACSARGS) -f org-org-export-to-org
	../scripts/make-notes lec-en.org.org $@

lec-en-notes.html: lec-en-notes.org
	emacs $< $(EMACSARGS) -f org-html-export-to-html

lec-en-notes.tex: lec-en-notes.org
	emacs $< $(EMACSARGS) -f org-latex-export-to-latex $<

lec-en-notes.pdf: lec-en-notes.tex
	latexmk $(LATEXMKARGS) $<

all: $(patsubst lec-%-en.org,lec-%-en-slides.pdf,$(wildcard lec-*-en.org)) $(patsubst lec-%-en.org,lec-%-en-notes.pdf,$(wildcard lec-*-en.org)) lec-en-notes.pdf lec-en-notes.html $(patsubst lec-%-en.org,lec-%-en-notes.html,$(wildcard lec-*-en.org))

clean:
	rm  *-notes.* *-slides.*

watch: 
	while true ; do make all ; sleep 1; done

.PHONY: marp-install clean all watch
