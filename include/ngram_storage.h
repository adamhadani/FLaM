/*
 *
 * NGram storage implementations
 *
 * @author Adam Ever-Hadani <adamhadani@videosurf.com>
 *
 */
#ifndef NGRAMSTORAGE_H
#define NGRAMSTORAGE_H

#include <set>

#include "types.h"

using std::set;

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

    protected:

        // Represent a single terminal (leaf) node in the trie
        struct terminal_t {
            // Word ID associated with current node.
            flmwid_t wid;

            flmcount_t count;
        };

        // Represent a single non-terminal node in the trie
        struct node_t : terminal_t {
            // index of last element in next level of trie
            // belonging to current node.
            flmwid_t bound;

            // Backoff weight associated with node
            float boweight;
        };

        struct nodecmp {
            bool operator()(const node_t* n1, const node_t* n2) {

            }
        };



};


}

#endif // NGRAMSTORAGE_H
