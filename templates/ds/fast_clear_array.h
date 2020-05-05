#pragma once

#include "template_tests/global_includes.h"

//begintemplate fastcleararray
//description An array that can reset itself in O(1) time.  Get and set operations are both O(1) also
/*
 * Fast clearing array template.  Besides being a normal array, it also allows for resetting itself in O(1) time.
 * -- Abstraction --
 * A[N] - Array of size N
 * -- Functions to Implement --
 * T getDefault() - The value that the reset operation should reset all elements to
 * -- Functions Available --
 * void init() - Initializes the DS | Complexity: O(N)
 * T& operator[](int index) - Retrieves A[index] | Complexity: O(1)
 * void reset() - Resets A[1..N] to getDefault() | Complexity: O(1)
 */
template <int MN, typename T = int>
struct FastClearArray {
    int cqid = 1, qids[MN]; T arr[MN];
    virtual T getDefault() = 0;
    void init() { memset(qids, 0, sizeof qids); }
    void reset() { cqid++; }
    T& operator[](size_t idx) { if (cqid > qids[idx]) { qids[idx] = cqid; arr[idx] = getDefault(); } return arr[idx]; }
    const T& operator[](size_t idx) const { return operator[](idx); }
};
//endtemplate fastcleararray

namespace __fca_tests {
    using Data = vector<tuple<int, int, int>>;
    const int N = 1000, Q = 1000, V = 1000000;

    struct FCATestDS : FastClearArray<N + 1, int> {
        int getDefault() override { return 0; }
    };

    struct FCATest : Test<Data> {
        string get_name() override { return "Fast Clearing Array Tests"; }
        Data generate_data() override {
            Data ret;
            for (int i = 0; i < Q; i++) {
                int type = randint(1, 101);
                if (type <= 100 && type % 2 == 1) // Update
                    ret.emplace_back(1, randint(1, N), randint(0, V));
                else if (type <= 100) // Query
                    ret.emplace_back(2, randint(1, N), -1);
                else if (type == 101) // Reset
                    ret.emplace_back(3, -1, -1);
            }
            return ret;
        }

        bool run_test(Data test) override {
            vector<int> dummy; dummy.assign(N + 1, 0);
            FCATestDS fca; fca.init();

            for (auto query : test) {
                auto [type, a, b] = query;
//                printf("Q: t=%d a=%d b=%d\n", type, a, b);
                if (type == 1) {
                    fca[a] = b;
                    dummy[a] = b;
                }
                else if (type == 2) {
                    if (fca[a] != dummy[a]) {
                        WRONG(fca[a], dummy[a]);
                        return false;
                    }
                }
                else {
                    for (int i = 1; i <= N; i++)
                        dummy[i] = 0;
                    fca.reset();
                }
            }

            return true;
        }
    };

    void fca_tests() {
        FCATest().run();
    }
}
using __fca_tests::fca_tests;
