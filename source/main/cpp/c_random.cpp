#include "cbase/c_target.h"
#include "cbase/c_allocator.h"
#include "cbase/c_buffer.h"

#include "crandom/c_random.h"


namespace ncore
{
	namespace nrnd
	{
		good_t	good;
		mt_t	mersenne;
		quick_t	quick;
		sitmo_t	sitmo;

		quick_t::quick_t() : mSeed(0) {}

		void quick_t::reset(s64 seed) { mSeed = seed; }
		u32 quick_t::generate()
		{
			mSeed = mSeed * 1664525 + 1013904223; 
			return mSeed;
		}

		template <typename R> void randBuffer(R* rnd, buffer_t& buffer)
		{
			u32 r = 0;
			for (u32 i = 0; i < buffer.size(); ++i)
			{
				if ((i & 3) == 0)
				{
					r = rnd->generate();
				}
				else
				{
					r = r >> 8;
				}
				buffer.m_mutable[i] = (r & 0xff);
			}
		}

        void  randBuffer(buffer_t& buffer)
		{
			randBuffer<good_t>(&good, buffer);
		}
	}
}