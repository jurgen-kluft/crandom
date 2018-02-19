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
#include "xrandom/x_rndgen.h"

namespace xcore
{
	// Forward declares
	class x_iallocator;

	/**
	 * @group		xrandom
	 * @brief		Quick and dirty random generator
	 */
	class xrng_quick : public xrndgen
	{
	private:
		///@name Implementation
		u32					mSeed;													///< Random seed
		x_iallocator*		mAllocator;

	public:
		///@name Construction/Destruction
							xrng_quick(x_iallocator* alloc=NULL);

		///@name Random functions
		virtual void		reset(s32 inSeed = 0);									///< Init with random seed
		
		virtual u32			randU32(u32 inBits = 32);
		virtual s32			randS32(u32 inBits = 31);
		virtual f32			randF32();
		virtual f32			randF32S();
		virtual xbool		randBool();
		virtual void		randBuffer(xbuffer& buffer);

		virtual void		release();

		XCORE_CLASS_PLACEMENT_NEW_DELETE
	};

}

#endif	// __XRANDOM_RANDOM_QUICK_H__
