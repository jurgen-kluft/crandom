// xmtrandom.h - Mersenne Twister random number generator - 
#ifndef __XRANDOM_MT_RANDOM_H__
#define __XRANDOM_MT_RANDOM_H__
#include "xbase\x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

// Includes
#include "xbase\x_types.h"

namespace xcore
{
	/**
	@group		xrandom
	@desc		Mersenne Twister random number generator
	@note		The period is 2^19937-1, and 623-dimensional equi-distribution property is assured.
				Note that this means, by default, that there is negligible serial correlation between 
				successive values in the output sequence. 
	**/
	class xmtrandom
	{
		enum EPeriodParameters
		{
			N			= 624,
			M			= 397,
			MATRIX_A	= 0x9908b0df,												// Constant vector a
			UMASK		= 0x80000000,												// Most significant w-r bits
			LMASK		= 0x7fffffff												// Least significant r bits
		};

		inline u32			MixBits(u32 u, u32 v)									{ return (u & UMASK) | (v & LMASK); }
		inline u32			Twist(u32 u, u32 v)										{ return (MixBits(u,v) >> 1) ^ ((v&1) ? MATRIX_A : 0); }

		inline f32			ToFloat(u32 inUInt)										{ u32 fakeFloat = (inUInt>>(32-23)) | 0x3f800000; return ((*(f32 *)&fakeFloat)-1.0f); }

	public:
							xmtrandom();

		void				Seed(u32 inSeed = 19650218);
		void				Seed(u32 const* inSeed, s32 inLength);

		void				Release();												///< Reset to initial state

		u32					Rand(s32 inBits = 32);
		s32					RandSign(s32 inBits = 31);
		f32					RandF()													{ return (ToFloat(Rand())); }		///< Return f32 in range [0.0 ... 1.0]
		f32					RandFSign()												{ return ((RandF()-0.5f)*2.0f); }	///< Return f32 in range [-1.0 ... 1.0]
		xbool				RandBool()												{ return (Rand(1)==0); }			///< Return true or false

	private:
		u32					Twiddle(u32, u32);
		void				GenerateNewState();


		u32*				mState;
		u32*				mNextState;
		s32					mLeft;
		xbool				mInitialized;
	};


}
#endif	///< __XRANDOM_MT_RANDOM_H__