#pragma once

#include "stdincludes.h"
#include "graph.h"

//begintemplate topologicalsortnt
//description Topological Sort algorithm but no transposition is required.  This will fail on any graph with cycles
template <int MAX, typename T>
struct TopologicalSortNT {
    int &n, inDeg[MAX]; vector<int> order; queue<int> nxt; T &graph;
    TopologicalSortNT(T &graph0) : n(graph0.n), graph(graph0) {}
    void sort() {
        for (int i = 1; i <= n; i++)
            for (int adj : graph.adjs(i))
                inDeg[adj]++;
        for (int i = 1; i <= n; i++)
            if (inDeg[i] == 0)
                nxt.push(i);
        while (!nxt.empty()) {
            int cur = nxt.front(); nxt.pop();
            order.push_back(cur);
            for (int adj : graph.adjs(cur)) {
                inDeg[adj]--;
                if (!inDeg[adj])
                    nxt.push(adj);
            }
        }
    }
};
//endtemplate topologicalsortnt