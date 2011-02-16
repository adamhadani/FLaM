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

    inline ValueT* find(KeyT key) {
        Trie<KeyT, ValueT>* trie = (Trie<KeyT, ValueT> *)(findTrie(key));
        return trie? &trie->data : 0;
    }
    //ValueT* find(const KeyT* keys = 0) const;

    inline ValueT* insert(KeyT key) {
        return &(insertTrie(key)->data);
    }
    //ValueT* insert(const KeyT* keys = 0);

    inline ValueT* remove(KeyT key) {
        Trie<KeyT, ValueT>* trie = removeTrie(key);
        return trie ? &trie->data : 0;
    }
    //ValueT* remove(KeyT* keys = 0);

    Trie<KeyT, ValueT>* findTrie(KeyT key);
    Trie<KeyT, ValueT>* insertTrie(KeyT key);
    Trie<KeyT, ValueT>* removeTrie(KeyT key);


    inline void clear() { children.clear(); }

    size_t numEntries() const { return children.size(); }

  private:
    TRIE_INDEX_T<KeyT, ValueT > children;
    ValueT data;
};

}


#endif // TRIE_H
