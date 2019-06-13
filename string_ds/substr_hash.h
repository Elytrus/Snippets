#pragma once

#include "../stdincludes.h"

//begintemplate substringhash
//description O(1) Rolling hashes on a substring with O(N) setup.  This DS also has the ability to preform the same hash on any arbitrary string in O(N) time.  Note that MAX has to be at least 1 over the size of N
template <int MAX, int PRIME = 113, char A = 'A'>
struct SubstrHash {
    int n; string s;
    ll pows[MAX], pfxHash[MAX];
    inline int charVal(char c) { return c - A; }
    SubstrHash() {}
    void init(string &s0) {
        n = s0.length(); s = s0; assert(n < MAX);
        pows[0] = 1; pfxHash[0] = 0;
        for (int i = 1; i <= n; i++) {
            pows[i] = pows[i - 1] * PRIME;
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

void substr_hash_test() {
    SubstrHash<21, 113, 'a'> hash;
    string s = "hellohelloworldworld"; hash.init(s);

//    for (int i = 0; i <= 20; i++)
//        cout << "a[" << i << "] = " << hash.pfxHash[i] << ", ot: " << hash.pows[i] << "\n";
//    cout << hash.hashSubstr(1, 5) << " " << hash.hashSubstr(6, 10) << " done\n";
//
//    cout << "solo: " << hash.hashSubstr(1, 1) << "\n";

    assert(hash.hashSubstr(1, 5) == hash.hashSubstr(6, 10));
    assert(hash.hashSubstr(11, 15) == hash.hashSubstr(16, 20));
    assert(hash.hashSubstr(1, 3) != hash.hashSubstr(2, 4));
    assert(hash.hashSubstr(5, 10) != hash.hashSubstr(15, 20));

    string ot = "lloh"; assert(hash.hashSubstr(3, 6) == hash.hashOtherStr(ot));
    ot = "orldworl"; assert(hash.hashSubstr(12, 19) == hash.hashOtherStr(ot));
    ot = "orld"; assert(hash.hashSubstr(17, 20) == hash.hashOtherStr(ot));

    PASSED("Substring Hash");
}