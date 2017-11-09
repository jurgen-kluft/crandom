/**
* @file x_random_mersenne_twister.cpp
*
* Mersenne Twister random number generator
*/

#include "xbase/x_target.h"
#include "xbase/x_allocator.h"
#include "xbase/x_debug.h"

#include "xrandom/x_random_mersenne_twister.h"


namespace xcore
{
	xrng_mt::xrng_mt(x_iallocator* allocator)
		: mAllocator(allocator)
		, mState(NULL)
		, mNextState(NULL)
		, mLeft(0)
		, mInitialized(false)
	{

	}

	void		xrng_mt::seed(u32 inSeed)
	{
		if (mState==NULL)
			mState = mStateData;

		mState[0]= inSeed & (u32)0xffffffff;
		for (s32 j=1; j<N; j++)
		{
			mState[j] = ((u32)1812433253 * (mState[j-1] ^ (mState[j-1] >> 30)) + j); 
			mState[j] &= (u32)0xffffffff;
		}
		mLeft = 1;
		mInitialized = true;
	}



	void	xrng_mt::seed(u32 const* inSeedArray, s32 inLength)
	{
		seed();

		s32 i=1;
		s32 j=0;

		s32 k = (N>inLength) ? N : inLength;

		for (; k; k--)
		{
			mState[i] = (mState[i] ^ ((mState[i-1] ^ (mState[i-1] >> 30)) * (u32)1664525)) + inSeedArray[j] + j;
			mState[i] &= (u32)0xffffffff;

			i++;
			j++;
			if (i>=N)
			{
				mState[0] = mState[N-1];
				i=1;
			}
			if (j>=inLength)
				j=0;
		}
		for (k=N-1; k; k--)
		{
			mState[i] = (mState[i] ^ ((mState[i-1] ^ (mState[i-1] >> 30)) * (u32)1566083941)) - i;
			mState[i] &= (u32)0xffffffff;

			i++;
			if (i>=N)
			{
				mState[0] = mState[N-1];
				i = 1;
			}
		}

		mState[0] = 0x80000000;														// MSB is 1; assuring non-zero initial array
		mLeft = 1;
		mInitialized = true;
	}

	/**
	 * @brief	Releases all memory and resets the generator to it's initial state
	 */
	void	xrng_mt::init(s32 inSeed)
	{
		mState = NULL;
		mNextState = NULL;
		mLeft = 0;
		mInitialized = false;
		seed(inSeed);
	}

	/**
	 * @brief	Releases all memory and resets the generator to it's initial state
	 */
	void	xrng_mt::release()
	{
		mState = NULL;
		mNextState = NULL;
		mLeft = 0;
		mInitialized = false;

		if (mAllocator!=NULL) 
		{
			this->~xrng_mt(); 
			mAllocator->deallocate(this); 
			mAllocator = NULL;
		}
	}

	/**
	 * @brief	Generates a random number on [0,0xffffffff]-interval
	 */
	u32	xrng_mt::rand(u32 inBits)
	{
		ASSERT( inBits <= 32 );

		if (--mLeft == 0)
			generateNewState();

		u32 x = *mNextState++;
		return (x>>(32-inBits));
	}


	/**
	 * @brief	Generates a random number on [0,0x7fffffff]-interval
	 */
	s32		xrng_mt::randSign(u32 inBits)
	{
		if (--mLeft == 0)
			generateNewState();

		u32 x = *mNextState++;
		return (s32)(x>>(32-inBits));
	}


	void	xrng_mt::generateNewState()
	{
		// If Seed() has not been called, a default initial seed is used
		if (!mInitialized)
			seed();

		mLeft = N;
		mNextState = mState;

		u32*	statePtr = mState;

		s32 j;
		for (j=N-M+1; --j; statePtr++) 
			*statePtr = statePtr[M] ^ twist(statePtr[0], statePtr[1]);

		for (j=M; --j; statePtr++) 
			*statePtr = statePtr[M-N] ^ twist(statePtr[0], statePtr[1]);

		*statePtr = statePtr[M-N] ^ twist(statePtr[0], mState[0]);
	}

}
