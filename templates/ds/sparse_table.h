#pragma once

#include "bits/stdc++.h"

using namespace std;

//begintemplate sparsetable
//description Sparse Table (RMQ) data structure.  Structure is 1-indexed (and init array should be as well)
template <typename T>
struct SparseTable {
    virtual T Op(T &a, T &b) = 0;
    int N, lg;
    vector<vector<T>> tb;
    void init(int n, T* init) {
        N = n; lg = 31 - __builtin_clz(N) + 1; tb.assign(lg, vector<T>(N + 1));
        copy(init + 1, init + 1 + N, tb[0].begin() + 1);
        for (int i = 1; i < lg; i++) {
            int jmp = 1 << (i - 1), end = N - jmp;
            for (int j = 1; j <= end; j++)
                tb[i][j] = Op(tb[i - 1][j], tb[i - 1][j + jmp]);
        }
    }
    T query(int L, int R) {
        int bit = 31 - __builtin_clz(R - L + 1);
        return Op(tb[bit][L], tb[bit][R - (1 << bit) + 1]);
    }
};
//endtemplate sparsetable