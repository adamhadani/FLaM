#
# FLaM Makefile
#
SRCDIR=src
SRCS=$(SRCDIR)/flamapp.cpp

EXECUTABLES=flamapp

INCDIR=-I./include
LIBS=-lcxxtools

CC=gcc
CFLAGS=-Wno-deprecated -Wall -O3
OBJS=$(SRCS:.cpp=.o)

.SUFFIXES: .cpp .o
.PHONY: clean

all: flamapp

$(EXECUTABLES): $(OBJS)
	$(CC) $(CFLAGS) $(INCDIR) -o $@ $(subst src,.,$(OBJS)) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCDIR) -c $<

clean:
	rm -rf *.o $(EXECUTABLES)



