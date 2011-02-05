#ifndef LANGUAGEMODEL_H
#define LANGUAGEMODEL_H

#include "types.h"

namespace FLaM {

/**
 * Base class for implementing an N-Gram language model.
 * Defines the common interface supported by all implementations.
 *
 */
class LanguageModel
{
    public:
        LanguageModel();
        virtual ~LanguageModel();

        virtual size_t numUnigrams() const =0;
        virtual size_t getOrder() const    =0;

        virtual float getCount(const flmwid_t*) const =0;
        virtual float getProb(const flmwid_t*) const  =0;

    protected:
        const size_t order;
};

}

#endif // LANGUAGEMODEL_H
