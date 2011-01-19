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
    if ( hasKey(key) )
        return;

    _hash[const_cast<flmchar_t *>(key)] = 0;
}

bool HashVocabulary::hasKey(const flmchar_t* key)
{
    if ( _hash.find(const_cast<flmchar_t *>(key)) == _hash.end() )
        return false;

    return true;
}

void HashVocabulary::inc(const flmchar_t* key, uint32_t value)
{
    if ( !hasKey(key) )
        return;

    _hash[const_cast<flmchar_t *>(key)] += value;
}
