#
# FLaM Makefile
#
SRCDIR=src
SRCS = \
	$(SRCDIR)/flamapp.cpp \
	$(SRCDIR)/stringtokenizer.cpp \
	$(SRCDIR)/lineiterator.cpp \
	$(SRCDIR)/vocabulary.cpp \
	$(SRCDIR)/discounting.cpp \
	$(SRCDIR)/language_model.cpp \
	$(SRCDIR)/text_utils.cpp \
	$(SRCDIR)/trie.cpp

EXECUTABLES=flamapp

INCDIR=-I./include
LIBS=-lcxxtools

CC=gcc
CFLAGS=-Wno-deprecated -Wall -O3 -std=c++0x
#PROFILEFLAGS=-pg
PROFILEFLAGS=
OBJS=$(SRCS:.cpp=.o)

.SUFFIXES: .cpp .o
.PHONY: clean

all: flamapp

$(EXECUTABLES): $(OBJS)
	$(CC) $(CFLAGS) $(PROFILEFLAGS) $(INCDIR) -o $@ $(subst src,.,$(OBJS)) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(PROFILEFLAGS) $(INCDIR) -c $<

clean:
	rm -rf *.o $(EXECUTABLES)



