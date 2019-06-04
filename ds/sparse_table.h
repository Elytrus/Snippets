#pragma once

#include "../stdincludes.h"

//begintemplate sparsetable
//description Sparse Table (RMQ) data structure
template <int MAX, int LOG, typename T>
struct SparseTable {
    int n; T table[LOG][MAX];
    function<T(T, T)> merge;
    SparseTable (int n0, function<T(T, T)> merge0) : n(n0), merge(merge0) {}
    void build(int *arr){
        copy(arr + 1, arr + n + 1, table[0] + 1);
        for(int i = 1; i < LOG; i++){
            int jmp = 1 << (i - 1), end = n - jmp;
            for(int j = 1; j <= end; j++)
                table[i][j] = merge(table[i - 1][j], table[i - 1][j + jmp]);
        }
    }
    T query(int l, int r){
        int delta = r - l + 1, bit = 31 - __builtin_clz(delta);
        return merge(table[bit][l], table[bit][r - (1 << bit) + 1]);
    }
};
//endtemplate sparsetable