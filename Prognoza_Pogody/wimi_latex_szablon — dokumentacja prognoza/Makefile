###############################################################################
# Plik Makefile dla szablonu pracy magisterskiej/inżynierskiej
#
# Tomasz Olas
###############################################################################

DOC = mgr


all: build


build:
	pdflatex $(DOC).tex
	bibtex $(DOC)
	pdflatex $(DOC).tex


print:
	lpr $(DOC).ps


show:
	acroread $(DOC).pdf


clean:
	rm -rf $(DOC).aux
	rm -rf $(DOC).dvi
	rm -rf $(DOC).log
	rm -rf $(DOC).toc


realclean: clean
	rm -rf $(DOC).pdf
