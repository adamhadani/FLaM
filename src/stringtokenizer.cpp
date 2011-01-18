#include <cstdio>
#include <cstdlib>
#include <string>

#include "stringtokenizer.h"

StringTokenizer::StringTokenizer(flmchar_t* delim, flmchar_t* s)
{
    this->delim = (char*)malloc(flmstrlen(delim) + 2);
    flmstrcpy(this->delim, delim);

    if (s)
        setString(s);
}

StringTokenizer::~StringTokenizer()
{
}

flmchar_t* StringTokenizer::next()
{
    if (nextPos >= strLen)
        return NULL;

    int pos = nextPos;
    while (string[pos] != 0) {
        bool found = false;
        for (int i=0; delim[i] != 0; ++i) {
            if (string[pos] == delim[i])
                found = true;
        }

        if (found)
            break;

        pos++;
    }

    if (string[pos] == 0)
        string[pos+1] = 0;
    else
        string[pos] = 0;

    flmchar_t* result = &string[nextPos];
    nextPos = pos+1;
    return result;

}
