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
#include "xrandom/x_rndgen.h"

namespace xcore
{
	// Forward declares
	class xalloc;

	/**
	 * @group		xrandom
	 * @brief		Sitmo random number generator (https://www.sitmo.com)
	 */
	class xrndsitmo : public xrandom
	{
	public:
		struct state
		{
			u64 _k[4];			// key
			u64 _s[4];			// state (counter)
			u64 _o[4];			// cipher output    4 * 64 bit = 256 bit output
			u16 _o_counter;		// output chunk counter, the 256 random bits in _o are returned in eight 32 bit chunks
		};

	private:
		state		mState;
		xalloc*		mAllocator;

	public:
		///@name Construction/Destruction
							xrndsitmo(x_iallocator* alloc=NULL);

		///@name Random functions
		virtual void		reset(s32 inSeed = 0);									///< Init with random seed
		virtual u32			generate();

		virtual void		release();

		XCORE_CLASS_PLACEMENT_NEW_DELETE
	};

}

#endif	// __XRANDOM_RANDOM_SITMO_H__
