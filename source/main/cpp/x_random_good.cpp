/**
* @file x_random_good.cpp
*
* Core Random number generators, good
*/

#include "xbase\x_target.h"
#include "xbase\x_memory_std.h"
#include "xbase\x_allocator.h"

#include "xrandom\private\x_random_good.h"

namespace xcore
{

	/**
	 *	Good random
	 */
	xrnd_good::xrnd_good(x_iallocator* alloc) 
		: mIndex(0)
		, mAllocator(alloc)
	{
	}

	void		xrnd_good::release()
	{
		this->~xrnd_good(); 
		if (mAllocator!=NULL) 
		{
			mAllocator->deallocate(this); 
			mAllocator = NULL;
		}
	}

	/// All 256 byte values shuffled
	static u8 sChaos[256]={
		198,126,129,107, 75,251,226,251, 84,246,189,223,124, 28,225,135,  1,191, 49,
		222, 86,114, 15, 71,103,102,135, 89,170,136, 60, 89,234, 86, 19,123,210,133,
		161,216, 60, 84, 85, 47, 55,174,101, 91,218,  2,121,152,204,227, 26,118,142,
		95,217,153,143, 31, 63, 54,238, 67,120, 77, 13,250,190,166,218,228,134,142,
		220, 41,109, 78,255, 86,225,112, 32,251,143,177, 88,  5,144,197,  9,220, 83,
		205,170, 59, 72,153, 82,211, 82,157,  6,159,234,181,194,  6, 19,152, 73,178,
		1, 30,172, 50,136, 49,156, 82, 70,149,113, 54,143, 87,246, 57, 29, 22,250,
		136,116,245,152,124, 23, 92, 65,187,109,113,142, 15,112, 89,199,  1, 27, 47,
		51, 61,145,192, 29,165, 13, 13,171, 51,141,126, 94,143, 62,230,104,116,166,
		58,177,195,147, 17,168,100,199,219,202,224, 96,225,243,191,  9,  0,103,162,
		227, 37,160, 33, 49,135,213, 98,197,168, 79,126, 46,  9,107,148,159,176,109,
		169,158, 90, 11, 70,112,128,182,207, 71, 12,166,165, 42,216,172,251,160,235,
		183,121, 36,114, 35,146, 72,128,197,166,167,133,183,215,140,144,228,171, 99,
		68, 82,102,227,156, 51, 37,249, 94
	};

	//
	// Initialize random table with seed <inSeed>
	//
	void xrnd_good::init(s32 inSeed)
	{
		// Create random table
		for (s32 i=0; i<static_cast<s32>(256+sizeof(u32)); i++)
			mArray[i] = sChaos[(u8)(inSeed+i)];									// Create semi-random table

		mIndex = (u8)inSeed;														// Start index
	}

}
