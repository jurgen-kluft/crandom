#include "ccore/c_target.h"
#include "ccore/c_debug.h"
#include "crandom/c_random.h"

namespace ncore
{
    namespace nmersenne
    {
        enum EPeriodParameters
        {
            N                = 624,        // State vector length
            M                = 397,        // State vector M
            MATRIX_A         = 0x9908b0df, // Constant vector a
            UMASK            = 0x80000000, // Most significant w-r bits
            LMASK            = 0x7fffffff, // Least significant r bits
            TEMPERING_MASK_B = 0x9d2c5680,
            TEMPERING_MASK_C = 0xefc60000,
        };

        void state_seed(nrnd::mt_t& state, s64 inSeed)
        {
            state.mStateData[0] = (u32)inSeed & (u32)0xffffffff;
            for (state.mIndex = 1; state.mIndex < N; state.mIndex++)
            {
                state.mStateData[state.mIndex] = ((u32)1812433253 * (state.mStateData[state.mIndex - 1] ^ (state.mStateData[state.mIndex - 1] >> 30)) + state.mIndex);
                state.mStateData[state.mIndex] &= (u32)0xffffffff;
            }
        }

        void state_generate(nrnd::mt_t& state, u8* outData, u32 numBytes)
        {
            u32 i = 0;
            while (i < numBytes)
            {
                u32 y;
                if (state.mIndex >= N || state.mIndex < 0)
                {
                    /* generate N words at a time */
                    s32 kk;
                    if (state.mIndex >= N + 1 || state.mIndex < 0)
                    {
                        state_seed(state, 4357);
                    }
                    for (kk = 0; kk < N - M; kk++)
                    {
                        y                    = (state.mStateData[kk] & UMASK) | (state.mStateData[kk + 1] & LMASK);
                        state.mStateData[kk] = state.mStateData[kk + M] ^ (y >> 1) ^ ((y & 0x1) ? MATRIX_A : 0x0);
                    }
                    for (; kk < N - 1; kk++)
                    {
                        y                    = (state.mStateData[kk] & UMASK) | (state.mStateData[kk + 1] & LMASK);
                        state.mStateData[kk] = state.mStateData[kk + (M - N)] ^ (y >> 1) ^ ((y & 0x1) ? MATRIX_A : 0x0);
                    }
                    y                       = (state.mStateData[N - 1] & UMASK) | (state.mStateData[0] & LMASK);
                    state.mStateData[N - 1] = state.mStateData[M - 1] ^ (y >> 1) ^ ((y & 0x1) ? MATRIX_A : 0x0);
                    state.mIndex            = 0;
                }
                y = state.mStateData[state.mIndex++];
                y ^= (y >> 11);
                y ^= (y << 7) & TEMPERING_MASK_B;
                y ^= (y << 15) & TEMPERING_MASK_C;
                y ^= (y >> 18);

                u32       j  = 0;
                u8 const* rp = (u8*)&y;
                while (j < 4 && i < numBytes)
                {
                    outData[i++] = rp[j++];
                }
            }
        }
    } // namespace nmersenne

    nrnd::mt_t::mt_t()
        : mIndex(-1)
    {
        const s64 seed = 5489;
        nmersenne::state_seed(*this, seed);
    }

    void nrnd::mt_t::reset(s64 seed) { nmersenne::state_seed(*this, seed); }

    void nrnd::mt_t::generate(u8* outData, u32 numBytes) { return nmersenne::state_generate(*this, outData, numBytes); }

    u32 nrnd::mt_t::rand32()
    {
        u32 r;
        nmersenne::state_generate(*this, (u8*)&r, sizeof(r));
        return r;
    }

    u64 nrnd::mt_t::rand64()
    {
        u64 r;
        nmersenne::state_generate(*this, (u8*)&r, sizeof(r));
        return r;
    }

} // namespace ncore
