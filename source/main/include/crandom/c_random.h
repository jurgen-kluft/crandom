#ifndef __CRANDOM_RANDOM_API_H__
#define __CRANDOM_RANDOM_API_H__
#include "ccore/c_target.h"
#ifdef USE_PRAGMA_ONCE
#    pragma once
#endif

#include "ccore/c_debug.h"

namespace ncore
{
    namespace nrnd
    {
        struct good_t
        {
            u8  mArray[256 + sizeof(u32)];
            s32 mIndex;

            good_t();
            void reset(s64 seed = 0);
            void generate(u8* outData, u32 numBytes);
            u32  rand32();
            u64  rand64();
        };
        extern good_t good;

        struct mt_t
        {
            enum
            {
                N = 624
            };
            u32  mStateData[N];
            s32  mIndex;

            mt_t();
            void reset(s64 seed = 0);
            void generate(u8* outData, u32 numBytes);
            u32  rand32();
            u64  rand64();
        };
        extern mt_t mersenne;

        struct quick_t
        {
            s64 mS0;
            s64 mS1;

            quick_t();
            void reset(s64 seed = 0);
            void generate(u8* outData, u32 numBytes);
            u32  rand32();
            u64  rand64();
        };
        extern quick_t quick;

        struct sitmo_t
        {
            u64 _k[4];      // key
            u64 _s[4];      // state (counter)
            u64 _o[4];      // cipher output    4 * 64 bit = 256 bit output
            u16 _o_counter; // output chunk counter, the 256 random bits in _o are returned in eight 32 bit chunks

            sitmo_t();
            void reset(s64 seed = 0);
            void generate(u8* outData, u32 numBytes);
            u32  rand32();
            u64  rand64();
        };
        extern sitmo_t sitmo;

    }; // namespace nrnd

} // namespace ncore
#endif
