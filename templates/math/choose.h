#pragma once

#include "bits/stdc++.h"
#include "mod.h"
using namespace std;

//begintemplate choose
//description N choose K (and N permute K) in log(n) time with O(n) setup
vector<ll> fact;
void init_nchoosek(int MN, ll mod = MOD) {
    fact.resize(MN + 1);
    fact[0] = 1LL;
    for (int i = 1; i <= MN; i++)
        fact[i] = mmul(fact[i - 1], i, mod);
}
ll choose(ll N, ll K, ll mod = MOD) { return mdiv(fact[N], mmul(fact[K], fact[N - K], mod), mod); }
ll permute(ll N, ll K, ll mod = MOD) { return mdiv(fact[N], fact[N - K], mod); }
//endtemplate choose

/*
Given n coins, the probability of getting k of them to be heads,
with the probability of a coin being heads being p, can be computed
with the following formula:

(n choose k) * p^k * (1 - p)^(n - k)
*/

