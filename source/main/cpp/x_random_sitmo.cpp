/**
* @file x_random_quick.cpp
*
* Core Random number generators, quick
*/

#include "xbase\x_target.h"
#include "xbase\x_memory_std.h"
#include "xbase\x_allocator.h"

#include "xrandom\x_random_sitmo.h"

namespace xcore
{

	/**
	 *	Sitmo random
	 */
	 // Double mixing function
	#define MIX2(x0,x1,rx,z0,z1,rz) \
	    x0 += x1; \
	    z0 += z1; \
	    x1 = (x1 << rx) | (x1 >> (64-rx)); \
	    z1 = (z1 << rz) | (z1 >> (64-rz)); \
	    x1 ^= x0; \
	    z1 ^= z0; 


	 // Double mixing function with key adition
	#define MIXK(x0,x1,rx,z0,z1,rz,k0,k1,l0,l1) \
	    x1 += k1; \
	    z1 += l1; \
	    x0 += x1+k0; \
	    z0 += z1+l0; \
	    x1 = (x1 << rx) | (x1 >> (64-rx)); \
	    z1 = (z1 << rz) | (z1 >> (64-rz)); \
	    x1 ^= x0; \
	    z1 ^= z0; \

	class xrng_sitmo_engine : xrng_sitmo_state
	{
	public:

		// -------------------------------------------------
		// Constructors
		// -------------------------------------------------

		// req: 26.5.1.4 Random number engine requirements, p.907 table 117, row 1
		// Creates an engine with the same initial state as all other
		// default-constructed engines of type E.
		xrng_sitmo_engine()
		{
			seed();
		}


		// req: 26.5.1.4 Random number engine requirements, p.907 table 117, row 3
		// Creates an engine with initial O(size of state) state determined by s.
		xrng_sitmo_engine(u32 s)
		{
			seed(s);
		}

		// -------------------------------------------------
		// Seeding
		// -------------------------------------------------

		void seed()
		{
			for (unsigned short i = 0; i < 4; ++i)
			{
				_k[i] = 0;
				_s[i] = 0;
			}
			_o_counter = 0;

			_o[0] = 0x09218ebde6c85537;
			_o[1] = 0x55941f5266d86105;
			_o[2] = 0x4bd25e16282434dc;
			_o[3] = 0xee29ec846bd2e40b;
		}

		void seed(u32 s)
		{
			for (unsigned short i = 0; i < 4; ++i)
			{
				_k[i] = 0;
				_s[i] = 0;
			}
			_k[0] = s;
			_o_counter = 0;

			encrypt_counter();
		}


		// Advances e’s state ei to ei+1 = TA(ei) and returns GA(ei).
		u32 gen_u32()
		{
			// can we return a value from the current block?
			if (_o_counter < 8)
			{
				unsigned short _o_index = _o_counter >> 1;
				_o_counter++;
				if (_o_counter & 1)
					return _o[_o_index] & 0xFFFFFFFF;
				else
					return _o[_o_index] >> 32;
			}

			// generate a new block and return the first 32 bits
			inc_counter();
			encrypt_counter();
			_o_counter = 1; // the next call
			return (s32)(_o[0] & 0xFFFFFFFF);   // this call
		}

		s32 gen_s32()
		{
			u32 v = gen_u32();
			return (s32)v;
		}

		static inline f32	uint2float(u32 inUInt)
		{
			u32 fake_float = (inUInt >> (32 - 23)) | 0x3f800000;
			return ((*(f32 *)&fake_float) - 1.0f);
		}

		f32 gen_f32()
		{
			u32 v = gen_u32();
			return uint2float(v);
		}

		// -------------------------------------------------
		// misc
		// -------------------------------------------------

		// Advances e’s state ei to ei+z by any means equivalent to z consecutive calls e().
		void discard(u64 z)
		{
			// check if we stay in the current block
			if (z < 8 - _o_counter)
			{
				_o_counter += static_cast<unsigned short>(z);
				return;
			}

			// we will have to generate a new block...
			z -= (8 - _o_counter);  // discard the remainder of the current blok
			_o_counter = z % 8;     // set the pointer in the correct element in the new block
			z -= _o_counter;        // update z
			z >>= 3;                // the number of buffers is elements/8
			++z;                    // and one more because we crossed the buffer line
			inc_counter(z);
			encrypt_counter();
		}


		// Extra function to set the key
		void set_key(u64 k0 = 0, u64 k1 = 0, u64 k2 = 0, u64 k3 = 0)
		{
			_k[0] = k0; _k[1] = k1; _k[2] = k2; _k[3] = k3;
			encrypt_counter();
		}

		// set the counter
		void set_counter(u64 s0 = 0, u64 s1 = 0, u64 s2 = 0, u64 s3 = 0, unsigned short o_counter = 0)
		{
			_s[0] = s0;
			_s[1] = s1;
			_s[2] = s2;
			_s[3] = s3;
			_o_counter = o_counter % 8;
			encrypt_counter();
		}

