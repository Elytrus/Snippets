#pragma once

#include "test/global_includes.h"

//begintemplate fastcleararray
//description An array that can reset itself in O(1) time.  Get and set operations are both O(1) also
template <int MAX, typename T = int, T resetValue = 0>
struct FastClearArray {
    int cqid = 0, qids[MAX]; T arr[MAX];
    FastClearArray() { memset(qids, 0, sizeof qids); }
    void reset() { cqid++; }
    T& operator[](size_t idx) { if (cqid > qids[idx]) { qids[idx] = cqid; arr[idx] = resetValue; } return arr[idx]; }
    const T& operator[](size_t idx) const { return operator[](idx); }
};
//endtemplate fastcleararray

void fca_test() {
    FastClearArray<10, int, 0> fca;

    fca.reset();
    fca[0] = 34;
    fca[3] = 25;
    fca[2] = 123;

    assert(fca[0] == 34);
    assert(fca[3] == 25);
    assert(fca[2] == 123);
    assert(fca[1] == 0);
    assert(fca[7] == 0);

    fca.reset();

    assert(fca[0] == 0);
    assert(fca[3] == 0);
    assert(fca[2] == 0);
    assert(fca[1] == 0);
    assert(fca[7] == 0);

    PASSED("Fast Clearing Array");
}