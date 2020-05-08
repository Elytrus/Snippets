#include "test/global_includes.h";
template <typename T> using vec = vector<T>;

//begintemplate matrix
//description Matrix Multiplication (NbyN) in O(N^3) and Matrix Exponentiation (NbyN) * K in O(N^3logK)
using Mat = vec<vec<ll>>;
const ll MOD = 1e9 + 7;

inline Mat matrix(int r, int c) {
    Mat ret; ret.reserve(r);
    for (int i = 0; i < r; i++)
        ret.pb(vector<ll>(c));
    return ret;
}

Mat mul(Mat &a, Mat &b) {
    int N = a.size(), M = b.size(), K = b[0].size();
    assert(a[0].size() == (size_t)M); // NxM by MxK
    Mat ret = matrix(N, K);
    for (int i = 0; i < N; i++) 
        for (int j = 0; j < K; j++)
            for (int k = 0; k < M; k++)
                ret[i][j] = (ret[i][j] + a[i][k] * b[k][j]) % MOD;
    return ret;
}

Mat exp(Mat a, ull pow) {
    int N = a.size();
    assert((size_t)N == a[0].size()); // NxN
    Mat ret = matrix(N, N); // Make identity matrix
    for (int i = 0; i < N; i++)
        ret[i][i] = 1;
    for (ull bit = 0; bit < 64; bit++) {
        if ((pow >> bit) & 1)
            ret = mul(ret, a);
        a = mul(a, a);
    }
    return ret;
}
//endtemplate matrix
