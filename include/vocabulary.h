#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <cstdint>

#include "types.h"

namespace FLaM {

/**
 * Define the basic vocabulary interface.
 * Concrete implementations are typically hash-based
 * or trie-based, and support increment operations for
 * keeping counts.
 */
class Vocabulary
{
    public:
        Vocabulary();
        virtual ~Vocabulary();

        virtual bool has_key(const flmchar_t* key) =0;
        virtual void add_key(const flmchar_t* key) =0;
        virtual void inc(const flmchar_t* key, uint32_t value) =0;

    private:
};

class HashVocabulary : public Vocabulary
{
  private:
    std::hash_map<flmchar_t*, uint32_t> _hash;
};

class TrieVocabulary : public Vocabulary
{
  private:
    Trie<flmchar_t*, uint32_t> _trie;
};

}

#endif // VOCABULARY_H
