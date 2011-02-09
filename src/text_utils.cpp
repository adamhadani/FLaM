#include "text_utils.h"
#include "types.h"

/**
 * Return a lower-case copy of input string
 *
 */
flmchar_t* lower_case(flmchar_t* key, bool in_place) {
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
