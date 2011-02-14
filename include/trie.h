/*
 *
 * Trie data structure
 *
 * @author Adam Ever-Hadani <adamhadani@videosurf.com>
 *
 */
#ifndef TRIE_H
#define TRIE_H

namespace FLaM {

// Forward declerations
template <typename triechar_t, typename trieval_t> class TrieIter;

/**
 * Implementation of a Trie
 *
 */
template <typename KeyT, typename ValueT>
class Trie
{
    friend class TrieIter;

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
    TrieNode<KeyT, ValueT>* root;
};

}

#endif // TRIE_H
