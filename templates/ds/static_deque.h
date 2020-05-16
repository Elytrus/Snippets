#pragma once

#include "bits/stdc++.h"
using namespace std;

//begintemplate staticdeque
//description A static, array based deque that's very fast
template <typename T, int MN> // Note that MAX is the max number of push operations
struct StaticDeque {
    array<T, MN + 1> val; int lptr = 0, rptr = 0;
    int __inc(int x) { return (x + 1) % (MN + 1); }
    int __dec(int x) { return (x + MN) % (MN + 1); }
    void __too_big() { if (lptr == rptr) throw runtime_error("Too many values (exceeded maximum size)"); }
    void push_back(T v) { val[rptr] = v; rptr = __inc(rptr); __too_big(); }
    void push_front(T v) { val[lptr = __dec(lptr)] = v; __too_big(); }
    T pop_back() { return val[rptr = __dec(rptr)]; }
    T pop_front() { T res = val[lptr]; lptr = __inc(lptr); return res; }
    T back() { return val[__dec(rptr)]; }
    T front() { return val[lptr]; }
    bool empty() { return lptr == rptr; }
    void clear() { lptr = rptr = 0; }
};
//endtemplate staticdeque
