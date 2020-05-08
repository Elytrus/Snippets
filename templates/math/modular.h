#pragma once

//begintemplate mod
//description Basic modular arithmetic
const ll MOD = 1e9 + 7;
ll madd(ll a, ll b) { return (a + b) % MOD; }
ll msub(ll a, ll b) { return (a - b + MOD) % MOD; }
ll mmul(ll a, ll b) { return (a * b) % MOD; }
ll fpow(ll x, ll y) {
    if (!y) return 1LL;
    return mmul(fpow(mmul(x, x), y >> 1), (y & 1) ? x : 1LL);
}
ll mdiv(ll x, ll y) { return mmul(x, fpow(y, MOD - 2)); }
//endtemplate mod

//begintemplate dynamicmod
//description Basic modular arithmetic with dynamic mod
ll madd(ll a, ll b, ll MOD) { return (a + b) % MOD; }
ll msub(ll a, ll b, ll MOD) { return (a - b + MOD) % MOD; }
ll mmul(ll a, ll b, ll MOD) { return (a * b) % MOD; }
ll fpow(ll x, ll y, ll MOD) {
    if (!y) return 1LL;
    return mmul(fpow(mmul(x, x, MOD), y >> 1, MOD), (y & 1) ? x : 1LL, MOD);
}
ll mdiv(ll x, ll y, ll MOD) { return mmul(x, fpow(y, MOD - 2, MOD), MOD); }
//endtemplate dynamicmod

//begintemplate fastmulmod
//description (a * b) mod (mod) without overflow (mod <= 2 * LLONG_MAX)
ll fmul(ll x, ll y, ll mod) {
    if (!y) return 0LL;
    return (fmul((x + x) % mod, y >> 1, mod) + ((y & 1) ? x : 0LL)) % mod;
}
//endtemplate fastmulmod
