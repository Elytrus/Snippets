#pragma once

#include "stdincludes.h"
#include "graph/graph.h"

//begintemplate binaryliftlca
//description LCA implementation using the Binary Lift method.  O(N log N) setup and O(log N) query
template <int MAX, int LOG, typename T>
struct BinaryLiftLCA {
    int pars[LOG][MAX], levels[MAX]; T graph;
    BinaryLiftLCA() {}
    void dfs(int cur, int par, int level) {
        levels[cur] = level;
        pars[0][cur] = par;
        for (auto adj : graph.adjs(cur))
            if (adj ^ par)
                dfs(adj, cur, level + 1);
    }
    void init(T &graph0) {
        graph = graph0;

        // Setting sparse table
        dfs(1, -1, 0);
        for (int i = 1; i < LOG; i++) {
            for (int j = 0; j <= graph.n; ++j)
                pars[i][j] = pars[i - 1][j] == -1 ? -1 : pars[i - 1][pars[i - 1][j]];
        }
    }
    int lca(int a, int b) {
        if (levels[a] > levels[b]) swap(a, b);
        int delta = levels[b] - levels[a];
        for (int i = LOG - 1; i >= 0; i--)
            if ((delta >> i) & 1)
                b = pars[i][b];
        if (a == b) return a;
        for (int i = LOG - 1; i >= 0; i--) {
            if (pars[i][a] != pars[i][b]) {
                a = pars[i][a];
                b = pars[i][b];
            }
        }
        return pars[0][a];
    }
};
//endtemplate binaryliftlca

void BINARY_LIFT_LCA_CE_TEST() {
    Graph<10> g; g.init(10, 5);
    BinaryLiftLCA<10, 5, Graph<10>> lca;
    lca.init(g);
    lca.lca(1, 2);
}