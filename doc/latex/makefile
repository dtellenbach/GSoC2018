# Makefile for producing the PDF documentation of the project using pdflatex

SRCFILE := Project.tex
PDFLATEX := $(shell command -v pdflatex 2> /dev/null)

.PHONY: all

all:
ifndef PDFLATEX
	$(error "Could not find pdflatex")
endif
	pdflatex $(SRCFILE)

	