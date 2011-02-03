/*
 *
 * String Tokenization
 *
 * @author Adam Ever-Hadani <adamhadani@videosurf.com>
 *
 */
#ifndef STRINGTOKENIZER_H
#define STRINGTOKENIZER_H

#include "types.h"

namespace FLaM {

class StringTokenizer
{
    public:
        StringTokenizer(const flmchar_t* delim=" ", const flmchar_t* s=NULL);
        virtual ~StringTokenizer();

        // Set the string to tokenize. This function allows for object
        // reuse of the StringTokenizer instance.
        void setString(const flmchar_t* string);

        bool hasNext();
        flmchar_t* next();

    private:
        flmchar_t* string, *delim;
        size_t strLen;
        uint16_t nextPos;
};

}

#endif // STRINGTOKENIZER_H
