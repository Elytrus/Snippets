#include "stdincludes.h"

#include "ds/all.h"
#include "graph/all.h"
#include "graph_ds/all.h"
#include "math/all.h"
#include "string_ds/substr_hash.h"

FastPow<ll, 1000000007> test;

int main() {
    cout << test.fastPow(2, 4) << endl;
    cout << test.fastPow(3, 1) << endl;
    cout << test.fastPow(3, 3) << endl;
    cout << test.fastPow(5, 3) << endl;
    cout << test.fastPow(1555, 0) << endl;

    return 0;
}