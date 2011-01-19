#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <cstdint>
#include <map>

#ifdef __GNUC__
  #include <ext/hash_map>
  #include <ext/hash_set>
#else
  #include <hash_map>
  #include <hash_set>
#endif

#include "types.h"
#include "trie.h"

namespace std { using namespace __gnu_cxx; }


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

        virtual bool hasKey(const flmchar_t* key) =0;
        virtual void addKey(const flmchar_t* key) =0;
        virtual void inc(const flmchar_t* key, uint32_t value) =0;

    private:
};

class HashVocabulary : public Vocabulary
{
  public:
    bool hasKey(const flmchar_t* key);
    void addKey(const flmchar_t* key);
    void inc(const flmchar_t* key, uint32_t value);

    inline std::map<flmstring_t, uint32_t>::iterator begin() { return _hash.begin(); }
    inline std::map<flmstring_t, uint32_t>::iterator end() { return _hash.end(); }

  private:
    std::map<flmstring_t, uint32_t> _hash;
};

class TrieVocabulary : public Vocabulary
{
  private:
    Trie<flmchar_t*, uint32_t> _trie;
};

}

#endif // VOCABULARY_H
