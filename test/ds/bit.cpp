#include "bits/stdc++.h"
#include "../../templates/ds/bit.h"
using namespace std;
using ll = long long;

struct Bit : public BIT<ll> {
    ll Op(ll &a, ll &b) { return a + b; }
    ll Default() { return 0; }
};

int N, Q;
Bit b;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    b.init(N);
    for (int i = 1; i <= N; i++) {
        int x; cin >> x;
        b.update(i, x);
    }

    while (Q--) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t) cout << (b.query(y) - b.query(x)) << '\n';
        else b.update(x + 1, y);
    }

    return 0;
}
