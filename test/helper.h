#pragma once

#include "testlib.h"
#include "bits/stdc++.h"
using namespace std;

// Testlib: https://github.com/MikeMirzayanov/testlib

const unsigned long long FIXED_SEED = 0xEC00;

void init_rng(unsigned long long seed = FIXED_SEED) {
    rnd.setSeed(seed);
}

// Rand stuff
template <typename T>
vector<T> rand_vec(int N, T min = 0, T max = 1e9) {
    vector<T> res;
    while (N--) res.push_back(rnd.next(min, max));
    return res;
}

vector<int> rand_perm(int N) {
    vector<int> res(N);
    iota(res.begin(), res.end(), 1);
    shuffle(res.begin(), res.end());
    return res;
}

// Exit stuff
void ok() {
    cout << "OK";
}

// Same as assert (if cond is false, program will exit with failure)
void check(bool cond, string feedback) {
    if (!cond) {
        cout << "FAIL " << feedback;
        exit(0);
    }
}

