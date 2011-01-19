#ifndef LINEITERATOR_H
#define LINEITERATOR_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "types.h"


class LineIterator
{
    public:
        LineIterator(FILE* ifh=NULL);
        virtual ~LineIterator();

        void setFile(FILE* ifh)
        flmchar_t* next();
        bool hasNext();

    protected:
    private:
};

#endif // LINEITERATOR_H
