#ifndef __CRANDOM_RANDOM_SITMO_H__
#define __CRANDOM_RANDOM_SITMO_H__
#include "ccore/c_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#include "ccore/c_debug.h"
#include "cbase/c_random.h"
#include "crandom/c_random.h"

namespace ncore
{
	// Sitmo random number generator (https://www.sitmo.com)
	class rndsitmo : public random_t
	{
	private:
		nrnd::sitmo_t		m_rnd;
	public:
							rndsitmo() {}

		virtual void reset(s64 seed = 0) final { m_rnd.reset(seed); }
		virtual u32			generate() final { return m_rnd.generate(); }
		
		inline u32			randU32(u32 inBits = 32)
		{
			ASSERT(inBits <= 32);
			u32 r = generate();
			return (r >> (32 - inBits));
		}
		inline s32			randS32(u32 inBits = 31)
		{
			ASSERT(inBits <= 31);
			return (randU32(inBits + 1) - (1 << inBits));
		}
		inline f32			randF32()
		{
			u32 r          = generate();
			u32 fake_float = (r >> (32 - 23)) | 0x3f800000;
			return ((*(f32*)&fake_float) - 1.0f);
		}

		inline f32 randF32S() { return ((randF32() - 0.5f) * 2.0f); }
		inline bool randBool() { return (randU32(1) == 0); }

	};

}

#endif	// __CRANDOM_RANDOM_SITMO_H__
