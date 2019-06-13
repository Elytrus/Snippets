#pragma once

#include "stdincludes.h"
#include "graph.h"

//begintemplate dijkstra
//description Dijkstra Algorithm Template (unweighted only).  Distances are initialized to the 0x3f3f3f3f... infinity
template <int MAX, typename T, typename dis_t>
struct Dijkstra {
    dis_t dis[MAX]; priority_queue<ed<dis_t>> nxt;
    void dijkstra(int start, T& graph) {
        vector<int> starts = {start};
        multisource_dijkstra(starts, graph);
    }
    void multisource_dijkstra(vector<int> &starts, T& graph) {
        memset(dis, 0x3f, sizeof dis);
        for (int start : starts) {
            dis[start] = 0;
            nxt.push({start, 0});
        }

        while (!nxt.empty()) {
            auto cur = nxt.top(); nxt.pop();

            if (cur.w > dis[cur.v])
                continue;

            for (auto adj : graph.adjs(cur)) {
                dis_t alt = cur.w + adj.w;
                if (alt < dis[adj.v]) {
                    dis[adj.v] = alt;
                    nxt.push({adj, alt});
                }
            }
        }
    }
};
//endtemplate dijkstra

void dijkstra_test() {
    WeightedGraph<10, int> g;

    g.init(4, 3);
    g.addEdge(1, {2, 2}); g.addEdge(2, {1, 2});
    g.addEdge(1, {3, 5}); g.addEdge(3, {1, 5});
    g.addEdge(2, {3, 2}); g.addEdge(3, {2, 2});

    Dijkstra<10, WeightedGraph<10, int>, int> dijk;
    dijk.dijkstra(1, g);

    assert(dijk.dis[1] == 0);
    assert(dijk.dis[2] == 2);
    assert(dijk.dis[3] == 4);
    assert(dijk.dis[4] == 0x3f3f3f3f);

    PASSED("Dijkstra");
}