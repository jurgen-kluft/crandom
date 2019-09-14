#ifndef __XRANDOM_MT_RANDOM_H__
#define __XRANDOM_MT_RANDOM_H__
#include "xbase/x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

// Includes
#include "xrandom/x_random.h"

namespace xcore
{
	/**
	 * @group		xrandom
 	 * @desc		Mersenne Twister random number generator
	 * @note		The period is 2^19937-1, and 623-dimensional equi-distribution property is assured.
	 *			Note that this means, by default, that there is negligible serial correlation between 
	 *			successive values in the output sequence. 
	 */
	class xmersenne : public xrandom
	{
	private:
		xrnd::xmt			m_rnd;

	public:
							xrndmt() {}
		virtual void		reset(s32 inSeed = 0) { m_rnd.reset(seed); }
		virtual u32			generate() { return m_rnd.generate(); }
		virtual void		release() {}
	};
}

#endif	///< __XRANDOM_MT_RANDOM_H__