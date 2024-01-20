#ifndef __CRANDOM_MT_RANDOM_H__
#define __CRANDOM_MT_RANDOM_H__
#include "ccore/c_target.h"
#ifdef USE_PRAGMA_ONCE
#    pragma once
#endif

#include "ccore/c_debug.h"
#include "cbase/c_random.h"
#include "crandom/c_random.h"

namespace ncore
{
    /**
     * @group		random_t
     * @desc		Mersenne Twister random number generator
     * @note		The period is 2^19937-1, and 623-dimensional equi-distribution property is assured.
     *			Note that this means, by default, that there is negligible serial correlation between
     *			successive values in the output sequence.
     */
    class rndmersenne : public random_t
    {
    private:
        nrnd::mt_t m_rnd;

    public:
        rndmersenne() {}

        virtual void reset(s64 seed = 0) final { m_rnd.reset(seed); }
        virtual void generate(u8* outData, u32 numBytes) final { m_rnd.generate(outData, numBytes); }

        inline u32 generate_u32() { u32 val; m_rnd.generate((u8*)&val, 4); return val; }
        inline u64 generate_u64() { u64 val; m_rnd.generate((u8*)&val, 8); return val; }
    };
} // namespace ncore

#endif ///< __CRANDOM_MT_RANDOM_H__
