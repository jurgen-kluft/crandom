#ifndef __CRANDOM_RANDOM_QUICK_H__
#define __CRANDOM_RANDOM_QUICK_H__
#include "cbase/c_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#include "cbase/c_debug.h"
#include "cbase/c_random.h"
#include "crandom/c_random.h"

namespace ncore
{
	class rndquick : public random_t
	{
	private:
		nrnd::quick_t		m_rnd;
	public:
							rndquick() {}

		virtual void		reset(s64 seed = 0) { m_rnd.reset(seed); }
		virtual u32			generate() { return m_rnd.generate(); }

		inline u32			randU32(u32 inBits = 32)
		{
			ASSERT(inBits <= 32);
			u32 r = generate();
			return (r >> (32 - inBits));
		}
		inline s32			randS32( u32 inBits = 31)
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

} // namespace ncore

#endif // __CRANDOM_RANDOM_QUICK_H__