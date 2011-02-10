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
    ngramStorage = new TreeNGramStorage();
}

LanguageModel::~LanguageModel()
{
    if (vocabulary)
        delete vocabulary;

    if (ngramStorage)
        delete ngramStorage;
}

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
