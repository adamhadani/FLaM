/*
 *
 * Define the various discounting models we support
 *
 * @author Adam Ever-Hadani <adamhadani@videosurf.com>
 *
 */
#ifndef DISCOUNTING_H_INCLUDED
#define DISCOUNTING_H_INCLUDED

#include "types.h"

namespace FLaM {

class Discounting {
    public:
        virtual ~Discounting();

        virtual float getDiscProb(uint32_t count, uint32_t total_seen) =0;
};

class GoodTuringDisc : public Discounting {
    public:
        GoodTuringDisc();
        ~GoodTuringDisc();

        float getDiscProb(uint32_t count, uint32_t total_seen);

};

/**
 * In Absolute Discounting, we subtract a constant (delta)
 * from the ngram count when computing probabilities.
 *
 */
class AbsoluteDisc : public Discounting {
    public:
        AbsoluteDisc(float delta);
        ~AbsoluteDisc();

        float getDiscProb(uint32_t count, uint32_t total_seen);

    private:
        // We subtract a constant (Delta) from each count
        float delta;
};

}

#endif // DISCOUNTING_H_INCLUDED
