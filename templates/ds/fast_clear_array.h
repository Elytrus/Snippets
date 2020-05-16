#pragma once

#include "bits/stdc++.h"
using namespace std;

//begintemplate fastcleararray
//description An array that can reset itself in O(1) time.  Get and set operations are both O(1) also
/*
 * Fast clearing array template.  Besides being a normal array, it also allows for resetting itself in O(1) time.
 * -- Abstraction --
 * A[N] - Array of size N
 * -- Functions to Implement --
 * T getDefault() - The value that the reset operation should reset all elements to
 * -- Functions Available --
 * void init(int N) - Initializes the DS | Complexity: O(N)
 * T& operator[](int index) - Retrieves A[index] | Complexity: O(1)
 * void reset() - Resets A[1..N] to getDefault() | Complexity: O(1)
 */
template <typename T = int>
struct FastClearArray {
    int cqid = 1; vector<int> qids; vector<T> val;
    virtual T getDefault() = 0;
    void init(int N) { cqid = 1; qids.assign(N, 0); val.assign(N, getDefault()); }
    void reset() { cqid++; }
    T& operator[](size_t idx) { if (cqid > qids[idx]) { qids[idx] = cqid; val[idx] = getDefault(); } return val[idx]; }
    const T& operator[](size_t idx) const { return operator[](idx); }
};
//endtemplate fastcleararray
