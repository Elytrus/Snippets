#include "../helper.h"
#include "../../templates/math/mod.h"
using namespace std;

const int Q = 100000;
const ll OTHER_MOD = 998244353, MMUL = 1000, MQ = 10;

ll spow(ll x, ll y, ll mod = MOD) {
    ll res = 1;
    while (y--) res = (res * x) % mod;
    return res;
}
ll smul(ll x, ll y, ll mod = MOD) {
    ll res = 0;
    while (y--) res = (res + x) % mod;
    return res;
}

int main() {
    init_rng();

    ll lim = min(MOD, OTHER_MOD);

    // fast pow tests
    for (int i = 0; i < Q; i++) {
        ll x = rnd.next(0LL, lim - 1), y = rnd.next(0LL, MMUL);
        check(fpow(x, y) == spow(x, y), "fast pow 1e9+7");
        check(fpow(x, y, OTHER_MOD) == spow(x, y, OTHER_MOD), "fast pow dynamic mod");
    }

    // division tests
    for (int i = 0; i < Q; i++) {
        ll x = rnd.next(0LL, lim - 1);
        check(mmul(x, mdiv(1, x)) == 1, "modular inverse 1e9+7");
        check(mmul(x, mdiv(1, x, OTHER_MOD), OTHER_MOD) == 1, "modular inverse dynamic mod");
    }

    // fmul tests
    for (int i = 0; i < Q; i++) {
        ll x = rnd.next(0LL, lim - 1), y = rnd.next(0LL, MMUL);
        check(fmul(x, y) == smul(x, y), "fast mul 1e9+7");
        check(fmul(x, y, OTHER_MOD) == smul(x, y, OTHER_MOD), "fast mul dynamic mod");
    }

    cout << "OK";

    return 0;
}
