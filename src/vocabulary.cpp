/*
 *
 * Vocabulary implementations
 *
 * @author Adam Ever-Hadani <adamhadani@videosurf.com>
 *
 */
#include <iostream>
#include <sstream>

#include "vocabulary.h"
#include "types.h"
#include "utils.h"
#include "lineiterator.h"

using std::stringstream;

using namespace FLaM;


Vocabulary::Vocabulary()
{
    //ctor
}

Vocabulary::~Vocabulary()
{
    //dtor
}


// HashVocabulary Implementation

/**
 * Factory method to instantiate vocabulary
 * from file (e.g as created by text2vocab)
 *
 */
HashVocabulary* HashVocabulary::fromFile(FILE* vocabfile)
{
    HashVocabulary* vocabulary = new HashVocabulary();

    LineIterator lineiterator(vocabfile);

    flmchar_t* normalized_term = NULL;
    flmchar_t* line = lineiterator.next();

    for (flmwid_t id=1; line != NULL; ++id) {
        normalized_term = lower_case(line);
        vocabulary->addKey(normalized_term, id);

        line = lineiterator.next();
    }

    return vocabulary;
}

HashVocabulary::~HashVocabulary()
{
    // TODO: Free up memory used by symbol map
    //SymbolMap::iterator* it;

}
