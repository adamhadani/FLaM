#ifndef TRIE_H
#define TRIE_H

namespace FLaM {

template <typename triechar_t, typename trieval_t>
class Trie;

/**
 * Represent a node in a Trie.
 *
 */
template <typename triechar_t, typename trieval_t>
class TrieNode
{
  friend class Trie<triechar_t, trieval_t>;

  public:
    TrieNode();
    virtual ~TrieNode();

    const trieval_t* getValue() const { return value; }

  protected:
    TrieNode* left;
    TrieNode* right;

    triechar_t key;
    trieval_t* value;
};

/**
 * Implementation of a Trie
 *
 */
template <typename triechar_t, typename trieval_t>
class Trie
{
    public:
        Trie();
        virtual ~Trie();

        void add(const triechar_t* key, trieval_t* value);
        bool hasKey(const triechar_t* key);
        trieval_t* get(const triechar_t* key);

    private:
        TrieNode<triechar_t, trieval_t>* root;
};

}

#endif // TRIE_H
