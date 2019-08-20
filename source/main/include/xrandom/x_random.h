#ifndef __XRANDOM_RANDOM_H__
#define __XRANDOM_RANDOM_H__
#include "xbase/x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#include "xrandom/x_random_good.h"

namespace xcore
{
    template <class R> inline u32 randU32(R* rnd, u32 inBits)
    {
        ASSERT(inBits <= 32);
        u32 r = rnd->generate();
        return (r >> (32 - inBits));
    }

    template <class R> inline s32 randS32(R* rnd, u32 inBits)
    {
        ASSERT(inBits <= 31);
        return (randU32(inBits + 1) - (1 << inBits));
    }

    template <class R> inline f32 randF32(R* rnd)
    {
        u32 r          = rnd->generate();
        u32 fake_float = (r >> (32 - 23)) | 0x3f800000;
        return ((*(f32*)&fake_float) - 1.0f);
    }

    template <class R> inline f32 randF32S(R* rnd) { return ((randF32(rnd) - 0.5f) * 2.0f); }

    template <class R> inline xbool randBool(R* rnd) { return (randU32(rnd, 1) == 0); }

    template <class R> void randBuffer(R* rnd, xbuffer& buffer)
    {
        for (u32 i = 0; i < buffer.size(); ++i)
        {
            if ((i & 3) == 0)
                rnd = rnd->generate();

            buffer[i] = (rnd & 0xff);
            rnd       = rnd >> 8;
        }
    } // namespace xcore

    class xrnd
    {
        xrndgood mrnd;

    public:
        void reset(s32 seed = 0) { mrnd.reset(seed); }
        u32  generate() { return mrnd.generate(); }

        inline u32   randU32(u32 inBits) { return randU32<xrndgood>(&mrnd, inBits); }
        inline s32   randS32(u32 inBits) { return randS32<xrndgood>(&mrnd, inBits); }
        inline f32   randF32() { return randF32<xrndgood>(&mrnd, inBits); }
        inline f32   randF32S() { return ((randF32<xrndgood>(&mrnd) - 0.5f) * 2.0f); }
        inline xbool randBool() { return (randU32<xrndgood>(&mrnd, 1) == 0); }
        inline void  randBuffer(xbuffer& buffer) { randBuffer<xrndgood>(&mrnd, buffer); }
    };
    static xrnd rnd;

} // namespace xcore
#endif
