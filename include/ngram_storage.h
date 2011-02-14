/*
 *
 * NGram storage implementations
 *
 * @author Adam Ever-Hadani <adamhadani@videosurf.com>
 *
 */
#ifndef NGRAMSTORAGE_H
#define NGRAMSTORAGE_H

#include <cstdint>

#include "types.h"
#include "trie.h"

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
 * Define a trie-based NGram storage representations.
 * this is the most commonly used implementation in most
 * lm toolkits (e.g CMU)
 *
 */
class TrieNGramStorage : public NGramStorage
{
    public:
        TrieNGramStorage();
        virtual ~TrieNGramStorage();

        const flmcount_t getNGramCount(const flmngram_t& ngram) const;
        void addNGram(const flmngram_t& ngram);


        // Terminal node (leaf) type
        struct terminal_t {
            // Word id
            flmwid_t wid;
            // Probability
            flmprob_t prob;
        };

        struct node_t : terminal_t {
            // Back-off weight associated with non-terminal nodes
            float bow;
        };

    protected:
        Trie<flmwid_t, const node_t*> trie;

};


}

#endif // NGRAMSTORAGE_H
