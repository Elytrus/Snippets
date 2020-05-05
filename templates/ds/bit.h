#pragma once
#include "bits/stdc++.h"
using namespace std;

/*
 * Binary Indexed Tree (Fenwick Tree) Template.  Supports O(log N) update and prefix/suffix query on an array
 * -- Abstraction --
 * A[N] - An array of size N
 * `op` - A binary operation that is commutative and associative
 * -- Functions to Implement --
 * void merge(T& a, T& b) - Executes a = a `op` b
 * T getDefault() - Returns the identity value of your operation.  A value "x" such that x `op` y (any value) = y
 * -- Functions Available --
 * void init(int n0) - Initializes the data structure as size n0 | Complexity: O(N)
 * void update(int x, T z) - Executes A[x] = A[x] `op` z | Complexity O(log N * (complexity of merge))
 * T query(int x) - Returns op(A[1..x]) | Complexity O(log N * (complexity of merge))
 */
//begintemplate bit
//description Binary Indexed Tree.  1-indexed
template <typename T>
struct BIT {
    virtual T Default() = 0;
    virtual T Op(T &a, T &b) = 0;
    int N;
    vector<T> bit;
    void init(int n) { N = n; bit.resize(N + 1); }
    void update(int x, T v) { for (; x <= N; x += x & - x) bit[x] = Op(bit[x], v); }
    T query(int x) { T sum = Default(); for (; x; x -= x & -x) sum = Op(sum, bit[x]); return sum; }
};
//endtemplate bit

/*
// TODO: bit bsearch tests
/*
 * Summation Binary Indexed Tree (Fenwick Tree) Template.  This template also supports a few additional operations along with the
 * standard BIT ones.  To use this template, the BIT template must also be present in your code.
 * -- Abstraction --
 * See: Binary Indexed Tree
 * -- Functions to Implement --
 * merge(T&, T&) is already implemented using the "+=" operator.
 * T getDefault() - Returns the identity value of your operation.  Generally, this value is 0 as the operation is addition.
 * -- Functions Available --
 * void init(int n0) - Initializes the data structure as size n0 | Complexity: O(N)
 * void upd(int x, T z) - Executes A[x] = A[x] + z | Complexity O(log N * (complexity of + operator))
 * T query(int x) - Returns sum(A[1..x]) | Complexity O(log N * (complexity of + operator))
 * T rsq(int l, int r) - Returns sum(A[l..r]).  Requires the "-" operator to be implemented
 * int bsearch(T minVal) - Returns the first index `i` where sum(A[1..i]) >= `minVal` | Complexity O(log N * (complexity of + operator))
 */
//begintemplate sumbit
/* template <int MN, typename T = int>
struct SumBIT : BIT<MN, T> {
    using BT = BIT<MN, T>; using BT::n; using BT::query; using BT::getDefault; using BT::bit;
    void merge(T& a, T& b) override { a += b; }
    T rsq(int l, int r) { return query(r) - query(l - 1); }
    int bsearch(T minVal) {
        T curSum = getDefault();
        int idx = 0;
        for (int cbit = 1 << (31 - __builtin_clz(n)); cbit > 0; cbit >>= 1) {
            int alt = idx | cbit;
            if (alt <= n && curSum + bit[alt] < minVal) {
                curSum += bit[alt];
                idx = alt;
            }
        }
        idx++;
        return idx;
    }
}; */
//endtemplate sumbit

// TODO: 2dbit tests
/*
 * 2D Binary Indexed Tree (Fenwick Tree) Template.  Supports O(log N * log M) update and query on the result of any binary operation that is both commutative and associative on
 * an N by M grid.  (i.e. summation, max, min).  See the BIT template for more details
 * -- Abstraction --
 * A[N][M] - A 2D array of size N x M
 * `op` - A binary operation (with the above specifications).  A op B
 * -- Functions to Implement --
 * See: Binary Indexed Tree (BIT)
 * -- Functions Available --
 * void init(int n0, int m0) - Initializes the data structure as size n0, m0 | Complexity: O(N * M)
 * void upd(int x, int y, T z) - Executes A[x][y] = A[x][y] `op` z | Complexity O(log N * log M * (complexity of merge))
 * T query(int x, int y) - Returns the result of preforming `op` on the subgrid (1, 1), (x, y) | Complexity O(log N * log M * (complexity of merge))
 */
//begintemplate 2dbit
//description 2D Binary Indexed Tree
/*template <int MN, int MM, typename T = int>
struct BIT2D {
    int n, m; T bit[MN][MM];
    virtual void merge(T& a, T& b) = 0;
    virtual T getDefault() = 0;
    void init(int n0, int m0) {
        n = n0; m = m0;
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m; j++)
                bit[i][j] = getDefault();
    }
    void upd(int x, int y, T z){ // Adds `z` to index `(x, y)`
        for (int cx = x; cx <= n; cx += cx & -cx)
            for (int cy = y; cy <= m; cy += cy & -cy)
                merge(bit[cx][cy], z);
    }
    T query(int x, int y){ // Querys index `(x, y)`
        T sum = getDefault();
        for (int cx = x; cx; cx -= cx & -cx)
            for (int cy = y; cy; cy -= cy & -cy)
                merge(sum, bit[cx][cy]);
        return sum;
    }
};*/
//endtemplate 2dbit
