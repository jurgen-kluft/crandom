#ifndef __XRANDOM_RANDOM_QUICK_H__
#define __XRANDOM_RANDOM_QUICK_H__
#include "xbase/x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

namespace xcore
{
    class xrndquick
    {
    private:
        u32 mSeed;

    public:
        xrndquick();

        void reset(s32 inSeed = 0);
        u32  generate();
    };

} // namespace xcore

#endif // __XRANDOM_RANDOM_QUICK_H__
