/*
 *
 * NGram storage implementations
 *
 * @author Adam Ever-Hadani <adamhadani@videosurf.com>
 *
 */
#include <algorithm>

#include "ngram_storage.h"

using namespace FLaM;

// Template instantiations
#include "trie.cpp"
INSTANTIATE_TRIE(flmwid_t, FLaM::TrieNGramStorage::node_t const*);

NGramStorage::NGramStorage()
{
    //ctor
}

NGramStorage::~NGramStorage()
{
    //dtor
}


TrieNGramStorage::TrieNGramStorage()
{
}

TrieNGramStorage::~TrieNGramStorage()
{

}

const flmcount_t TrieNGramStorage::getNGramCount(const flmngram_t& ngram) const
{

    return 0;
}

/**
 * Add an ngram (with associated metadata e.g count) to tree structure.
 * This function assumes no previous state and thus is less efficient
 * for batch insertion. If pre-sorted input ngram data is available,
 * addBatchNGrams should be used instead.
 *
 */
void TrieNGramStorage::addNGram(const flmngram_t& ngram)
{
}
