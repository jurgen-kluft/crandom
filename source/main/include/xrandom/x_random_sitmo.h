#ifndef __XRANDOM_RANDOM_SITMO_H__
#define __XRANDOM_RANDOM_SITMO_H__
#include "xbase/x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

namespace xcore
{
    /**
     * @group		xrandom
     * @brief		Sitmo random number generator (https://www.sitmo.com)
     */
    class xrndsitmo
    {
    private:
        struct state
        {
            u64 _k[4];      // key
            u64 _s[4];      // state (counter)
            u64 _o[4];      // cipher output    4 * 64 bit = 256 bit output
            u16 _o_counter; // output chunk counter, the 256 random bits in _o are returned in eight 32 bit chunks
        };

        state mState;

    public:
        xrndsitmo();

        void reset(s32 inSeed = 0);
        u32  generate();
    };

} // namespace xcore

#endif // __XRANDOM_RANDOM_SITMO_H__
