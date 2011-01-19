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

void HashVocabulary::addKey(const flmchar_t* key)
{
    flmstring_t _key = _toKey(key);
    _hash[_key] = 1;
}

bool HashVocabulary::hasKey(const flmchar_t* key)
{
    flmstring_t _key = _toKey(key);
    if ( _hash.find(_key) == _hash.end() ) {
        return false;
    }

    return true;
}

void HashVocabulary::inc(const flmchar_t* key, uint32_t value)
{
    flmstring_t _key = _toKey(key);
    _hash[_key] += value;
}
