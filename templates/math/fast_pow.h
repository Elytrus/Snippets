#pragma once

#include "test/global_includes.h"

//begintemplate fastpow
//description Basic Fastpow and Modular Division template
const ll MOD = 1e9 + 7;
ll fastPow(ll x, ll y) {
    ll ans = 1;
    for (ll mag = 1, cpow = x; mag <= y; mag <<= 1, cpow = (cpow * cpow) % MOD)
        if (y & mag) ans = (ans * cpow) % MOD;
    return ans;
}
ll divMod(ll x, ll y) { return (x * fastPow(y, MOD - 2)) % MOD; }
//endtemplate fastpow

// Stops name conflicts
namespace STOP_CONFLICTS {
//begintemplate fastpowrec
//description Fastpow but using recursive method instead
const ll MOD = 1e9 + 7;
ll fastPow(ll x, ll y) {
    if (!y) return 1LL;
    return ((y & 1 ? x : 1) * fastPow((x * x) % MOD, y >> 1)) % MOD;
}
ll divMod(ll x, ll y) { return (x * fastPow(y, MOD - 2)) % MOD; }
//endtemplate fastpowrec
}

void fast_pow_test() {
    assert(fastPow(2, 4) == 16);
    assert(fastPow(3, 1) == 3);
    assert(fastPow(3, 3) == 27);
    assert(fastPow(5, 3) == 125);
    assert(fastPow(1555, 0) == 1);

    assert(STOP_CONFLICTS::fastPow(2, 4) == 16);
    assert(STOP_CONFLICTS::fastPow(3, 1) == 3);
    assert(STOP_CONFLICTS::fastPow(3, 3) == 27);
    assert(STOP_CONFLICTS::fastPow(5, 3) == 125);
    assert(STOP_CONFLICTS::fastPow(1555, 0) == 1);

    PASSED("FastPow");
}
