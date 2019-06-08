#pragma once

#include "../stdincludes.h"
#include "graph.h"

//begintemplate flatgraphiter
//description The iterable object that's returned by the adj function
template <typename T>
struct FlatGraphIter {
    T* _begin, _end;
    T* begin() { return _begin; }
    T* end() { return _end; }
};
//endtemplate flatgraphiter

//begintemplate flatgraph
//description An array based implementation of a graph
template <int MAX, int MAXE>
struct FlatGraph {
    int n, m, start[MAX + 1], to[MAXE], A[MAXE], B[MAXE];
    void init(int n0, int m0) { n = n0; m = m0; }
    void input() {
        for (int i = 0; i < m; i++) {
            cin >> A[i] >> B[i];
            start[A[i]]++;
        }
        setup();
    }
    void setup() {
        partial_sum(start, start + n + 2);
    }
    FlatGraphIter<int> adjs(int x) { return {to + start[x], to + start[x + 1]}; }
};
//endtemplate flatgraph