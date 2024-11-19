#include "ccore/c_target.h"
#include "crandom/c_random.h"

namespace ncore
{
    static inline u64 rotl(const u64 x, int k) { return (x << k) | (x >> (64 - k)); }

    static inline void state_reset(nrnd::quick_t& state, u64 seed)
    {
        state.mS0 = 0x41;
        state.mS1 = 0x29837592 ^ seed;
    }

    static inline void state_generate(nrnd::quick_t& state, u8* outData, u32 numBytes)
    {
        u64 s0 = state.mS0;
        u64 s1 = state.mS1;

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

        state.mS0 = s0;
        state.mS1 = s1;
    }

    nrnd::quick_t::quick_t()
        : mS0(0)
        , mS1(0)
    {
    }

    void nrnd::quick_t::reset(s64 seed) { state_reset(*this, seed); }
    void nrnd::quick_t::generate(u8* outData, u32 numBytes) { state_generate(*this, outData, numBytes); }
    u32  nrnd::quick_t::rand32()
    {
        u32 r;
        generate((u8*)&r, sizeof(r));
        return r;        
    }
    u64  nrnd::quick_t::rand64()
    {
        u64 r;
        generate((u8*)&r, sizeof(r));
        return r;
    }

} // namespace ncore
