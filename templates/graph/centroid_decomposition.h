#pragma once

#include "graph.h"
#include "test/global_includes.h"

//begintemplate centroiddecomp
//description Centroid Decomposition Template with fill-ins
template <int MAX, typename T>
struct CentroidDecomposition {
    int sz[MAX]; bool blocked[MAX]; T& graph;
    CentroidDecomposition(T& graph0) : graph(graph0) { memset(blocked, false, sizeof blocked); }
    int gsz(int cur, int par) {
        sz[cur] = 1;
        for (int adj : graph.adjs(cur))
            if ((adj ^ par) && !blocked[adj])
                sz[cur] += gsz(adj, cur);
        return sz[cur];
    }
    int gcentroid(int cur, int par, int half) {
        for (int adj : graph.adjs(cur))
            if ((adj ^ par) && !blocked[adj] && sz[adj] > half)
                return gcentroid(adj, cur, half);
        return cur;
    }
    void dfs() { assert(("Not implemented yet!", 0)); }
    void decomp(int cur = 1) {
        gsz(cur, -1);
        if (sz[cur] == 1) return;

        int centroid = gcentroid(cur, -1, sz[cur] >> 1);
        for (int adj : graph.adjs(centroid)) {
            if (!blocked[adj]) {
                assert(("Not implemented yet!", 0)); // Implement subtree dfs
            }
        }

        blocked[centroid] = true;
        for (int adj : graph.adjs(centroid))
            if (!blocked[adj])
                decomp(adj);
    }
};
//endtemplate centroiddecomp
