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
#include "textstats.h"
#include "ngram_storage.h"

namespace FLaM {

/**
 * Base class for implementing an N-Gram language model.
 * Defines the common interface supported by all implementations.
 *
 */
class LanguageModel
{
    public:
        LanguageModel(size_t n, Vocabulary* vocabulary);
        virtual ~LanguageModel();

        inline size_t getOrder() const { return n; }

        // Get conditional word probabiltities with given history P(w_i | w_i-n+1 .. w_i-1)
        virtual flmprob_t getWordProb(flmwid_t word, const flmwid_t *context) = 0;
        virtual flmprob_t getWordProb(const flmchar_t* word, const flmwid_t *context);


        // Get sentence probability
        virtual flmprob_t sentenceProb(const flmwid_t *sentence, OUT TextStats &stats);
        virtual flmprob_t sentenceProb(const flmchar_t* *sentence, OUT TextStats &stats);

        virtual void save(FILE* outfile) =0;
        virtual void load(FILE* infile)  =0;

        //virtual float getCount(const flmwid_t*) const =0;
        //virtual float getProb(const flmwid_t*) const  =0;

    protected:
        // Model order (bigram, trigram..)
        const size_t n;

        // Vocabulary. Holds the term <=> id mappings
        Vocabulary* vocabulary;

        // NGram storage
        NGramStorage* ngramStorage;
};

/**
 * MLE (naive) language model - computes probabilities
 * from raw counts.
 *
 */
class MLELanguageModel : public LanguageModel
{
    public:
        MLELanguageModel(size_t n, Vocabulary* vocabulary) : LanguageModel(n, vocabulary) {}
        virtual ~MLELanguageModel();
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
        InterpolatedLanguageModel(size_t n, Vocabulary* vocabulary) : LanguageModel(n, vocabulary) {}
        virtual ~InterpolatedLanguageModel();
};

/**
 * Language model which applies discounting to the
 * seen events probabilities in order to save
 * some probability mass to unseen events.
 *
 */
class DiscountedLanguageModel : public LanguageModel
{
    public:
        enum DiscountTypes { tGoodTuring, tLinearDisc, tAbsoluteDisc };

        DiscountedLanguageModel(size_t, Vocabulary* vocabulary) : LanguageModel(n, vocabulary) {}
        virtual ~DiscountedLanguageModel();

         void addNGram(const flmngram_t& ngram, flmcount_t count);

    protected:

        // frequency-of-frequency information. used in discounting.
        unsigned int **freq_of_freq;

        // Sizes of the freq_of_freq arrays
        size_t *fof_sizes;
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
        BackoffLanguageModel(size_t n, Vocabulary* vocabulary);
        virtual ~BackoffLanguageModel();

        flmprob_t getWordProb(flmwid_t word, const flmwid_t *context);

        virtual void save(FILE* outfile) {}
        virtual void load(FILE* infile) {}

    protected:

};

}

#endif // LANGUAGEMODEL_H
