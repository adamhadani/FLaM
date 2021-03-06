/*
 *
 * Line iterator over input files
 *
 * @author Adam Ever-Hadani <adamhadani@videosurf.com>
 *
 */
#include "lineiterator.h"

#define MAX_BUF_SZ 1024

using namespace FLaM;

LineIterator::LineIterator(FILE* infile)
    : infile(infile), buf(NULL)
{
    buf = new flmchar_t[MAX_BUF_SZ];
}

LineIterator::~LineIterator()
{
    if (buf)
        delete buf;
}

/**
 * Reset internal file stream.
 * Allows re-use of lineiterator objects.
 *
 */
void LineIterator::setFile(FILE* infile)
{
    infile = infile;
}

flmchar_t* LineIterator::next()
{
	if ( fgets(buf, MAX_BUF_SZ, infile) == NULL )
        return NULL;

    // strip newline (UNIX style)
    char *nlptr = strchr(buf, '\n');
    if (nlptr) *nlptr = '\0';

    return buf;
}
