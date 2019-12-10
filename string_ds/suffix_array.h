#pragma once

#include "test/global_includes.h"

// Link: https://www.hackerearth.com/practice/data-structures/advanced-data-structures/suffix-arrays/tutorial/

//begintemplate suffixarray
//description Suffix Array implementation in O(N log^2 N)
struct suffix {
    int idx, fst, snd;
    bool operator<(const suffix &o) const { return fst == o.fst ? snd < o.snd : fst < o.fst; }
};
template <size_t MAX, char A = 'a'>
struct SuffixArray {
    static const int LOG = log2(MAX) + 2;
    int &n; string &s; suffix sfx[MAX]; int rnk[LOG][MAX];
    SuffixArray(int &n0, string &s0) : n(n0), s(s0) {}
    void init() {
        for (int i = 0; i < n; i++)
            rnk[0][i] = s[i] - A;
        for (int i = 1; (1 << (i - 1)) < n; i++) {
            int jmp = 1 << (i - 1);
            for (int j = 0; j < n; j++)
                sfx[j] = {j, rnk[i - 1][j], j + jmp < n ? rnk[i - 1][j + jmp] : -1};
            sort(sfx, sfx + n);
            for (int j = 0; j < n; j++)
                rnk[i][sfx[j].idx] = (j > 0 && sfx[j].fst == sfx[j - 1].fst && sfx[j].snd == sfx[j - 1].snd ? rnk[i][sfx[j - 1].idx] : j);
        }
    }
    inline int get(int id) { return sfx[id].idx; }
    inline char ch(int id, int chId) { return s[sfx[id].idx + chId]; }
    void print() { for (int i = 0; i < n; i++) cout << i << ": " << s.substr(get(i)) << "\n"; }
    int bsearch(int l, int r, int chId, char find) { // l, r, and chId are 1-indexed.  Acts like C++ lower_bound
        l--; l--; chId--;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (ch(mid, chId) >= find) r = mid; else l = mid;
        } return r + 1;
    }
};
//endtemplate suffixarray

//TODO: Suffix array tests