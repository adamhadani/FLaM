#
# FLaM Makefile
#
###############################################################################

CC=g++
CFLAGS=-lcxxtools -Wall

SRCDIR=src
BUILDDIR=build

###############################################################################

make: $(SRCDIR)/flamapp.o
	mkdir -p $(BUILDDIR)
	$(CC) -o $(BUILDDIR)/flamapp $(SRCDIR)/flamapp.o $(CFLAGS)

.PHONY: clean

clean:
	rm -rf $(BUILDDIR) $(SRCDIR)/*.o



