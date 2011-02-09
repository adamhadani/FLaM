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

        //virtual float getCount(const flmwid_t*) const =0;
        //virtual float getProb(const flmwid_t*) const  =0;

    protected:

        // Model order (bigram, trigram..)
        const size_t n;

        // Vocabulary. This typically holds the term <=> id mappings hash
        Vocabulary* vocabulary;
};

/**
 * Interpolation based language models use weighted
 * combination of different models to create a final probability
 * for events.
 *
 */
class InterpolatedLanguageModel : public LanguageModel
{
    public:
        InterpolatedLanguageModel();
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
class BackoffLanguageModel : public LanguageModel
{
    public:
        BackoffLanguageModel(size_t n, Vocabulary* vocabulary) : LanguageModel(n, vocabulary) {}
        ~BackoffLanguageModel() {}

    protected:

};

}

#endif // LANGUAGEMODEL_H
