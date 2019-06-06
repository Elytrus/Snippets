#pragma once

#include "stdincludes.h"
#include "graph.h"

//begintemplate scc
//description Tarjan's Strongly Connected Components algorithm
template <int MAX, typename T>
struct SCC {
    int curOrd = -1, ord[MAX], low[MAX]; stack<int> stk; bool inStk[MAX], vis[MAX]; T graph;
    vector<vector<int>> comps;
    void tarjan(T &graph0) {
        comps.clear();
        graph = graph0;
        curOrd = -1;
        memset(inStk, false, sizeof inStk);
        memset(vis, false, sizeof vis);

        for (int i = 1; i <= graph.n; i++)
            if (!vis[i])
                dfs(i);
    }
    void dfs(int cur) {
        stk.push(cur);
        vis[cur] = inStk[cur] = true;
        ord[cur] = low[cur] = ++curOrd;

        for (int adj : graph.adjs(cur)) {
            if (!vis[adj]) {
                dfs(adj);
                low[cur] = min(low[cur], low[adj]);
            }
            else if (inStk[adj])
                low[cur] = min(low[cur], ord[adj]);
        }

        // If root of SCC
        if (low[cur] == ord[cur]) {
            int st = -1, v = -1;
            vector<int> comp;
            do {
                v = stk.top(); stk.pop(); inStk[v] = false;
                comp.push_back(v);
            }
            while (v != cur);
            comps.push_back(comp);
        }
    }
};
//endtemplate scc

void SCC_CE_TEST() {
    Graph<10> g; g.init(10, 5);
    WeightedGraph<10, int> g2; g2.init(10, 5);

    SCC<10, Graph<10>> scc; scc.tarjan(g);
    SCC<10, WeightedGraph<10, int>> scc2; scc2.tarjan(g2);
}