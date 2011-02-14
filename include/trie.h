/*
 *
 * Trie data structure
 *
 * @author Adam Ever-Hadani <adamhadani@videosurf.com>
 *
 */
#ifndef TRIE_H
#define TRIE_H

#include <cstdio>
#include <cstdint>
#ifdef __GNUC__
  #include <ext/hash_map>
  #include <ext/hash_set>
#else
  #include <hash_map>
  #include <hash_set>
#endif

#define TRIE_INDEX_T std::hash_map

namespace std { using namespace __gnu_cxx; }

using std::hash_map;

namespace FLaM {

// Forward declerations
template <typename KeyT, typename ValueT> class TrieIter;

/**
 * Implementation of a Trie
 *
 */
template <typename KeyT, typename ValueT>
class Trie
{
    friend class TrieIter<KeyT, ValueT>;

  public:
    Trie(size_t size=0);
    ~Trie();

    ValueT& value() { return data; }

    ValueT* find(KeyT key) const;
    ValueT* find(const KeyT* keys = 0) const;

    ValueT* insert(KeyT key);
    ValueT* insert(const KeyT* keys = 0);

    ValueT* remove(KeyT key);
    ValueT* remove(KeyT* keys = 0);

    void clear();

    size_t numEntries() const;

  private:
    TRIE_INDEX_T<KeyT, ValueT > children;
    ValueT data;
};

}

//#include "../src/trie.cpp"

#endif // TRIE_H
