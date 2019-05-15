
#ifndef __XRANDOM_RANDOM_H__
#define __XRANDOM_RANDOM_H__
#include "xbase/x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#include "xbase/x_allocator.h"
#include "xbase/x_random.h"

namespace xcore
{
    // Forward declares
    class xalloc;

    /*
        class xrndgood : public xrandom
        {
        public:
            struct state
            {
                u8  mArray[256 + sizeof(u32)];
                s32 mIndex;
            };

        private:
            xalloc* mAllocator;
            state   mState;

        public:
            xrndgood(xalloc* alloc = NULL);

            ///@name Random functions
            virtual void reset(s32 inSeed = 0); ///< Init with random seed
            virtual u32  generate();

            virtual void release();

            XCORE_CLASS_PLACEMENT_NEW_DELETE
        };
    */

    class xrnd
    {
    public:
        struct xgood
        {
            struct state
            {
                u8  mArray[256 + sizeof(u32)];
                s32 mIndex;
            };
            state mState;

            void reset(s32 seed = 0);
            u32  generate();
        };
        xgood good;

        struct xquick
        {
            u32  mSeed;
            void reset(s32 seed = 0);
            u32  generate();
        };
        xquick quick;

        struct xsitmo
        {
            struct state
            {
                u64 _k[4];      // key
                u64 _s[4];      // state (counter)
                u64 _o[4];      // cipher output    4 * 64 bit = 256 bit output
                u16 _o_counter; // output chunk counter, the 256 random bits in _o are returned in eight 32 bit chunks
            };
            state mState;

            void reset(s32 inSeed = 0); ///< Init with random seed
            u32  generate();
        };
        xsitmo sitmo;

        struct xmt
        {
            struct state
            {
                u32   mStateData[N];
                u32*  mState;
                u32*  mNextState;
                s32   mLeft;
                xbool mInitialized;
            };
            state mState;

            void reset(s32 inSeed = 0); ///< Init with random seed
            u32  generate();
        };
        xmt mt;
    };
    static xrnd rnd;

} // namespace xcore
#endif
