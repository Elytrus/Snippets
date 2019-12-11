#pragma once

#include "test/global_includes.h"

//begintemplate bit
//description Binary Indexed Tree
/*
 * Binary Indexed Tree (Fenwick Tree) Template.  Supports O(log N) update and query on the result of any binary operation that is both commutative and associative on an array (i.e. summation, max, min).
 * -- Abstraction --
 * A[N] - An array of size N
 * N - The size of the array
 * `op` - A binary operation (with the above specifications).  A op B
 * rev - Whether the queries and updates are reversed
 * -- Functions to Implement --
 * void merge(T& a, T& b) - Executes a = a `op` b
 * T getDefault() - Returns the identity value of your operation.  The identity is a value "x" such given an arbitrary value "y", x `op` y = y.  i.e. for summation it would be 0, for max it would be -infinity.
 * -- Functions Available --
 * void init(int n0) - Initializes the data structure as size n0 | Complexity: O(1)
 * void upd(int x, T z) - Executes A[x] = A[x] `op` z | Complexity O(log N * (complexity of merge))
 * T query(int x) - Returns A[1] `op` A[2] `op` ... `op` A[x].  If rev is true, it will return A[x] `op` A[x + 1] `op` ... `op` A[N] | Complexity O(log N * (complexity of merge))
 */
template <int MN, typename T = int, bool rev = false>
struct BIT {
    int n; T bit[MN];
    virtual void merge(T& a, T& b);
    virtual T getDefault();
    void init(int n0) { n = n0; }
    void upd(int x, T z){
        if (rev) x = n - x + 1;
        for(; x <= n; x += x & -x) merge(bit[x], z);
    }
    T query(int x){ // Queries index `x`
        if (rev) x = n - x + 1;
        T sum = getDefault();
        for(; x; x -= x & -x) merge(sum, bit[x]);
        return sum;
    }
};
//endtemplate bit

/*
 * Summation Binary Indexed Tree (Fenwick Tree) Template.  Besides the normal BIT operations, it also supports a few additional ones.  See the BIT template for more details.
 * To use this template, the BIT template must also be present in your code.
 * -- Abstraction --
 * See: Binary Indexed Tree
 * -- Functions to Implement --
 * Note that merge(T&, T&) is already implemented using the addition operator.
 * T getDefault() - Returns the identity value of your operation.  Generally, this value is 0 as the operation is addition.
 * -- Functions Available --
 * void init(int n0) - Initializes the data structure as size n0 | Complexity: O(1)
 * void upd(int x, T z) - Executes A[x] = A[x] + z | Complexity O(log N * (complexity of + operator))
 * T query(int x) - Returns A[1] + A[2] + ... + A[x].  If rev is true, it will return A[x] + A[x + 1] + ... + A[N] | Complexity O(log N * (complexity of + operator))
 * T rsq(int l, int r) - Returns A[l] + A[l + 1] + ... + A[r].
 * int bsearch(T minVal) - Returns the first index `i` where A[1] + A[2] + ... + A[i] is greater or equal to `minVal`.  If rev is true, it will return the
 */
template <int MN, typename T = int, bool rev = false>
struct SumBIT : BIT<MN, T, rev> {
    using BT = BIT<MN, T, rev>; using BT::n; using BT::query; using BT::bit;
    void merge(T& a, T& b) { a += b; }
    virtual T getDefault();
    T rsq(int l, int r) { return query(r) - query(l - 1); }
    int bsearch(T minVal) {
        T curSum = getDefault();
        int idx = 0;
        for (int bit = 1 << (31 - __builtin_clz(n)); bit > 0; bit >>= 1) {
            int alt = idx | bit;
            T altSum = curSum; merge(altSum, bit[alt]);
            if (alt <= n && altSum < minVal) {
                curSum = altSum;
                idx = alt;
            }
        }
        idx++;
        if (rev) n = n - idx + 1;
        return idx;
    }
};

/*
 * 2D Binary Indexed Tree (Fenwick Tree) Template.  Supports O(log N * log M) update and query on the result of any binary operation that is both commutative and associative on
 * an N by M grid.  (i.e. summation, max, min).  See the BIT template for more details
 */
//begintemplate 2dbit
//description 2D Binary Indexed Tree
template <int MN, int MM, typename T = int>
struct BIT2D {
    int n, m; T bit[MN][MM];
    virtual void merge(T& a, T& b);
    virtual T getDefault();
    void init(int n0, int m0) { n = n0; m = m0; }
    void add(int x, int y, T z){ // Adds `z` to index `(x, y)`
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
    T revQuery(int x, int y) { return query(n - x + 1, m - y + 1); }
    void revUpd(int x, int y, T z) { upd(n - x + 1, m - y + 1, z); }
};
//endtemplate 2dbit
