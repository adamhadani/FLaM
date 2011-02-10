/*
 *
 * Define the language model classes and functionality
 *
 * @author Adam Ever-Hadani <adamhadani@videosurf.com>
 *
 */
#ifndef LANGUAGEMODEL_H
#define LANGUAGEMODEL_H

#include "types.h"
#include "vocabulary.h"

namespace FLaM {

/**
 * Base class for implementing an N-Gram language model.
 * Defines the common interface supported by all implementations.
 *
 */
class LanguageModel
{
    public:
        LanguageModel(size_t n, Vocabulary* vocabulary) : n(n), vocabulary(vocabulary) {}
        virtual ~LanguageModel();

        virtual inline size_t getOrder() const { return n; }

        virtual void save(FILE* outfile) =0;

        //virtual float getCount(const flmwid_t*) const =0;
        //virtual float getProb(const flmwid_t*) const  =0;

    protected:

        // Model order (bigram, trigram..)
        const size_t n;


        // Vocabulary. Holds the term <=> id mappings
        Vocabulary* vocabulary;
};

class DiscountedLanguageModel : public LanguageModel
{
    public:
        DiscountedLanguageModel(size_t, Vocabulary* vocabulary) : LanguageModel(n, vocabulary) {}
        virtual ~DiscountedLanguageModel();

    protected:

        // frequency-of-frequency information. used in discounting.
        unsigned int **freq_of_freq;

        // Sizes of the freq_of_freq arrays
        size_t *fof_sizes;
};

/**
 * Interpolation based language models use weighted
 * combination of different models to create a final probability
 * for events.
 *
 */
class InterpolatedLanguageModel : public DiscountedLanguageModel
{
    public:
        InterpolatedLanguageModel(size_t n, Vocabulary* vocabulary) : DiscountedLanguageModel(n, vocabulary) {}
        ~InterpolatedLanguageModel();
};

/**
 * Backoff-based Language models
 * use lower-order model statistics for
 * computing probabilities of unseen events.
 * They are typically combined with a discounting
 * scheme to allocate part of the probability mass
 * to the unseen events and deciding how to distribute
 * that mass among them different unseen events.
 *
 * We use the popular Katz backoff method.
 *
 */
class BackoffLanguageModel : public DiscountedLanguageModel
{
    public:
        BackoffLanguageModel(size_t n, Vocabulary* vocabulary) : DiscountedLanguageModel(n, vocabulary) {}
        ~BackoffLanguageModel() {}

        virtual void save(FILE* outfile) {}

    protected:

};

}

#endif // LANGUAGEMODEL_H
