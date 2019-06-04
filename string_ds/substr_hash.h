#pragma once

#include "../stdincludes.h"

//begintemplate substringhash
//description O(1) Rolling hashes on a substring with O(N) setup.  This DS also has the ability to preform the same hash on any arbitrary string in O(N) time
template <int MAX, int PRIME = 113, char A = 'A'>
struct SubstrHash {
    int n; string s;
    ll pows[MAX], pfxHash[MAX];
    inline int charVal(char c) { return c - A; }
    SubstrHash() {}
    void init(string &s0) {
        n = s0.length(); s = s0;
        pows[0] = 1; pfxHash[0] = 0;
        for (int i = 1; i <= n; i++) {
            pows[i] = (pows[i - 1] * PRIME);
            pfxHash[i] = pfxHash[i - 1] * PRIME + charVal(s[i - 1]);
        }
    }
    ll hashSubstr(int l, int r) { return pfxHash[r] - pfxHash[l - 1] * pows[r - l + 1]; }
    ll hashOtherStr(string &s) { // Can also hash any other string using the same prime value
        ll hash = charVal(s[0]);
        for (int i = 1, sz = s.length(); i < sz; i++)
            hash = hash * PRIME + charVal(s[i]);
        return hash;
    }
};
//endtemplate substringhash