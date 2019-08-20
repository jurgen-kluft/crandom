#ifndef __XRANDOM_RANDOM_GOOD_H__
#define __XRANDOM_RANDOM_GOOD_H__
#include "xbase/x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

namespace xcore
{
    class xrndgood
    {
    private:
        struct state
        {
            u8  mArray[256 + sizeof(u32)];
            s32 mIndex;
        };
        state mState;

    public:
        xrndgood();

        void reset(s32 inSeed = 0);
        u32  generate();
    };

} // namespace xcore
#endif
