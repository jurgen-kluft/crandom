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
        };
        extern good_t good;

        struct mt_t
        {
            enum
            {
                N = 624
            };
            u32  mStateData[N];
            u32* mState;
            u32* mNextState;
            s32  mLeft;
            bool mInitialized;

            mt_t();
            void reset(s64 seed = 0);
            void generate(u8* outData, u32 numBytes);
        };
        extern mt_t mersenne;

        struct quick_t
        {
            s64 mS0;
            s64 mS1;

            quick_t();
            void reset(s64 seed = 0);
            void generate(u8* outData, u32 numBytes);
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
        };
        extern sitmo_t sitmo;

        template <class T> inline bool random_bool(T* inRandom)
        {
            u8 val;
            inRandom->generate(&val, 1);
            return val == 0;
        }

        template <class T> inline u32 random_u32(T* inRandom, u32 inBits = 32)
        {
            ASSERT(inBits <= 32);
            u32 val;
            u8* pval = (u8*)&val;
            inRandom->generate(pval, 4);
            return (val >> (32 - inBits));
        }

        template <class T> inline s32 random_s32(T* inRandom, u32 inBits = 31)
        {
            ASSERT(inBits <= 31);
            return (random_u32(inRandom, inBits + 1) - (1 << inBits));
        }

        template <class T> inline f32 random_f32(T* inRandom)
        {
            u32 r          = random_u32(inRandom);
            u32 fake_float = (r >> (32 - 23)) | 0x3f800000;
            return ((*(f32*)&fake_float) - 1.0f);
        }

        template <class T> inline f32 random_f32S(T* inRandom) { return ((random_f32(inRandom) - 0.5f) * 2.0f); }

    }; // namespace nrnd

} // namespace ncore
#endif
