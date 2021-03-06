#pragma once

#include "test/global_includes.h"
#include "graph.h"

//begintemplate bridges
//description Tarjan's Bridge Finding algorithm.  Note that only EdgeIdGraphs are accepted
template <int MAX, typename T>
struct Bridges {
    int curOrd = -1, ord[MAX], low[MAX]; bool vis[MAX]; T &graph;
    vector<int> bridges;
    Bridges(T &graph0) : graph(graph0) {}
    void tarjan() {
        curOrd = -1;
        memset(vis, false, sizeof vis);

        for (int i = 1; i <= graph.n; i++)
            if (!vis[i])
                dfs(i, -1);
    }
    void dfs(int cur, int par) {
        vis[cur] = true;
        ord[cur] = low[cur] = ++curOrd;

        for (auto adj : graph.adjs(cur)) {
            if (adj ^ par) {
                if (!vis[adj.v])
                    dfs(adj.v, cur);
                low[cur] = min(low[cur], low[adj.v]);
                if (low[adj.v] > ord[cur])
                    bridges.push_back(adj.i);
            }
        }
    }
};
//endtemplate bridges

void bridges_test() {
    const int MAX = 21;
    const vector<int> IDS = {0, 1, 5, 10, 12};

    EdgeIdGraph<MAX> g = test_edge_id_graph();
    Bridges<MAX, EdgeIdGraph<MAX>> bd(g);

//    for (int i = 1; i <= 20; i++)
//        cout << "i: " << i << ", v: " << bd.order[i] << ", low: " << bd.low[i] << "\n";
//    for (auto x : bd.bridges) {
//        cout << x << ", ";
//    }
//    cout << "]]\n";

    bd.tarjan();

    sort(bd.bridges.begin(), bd.bridges.end());
    assert(bd.bridges == IDS);

    PASSED("Bridges");
}