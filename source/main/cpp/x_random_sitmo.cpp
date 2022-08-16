#include "xbase/x_target.h"
#include "xbase/x_buffer.h"

#include "xrandom/x_random_sitmo.h"

namespace ncore
{
    /**
     *	Sitmo random
     */
    // Double mixing function
#define MIX2(x0, x1, rx, z0, z1, rz)     \
    x0 += x1;                            \
    z0 += z1;                            \
    x1 = (x1 << rx) | (x1 >> (64 - rx)); \
    z1 = (z1 << rz) | (z1 >> (64 - rz)); \
    x1 ^= x0;                            \
    z1 ^= z0;

    // Double mixing function with key adition
#define MIXK(x0, x1, rx, z0, z1, rz, k0, k1, l0, l1) \
    x1 += k1;                                        \
    z1 += l1;                                        \
    x0 += x1 + k0;                                   \
    z0 += z1 + l0;                                   \
    x1 = (x1 << rx) | (x1 >> (64 - rx));             \
    z1 = (z1 << rz) | (z1 >> (64 - rz));             \
    x1 ^= x0;                                        \
    z1 ^= z0;

    void encrypt_counter(nrnd::sitmo_t& state)
    {
        u64 b[4];
        u64 k[5];

        for (unsigned short i = 0; i < 4; ++i)
            b[i] = state._s[i];
        for (unsigned short i = 0; i < 4; ++i)
            k[i] = state._k[i];

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

        for (unsigned int i = 0; i < 4; ++i)
            state._o[i] = b[i] + k[i];
        state._o[3] += 5;
    }

    void inc_counter(nrnd::sitmo_t& state)
    {
        ++state._s[0];
        if (state._s[0] != 0)
            return;
        ++state._s[1];
        if (state._s[1] != 0)
            return;
        ++state._s[2];
        if (state._s[2] != 0)
            return;
        ++state._s[3];
    }

    void inc_counter(nrnd::sitmo_t& state, u64 z)
    {
        // check if we will overflow the first 64 bit int
        if (z > 0xFFFFFFFFFFFFFFFF - state._s[0])
        {
            ++state._s[1];
            if (state._s[1] == 0)
            {
                ++state._s[2];
                if (state._s[2] == 0)
                {
                    ++state._s[3];
                }
            }
        }
        state._s[0] += z;
    }

    // -------------------------------------------------
    // Seeding
    // -------------------------------------------------

    void state_seed(nrnd::sitmo_t& state)
    {
        for (unsigned short i = 0; i < 4; ++i)
        {
            state._k[i] = 0;
            state._s[i] = 0;
        }
        state._o_counter = 0;

        state._o[0] = 0x09218ebde6c85537;
        state._o[1] = 0x55941f5266d86105;
        state._o[2] = 0x4bd25e16282434dc;
        state._o[3] = 0xee29ec846bd2e40b;
    }

    void state_seed(nrnd::sitmo_t& state, s64 s)
    {
        for (unsigned short i = 0; i < 4; ++i)
        {
            state._k[i] = 0;
            state._s[i] = 0;
        }
        state._k[0]      = (u64)s;
        state._o_counter = 0;
        encrypt_counter(state);
    }

    // Advances e�s state ei to ei+1 = TA(ei) and returns GA(ei).
    u32 state_generate(nrnd::sitmo_t& state)
    {
        // can we return a value from the current block?
        if (state._o_counter < 8)
        {
            unsigned short _o_index = state._o_counter >> 1;
            state._o_counter++;
            if (state._o_counter & 1)
                return state._o[_o_index] & 0xFFFFFFFF;
            else
                return state._o[_o_index] >> 32;
        }

        // generate a new block and return the first 32 bits
        inc_counter(state);
        encrypt_counter(state);
        state._o_counter = 1;                   // the next call
        return (s32)(state._o[0] & 0xFFFFFFFF); // this call
    }

    // -------------------------------------------------
    // misc
    // -------------------------------------------------

    // Advances e�s state ei to ei+z by any means equivalent to z consecutive calls e().
    void discard(nrnd::sitmo_t& state, u64 z)
    {
        // check if we stay in the current block
        if (z < 8 - state._o_counter)
        {
            state._o_counter += static_cast<unsigned short>(z);
            return;
        }

        // we will have to generate a new block...
        z -= (8 - state._o_counter); // discard the remainder of the current blok
        state._o_counter = z % 8;    // set the pointer in the correct element in the new block
        z -= state._o_counter;       // update z
        z >>= 3;                     // the number of buffers is elements/8
        ++z;                         // and one more because we crossed the buffer line
        inc_counter(state, z);
        encrypt_counter(state);
    }

    // Extra function to set the key
    void set_key(nrnd::sitmo_t& state, u64 k0 = 0, u64 k1 = 0, u64 k2 = 0, u64 k3 = 0)
    {
        state._k[0] = k0;
        state._k[1] = k1;
        state._k[2] = k2;
        state._k[3] = k3;
        encrypt_counter(state);
    }

    // set the counter
    void set_counter(nrnd::sitmo_t& state, u64 s0 = 0, u64 s1 = 0, u64 s2 = 0, u64 s3 = 0, unsigned short o_counter = 0)
    {
        state._s[0]      = s0;
        state._s[1]      = s1;
        state._s[2]      = s2;
        state._s[3]      = s3;
        state._o_counter = o_counter % 8;
        encrypt_counter(state);
    }

#undef MIXK
#undef MIX2

    nrnd::sitmo_t::sitmo_t()
    {
        state_seed(*this, (s64)0xdeadbeefdeadbeef);
    }

    void nrnd::sitmo_t::reset(s64 seed) { state_seed(*this, seed); }
    u32 nrnd::sitmo_t::generate() { return state_generate(*this); }

}
