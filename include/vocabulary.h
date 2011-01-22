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
        virtual void addKey(const flmchar_t* key) =0;
        virtual void inc(const flmchar_t* key, uint32_t value) =0;

    protected:
        inline flmchar_t* _toKey(const flmchar_t* key) {
            flmchar_t* _key = (flmchar_t *)malloc(flmstrlen(key) + 1);
            flmstrcpy(_key, key);

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
    ~HashVocabulary();

    typedef std::hash_map<const flmchar_t*, uint32_t, hash<const flmchar_t*>, eqstr> HashMap;

    bool hasKey(const flmchar_t* key);
    void addKey(const flmchar_t* key);
    void inc(const flmchar_t* key, uint32_t value);

    inline HashMap::iterator begin() { return _hash.begin(); }
    inline HashMap::iterator end() { return _hash.end(); }

  private:
    HashMap _hash;
};

class TrieVocabulary : public Vocabulary
{
  private:
    Trie<flmchar_t*, uint32_t> _trie;
};

}

#endif // VOCABULARY_H
