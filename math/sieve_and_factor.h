#pragma once

#include "stdincludes.h"

//begintemplate primesieve
//description Sieve of Eratosthenes + Factorization implementation
template <int MAX>
struct PrimeSieve {
    bool isPrime[MAX]; vector<int> primes;
    PrimeSieve() {}
    inline void doWithFactor(int x) { assert(("Needs to be implemented!", 0)); }
    inline void doWithPrimeFactors(vector<pair<int, int>> &facts) { assert(("Needs to be implemented!", 0)); }
    void calc() {
        memset(isPrime, true, sizeof isPrime);
        isPrime[0] = isPrime[1] = false;
        for (int i = 2; i < MAX; i++) {
            if (isPrime[i]) {
                for (int j = i + i; j < MAX; j += i)
                    isPrime[j] = false;
                primes.push_back(i);
            }
        }
    }
    void factor(int v, bool prime_factor) { // if prime_factor is true, it will only prime factor the number
        int sqv = sqrt(v);
        vector<pair<int, int>> facts;

        for (int prime : primes) {
            if (prime > sqv)
                break;

            int cnt = 0;
            while (v % prime == 0) {
                v /= prime;
                cnt++;
            }

            if (cnt)
                facts.push_back(make_pair(prime, cnt));
        }
        if (v > 1)
            facts.push_back(make_pair(v, 1));

        if (!prime_factor)
            factorRec(1, 0, facts.size(), facts);
        else
            doWithPrimeFactors(facts);
    }
    void factorRec(int cur, int pos, int sz, vector<pair<int, int>> &facts) {
        if (pos == sz) {
            doWithFactor(cur);
            return;
        }

        for (int i = 0; i <= facts[pos].second; i++) {
            factorRec(cur, pos + 1, sz, facts);
            cur *= facts[pos].first;
        }
    }
};
//endtemplate primesieve

//TODO: Sieve Test