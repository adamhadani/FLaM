#ifndef STRINGTOKENIZER_H
#define STRINGTOKENIZER_H

#include "types.h"

class StringTokenizer
{
    public:
        StringTokenizer(flmchar_t* delim=" ", flmchar_t* s=NULL);
        virtual ~StringTokenizer();

        inline void setString(flmchar_t* string) {
            this->string = (char*)malloc(flmstrlen(string) + 2);
            flmstrcpy(this->string, string);

            nextPos = 0;
            strLen = flmstrlen(string);
        }

        bool hasNext();

        flmchar_t* next();

    private:
        flmchar_t* string, *delim;
        size_t strLen;
        uint16_t nextPos;
};

#endif // STRINGTOKENIZER_H
