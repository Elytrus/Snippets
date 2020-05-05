#pragma once

#include "test/global_includes.h"

// Stops name conflicts
namespace STOP_CONFLICTS_2 {
//begintemplate fastmul
//description Modular multiplication for cases where overflow becomes an issue
const ll MOD = 1e9 + 7;
ll fastMul(ll x, ll y) {
    ll ans = 0;
    for (ll mag = 1, cmul = x; mag <= y; mag <<= 1, cmul = (cmul << 1) % MOD)
        if (y & mag) ans = (ans + cmul) % MOD;
    return ans;
}
//endtemplate fastmul
}

// Stops name conflicts
namespace STOP_CONFLICTS_3 {
//begintemplate fastmulrec
//description Fastmul but using recursive method instead
const ll MOD = 1e9 + 7;
ll fastMul(ll x, ll y) {
    if (!y) return 0LL;
    return (x * (y & 1) + fastMul((x + x) % MOD, y >> 1)) % MOD;
}
//endtemplate fastmulrec
}

void fast_mul_test() {
    assert(STOP_CONFLICTS_2::fastMul(2, 4) == 8);
    assert(STOP_CONFLICTS_2::fastMul(3, 1) == 3);
    assert(STOP_CONFLICTS_2::fastMul(3, 3) == 9);
    assert(STOP_CONFLICTS_2::fastMul(5, 3) == 15);
    assert(STOP_CONFLICTS_2::fastMul(1555, 0) == 0);

    assert(STOP_CONFLICTS_3::fastMul(2, 4) == 8);
    assert(STOP_CONFLICTS_3::fastMul(3, 1) == 3);
    assert(STOP_CONFLICTS_3::fastMul(3, 3) == 9);
    assert(STOP_CONFLICTS_3::fastMul(5, 3) == 15);
    assert(STOP_CONFLICTS_3::fastMul(1555, 0) == 0);

    PASSED("FastMul");
}
