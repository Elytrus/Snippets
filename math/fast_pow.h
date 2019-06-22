#pragma once

#include "../stdincludes.h"

//begintemplate fastpow
//description Basic Fastpow and Modular Division template
template <ll MOD>
struct FastPow {
    ll fastPow(ll x, ll y) {
        ll ans = 1;
        for (ll mag = 1, cpow = x; mag <= y; mag <<= 1, cpow = (cpow * cpow) % MOD)
            if (y & mag) ans = (ans * cpow) % MOD;
        return ans;
    }
    ll divMod(ll x, ll y) { return (x * fastPow(y, MOD - 2)) % MOD; }
};
//endtemplate fastpow

void fast_pow_test() {
    FastPow<1000000007> test;

    assert(test.fastPow(2, 4) == 16);
    assert(test.fastPow(3, 1) == 3);
    assert(test.fastPow(3, 3) == 27);
    assert(test.fastPow(5, 3) == 125);
    assert(test.fastPow(1555, 0) == 1);

    PASSED("FastPow");
}
