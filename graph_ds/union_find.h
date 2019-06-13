#pragma once
#include "../stdincludes.h"

//begintemplate unionfind
//description Union-Find/disjoint sets data structure
template <int MAX>
struct UnionFind{
    int n, set[MAX];
    void init(int n0) { n = n0; iota(set, set + n + 1); }
    int root(int v) { return set[v] == v ? v : set[v] = root(set[v]); }
    void merge(int v, int w) { set[root(v)] = root(w); }
    bool intersect(int v, int w) { return root(v) == root(w); }
};
//endtemplate unionfind

//TODO: Union Find Test