	private:
		void encrypt_counter()
		{
			u64 b[4];
			u64 k[5];

			for (unsigned short i = 0; i < 4; ++i) b[i] = _s[i];
			for (unsigned short i = 0; i < 4; ++i) k[i] = _k[i];

			k[4] = 0x1BD11BDAA9FC1A22 ^ k[0] ^ k[1] ^ k[2] ^ k[3];

			MIXK(b[0], b[1], 14, b[2], b[3], 16, k[0], k[1], k[2], k[3]);
			MIX2(b[0], b[3], 52, b[2], b[1], 57);
			MIX2(b[0], b[1], 23, b[2], b[3], 40);
			MIX2(b[0], b[3], 5, b[2], b[1], 37);
			MIXK(b[0], b[1], 25, b[2], b[3], 33, k[1], k[2], k[3], k[4] + 1);
			MIX2(b[0], b[3], 46, b[2], b[1], 12);
			MIX2(b[0], b[1], 58, b[2], b[3], 22);
			MIX2(b[0], b[3], 32, b[2], b[1], 32);

			MIXK(b[0], b[1], 14, b[2], b[3], 16, k[2], k[3], k[4], k[0] + 2);
			MIX2(b[0], b[3], 52, b[2], b[1], 57);
			MIX2(b[0], b[1], 23, b[2], b[3], 40);
			MIX2(b[0], b[3], 5, b[2], b[1], 37);
			MIXK(b[0], b[1], 25, b[2], b[3], 33, k[3], k[4], k[0], k[1] + 3);

			MIX2(b[0], b[3], 46, b[2], b[1], 12);
			MIX2(b[0], b[1], 58, b[2], b[3], 22);
			MIX2(b[0], b[3], 32, b[2], b[1], 32);

			MIXK(b[0], b[1], 14, b[2], b[3], 16, k[4], k[0], k[1], k[2] + 4);
			MIX2(b[0], b[3], 52, b[2], b[1], 57);
			MIX2(b[0], b[1], 23, b[2], b[3], 40);
			MIX2(b[0], b[3], 5, b[2], b[1], 37);

			for (unsigned int i = 0; i < 4; ++i) _o[i] = b[i] + k[i];
			_o[3] += 5;
		}

		void inc_counter()
		{
			++_s[0];
			if (_s[0] != 0) return;

			++_s[1];
			if (_s[1] != 0) return;

			++_s[2];
			if (_s[2] != 0) return;

			++_s[3];
		}

		void inc_counter(u64 z)
		{
			// check if we will overflow the first 64 bit int
			if (z > 0xFFFFFFFFFFFFFFFF - _s[0])
			{
				++_s[1];
				if (_s[1] == 0) 
				{
					++_s[2];
					if (_s[2] == 0) 
					{
						++_s[3];
					}
				}
			}
			_s[0] += z;
		}
	};

	#undef MIXK
	#undef MIX2


	xrng_sitmo::xrng_sitmo(x_iallocator* alloc)
		: mSeed(0xdeadbeef)
		, mAllocator(alloc)
	{
	}

	void		xrng_sitmo::init(s32 inSeed)
	{
		mSeed = inSeed;
		xrng_sitmo_engine* engine = (xrng_sitmo_engine*)&mState;
		engine->seed(mSeed);
	}

	u32			xrng_sitmo::rand(u32 inBits)
	{
		ASSERT(inBits <= 32);
		xrng_sitmo_engine* engine = (xrng_sitmo_engine*)&mState;
		u32 rVal = engine->gen_u32();
		rVal = rVal & (0xFFFFFFFF >> (32 - inBits));
		return rVal;
	}

	s32			xrng_sitmo::randSign(u32 inBits)
	{
		ASSERT(inBits <= 31);
		xrng_sitmo_engine* engine = (xrng_sitmo_engine*)&mState;
		u32 rVal = engine->gen_u32();
		rVal = rVal & (0xFFFFFFFF >> (32 - inBits));
		return (s32)rVal - (s32)(1 << inBits);
	}

	f32			xrng_sitmo::randF()
	{
		xrng_sitmo_engine* engine = (xrng_sitmo_engine*)&mState;
		f32 r = engine->gen_f32();
		return r;
	}

	f32			xrng_sitmo::randFSign()
	{
		return ((randF() - 0.5f)*2.0f);
	}

	bool		xrng_sitmo::randBool()
	{
		return (rand(1) == 0);
	}

	void		xrng_sitmo::release()
	{
		if (mAllocator != NULL)
		{
			this->~xrng_sitmo();
			mAllocator->deallocate(this);
			mAllocator = NULL;
		}
	}

}
