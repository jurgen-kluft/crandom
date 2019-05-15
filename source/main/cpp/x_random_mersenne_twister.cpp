#include "xbase/x_target.h"
#include "xbase/x_allocator.h"
#include "xbase/x_debug.h"

#include "xrandom/x_random.h"


namespace xcore
{
	enum EPeriodParameters
	{
		N			= 624,
		M			= 397,
		MATRIX_A	= 0x9908b0df,												///< Constant vector a
		UMASK		= 0x80000000,												///< Most significant w-r bits
		LMASK		= 0x7fffffff												///< Least significant r bits
	};

	inline u32			mixBits(u32 u, u32 v)									{ return (u & UMASK) | (v & LMASK); }
	inline u32			twist(u32 u, u32 v)										{ return (mixBits(u,v) >> 1) ^ ((v&1) ? MATRIX_A : 0); }

	xrnd::xmt::state::state()
		: mState(NULL)
		, mNextState(NULL)
		, mLeft(0)
		, mInitialized(false)
	{}

	void		state_reset(xrnd::xmt::state& state)
	{
		state.mState = NULL;
		state.mNextState = NULL;
		state.mLeft = 0;
		state.mInitialized = false;
	}

	void		state_seed(xrnd::xmt::state& state, u32 inSeed)
	{
		if (state.mState==NULL)
			state.mState = state.mStateData;

		state.mState[0]= inSeed & (u32)0xffffffff;
		for (s32 j=1; j<N; j++)
		{
			state.mState[j] = ((u32)1812433253 * (state.mState[j-1] ^ (state.mState[j-1] >> 30)) + j); 
			state.mState[j] &= (u32)0xffffffff;
		}
		state.mLeft = 1;
		state.mInitialized = true;
	}

	void	state_seed_from_array(xrnd::xmt::state& state, u32 const* inSeedArray, s32 inLength)
	{
		state_seed(state);

		s32 i=1;
		s32 j=0;

		s32 k = (N>inLength) ? N : inLength;

		for (; k; k--)
		{
			state.mState[i] = (state.mState[i] ^ ((state.mState[i-1] ^ (state.mState[i-1] >> 30)) * (u32)1664525)) + inSeedArray[j] + j;
			state.mState[i] &= (u32)0xffffffff;

			i++;
			j++;
			if (i>=N)
			{
				state.mState[0] = state.mState[N-1];
				i=1;
			}
			if (j>=inLength)
				j=0;
		}
		for (k=N-1; k; k--)
		{
			state.mState[i] = (state.mState[i] ^ ((state.mState[i-1] ^ (state.mState[i-1] >> 30)) * (u32)1566083941)) - i;
			state.mState[i] &= (u32)0xffffffff;

			i++;
			if (i>=N)
			{
				state.mState[0] = state.mState[N-1];
				i = 1;
			}
		}

		state.mState[0] = 0x80000000;														// MSB is 1; assuring non-zero initial array
		state.mLeft = 1;
		state.mInitialized = true;
	}

	void	state_generate_new(xrnd::xmt::state& state)
	{
		// If Seed() has not been called, a default initial seed is used
		if (!state.mInitialized)
			state_seed(state);

		state.mLeft = N;
		state.mNextState = state.mState;

		u32* statePtr = state.mState;

		s32 j;
		for (j=N-M+1; --j; statePtr++) 
			*statePtr = statePtr[M] ^ twist(statePtr[0], statePtr[1]);

		for (j=M; --j; statePtr++) 
			*statePtr = statePtr[M-N] ^ twist(statePtr[0], statePtr[1]);

		*statePtr = statePtr[M-N] ^ twist(statePtr[0], state.mState[0]);
	}

	u32			state_generate(xrnd::xmt::state& state)
	{
		if (--state.mLeft == 0)
			state_generate_new(state);
		return *state.mNextState++;
	}


	xrnd::xmt::xmt()
	{
		state_reset(mState);
	}

	void	xrnd::xmt::reset(s32 inSeed)
	{
		state_reset(mState);
		state_seed(mState, inSeed);
	}

	u32	xrnd::xmt::generate()
	{
		return state_generate(mState);
	}

}
