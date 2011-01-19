#include "lineiterator.h"

#define MAX_BUF_SZ 512

using namespace FLaM;

LineIterator::LineIterator(FILE* infile)
    : infile(infile)
{
    buf = new flmchar_t[MAX_BUF_SZ];
}

LineIterator::~LineIterator()
{
    delete buf;
}

void LineIterator::setFile(FILE* infile)
{
    infile = infile;
}

flmchar_t* LineIterator::next()
{
	if ( fgets(buf, MAX_BUF_SZ, infile) == NULL )
        return NULL;

    // strip newline
    char *nlptr = strchr(buf, '\n');
    if (nlptr) *nlptr = '\0';

    return buf;
}
