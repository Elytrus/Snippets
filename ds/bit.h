#pragma once

#include "../stdincludes.h"

//begintemplate bit
//description Binary Indexed Tree
template <int MAX, typename T = int>
struct BIT {
    int n; T tree[MAX];
    BIT(int n0) : n(n0) {}
    void add(int x, T z){ // Adds value `z` to index `x`
        for(; x <= n; x += x & -x)
            tree[x] += z;
    }
    T sum(int x){ // Queries index `x`
        T sum = 0;
        for(; x; x -= x & -x)
            sum += tree[x];
        return sum;
    }
};
//endtemplate bit

//begintemplate 2dbit
//description 2D Binary Indexed Tree
template <int MAXN, int MAXM, typename T = int>
struct BIT2D {
    int n, m; T tree[MAXN][MAXM];
    BIT2D(int n0, int m0) : n(n0), m(m0) {}
    void add(int x, int y, T z){ // Adds `z` to index `(x, y)`
        for(int cx = x; cx <= n; cx += cx & -cx)
            for(int cy = y; cy <= m; cy += cy & -cy)
                tree[cx][cy] += z;
    }
    T sum(int x, int y){ // Querys index `(x, y)`
        T sum = 0;
        for(int cx = x; cx; cx -= cx & -cx)
            for(int cy = y; cy; cy -= cy & -cy)
                sum += tree[cx][cy];
        return sum;
    }
};
//endtemplate 2dbit