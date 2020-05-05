#include "bits/stdc++.h"
#include "../../templates/ds/prefix_sum_array.h"
using namespace std;
using ll = long long;

struct SumPSA : public PSA<ll> {
    ll Op(ll &a, ll &b) { return a + b; }
    ll Invop(ll &a, ll &b) { return a - b; }
};

int N, Q;
ll arr[500001];
SumPSA p;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    p.init(arr, arr + N + 1);
    p.build();

    while (Q--) {
        int l, r;
        cin >> l >> r;
        cout << p.query(l + 1, r) << '\n';
    }

    return 0;
}
