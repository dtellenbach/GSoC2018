# Compiler and flags
CC = g++
SRCEXT := cc
CCFLAGS := -std=c++11 -O3
ICCFLAGS := -std=c++11 -fast	# Intel C++ compiler icpc supports additional optimization
DEBUGFLAGS := -Wall -Werror -Wpedantic -std=c++11
LDFLAGS := -lbenchmark

# Directories
BINDIR := bin
INCDIR := include
EXAMPLEDIR := examples
BENCHDIR := benchmark
GBENCHDIR := googlebenchmark
TESTDIR := test
DOXYDIR := doc/doxygen

# Dependencies
DOXYGEN := $(shell command -v doxygen 2> /dev/null)
PDFLATEX := $(shell command -v pdflatex 2> /dev/null)

.PHONY: all example test benchmark googlebenchmark doxygen clean

all: example benchmark googlebenchmark test

example:
ifeq ($(wildcard $(BINDIR)/.),)
	$(shell mkdir $(BINDIR))
endif

ifeq ($(CC),icpc)
	$(foreach src, $(wildcard $(EXAMPLEDIR)/*.$(SRCEXT)), $(CC) -I $(INCDIR) $(ICCFLAGS) $(src) -o $(BINDIR)/$(shell basename $(basename $(src)));)
else
	$(foreach src, $(wildcard $(EXAMPLEDIR)/*.$(SRCEXT)), $(CC) -I $(INCDIR) $(CCFLAGS) $(src) -o $(BINDIR)/$(shell basename $(basename $(src)));)
endif

benchmark:
ifeq ($(wildcard $(BINDIR)/.),)
	$(shell mkdir $(BINDIR))
endif

ifeq ($(CC),icpc)
	$(foreach src, $(wildcard $(BENCHDIR)/*.$(SRCEXT)), $(CC) -I $(INCDIR) $(ICCFLAGS) $(src) -o $(BINDIR)/$(shell basename $(basename $(src)));)
else
	$(foreach src, $(wildcard $(BENCHDIR)/*.$(SRCEXT)), $(CC) -I $(INCDIR) $(CCFLAGS) $(src) -o $(BINDIR)/$(shell basename $(basename $(src)));)
endif

googlebenchmark:
ifeq ($(wildcard $(BINDIR)/.),)
	$(shell mkdir $(BINDIR))
endif

ifeq ($(CC),icpc)
	echo $(foreach src, $(wildcard $(GBENCHDIR)/*.$(SRCEXT)), $(CC) -I $(INCDIR) $(ICCFLAGS) $(LDFLAGS) $(src) -o $(BINDIR)/$(shell basename $(basename $(src)));)
else
	$(foreach src, $(wildcard $(GBENCHDIR)/*.$(SRCEXT)), $(CC) -I $(INCDIR) $(CCFLAGS) $(LDFLAGS) $(src) -o $(BINDIR)/$(shell basename $(basename $(src)));)
endif

test:
ifeq ($(wildcard $(BINDIR)/.),)
	$(shell mkdir $(BINDIR))
endif
	$(foreach src, $(wildcard $(TESTDIR)/*.$(SRCEXT)), $(CC) -I $(INCDIR) $(DEBUGFLAGS) $(src) -o $(BINDIR)/$(shell basename $(basename $(src)));)

html-doc:
ifndef DOXYGEN
	$(error "Could not find doxygen")
endif
	doxygen $(DOXYDIR)/Doxyfile
	ln -sf $(DOXYDIR)/html/index.html SymmetricMatrix.html

pdf-doc:
ifndef pdflatex
	$(error "Could not find pdflatex")
endif
	
clean:
	$(RM) -f $(BINDIR)/*; $(RM) -f SymmetricMatrix.html; $(RM) -rf $(DOXYDIR)/html





