#ifndef __XRANDOM_RANDOM_API_H__
#define __XRANDOM_RANDOM_API_H__
#include "xbase/x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#include "xbase/x_debug.h"

namespace xcore
{
	class xbuffer;

    namespace xrnd
    {
		struct xrndgood
		{
			u8		mArray[256+sizeof(u32)];
			s32		mIndex;

					xrndgood();
			void	reset(s32 seed = 0);
			u32		generate();
		};
		extern xrndgood	good;

		struct xrndmt
		{
			enum { N = 624 };
			u32   mStateData[N];
			u32*  mState;
			u32*  mNextState;
			s32   mLeft;
			xbool mInitialized;

					xrndmt();
			void	reset(s32 seed = 0);
			u32		generate();
		};
		extern xrndmt		mersenne;

		struct xrndquick
		{
			u32 mSeed;	

					xrndquick();
			void	reset(s32 seed = 0);
			u32		generate();
		};
		extern xrndquick	quick;

		struct xrndsitmo
		{
			u64 _k[4];			// key
			u64 _s[4];			// state (counter)
			u64 _o[4];			// cipher output    4 * 64 bit = 256 bit output
			u16 _o_counter;		// output chunk counter, the 256 random bits in _o are returned in eight 32 bit chunks

					xrndsitmo();
			void	reset(s32 seed = 0);
			u32		generate();
		};
		extern xrndsitmo	sitmo;

		template <typename R> inline u32 randU32(R* rnd, u32 inBits)
		{
			ASSERT(inBits <= 32);
			u32 r = rnd->generate();
			return (r >> (32 - inBits));
		}

		template <typename R> inline s32 randS32(R* rnd, u32 inBits)
		{
			ASSERT(inBits <= 31);
			return (randU32(inBits + 1) - (1 << inBits));
		}

		template <typename R> inline f32 randF32(R* rnd)
		{
			u32 r          = rnd->generate();
			u32 fake_float = (r >> (32 - 23)) | 0x3f800000;
			return ((*(f32*)&fake_float) - 1.0f);
		}

		template <typename R> inline f32 randF32S(R* rnd) { return ((randF32(rnd) - 0.5f) * 2.0f); }
		template <typename R> inline xbool randBool(R* rnd) { return (randU32(rnd, 1) == 0); }

        inline static void  reset(s32 seed = 0) { good.reset(seed); }
        inline static u32   generate() { return good.generate(); }
        inline static u32   randU32(u32 inBits) { return randU32<xrndgood>(&good, inBits); }
        inline static s32   randS32(u32 inBits) { return randS32<xrndgood>(&good, inBits); }
        inline static f32   randF32() { return randF32<xrndgood>(&good); }
        inline static f32   randF32S() { return randF32S<xrndgood>(&good); }
        inline static xbool randBool() { return (randU32<xrndgood>(&good, 1) == 0); }
        inline static void  randBuffer(xbuffer& buffer);
    };


} // namespace xcore
#endif
