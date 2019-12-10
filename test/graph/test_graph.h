#pragma once

#include "graph/graph.h"

Graph<21> test_graph() {
    Graph<21> g;
    g.init(20, 15);

    g.addEdge(1, 2); g.addEdge(2, 1);
    g.addEdge(10, 17); g.addEdge(17, 10);
    g.addEdge(1, 13); g.addEdge(13, 1);
    g.addEdge(5, 7); g.addEdge(7, 5);
    g.addEdge(3, 11); g.addEdge(11, 3);
    g.addEdge(7, 18); g.addEdge(18, 7);
    g.addEdge(11, 18); g.addEdge(18, 11);
    g.addEdge(1, 5); g.addEdge(5, 1);
    g.addEdge(3, 18); g.addEdge(18, 3);
    g.addEdge(1, 19); g.addEdge(19, 1);
    g.addEdge(3, 9); g.addEdge(9, 3);
    g.addEdge(1, 8); g.addEdge(8, 1);
    g.addEdge(12, 16); g.addEdge(16, 12);
    g.addEdge(13, 19); g.addEdge(19, 13);
    g.addEdge(7, 8); g.addEdge(8, 7);

    return g;
}

EdgeIdGraph<21> test_edge_id_graph() {
    EdgeIdGraph<21> g;
    g.init(20, 15);

    g.addEdge(1, 2, 0); g.addEdge(2, 1, 0);
    g.addEdge(10, 17, 1); g.addEdge(17, 10, 1);
    g.addEdge(1, 13, 2); g.addEdge(13, 1, 2);
    g.addEdge(5, 7, 3); g.addEdge(7, 5, 3);
    g.addEdge(3, 11, 4); g.addEdge(11, 3, 4);
    g.addEdge(7, 18, 5); g.addEdge(18, 7, 5);
    g.addEdge(11, 18, 6); g.addEdge(18, 11, 6);
    g.addEdge(1, 5, 7); g.addEdge(5, 1, 7);
    g.addEdge(3, 18, 8); g.addEdge(18, 3, 8);
    g.addEdge(1, 19, 9); g.addEdge(19, 1, 9);
    g.addEdge(3, 9, 10); g.addEdge(9, 3, 10);
    g.addEdge(1, 8, 11); g.addEdge(8, 1, 11);
    g.addEdge(12, 16, 12); g.addEdge(16, 12, 12);
    g.addEdge(13, 19, 13); g.addEdge(19, 13, 13);
    g.addEdge(7, 8, 14); g.addEdge(8, 7, 14);

    return g;
}

Graph<21> test_directed_cyclic_graph() {
    Graph<21> g;
    g.init(20, 21);

    g.addEdge(11, 3);
    g.addEdge(17, 20);
    g.addEdge(1, 6);
    g.addEdge(12, 16);
    g.addEdge(15, 19);
    g.addEdge(6, 7);
    g.addEdge(7, 15);
    g.addEdge(13, 16);
    g.addEdge(12, 17);
    g.addEdge(7, 10);
    g.addEdge(9, 20);
    g.addEdge(4, 14);
    g.addEdge(7, 18);
    g.addEdge(3, 19);
    g.addEdge(4, 11);
    g.addEdge(2, 17);
    g.addEdge(15, 12);
    g.addEdge(20, 6);
    g.addEdge(16, 20);
    g.addEdge(2, 15);
    g.addEdge(3, 4);

    return g;
}

Graph<21> test_DAG() {
    Graph<21> g;
    g.init(20, 20);

    g.addEdge(4, 7);
    g.addEdge(4, 8);
    g.addEdge(15, 19);
    g.addEdge(3, 7);
    g.addEdge(6, 14);
    g.addEdge(2, 19);
    g.addEdge(5, 18);
    g.addEdge(8, 20);
    g.addEdge(1, 10);
    g.addEdge(7, 14);
    g.addEdge(2, 6);
    g.addEdge(3, 13);
    g.addEdge(4, 16);
    g.addEdge(6, 12);
    g.addEdge(14, 20);
    g.addEdge(2, 14);
    g.addEdge(15, 17);
    g.addEdge(6, 19);
    g.addEdge(4, 6);
    g.addEdge(6, 8);

    return g;
}
