/**
* @file x_random_quick.h
*
* Core Random number generators
*/

#ifndef __XRANDOM_RANDOM_QUICK_H__
#define __XRANDOM_RANDOM_QUICK_H__
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

	/**
	 * @group		xrandom
	 * @brief		Quick and dirty random generator
	 */
	class xrng_quick : public xrandom
	{
	private:
		///@name Implementation
		u32					mSeed;													///< Random seed
		x_iallocator*		mAllocator;

	public:
		///@name Construction/Destruction
							xrng_quick(x_iallocator* alloc=NULL);

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

#endif	// __XRANDOM_RANDOM_QUICK_H__
