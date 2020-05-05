#include "bits/stdc++.h"
#include "../../templates/graph_ds/union_find.h"
using namespace std;

int N, Q;
DSU d;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    d.init(N + 1);

    while (Q--) {
        int t, a, b;
        cin >> t >> a >> b;
        if (t) cout << d.same(a, b) << '\n';
        else d.merge(a, b);
    }

    return 0;
}
