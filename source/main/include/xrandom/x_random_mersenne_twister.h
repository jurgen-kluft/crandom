/**
* @file x_random_mersenne_twister.h
*
* Mersenne Twister random number generator
*/

#ifndef __XRANDOM_MT_RANDOM_H__
#define __XRANDOM_MT_RANDOM_H__
#include "xbase\x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

// Includes
#include "xbase\x_allocator.h"

#include "xrandom\x_irandom.h"

namespace xcore
{
	// Forward declares
	class x_iallocator;

	/**
	 * @group		xrandom
 	 * @desc		Mersenne Twister random number generator
	 * @note		The period is 2^19937-1, and 623-dimensional equi-distribution property is assured.
	 *			Note that this means, by default, that there is negligible serial correlation between 
	 *			successive values in the output sequence. 
	 */
	class xrnd_mt : public xirnd
	{
		enum EPeriodParameters
		{
			N			= 624,
			M			= 397,
			MATRIX_A	= 0x9908b0df,												///< Constant vector a
			UMASK		= 0x80000000,												///< Most significant w-r bits
			LMASK		= 0x7fffffff												///< Least significant r bits
		};

		inline u32			mixBits(u32 u, u32 v)									{ return (u & UMASK) | (v & LMASK); }
		inline u32			twist(u32 u, u32 v)										{ return (mixBits(u,v) >> 1) ^ ((v&1) ? MATRIX_A : 0); }

		inline f32			toFloat(u32 inUInt)										{ u32 fakeFloat = (inUInt>>(32-23)) | 0x3f800000; return ((*(f32 *)&fakeFloat)-1.0f); }

	public:
							xrnd_mt(x_iallocator* alloc=NULL);

		void				seed(u32 inSeed = 19650218);
		void				seed(u32 const* inSeed, s32 inLength);

		virtual void		init(s32 inSeed);
		virtual void		release();

		virtual u32			rand(u32 inBits=32);
		virtual s32			randSign(u32 inBits=31);
		virtual f32			randF()													{ return (toFloat(rand())); }		///< Return f32 in range [0.0 ... 1.0]
		virtual f32			randFSign()												{ return ((randF()-0.5f)*2.0f); }	///< Return f32 in range [-1.0 ... 1.0]
		virtual xbool		randBool()												{ return (rand(1)==0); }			///< Return true or false

		XCORE_CLASS_PLACEMENT_NEW_DELETE

	private:
		u32					twiddle(u32, u32);
		void				generateNewState();

		x_iallocator*		mAllocator;
		u32					mStateData[N];
		u32*				mState;
		u32*				mNextState;
		s32					mLeft;
		xbool				mInitialized;
	};


}
#endif	///< __XRANDOM_MT_RANDOM_H__