#ifndef __XRANDOM_RANDOM_GOOD_H__
#define __XRANDOM_RANDOM_GOOD_H__
#include "xbase/x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#include "xrandom/x_random.h"

namespace xcore
{
	// Forward declares
	class xalloc;

	class xrndgood : public xrandom
	{
	private:
		xrnd::xgood			m_rnd;

	public:
							xrndgood() {}

		virtual void		reset(s32 inSeed = 0) { m_rnd.reset(seed); }
		virtual u32			generate() { return m_rnd.generate(); }
		virtual void		release() {}

		XCORE_CLASS_PLACEMENT_NEW_DELETE
	};
}
#endif
