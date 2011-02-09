/*
 *
 * low-level textual/string processing utilities
 *
 * @author Adam Ever-Hadani <adamhadani@videosurf.com>
 *
 */
#include <cstdarg>

#include "utils.h"
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

/**
 * Read in an idngram from file into ngram data structure
 *
 */
int get_ngram(FILE *id_ngram_fp, OUT flmngram_t *ng, bool ascii) {

    int i;

    if (ascii) {
        // Read in ngram ids
        for (i=0; i < ng->n; ++i) {
            if ( fscanf(id_ngram_fp, "%u", &ng->id_array[i]) != 1 ) {
                if (feof(id_ngram_fp)) {
                    // Reached end of file
                    return 0;
                }

                // Error reading
                quit(-1, "Error reading from id_ngram file.\n");
            }
        }

        // read in count
        if ( fscanf(id_ngram_fp, "%d", &ng->count) != 1 ) {
            if (feof(id_ngram_fp)) {
                // Reached end of file
                return 0;
            }

            // Error reading
            quit(-1, "Error reading from id_ngram file.\n");
        }
    }

    // TODO: Implement binary mode if needed

    return 1;
}

/**
 * Display a message and quit
 *
 */
int quit(int rc, const char *msg, ...) {
   va_list args;

   va_start(args, msg);
   vfprintf(stderr, msg, args);
   va_end(args);

   exit(rc);
}
