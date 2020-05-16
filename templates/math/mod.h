#pragma once

#include "bits/stdc++.h"

using ll = long long;

//begintemplate mod
//description Basic modular arithmetic
const ll MOD = 1e9 + 7;
ll madd(ll a, ll b, ll mod = MOD) { return (a + b) % mod; }
ll msub(ll a, ll b, ll mod = MOD) { return (a - b + mod) % mod; }
ll mmul(ll a, ll b, ll mod = MOD) { return (a * b) % mod; }
ll fpow(ll x, ll y, ll mod = MOD) {
    if (!y) return 1LL;
    return mmul(fpow(mmul(x, x, mod), y >> 1, mod), (y & 1) ? x : 1LL, mod);
}
ll mdiv(ll x, ll y, ll mod = MOD) { return mmul(x, fpow(y, mod - 2, mod), mod); }
//endtemplate mod

//begintemplate fastmulmod
//description (a * b) math (math) without overflow (math <= 2 * LLONG_MAX)
ll fmul(ll x, ll y, ll mod = MOD) {
    if (!y) return 0LL;
    return (fmul((x + x) % mod, y >> 1, mod) + ((y & 1) ? x : 0LL)) % mod;
}
//endtemplate fastmulmod
