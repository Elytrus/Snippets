#pragma once

#include "stdincludes.h"
#include "graph.h"

//begintemplate bfs
//description Breadth-First Search Template (unweighted only)
template <int MAX, typename T>
struct BFS {
    int levels[MAX]; queue<int> nxt;
    void bfs(int start, T& graph) {
        vector<int> starts = {start};
        multisource_bfs(starts, graph);
    }
    void multisource_bfs(vector<int> &starts, T& graph) {
        memset(levels, -1, sizeof levels);
        for (int start : starts) {
            levels[start] = 0;
            nxt.push(start);
        }

        while (!nxt.empty()) {
            int cur = nxt.front(), level = levels[cur]; nxt.pop();

            for (int adj : graph.adjs(cur)) {
                if (levels[adj] == -1) {
                    levels[adj] = level + 1;
                    nxt.push(adj);
                }
            }
        }
    }
};
//endtemplate bfs

//begintemplate weightedbfs
//description Breadth-First Search Template (weighted only)
template <int MAX, typename T, typename WEIGHT_T>
struct WeightedBFS {
    WEIGHT_T levels[MAX]; queue<int> nxt;
    void bfs(int start, T& graph) {
        vector<int> starts = {start};
        multisource_bfs(starts, graph);
    }
    void multisource_bfs(vector<int> &starts, T& graph) {
        memset(levels, -1, sizeof levels);
        for (int start : starts) {
            levels[start] = 0;
            nxt.push(start);
        }

        while (!nxt.empty()) {
            int cur = nxt.front(); WEIGHT_T level = levels[cur]; nxt.pop();

            for (auto adj : graph.adjs(cur)) {
                if (levels[adj.v] == -1) {
                    levels[adj.v] = level + adj.w;
                    nxt.push(adj);
                }
            }
        }
    }
};
//endtemplate weightedbfs

void BFS_CE_TEST() {
    Graph<10> g; g.init(10, 5);
    BFS<10, Graph<10>> bfs; bfs.bfs(1, g);

    WeightedGraph<10, int> wg; wg.init(10, 5);
    WeightedBFS<10, WeightedGraph<10, int>, int> bfs2; bfs2.bfs(1, wg);
}