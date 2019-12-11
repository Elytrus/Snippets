#pragma once

#include "template_tests/global_includes.h"

//begintemplate bit
//description Binary Indexed Tree
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
 * void upd(int x, T z) - Executes A[x] = A[x] `op` z | Complexity O(log N * (complexity of merge))
 * T query(int x) - Returns A[1] `op` A[2] `op` ... `op` A[x] | Complexity O(log N * (complexity of merge))
 */
template <int MN, typename T = int>
struct BIT {
    int n; T bit[MN];
    virtual void merge(T& a, T& b) = 0;
    virtual T getDefault() = 0;
    void init(int n0) { n = n0; for (int i = 0; i <= n; i++) bit[i] = getDefault(); }
    void upd(int x, T z){ for(; x <= n; x += x & -x) merge(bit[x], z); }
    T query(int x){ // Queries index `x`
        T sum = getDefault();
        for(; x; x -= x & -x) merge(sum, bit[x]);
        return sum;
    }
};
//endtemplate bit

//begintemplate sumbit
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
 * T query(int x) - Returns A[1] + A[2] + ... + A[x] | Complexity O(log N * (complexity of + operator))
 * T rsq(int l, int r) - Returns A[l] + A[l + 1] + ... + A[r].  Requires the "-" operator to be implemented
 * int bsearch(T minVal) - Returns the first index `i` where A[1] + A[2] + ... + A[i] >= `minVal` | Complexity O(log N * (complexity of + operator))
 */
template <int MN, typename T = int>
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
};
//endtemplate sumbit

//begintemplate dynamicdifferencearray
//description Dynamic Difference Array
/*
 * Dynamic Difference Array for range updates and point queries.
 * To use this template, the BIT template must also be present in your code.
 * -- Abstraction --
 * A[N] - An array of size N
 * -- Functions to implement --
 * Operators "+" and "-" on type T
 * -- Operations --
 * upd(int l, int r, int v) - Preforms A[l], A[l + 1], ..., A[r] += v | Complexity: O(log N * (complexity of + operator))
 * query(int x) - Returns A[x] | Complexity: O(log N * (complexity of + operator))
 */
template <int MN, typename T = int>
struct DynamicDifferenceArray : public BIT<MN, T> {
    using BT = BIT<MN, T>; using BT::n; using BT::query; using BT::bit;
    void upd(int l, int r, T v) { upd(l, v); upd(r + 1, -v); }
private:
    using BT::upd;
};
//endtemplate dynamicdifferencearray

//begintemplate 2dbit
//description 2D Binary Indexed Tree
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
template <int MN, int MM, typename T = int>
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
};
//endtemplate 2dbit

// Testing
struct Test1DBIT : SumBIT<rsq_tests::N + 1, ll> {
    ll getDefault() override { return 0LL; }
};

struct Test1D : Test<RSQDataSet> {
    string get_name() override { return "1D BIT Test"; }
    RSQDataSet generate_data() override {
        return make_rmq_dataset(false, false, false);
    }
    bool run_test(RSQDataSet test) override {
        int N = rsq_tests::N;
        Test1DBIT bit; bit.init(N);
        RSQDummy dummy; dummy.init(N);

        for (auto query : test.queries) {
            auto [type, a, b, c] = query;
            if (type == 1) {
                bit.upd(a, b);
                dummy.range_update(a, a, b);
            }
            else {
                if (bit.query(a) != dummy.range_query(1, a)) {
                    return false;
                }
            }
        }

        return true;
    }
};

struct TestBitBsearch : Test<RSQDataSet> {
    string get_name() override { return "BIT Bsearch Test"; }
    RSQDataSet generate_data() override {
        int N = rsq_tests::N;
        RSQDataSet ret;
        for (int i = 0; i < rsq_tests::Q; i++) {
            int type = randint(1, 2);
            if (type == 1) {
                int a = randint(1, N), v = randint(0, rsq_tests::MAX_VAL);
                ret.queries.emplace_back(type, a, v, -1);
            }
            else {
                int v = randint(0, rsq_tests::MAX_VAL * max(1, (i - 5) / 3));
                ret.queries.emplace_back(type, v, -1, -1);
            }
        }
        return ret;
    }
    bool run_test(RSQDataSet test) override {
        int N = rsq_tests::N;
        Test1DBIT bit; bit.init(N);
        RSQDummy dummy; dummy.init(N);

        for (auto query : test.queries) {
            auto [type, a, b, c] = query;
//            printf("Q: t=%d a=%d b=%d c=%d ", type, a, b, c);
//            if (type == 2) printf("expected=%d\n", dummy.first_pfxsum_greater_or_equal(a)); else printf("\n");
            if (type == 1) {
                bit.upd(a, b);
                dummy.range_update(a, a, b);
            }
            else {
                if (bit.bsearch(a) != dummy.first_pfxsum_greater_or_equal(a)) {
                    return false;
                }
            }
        }

        return true;
    }
};

struct TestDDA : DynamicDifferenceArray<rsq_tests::N + 1> {
    void merge(int &a, int &b) override { a += b; }
    int getDefault() override { return 0; }
};

struct TestDiffArray : Test<RSQDataSet> {
    string get_name() override { return "BIT Difference Array Test"; }
    RSQDataSet generate_data() override {
        return make_rmq_dataset(false, true, false);
    }
    bool run_test(RSQDataSet test) override {
        const int N = rsq_tests::N;
        TestDDA da; da.init(N);
        RSQDummy dummy; dummy.init(N);

        for (auto query : test.queries) {
            auto [type, a, b, c] = query;
            if (type == 1) {
                da.upd(a, b, c);
                dummy.range_update(a, b, c);
            }
            else {
                if (da.query(a) != dummy.range_query(a, a)) {
                    return false;
                }
            }
        }

        return true;
    }
};

struct Test2DBIT : BIT2D<rsq_tests::N2 + 1, rsq_tests::N2 + 1, int> {
    void merge(int &a, int &b) override { a += b; }
    int getDefault() override { return 0; }
};

struct Test2D : Test<RSQDataSet> {
    string get_name() override { return "2D BIT Test"; }
    RSQDataSet generate_data() override {
        int N = rsq_tests::N2;
        RSQDataSet ret;
        for (int i = 0; i < rsq_tests::Q; i++) {
            int type = randint(1, 2), a = randint(1, N), b = randint(1, N), v = randint(0, rsq_tests::MAX_VAL);
            ret.queries.emplace_back(type, a, b, v);
        }
        return ret;
    }
    bool run_test(RSQDataSet test) override {
        int N = rsq_tests::N2;
        Test2DBIT bit; bit.init(N, N);
        RSQDummy2D dummy; dummy.init(N, N);

        for (auto query : test.queries) {
            auto [type, a, b, c] = query;
            if (type == 1) {
                bit.upd(a, b, c);
                dummy.range_update(a, b, a, b, c);
            }
            else {
                if (bit.query(a, b) != dummy.range_query(1, 1, a, b)) {
                    WRONG(bit.query(a, b), dummy.range_query(1, 1, a, b));
                    return false;
                }
            }
        }

        return true;
    }
};

void bit_tests() {
    Test1D().run();
    TestDiffArray().run();
    TestBitBsearch().run();
    Test2D().run();
}
