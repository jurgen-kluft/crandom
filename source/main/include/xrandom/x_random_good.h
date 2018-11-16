#ifndef __XRANDOM_RANDOM_GOOD_H__
#define __XRANDOM_RANDOM_GOOD_H__
#include "xbase/x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#include "xbase/x_allocator.h"
#include "xbase/x_random.h"

namespace xcore
{
	// Forward declares
	class xalloc;

	class xrndgood : public xrandom
	{
	public:
		struct state
		{
			u8		mArray[256+sizeof(u32)];
			s32		mIndex;
		};

	private:
		xalloc*				mAllocator;
		state				mState;

	public:
							xrndgood(xalloc* alloc=NULL);

		///@name Random functions
		virtual void		reset(s32 inSeed = 0);									///< Init with random seed
		virtual u32			generate();

		virtual void		release();

		XCORE_CLASS_PLACEMENT_NEW_DELETE
	};


}
#endif
