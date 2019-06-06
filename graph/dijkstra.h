#pragma once

#include "stdincludes.h"
#include "graph.h"

//begintemplate dijkstra
//description Dijkstra Algorithm Template (unweighted only).  Distances are initialized to the 0x3f3f3f3f... infinity
template <int MAX, typename DIS_TYPE>
struct Dijkstra {
    DIS_TYPE dis[MAX]; priority_queue<ed<DIS_TYPE>> nxt;
    void dijkstra(int start, WeightedGraph<MAX, DIS_TYPE>& graph) {
        vector<int> starts = {start};
        multisource_dijkstra(starts, graph);
    }
    void multisource_dijkstra(vector<int> &starts, WeightedGraph<MAX, DIS_TYPE>& graph) {
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
                DIS_TYPE alt = cur.w + adj.w;
                if (alt < dis[adj.v]) {
                    dis[adj.v] = alt;
                    nxt.push({adj, alt});
                }
            }
        }
    }
};
//endtemplate dijkstra

//TODO: Generalize to flat graph
void DIJK_CE_TEST() {
    WeightedGraph<10, int> g; g.init(10, 5);
    Dijkstra<10, int> dijk;
    dijk.dijkstra(1, g);
}