/*
 *
 * NGram storage implementations
 *
 * @author Adam Ever-Hadani <adamhadani@videosurf.com>
 *
 */
#include "ngram_storage.h"

using namespace FLaM;

NGramStorage::NGramStorage()
{
    //ctor
}

NGramStorage::~NGramStorage()
{
    //dtor
}


TreeNGramStorage::TreeNGramStorage()
{

}

TreeNGramStorage::~TreeNGramStorage()
{

}

const flmcount_t TreeNGramStorage::getNGramCount(const flmngram_t& ngram) const
{

    return 0;
}

void TreeNGramStorage::addNGram(const flmngram_t& ngram)
{

}
