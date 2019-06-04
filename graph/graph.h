#pragma once

#include "../stdincludes.h"

//begintemplate weight
//description basic graph weight template for dijkstra and related
template <typename T>
struct ed {
    int v; T w;
    bool operator<(const ed &o) const { return w > o.w; }
    ostream& operator<<(ostream& out) const { out << "(v=" << v << ", w=" << w << ")"; return out; }
};
//endtemplate weight

//begintemplate graph
//description basic unweighted graph template
template <int MAX, bool UNDIRECTED>
struct Graph {
    int n, m, __ba, __bb; vector<int> matrix[MAX];
    Graph() {}
    void init(int &n0, int &m0) { n = n0; m = m0; }
    inline void addEdge(int &a, int &b) { matrix[a].push_back(b); }
    void input() {
        for (int i = 0; i < m; i++) {
            cin >> __ba >> __bb;
            addEdge(__ba, __bb);
            if (UNDIRECTED)
                addEdge(__bb, __ba);
        }
    }
    vector<int>& adj(int x) { return matrix[x]; }
};
//endtemplate graph

//begintemplate weightedgraph
//description basic weighted graph template
template <int MAX, bool UNDIRECTED, typename T = int>
struct WeightedGraph {
    int n, m, __ba, __bb; vector<ed<T>> matrix[MAX]; T __bc;
    WeightedGraph() {}
    void init(int &n0, int &m0) { n = n0; m = m0; }
    inline void addEdge(int &a, int &b, T &c) { matrix[a].push_back({b, c}); }
    void input() {
        for (int i = 0; i < m; i++) {
            cin >> __ba >> __bb >> __bc;
            addEdge(__ba, __bb, __bc);
            if (UNDIRECTED)
                addEdge(__bb, __ba, __bc);
        }
    }
    vector<ed<T>>& adj(int x) { return matrix[x]; }
};
//endtemplate weightedgraph