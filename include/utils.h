/*
 *
 * low-level textual/string processing utilities
 *
 * @author Adam Ever-Hadani <adamhadani@videosurf.com>
 *
 */
#ifndef TEXT_UTILS_H_INCLUDED
#define TEXT_UTILS_H_INCLUDED

#include <cstdarg>

#include "types.h"

flmchar_t* lower_case(flmchar_t* key, bool in_place=false);

int get_ngram(FILE* ngram_fp, flmngram_t *ngram, bool ascii=true);

int quit(int rc, const char *msg, ...);

#endif // TEXT_UTILS_H_INCLUDED
