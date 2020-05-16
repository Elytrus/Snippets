#include "../helper.h"
#include "../../templates/math/choose.h"
using namespace std;

const int Q = 1000000;
const ll B = 20, OTHER_MOD = 998244353;

ll slow_choose(ll N, ll K, ll mod = MOD) {
    ll b = 1 << N, res = 0;
    for (int i = 0; i < b; i++)
        res += __builtin_popcount(i) == K;
    return res;
}
ll slow_permute(ll N, ll K, ll mod = MOD) {
    return mmul(slow_choose(N, K, mod), fact[K], mod);
}

int main() {
    init_rng();

    init_nchoosek(B, OTHER_MOD);
    for (int i = 0; i <= B; i++) {
        for (int j = 0; j <= i; j++) {
            check(choose(i, j, OTHER_MOD) == slow_choose(i, j, OTHER_MOD), "choose dynamic mod (" + to_string(i) + ", " + to_string(j) + ")");
            check(permute(i, j, OTHER_MOD) == slow_permute(i, j, OTHER_MOD), "permute dynamic mod (" + to_string(i) + ", " + to_string(j) + ")");
        }
    }

    cout << "OK";

    return 0;
}
