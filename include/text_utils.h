#ifndef TEXT_UTILS_H_INCLUDED
#define TEXT_UTILS_H_INCLUDED

#include "types.h"

/**
 * Return a lower-case copy of input string
 *
 */
flmchar_t* lower_case(flmchar_t* key, bool in_place=false) {
    flmchar_t* _key = key;
    if ( !in_place ) {
        _key = (flmchar_t *)malloc(flmstrlen(key) + 1);
        flmstrcpy(_key, key);
    }

    // Lower case
    for (flmchar_t* c=_key; *c != '\x0'; ++c) {
        *c = tolower(*c);
    }

    return _key;
}

#endif // TEXT_UTILS_H_INCLUDED
