/*
 *
 * Trie data structure
 *
 * @author Adam Ever-Hadani <adamhadani@videosurf.com>
 *
 */
#include "trie.h"

using namespace FLaM;

#define INSTANTIATE_TRIE(KeyT,DataT) \
	typedef Trie<KeyT,DataT> TrieType; \
	template class Trie< KeyT,DataT>

template <typename KeyT, typename ValueT>
Trie<KeyT, ValueT>::Trie(size_t size)
{
    // Initialize data segment to zero
    memset(&data, 0, sizeof(data));
}

template <typename KeyT, typename ValueT>
Trie <KeyT, ValueT>::~Trie()
{
    //dtor
}

template <typename KeyT, typename ValueT>
Trie<KeyT, ValueT>* Trie<KeyT, ValueT>::findTrie(KeyT key)
{
    return 0;
}

template <typename KeyT, typename ValueT>
Trie<KeyT, ValueT>* Trie<KeyT, ValueT>::insertTrie(KeyT key)
{
    return 0;
}

template <typename KeyT, typename ValueT>
Trie<KeyT, ValueT>* Trie<KeyT, ValueT>::removeTrie(KeyT key)
{
    return 0;
}
