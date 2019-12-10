#pragma once

#include "global_includes.h"

// Shorthand Macros
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define mpr make_pair
#define pb push_back
#define popcount __builtin_popcount
#define clz __builtin_clz
#define ctz __builtin_ctz

// Typedefs
using ll = long long;
using ull = unsigned long long;

// Functions
ll timeMs() {
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
}

// Shorthand Functions
template<typename T> inline void maxa(T& st, T v) {
    st = max(st, v);
}

template<typename T> inline void mina(T& st, T v) {
    st = min(st, v);
}
