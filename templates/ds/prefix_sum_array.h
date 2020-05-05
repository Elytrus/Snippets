#pragma once
#include "bits/stdc++.h"
using namespace std;

//begintemplate prefix_sum_array
//description Supports range sum queries (after being built) in O(1) time.  Assumed that for query(l, r) l>0
template <typename T>
struct PSA {
    virtual T Op(T &a, T &b) = 0; // i.e. a + b
    virtual T Invop(T &a, T &b) = 0; // i.e. a - b
    vector<T> psum;
    void init(int N) { psum.resize(N); }
    template <typename It> void init(It st, It en) { init(en - st); copy(st, en, psum.begin()); }
    void update(int i, T v) { psum[i] = Op(psum[i], v); } // can only be called before build()
    void build() {
        for (int i = 1; i < psum.size(); i++)
            psum[i] = Op(psum[i - 1], psum[i]);
    }
    T query(int l, int r) { return Invop(psum[r], psum[l - 1]); }
};
//endtemplate

