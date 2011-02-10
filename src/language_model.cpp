/*
 *
 * Define the language model classes and functionality
 *
 * @author Adam Ever-Hadani <adamhadani@videosurf.com>
 *
 */
#include "language_model.h"

using namespace FLaM;

LanguageModel::~LanguageModel()
{
    if (vocabulary)
        delete vocabulary;
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
