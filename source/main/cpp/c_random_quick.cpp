#include "ccore/c_target.h"
#include "crandom/c_random.h"

namespace ncore
{
    static inline uint64_t rotl(const uint64_t x, int k) { return (x << k) | (x >> (64 - k)); }

    static inline u64 state_generate(nrnd::quick_t& state, u8* outData, u32 numBytes)
    {
        u64 s0 = state.mS[0];
        u64 s1 = state.mS[1];

        u32 i = 0;
        while (i < numBytes)
        {
            const u64 r = s0 + s1;

            s1 ^= s0;
            s0 = rotl(s0, 55) ^ s1 ^ (s1 << 14); // a, b
            s1 = rotl(s1, 36);                   // c

            const u8* rp = (const u8*)&r;
            u32       j  = 0;
            while (j < 8 && i < numBytes)
            {
                outData[i++] = rp[j++];
            }
        }

        state.mS[0] = s0;
        state.mS[1] = s1;
    }

    void nrnd::quick_t::reset(s64 seed) { state_reset(*this, seed); }
    void nrnd::quick_t::generate(u8* outData, u32 numBytes) { return state_generate(*this, outData, numBytes); }

} // namespace ncore
