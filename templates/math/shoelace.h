#pragma once

#include "test/global_includes.h"

//begintemplate shoelace
//description Shoelace Theorem for calculating area
struct pt { ll x, y; };
template <typename T> double shoelace(T begin, T end) { return shoelace2(begin, end) / 2.; }
template <typename T> ll shoelace2(T begin, T end) { // Gets area * 2 (since it's an integer)
    int n = end - begin;
    ll tot = 0;
    for (int i = 0; i < n; i++)
        tot += (begin[i].x * begin[(i + 1) % n].y) - (begin[i].y * begin[(i + 1) % n].x);
    return abs(tot);
}
ll shoelace2(vector<pt> pts) { return shoelace2(pts.begin(), pts.end()); }
double shoelace(vector<pt> pts) { return shoelace(pts.begin(), pts.end()); }
//endtemplate shoelace

void test_shoelace() {
    assert(shoelace({{0, 0}, {4, 0}, {0, 10}}) == 20LL);
}