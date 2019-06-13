#pragma once

#include "../stdincludes.h"

//begintemplate weight
//description basic graph weight template for dijkstra and related
template <typename T>
struct ed {
    int v; T w;
    operator int() const { return v; } // Returns the adjacent node
    bool operator<(const ed &o) const { return w > o.w; } // Reversed for dijkstra
    ostream& operator<<(ostream& out) const { out << "(v=" << v << ", w=" << w << ")"; return out; }
};
template <typename T> istream& operator>>(istream& in, ed<T> &o) { in >> o.v >> o.w; return in; }
//endtemplate weight

//begintemplate graph
//description basic (unweighted) graph template
template <int MAX>
struct Graph {
    int n, m, __ba, __bb; vector<int> matrix[MAX];
    void init(int n0, int m0) { n = n0; m = m0; }
    inline void addEdge(int a, int b) { matrix[a].push_back(b); }
    inline auto& adjs(int x) { return matrix[x]; }
    Graph& operator=(const Graph o) { n = o.n; m = o.m; copy(o.matrix, o.matrix + n + 1, matrix); return *this; }
    void input(bool undirected) { // Reads a graph's edges from stdin
        for (int i = 0; i < m; i++) {
            cin >> __ba >> __bb;
            addEdge(__ba, __bb);
            if (undirected) addEdge(__bb, __ba);
        }
    }
    auto transpose() { // Transposes the graph into its reversed form
        Graph<MAX> ret; ret.init(n, m);
        for (int i = 1; i <= n; i++)
            for (auto adj : adjs(i))
                ret.addEdge(adj, i);
        return ret;
    }
};
//endtemplate graph

//begintemplate weightedgraph
template <int MAX, typename T = int>
struct WeightedGraph {
    int n, m, __ba; ed<T> __bb; vector<ed<T>> matrix[MAX];
    void init(int n0, int m0) { n = n0; m = m0; }
    inline void addEdge(int a, ed<T> b) { matrix[a].push_back(b); }
    inline auto& adjs(int x) { return matrix[x]; }
    WeightedGraph& operator=(const WeightedGraph o) { n = o.n; m = o.m; copy(o.matrix, o.matrix + n + 1, matrix); return *this; }
    void input(bool undirected) {
        for (int i = 0; i < m; i++) {
            cin >> __ba >> __bb;
            addEdge(__ba, __bb);
            if (undirected) addEdge(__bb.v, {__ba, __bb.w});
        }
    }
    auto transpose() { // Transposes the graph into its reversed form
        WeightedGraph<MAX, T> ret; ret.init(n, m);
        for (int i = 1; i <= n; i++)
            for (auto adj : adjs(i))
                ret.addEdge(adj.v, {i, adj.w});
        return ret;
    }
};
//endtemplate weightedgraph

//begintemplate edgeidgraph
//description Unweighted graph with Edge IDs attached
struct edi {
    int i, v;
    operator int() const { return v; } // Returns the adjacent node
};
template <int MAX>
struct EdgeIdGraph {
    int n, m, __ba, __bb; vector<edi> matrix[MAX];
    void init(int n0, int m0) { n = n0; m = m0; }
    inline void addEdge(int a, int b, int i) { matrix[a].push_back({i, b}); }
    inline auto& adjs(int x) { return matrix[x]; }
    EdgeIdGraph& operator=(const EdgeIdGraph o) { n = o.n; m = o.m; copy(o.matrix, o.matrix + n + 1, matrix); return *this; }
    void input(bool undirected) { // Reads a graph's edges from stdin
        for (int i = 0; i < m; i++) {
            cin >> __ba >> __bb;
            addEdge(__ba, __bb, i);
            if (undirected) addEdge(__bb, __ba, i);
        }
    }
    auto transpose() { // Transposes the graph into its reversed form
        EdgeIdGraph<MAX> ret; ret.init(n, m);
        for (int i = 1; i <= n; i++)
            for (auto adj : adjs(i))
                ret.addEdge(adj.v, i, adj.i);
        return ret;
    }
};
//endtemplate edgeidgraph