#pragma once

#include "stdincludes.h"
#include "graph.h"

//begintemplate topologicalsort
//description Topological Sort Algorithm
template <int MAX, typename T>
struct TopologicalSort {
    vector<int> order; T graph; bool vis[MAX];
    void dfs(int cur) {
        vis[cur] = true;
        for (auto adj : graph.adjs(cur))
            if (!vis[adj]) dfs(adj);
        order.push_back(cur);
    }
    void sort(T graph0) {
        graph = graph0.transpose();
        memset(vis, false, sizeof vis);
        for (int i = 1; i <= graph.n; i++)
            if (!vis[i]) dfs(i);
    }
};
//endtemplate topologicalsort

void TOPOSORT_CE_TEST() {
    WeightedGraph<10, int> wg; wg.init(10, 5);
    Graph<10> g; g.init(10, 5);
    TopologicalSort<10, WeightedGraph<10, int>> top;
    TopologicalSort<10, Graph<10>> top2;
    top.sort(wg);
    top2.sort(g);
}