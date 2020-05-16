#include "../helper.h"
#include "../../templates/ds/fast_clear_array.h"
using namespace std;

const int Q = 300000;
const int N = 100, WAIT = 200;

struct FastClearArrayInt : public FastClearArray<int> {
    int getDefault() { return 0; }
};

vector<int> fca_check;
FastClearArrayInt fca;

int main() {
    init_rng();

    fca_check = rand_vec<int>(N);
    fca.init(N);
    for (int i = 0; i < N; i++)
        fca[i] = fca_check[i];

    for (int _ = 0; _ < Q; _++) {
        if (_ % WAIT == 0) {
            fca_check.assign(N, 0);
            fca.reset();
        }
        else {
            int ind = rnd.next(0, N - 1), val = rnd.next(0, int(1e9));
            fca_check[ind] = val;
            fca[ind] = val;
        }

        // Check
        for (int i = 0; i < N; i++) {
            if (fca_check[i] != fca[i]) {
                cout << "incorrect";
                return 0;
            }
        }
    }

    cout << "OK";

    return 0;
}
