#pragma once

#include "stdincludes.h"
#include "graph.h"
#include "topological_sort_no_transpose.h"
#include "test/test_graph.h"

/**
 * Note that for this template, the graph is passed into the sort function instead of as a constructor parameter
 * because the graph is transposed before sorting
 * @tparam MAX
 * @tparam T
 */

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
    void sort(T &graph0, T (*transposeFun)(T&)) {
        graph = transposeFun(graph0);
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
    topo.sort(g, transpose);

    TopologicalSortNT<21, Graph<21>> topo2(g);
    topo2.sort();

    check_sorting(g, topo);
    check_sorting(g, topo2);

    PASSED("Topological Sort");
}