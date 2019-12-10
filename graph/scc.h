#pragma once

#include "test/global_includes.h"
#include "graph.h"
#include "test/graph/test_graph.h"

//begintemplate scc
//description Tarjan's Strongly Connected Components algorithm
template <int MAX, typename T>
struct SCC {
    int curOrd = -1, ord[MAX], low[MAX]; stack<int> stk; bool inStk[MAX], vis[MAX]; T &graph;
    vector<vector<int>> comps;
    SCC(T &graph0) : graph(graph0) {}
    void tarjan() {
        comps.clear();
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

bool cmp(const vector<int> &a, const vector<int> &b) {
    return a[0] < b[0];
}

const vector<vector<int>> COMPS = {
        {1},
        {2},
        {3, 4, 11},
        {5},
        {6, 7, 12, 15, 16, 17, 20},
        {8},
        {9},
        {10},
        {13},
        {14},
        {18},
        {19}
};

void strongly_connected_components_test() {
    Graph<21> g = test_directed_cyclic_graph();
//    Graph<21> g = test_DAG();

    SCC<21, Graph<21>> scc(g);
    scc.tarjan();

    for (auto it = scc.comps.begin(); it != scc.comps.end(); it++)
        sort(it->begin(), it->end());
    sort(scc.comps.begin(), scc.comps.end(), cmp);

//    for (auto comp : scc.comps) {
//        cout << "comp: [";
//        for (auto x : comp) {
//            cout << x << ", ";
//        }
//        cout << "]\n";
//    }

    assert(scc.comps == COMPS);

    PASSED("Strongly Connected Components");
}