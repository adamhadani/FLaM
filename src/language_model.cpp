/*
 *
 * Define the language model classes and functionality
 *
 * @author Adam Ever-Hadani <adamhadani@videosurf.com>
 *
 */
#include "language_model.h"

using namespace FLaM;


LanguageModel::LanguageModel(size_t n, Vocabulary* vocabulary) :
    n(n), vocabulary(vocabulary), ngramStorage(NULL)
{
    // TODO: Move to constructor arg (IoC) or
    // parameterize as template argument
    ngramStorage = new TrieNGramStorage();
}

LanguageModel::~LanguageModel()
{
    if (vocabulary)
        delete vocabulary;

    if (ngramStorage)
        delete ngramStorage;
}

flmprob_t LanguageModel::getWordProb(const flmchar_t* word, const flmwid_t *context)
{
    return 0.0f;
}

flmprob_t LanguageModel::sentenceProb(const flmwid_t *sentence, OUT TextStats &stats)
{
    return 0.0f;
}

flmprob_t LanguageModel::sentenceProb(const flmchar_t* *sentence, OUT TextStats &stats)
{
    return 0.0f;
}

///////////////////////////////////////////////////////////////////////////////

DiscountedLanguageModel::~DiscountedLanguageModel()
{
    // Free up resources used

    if ( this->freq_of_freq ) {

    }
}

/**
 * Add an (id) ngram with associated count to model.
 *
 */
void DiscountedLanguageModel::addNGram(const flmngram_t& ngram, flmcount_t count) {

}

///////////////////////////////////////////////////////////////////////////////

BackoffLanguageModel::BackoffLanguageModel(size_t n, Vocabulary* vocabulary) :
    DiscountedLanguageModel(n, vocabulary)
{

}

BackoffLanguageModel::~BackoffLanguageModel()
{

}

flmprob_t BackoffLanguageModel::getWordProb(flmwid_t word, const flmwid_t *context)
{
    return 0.0f;
}
