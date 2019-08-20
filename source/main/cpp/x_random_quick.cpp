#include "xbase/x_target.h"
#include "xrandom/x_random_quick.h"

namespace xcore
{
    static inline u32 gen32(u32& seed)
    {
        u32 current = seed;
        seed        = seed * 1664525 + 1013904223;
        return current;
    }

    xrndquick::xrndquick()
        : mSeed(0xdeadbeef)
    {
    }

    void xrndquick::reset(s32 inSeed) { mSeed = inSeed; }

    u32 xrndquick::generate() { return gen32(mSeed); }

} // namespace xcore
