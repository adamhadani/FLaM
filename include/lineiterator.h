#ifndef LINEITERATOR_H
#define LINEITERATOR_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "types.h"


class LineIterator
{
    public:
        explicit LineIterator(FILE* infile);
        virtual ~LineIterator();

        void setFile(FILE* infile);
        flmchar_t* next();
        bool hasNext();

    private:
        FILE* infile;
        flmchar_t* buf;
};

#endif // LINEITERATOR_H
