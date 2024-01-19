#ifndef __CRANDOM_RANDOM_GOOD_H__
#define __CRANDOM_RANDOM_GOOD_H__
#include "ccore/c_target.h"
#ifdef USE_PRAGMA_ONCE
#    pragma once
#endif

#include "ccore/c_debug.h"
#include "cbase/c_random.h"
#include "crandom/c_random.h"

namespace ncore
{
    class rndgood : public random_t
    {
    private:
        nrnd::good_t m_rnd;

    public:
        rndgood() {}

        virtual void reset(s64 seed = 0) final { m_rnd.reset(seed); }
        virtual void generate(u8* outData, u32 numBytes) final { return m_rnd.generate(outData, numBytes); }
    };
} // namespace ncore
#endif
