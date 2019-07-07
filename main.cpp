#include "stdincludes.h"

#include "ds/all.h"
#include "graph/all.h"
#include "graph_ds/all.h"
#include "math/all.h"
#include "string_ds/all.h"

#define CATEGORY(x) cout << "-- Beginning Category: " << x << "\n"

int main() {
    // Test ds
    CATEGORY("Data Structures");
    fca_test();

    // Test Math
    CATEGORY("Math");
    fast_pow_test();
    fast_mul_test();

    // Test string_ds
    CATEGORY("String Data Structures");
    trie_test();
    substr_hash_test();

    // Test Graph
    CATEGORY("Graph Algorithms");
    dijkstra_test();
    articulation_points_test();
    bridges_test();
    strongly_connected_components_test();
    topological_sort_test();
    flat_graph_test();

    return 0;
}