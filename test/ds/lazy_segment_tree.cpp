#include "bits/stdc++.h"
#include "../../templates/math/mod.h"
#include "../../templates/ds/segment_tree.h"
using namespace std;

using pll = pair<ll, ll>;
const ll MOD2 = 998244353;

pll comb(pll f, pll g) {
    return {mmul(f.first, g.first, MOD2), madd(mmul(g.first, f.second, MOD2), g.second, MOD2)};
}
ll apply(pll f, ll x) {
    return madd(mmul(f.first, x, MOD2), f.second, MOD2);
}

struct Seg : public LazySegmentTree<ll, pll> {
    ll merge(ll a, ll b) { return madd(a, b, MOD2); }
    ll getDefault() { return 0LL; }
    pll getLazyDefault() { return {1LL, 0LL}; }
    void mergeLazy(pll &to, pll &from) { to = comb(to, from); }
    void applyLazy(ll &to, pll &from, int l, int r) {
        to = apply({from.first, mmul(from.second, r - l + 1, MOD2)}, to);
    }
};

const int MN = 5e5 + 1;
int N, Q;
ll val[MN];
Seg seg;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++) {
        cin >> val[i];
    }
    seg.init(N, val);

    while (Q--) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t) cout << seg.query(x + 1, y) << '\n';
        else {
            ll b, c;
            cin >> b >> c;
            seg.update(x + 1, y, {b, c});
        }
    }

    return 0;
}
