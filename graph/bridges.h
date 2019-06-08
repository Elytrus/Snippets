#pragma once

#include "stdincludes.h"
#include "graph.h"

//begintemplate bridges
//description Tarjan's Bridge Finding algorithm.  Note that only EdgeIdGraphs are accepted
template <int MAX, typename T>
struct Bridges {
    int curOrd = -1, ord[MAX], low[MAX]; bool vis[MAX]; T graph;
    vector<int> bridges;
    void tarjan(T &graph0) {
        graph = graph0;
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
            if (!vis[adj.v]) {
                dfs(adj.v, cur);
                low[cur] = min(low[cur], low[adj.v]);
                if (low[adj.v] > ord[cur])
                    bridges.push_back(adj.i);
            }
            else if (adj.v ^ par)
                low[cur] = min(low[cur], ord[adj.v]);
        }
    }
};
//endtemplate bridges

void BRIDGES_CE_TEST() {
    EdgeIdGraph<10> g; g.init(10, 5);
    Bridges<10, EdgeIdGraph<10>> bd; bd.tarjan(g);
}