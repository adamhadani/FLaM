/*
 *
 * Vocabulary implementations
 *
 * @author Adam Ever-Hadani <adamhadani@videosurf.com>
 *
 */
#include "vocabulary.h"

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

HashVocabulary::~HashVocabulary()
{
    // TODO: Free up memory used by symbol map
    //SymbolMap::iterator* it;

}

void HashVocabulary::addKey(const flmchar_t* key, uint32_t value)
{
    if (!key)
        return;

    flmchar_t* _key = _toKey(key);
    _hash[_key] = value;
}

bool HashVocabulary::hasKey(const flmchar_t* key)
{
    flmchar_t* _key_copy = (flmchar_t *)malloc(flmstrlen(key)+1);
    flmstrcpy(_key_copy, key);

    flmchar_t* _key = _toKey(_key_copy);
    if ( _hash.find(_key) == _hash.end() ) {
        return false;
    }

    return true;
}

