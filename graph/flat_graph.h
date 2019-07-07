#pragma once

#include "../stdincludes.h"
#include "graph.h"
#include "test/test_graph.h"

//begintemplate flatgraphiter
//description The iterable object that's returned by the adj function
template <typename T>
struct FlatGraphIter {
    T* _begin; T* _end;
    T* begin() { return _begin; }
    T* end() { return _end; }
};
//endtemplate flatgraphiter

//begintemplate flatgraph
//description An array based implementation of a graph.  If it's undirected MAXE should be double the max size of M
template <int MAX, int MAXE>
struct FlatGraph {
    int n, m, start[MAX + 1], to[MAXE], A[MAXE], B[MAXE], ptr[MAX];
    void init(int n0, int m0) { n = n0; m = m0; }
    void input(bool undirected) {
        memset(start, 0, sizeof start);
        for (int i = 0; i < m; i++) {
            cin >> A[i] >> B[i];
            start[A[i] + 1]++;
        }
        if (undirected) {
            for (int i = m, end = m << 1; i < end; i++) {
                A[i] = B[i - m]; B[i] = A[i - m];
                start[A[i] + 1]++;
            }
            m <<= 1;
        }
        setup();
    }
    void setup() {
        memset(ptr, 0, sizeof ptr);
        partial_sum(start, start + n + 2, start);
        for (int i = 0; i < m; i++)
            to[start[A[i]] + ptr[A[i]]++] = B[i];
    }
    FlatGraphIter<int> adjs(int x) { return {to + start[x], to + start[x + 1]}; }
};
//endtemplate flatgraph

//begintemplate weightedflatgraph
//description Flat Graph but weighted
template <int MAX, int MAXE, typename T = int>
struct WeightedFlatGraph {
    int n, m, start[MAX + 1]; ed<T> to[MAXE]; int A[MAXE]; ed<T> B[MAXE]; int ptr[MAX];
    void init(int n0, int m0) { n = n0; m = m0; }
    void input(bool undirected) {
        memset(start, 0, sizeof start);
        for (int i = 0; i < m; i++) {
            cin >> A[i] >> B[i].v >> B[i].w;
            start[A[i] + 1]++;
        }
        if (undirected) {
            for (int i = m, end = m << 1; i < end; i++) {
                A[i] = B[i - m].v; B[i].v = A[i - m]; B[i].w = B[i - m].w;
                start[A[i] + 1]++;
            }
            m <<= 1;
        }
        setup();
    }
    void setup() {
        memset(ptr, 0, sizeof ptr);
        partial_sum(start, start + n + 2, start);
        for (int i = 0; i < m; i++)
            to[start[A[i]] + ptr[A[i]]++] = B[i];
    }
    FlatGraphIter<ed<T>> adjs(int x) { return {to + start[x], to + start[x + 1]}; }
};
//endtemplate weightedflatgraph

//begintemplate flatgraphtranspose
//description Transposing but for flat graphs
template <int MAX, int MAXE> FlatGraph<MAX, MAXE> transpose(FlatGraph<MAX, MAXE> &g) {
    FlatGraph<MAX, MAXE> ret; ret.init(g.n, g.m);
    for (int i = 0; i < g.m; i++) {
        ret.A[i] = g.B[i];
        ret.B[i] = g.A[i];
    }
    ret.setup();
    return ret;
}
template <int MAX, int MAXE, typename T> WeightedFlatGraph<MAX, MAXE, T> transpose(WeightedFlatGraph<MAX, MAXE, T> &g) {
    WeightedFlatGraph<MAX, MAXE, T> ret; ret.init(g.n, g.m);
    for (int i = 0; i < g.m; i++) {
        ret.A[i] = g.B[i];
        ret.B[i] = g.A[i];
    }
    ret.setup();
    return ret;
}
//endtemplate flatgraphtranspose

FlatGraph<31, 30> test_flat_graph() {
    FlatGraph<31, 30> g;
    g.init(30, 30);

    // Simulates input
    memset(g.start, 0, sizeof g.start);
    g.A[0] = 11; g.B[0] = 16; g.start[11 + 1]++;
    g.A[1] = 16; g.B[1] = 28; g.start[16 + 1]++;
    g.A[2] = 8; g.B[2] = 9; g.start[8 + 1]++;
    g.A[3] = 19; g.B[3] = 22; g.start[19 + 1]++;
    g.A[4] = 18; g.B[4] = 30; g.start[18 + 1]++;
    g.A[5] = 4; g.B[5] = 9; g.start[4 + 1]++;
    g.A[6] = 10; g.B[6] = 18; g.start[10 + 1]++;
    g.A[7] = 5; g.B[7] = 25; g.start[5 + 1]++;
    g.A[8] = 11; g.B[8] = 27; g.start[11 + 1]++;
    g.A[9] = 1; g.B[9] = 28; g.start[1 + 1]++;
    g.A[10] = 17; g.B[10] = 23; g.start[17 + 1]++;
    g.A[11] = 5; g.B[11] = 22; g.start[5 + 1]++;
    g.A[12] = 25; g.B[12] = 29; g.start[25 + 1]++;
    g.A[13] = 15; g.B[13] = 22; g.start[15 + 1]++;
    g.A[14] = 29; g.B[14] = 30; g.start[29 + 1]++;
    g.A[15] = 8; g.B[15] = 11; g.start[8 + 1]++;
    g.A[16] = 23; g.B[16] = 29; g.start[23 + 1]++;
    g.A[17] = 13; g.B[17] = 15; g.start[13 + 1]++;
    g.A[18] = 16; g.B[18] = 23; g.start[16 + 1]++;
    g.A[19] = 13; g.B[19] = 28; g.start[13 + 1]++;
    g.A[20] = 11; g.B[20] = 12; g.start[11 + 1]++;
    g.A[21] = 4; g.B[21] = 11; g.start[4 + 1]++;
    g.A[22] = 15; g.B[22] = 17; g.start[15 + 1]++;
    g.A[23] = 5; g.B[23] = 16; g.start[5 + 1]++;
    g.A[24] = 12; g.B[24] = 26; g.start[12 + 1]++;
    g.A[25] = 4; g.B[25] = 15; g.start[4 + 1]++;
    g.A[26] = 12; g.B[26] = 19; g.start[12 + 1]++;
    g.A[27] = 16; g.B[27] = 27; g.start[16 + 1]++;
    g.A[28] = 8; g.B[28] = 18; g.start[8 + 1]++;
    g.A[29] = 17; g.B[29] = 26; g.start[17 + 1]++;

    g.setup();

    return g;
}

const vector<vector<int>> ADJS = {
        {},
        {28},
        {},
        {},
        {9, 11, 15},
        {16, 22, 25},
        {},
        {},
        {9, 11, 18},
        {},
        {18},
        {12, 16, 27},
        {19, 26},
        {15, 28},
        {},
        {17, 22},
        {23, 27, 28},
        {23, 26},
        {30},
        {22},
        {},
        {},
        {},
        {29},
        {},
        {29},
        {},
        {},
        {},
        {30},
        {}
};

void flat_graph_test() {
    FlatGraph<31, 30> g = test_flat_graph();

    for (int i = 1; i <= 30; i++) {
        vector<int> adjs(g.adjs(i).begin(), g.adjs(i).end());
        sort(adjs.begin(), adjs.end());
        assert(adjs == ADJS[i]);
    }

    WeightedFlatGraph<31, 30> wg;

    PASSED("Flat Graph");
}