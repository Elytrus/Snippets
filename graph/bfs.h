#pragma once

#include "stdincludes.h"
#include "graph.h"

//begintemplate bfs
//description Breadth-First Search Template (unweighted only)
template <int MAX>
struct BFS {
    int levels[MAX]; queue<int> nxt;
    void bfs(int start, Graph<MAX>& graph) {
        vector<int> starts = {start};
        multisource_bfs(starts, graph);
    }
    void multisource_bfs(vector<int> &starts, Graph<MAX>& graph) {
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

//TODO: Generalize to flat graph
void BFS_CE_TEST() {
    Graph<10> g; g.init(10, 5);
    BFS<10> bfs; bfs.bfs(1, g);
}