#pragma once

#include "stdincludes.h"
#include "graph.h"
#include "test/test_graph.h"

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
    void sort(T &graph0) {
        graph = graph0.transpose();
        memset(vis, false, sizeof vis);
        for (int i = 1; i <= graph.n; i++)
            if (!vis[i]) dfs(i);
    }
};
//endtemplate topologicalsort

template <typename T, typename G> void check_sorting(G g, T topo) {
    bool vis[21]; memset(vis, false, sizeof vis);
    int inDeg[21]; memset(inDeg, 0, sizeof inDeg);
    for (int i = 1; i < 21; i++)
        for (int adj : g.adjs(i))
            inDeg[adj]++;
    for (int i = 1; i < 21; i++)
        vis[i] = true;

    for (int i = 0, sz = topo.order.size(); i < sz; i++) {
        assert(vis[topo.order[i]]);
        for (int adj : g.adjs(topo.order[i]))
            vis[adj] = true;
    }
}

void topological_sort_test() {
    Graph<21> g = test_DAG();
    TopologicalSort<21, Graph<21>> topo;
    topo.sort(g);

    check_sorting(g, topo);

    PASSED("Topological Sort");
}