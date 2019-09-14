#ifndef __XRANDOM_RANDOM_QUICK_H__
#define __XRANDOM_RANDOM_QUICK_H__
#include "xbase/x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#include "xbase/x_allocator.h"
#include "xrandom/x_random.h"

namespace xcore
{
	class xrndquick : public xrandom
	{
	private:
		xrnd::xquick		m_rnd;
	public:
							xrndquick() {}

		virtual void		reset(s32 inSeed = 0) { m_rnd.reset(seed); }
		virtual u32			generate() { return m_rnd.generate(); }
		virtual void		release() {}

		XCORE_CLASS_PLACEMENT_NEW_DELETE
	};

}

#endif	// __XRANDOM_RANDOM_QUICK_H__
