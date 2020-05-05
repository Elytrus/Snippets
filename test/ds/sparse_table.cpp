#include "bits/stdc++.h"
#include "../../templates/ds/sparse_table.h"
using namespace std;
using ll = long long;

struct RMQ : public SparseTable<int> {
    int Op(int &a, int &b) { return min(a, b); }
};

int N, Q, arr[500001];
RMQ q;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    q.init(N, arr);

    while (Q--) {
        int l, r;
        cin >> l >> r;
        cout << q.query(l + 1, r) << '\n';
    }

    return 0;
}
