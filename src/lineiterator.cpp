#include "lineiterator.h"

LineIterator::LineIterator(FILE* ifh=NULL)
{
    //ctor
}

LineIterator::~LineIterator()
{
    //dtor
}

LineIterator::next()
{
	fgets(buf, MAX_BUF_SZ, fh);

    // strip newline
    char *nlptr = strchr(buf, '\n');
    if (nlptr) *nlptr = '\0';

}
