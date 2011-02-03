/*
 *
 * String Tokenization
 *
 * @author Adam Ever-Hadani <adamhadani@videosurf.com>
 *
 */
#include "stringtokenizer.h"

using namespace FLaM;

StringTokenizer::StringTokenizer(const flmchar_t* delim, const flmchar_t* s)
{
    this->delim = (char*)malloc(flmstrlen(delim) + 2);
    flmstrcpy(this->delim, delim);

    if (s)
        setString(s);
}

StringTokenizer::~StringTokenizer()
{
    if (delim)
        free(delim);
    if (string)
        free(string);
}

void StringTokenizer::setString(const flmchar_t* string)
{
    this->string = (char*)malloc(flmstrlen(string) + 2);
    flmstrcpy(this->string, string);

    nextPos = 0;
    strLen = flmstrlen(string);
}

flmchar_t* StringTokenizer::next()
{
    if (nextPos >= strLen)
        return NULL;

    int pos = nextPos;
    while (string[pos] != 0) {
        bool found = false;
        for (int i=0; delim[i] != 0; ++i) {
            if (string[pos] == delim[i]) {
                // TODO: Generalize to 'squeeze' all delimiters not just whitespaces if needed
                if (pos>nextPos && string[pos-1] != ' ') {
                    found = true;
                } else {
                    nextPos++;
                }
                break;
            }
        }

        if (found)
            break;

        pos++;
    }

    string[pos] = 0;

    if (nextPos == strLen)
        return NULL;

    flmchar_t* result = &string[nextPos];
    nextPos = pos+1;
    return result;
}

bool StringTokenizer::hasNext()
{
    if (string[nextPos] == 0)
        return false;

    return true;
}

