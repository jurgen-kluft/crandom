#ifndef __CRANDOM_RANDOM_SITMO_H__
#define __CRANDOM_RANDOM_SITMO_H__
#include "ccore/c_target.h"
#ifdef USE_PRAGMA_ONCE
#    pragma once
#endif

#include "ccore/c_debug.h"
#include "cbase/c_random.h"
#include "crandom/c_random.h"

namespace ncore
{
    // Sitmo random number generator (https://www.sitmo.com)
    class rndsitmo : public random_t
    {
    private:
        nrnd::sitmo_t m_rnd;

    public:
        rndsitmo() {}

        virtual void reset(s64 seed = 0) final { m_rnd.reset(seed); }
        virtual void generate(u8* outData, u32 numBytes) final { return m_rnd.generate(outData, numBytes); }
        virtual u32  rand32() { return m_rnd.rand32(); }
        virtual u64  rand64() { return m_rnd.rand64(); }
    };

} // namespace ncore

#endif // __CRANDOM_RANDOM_SITMO_H__
