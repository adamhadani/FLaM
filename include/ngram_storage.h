/*
 *
 * NGram storage implementations
 *
 * @author Adam Ever-Hadani <adamhadani@videosurf.com>
 *
 */
#ifndef NGRAMSTORAGE_H
#define NGRAMSTORAGE_H

#include "types.h"

namespace FLaM {

/**
 * Base class defining the common interface exposed by
 * all ngram storage implementations.

 */
class NGramStorage
{
    public:
        NGramStorage();
        virtual ~NGramStorage();

        virtual const flmcount_t getNGramCount(const flmngram_t& ngram) const =0;
        virtual void addNGram(const flmngram_t& ngram) =0;

};

/**
 * Define a tree-based NGram storage representations.
 * this is the most commonly used implementation in most
 * lm toolkits (e.g CMU)
 *
 */
class TreeNGramStorage : public NGramStorage
{
    public:
        TreeNGramStorage();
        virtual ~TreeNGramStorage();

        const flmcount_t getNGramCount(const flmngram_t& ngram) const;
        void addNGram(const flmngram_t& ngram);
};

}

#endif // NGRAMSTORAGE_H
