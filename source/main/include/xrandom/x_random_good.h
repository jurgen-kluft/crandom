/**
* @file x_random_good.h
*
* Core Random number generators
*/

#ifndef __XRANDOM_RANDOM_GOOD_H__
#define __XRANDOM_RANDOM_GOOD_H__
#include "xbase\x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#include "xbase\x_types.h"
#include "xbase\x_allocator.h"

#include "xrandom\x_irandom.h"
#include "xbase\x_endian.h"

namespace xcore
{
	// Forward declares
	class x_iallocator;

	/**
	 *	Random number generators (one very good, one very fast)
	 */

	/**
	 * @group		xrandom
	 * @brief		Good random value generator
	 */
	class xrnd_good : public xirnd
	{
	private:
		///@name Implementation
		u8					mArray[256+sizeof(u32)];								///< Random generator data
		s32					mIndex;													///< Random index
		x_iallocator*		mAllocator;

	public:
		///@name Construction/Destruction
							xrnd_good(x_iallocator* alloc=NULL);

		///@name Random functions
		virtual void		init(s32 inSeed = 0);									///< Init with random seed
		
		virtual u32			rand(u32 inBits = 32);
		virtual s32			randSign(u32 inBits = 31);
		virtual f32			randF();
		virtual f32			randFSign();
		virtual xbool		randBool();

		virtual void		release();

		XCORE_CLASS_PLACEMENT_NEW_DELETE
	};


}
#endif
