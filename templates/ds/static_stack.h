#pragma once

#include "bits/stdc++.h"
using namespace std;

//begintemplate staticstack
//description A static, array based stack that's very fast
template <typename T, int MN>
struct StaticStack {
    array<T, MN> val; int ptr = 0;
    void push(T v) { if (ptr == MN) throw runtime_error("Too many values! (stack is full)"); val[ptr++] = v; }
    T pop() { return val[--ptr]; }
    T top() { return val[ptr - 1]; }
    int size() { return ptr; }
    void clear() { ptr = 0; }
};
//endtemplate staticstack
