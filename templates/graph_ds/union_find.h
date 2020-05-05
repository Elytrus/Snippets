#pragma once
#include "bits/stdc++.h"
using namespace std;

//begintemplate unionfind
//description Union-Find/disjoint sets data structure
struct DSU {
    vector<int> dsu;
    void init(int N) { dsu.resize(N); iota(dsu.begin(), dsu.end(), 0); }
    int rt(int x) { return dsu[x] == x ? x : dsu[x] = rt(dsu[x]); }
    void merge(int x, int y) { dsu[rt(x)] = rt(y); }
    bool same(int x, int y) { return rt(x) == rt(y); }
};
//endtemplate unionfind

