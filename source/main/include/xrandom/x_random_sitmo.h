/**
* @file x_random_sitmo.h
*
* Core Random number generators
*/

#ifndef __XRANDOM_RANDOM_SITMO_H__
#define __XRANDOM_RANDOM_SITMO_H__
#include "xbase/x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#include "xbase/x_allocator.h"

#include "xrandom/x_irandom.h"

namespace xcore
{
	// Forward declares
	class x_iallocator;

	class xrng_sitmo_state
	{
	public:
		u64 _k[4];			// key
		u64 _s[4];			// state (counter)
		u64 _o[4];			// cipher output    4 * 64 bit = 256 bit output
		u16 _o_counter;		// output chunk counter, the 256 random bits in _o are returned in eight 32 bit chunks
	};

	/**
	 * @group		xrandom
	 * @brief		Sitmo random number generator (https://www.sitmo.com)
	 */
	class xrng_sitmo : public xrandom
	{
	private:
		///@name Implementation
		u32					mSeed;													///< Random seed
		xrng_sitmo_state	mState;
		x_iallocator*		mAllocator;

	public:
		///@name Construction/Destruction
							xrng_sitmo(x_iallocator* alloc=NULL);

		///@name Random functions
		virtual void		init(s32 inSeed = 0);
		virtual u32			rand(u32 inBits = 32);
		virtual s32			randSign(u32 inBits = 31);
		virtual f32			randF();
		virtual f32			randFSign();
		virtual xbool		randBool();

		virtual void		release();

		XCORE_CLASS_PLACEMENT_NEW_DELETE
	};

}

#endif	// __XRANDOM_RANDOM_SITMO_H__
