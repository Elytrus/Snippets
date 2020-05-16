#include "test/helper.h"
#include "templates/math/mod.h"
using namespace std;

const int Q = 5000000;
const ll OTHER_MOD =

ll spow(ll x, ll y) {
    ll res = 1;
    while (y--) res = (res * x) % MOD;
    return res;
}
ll spow(ll x, ll y, ll MOD) {
    ll res = 1;
    while (y--) res = (res * x) % MOD;
    return res;
}

int main() {
    init_rng();

    for (int i = 0; i < Q; i++) {

    }

    cout << "OK";

    return 0;
}
