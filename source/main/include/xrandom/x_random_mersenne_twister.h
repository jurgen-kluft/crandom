#ifndef __XRANDOM_MT_RANDOM_H__
#define __XRANDOM_MT_RANDOM_H__
#include "xbase/x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

// Includes
#include "xbase/x_allocator.h"
#include "xbase/x_random.h"

namespace xcore
{
	// Forward declares
	class xalloc;

	/**
	 * @group		xrandom
 	 * @desc		Mersenne Twister random number generator
	 * @note		The period is 2^19937-1, and 623-dimensional equi-distribution property is assured.
	 *			Note that this means, by default, that there is negligible serial correlation between 
	 *			successive values in the output sequence. 
	 */
	class xrndmt : public xrandom
	{
	public:
							xrndmt(xalloc* alloc=NULL);

		virtual void		reset(s32 inSeed = 0);
		virtual u32			generate();

		virtual void		release();

		struct state
		{
			u32				mStateData[N];
			u32*			mState;
			u32*			mNextState;
			s32				mLeft;
			xbool			mInitialized;
		};

	private:
		xalloc*			mAllocator;
		state			mState;
	};

}

#endif	///< __XRANDOM_MT_RANDOM_H__