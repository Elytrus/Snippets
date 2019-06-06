#pragma once

#include "../stdincludes.h"

//begintemplate bit
//description Binary Indexed Tree
template <int MAX, typename T = int>
struct BIT {
    int n; T tree[MAX];
    void init(int n0) { n = n0; }
    void upd(int x, T z){ // Adds value `z` to index `x`
        for(; x <= n; x += x & -x)
            tree[x] += z;
    }
    T query(int x){ // Queries index `x`
        T sum = 0;
        for(; x; x -= x & -x)
            sum += tree[x];
        return sum;
    }
    void reverseUpd(int x, T z) { upd(n - x + 1, z); }
    T reverseQuery(int x) { return query(n - x + 1); }
};
//endtemplate bit

//begintemplate 2dbit
//description 2D Binary Indexed Tree
template <int MAXN, int MAXM, typename T = int>
struct BIT2D {
    int n, m; T tree[MAXN][MAXM];
    void init(int n0, int m0) { n = n0; m = m0; }
    void add(int x, int y, T z){ // Adds `z` to index `(x, y)`
        for(int cx = x; cx <= n; cx += cx & -cx)
            for(int cy = y; cy <= m; cy += cy & -cy)
                tree[cx][cy] += z;
    }
    T query(int x, int y){ // Querys index `(x, y)`
        T sum = 0;
        for(int cx = x; cx; cx -= cx & -cx)
            for(int cy = y; cy; cy -= cy & -cy)
                sum += tree[cx][cy];
        return sum;
    }
    T reverseQuery(int x, int y) { return query(n - x + 1, m - y + 1); }
    void reverseUpd(int x, int y, T z) { upd(n - x + 1, m - y + 1, z); }
};
//endtemplate 2dbit