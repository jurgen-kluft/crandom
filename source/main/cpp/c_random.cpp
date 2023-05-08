#include "cbase/c_target.h"

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
			return (u32)mSeed;
		}
	}
}