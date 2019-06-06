#pragma once

#include "stdincludes.h"
#include "graph.h"

//begintemplate articulationpoints
//description Tarjan's Articulation Points algorithm
template <int MAX, typename T>
struct ArticulationPoints {
    int curOrd = -1, ord[MAX], low[MAX]; bool vis[MAX]; T graph;
    vector<int> points;
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

        int totBranches = 0;
        bool flag = false;
        for (int adj : graph.adjs(cur)) {
            if (!vis[adj]) {
                dfs(adj, cur);
                flag |= low[adj] >= ord[cur];
                low[cur] = min(low[cur], low[adj]);
                totBranches++;
            }
            else if (adj ^ par)
                low[cur] = min(low[cur], ord[adj]);
        }

        // is articulation point
        if (par == -1) {
            if (totBranches > 1)
                points.push_back(cur);
        }
        else if (flag)
            points.push_back(cur);
    }
};
//endtemplate articulationpoints