#pragma once

#include "../stdincludes.h"
#include "fast_pow.h"

//begintemplate choose
//description N choose K in log(n) time with O(n) setup
template <int MAX, typename T, T MOD>
struct NChooseK {
    T facts[MAX];
    FastPow<T, MOD> fastPow;
    NChooseK() {}
    void init() {
        facts[1] = 1;
        for (int i = 2; i < MAX; i++)
            facts[i] = (facts[i - 1] * i) % MOD;
    }
    T choose (int n, int k) { return fastPow.divMod(facts[n], (facts[k] * facts[n - k]) % MOD); }
};
//endtemplate choose

/*
Given n coins, the probability of getting k of them to be heads,
with the probability of a coin being heads being p, can be computed
with the following formula:

(n choose k) * p^k * (1 - p)^(n - k)
*/
