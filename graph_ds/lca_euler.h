#pragma once

#include "stdincludes.h"
#include "graph/graph.h"

//begintemplate eulertourlca
//description LCA implementation using the Euler Tour method.  O(N log N) setup and O(1) query
template <int MAX, int LOG, typename T>
struct EulerTourLCA {
    int eulerPtr = 1, levels[MAX], firstIdx[MAX], table[LOG + 1][MAX << 1]; T graph;
    EulerTourLCA() {}
    void dfs(int cur, int par, int level) {
        levels[cur] = level;
        table[0][eulerPtr++] = cur;
        for (auto adj : graph.adjs(cur)) {
            if (adj ^ par) {
                dfs(adj, cur, level + 1);
                table[0][eulerPtr++] = cur;
            }
        }
    }
    inline int levelMin(int a, int b) { return levels[a] < levels[b] ? a : b; }
    void init(T &graph0) {
        graph = graph0;

        // DFSing and setting firstIdx Table
        table[0][0] = -1;
        dfs(1, -1, 0);
        memset(firstIdx, -1, sizeof firstIdx);
        for (int i = 1; i < eulerPtr; i++)
            if (firstIdx[table[0][i]] == -1)
                firstIdx[table[0][i]] = i;

        // Setting sparse table
        for (int i = 1; i <= LOG; i++) {
            int jmp = 1 << (i - 1);
            for (int j = 1, end = eulerPtr - jmp; j < end; ++j)
                table[i][j] = levelMin(table[i - 1][j], table[i - 1][j + jmp]);
        }
    }
    int lca(int a, int b) {
        a = firstIdx[a]; b = firstIdx[b];
        if (a > b) swap(a, b);
        int delta = b - a + 1, bit = 31 - __builtin_clz(delta);
        return levelMin(table[bit][a], table[bit][b - (1 << bit) + 1]);
    }
};
//endtemplate eulertourlca

void EULER_LCA_CE_TEST() {
    Graph<10> g; g.init(10, 5);
    EulerTourLCA<10, 5, Graph<10>> lca;
    lca.init(g);
    lca.lca(1, 2);
}

//TODO: Euler LCA Test