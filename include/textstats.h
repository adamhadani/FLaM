#ifndef TEXTSTATS_H
#define TEXTSTATS_H

#include "types.h"

/**
 * Represents multiple statistics
 * and counts pertaining to a particular
 * body of text that was analyzed.
 *
 *
 */
class TextStats
{
    public:
        TextStats();
        virtual ~TextStats();
    protected:
        flmprob_t prob;
        size_t numZeroProb;
};


#endif // TEXTSTATS_H
