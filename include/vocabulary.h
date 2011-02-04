/*
 *
 * Vocabulary types
 *
 * @author Adam Ever-Hadani <adamhadani@videosurf.com>
 *
 */
#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <iostream>
#include <cstdint>
#include <cstring>
#include <algorithm>
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

using std::hash;

struct eqstr {
  bool operator()(const flmchar_t* s1, const flmchar_t* s2) const {
    return flmstrcmp(s1,s2)==0;
  }
};

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
        virtual void addKey(flmchar_t* key, uint32_t value=1) =0;
        virtual void inc(flmchar_t* key, uint32_t value) =0;

    protected:
        inline flmchar_t* _toKey(flmchar_t* key, bool inplace=true) {
            flmchar_t*  _key = NULL;

            if (!inplace) {
                _key = (flmchar_t *)malloc(flmstrlen(key) + 1);
                flmstrcpy(_key, key);
            } else {
                _key = key;
            }

            // Lower case
            for (flmchar_t* c=_key; *c != '\x0'; ++c) {
                *c = tolower(*c);
            }

            return _key;
        }

};

class HashVocabulary : public Vocabulary
{
  public:
    static const size_t PREALLOC_HASH_SZ = 1000000;

    // Internal hash table representation for the symbol -> id mapping
    typedef std::hash_map<const flmchar_t*, uint32_t, hash<const flmchar_t*>, eqstr> SymbolMap;

    //HashVocabulary() : _hash(HashVocabulary::PREALLOC_HASH_SZ) {}
    ~HashVocabulary();


    bool hasKey(const flmchar_t* key);
    void addKey(flmchar_t* key, uint32_t value=1);
    inline void inc(flmchar_t* key, uint32_t value) {
        flmchar_t* _key = _toKey(key);
        _hash[_key] += value;
    }

    inline SymbolMap::iterator begin() { return _hash.begin(); }
    inline SymbolMap::iterator end() { return _hash.end(); }

  private:
    SymbolMap _hash;
};

class TrieVocabulary : public Vocabulary
{
  private:
    Trie<flmchar_t*, uint32_t> _trie;
};

}

#endif // VOCABULARY_H
