#include "bits/stdc++.h"
#include "../../templates/ds/segment_tree.h"
using namespace std;
using ll = long long;

struct Seg : public SegmentTree<ll> {
    void setVal(ll &a, ll b) { a += b; }
    ll merge(ll a, ll b) { return a + b; }
    ll getDefault() { return 0LL; }
};

int N, Q;
Seg seg;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    seg.init(N);
    for (int i = 1; i <= N; i++) {
        int x; cin >> x;
        seg.update(i, x);
    }

    while (Q--) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t) cout << seg.query(x + 1, y) << '\n';
        else seg.update(x + 1, y);
    }

    return 0;
}
