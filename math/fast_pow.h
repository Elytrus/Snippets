#pragma once

#include "../stdincludes.h"

//begintemplate fastpow
//description Basic Fastpow and Modular Division template
template <typename T, T MOD>
struct FastPow {
    FastPow() {}
    ll fastPow(ll x, ll y) {
        ll ans = 1;
        for (ll mag = 1, cpow = x; mag <= y; mag <<= 1, cpow = (cpow * cpow) % MOD)
            if (y & mag)
                ans = (ans * cpow) % MOD;
        return ans;
    }
    ll divMod(ll x, ll y) { return (x * fastPow(y, MOD - 2)) % MOD; }
};
//endtemplate fastpow
