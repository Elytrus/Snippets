#pragma once

#include "test/global_includes.h"

//begintemplate staticstack
//description A static, array based stack that's very fast
template <int MAX, typename T>
struct StaticStack {
    T arr[MAX]; int ptr = -1;
    void push(T v) { arr[++ptr] = v; }
    T pop() { return arr[ptr--]; }
    T top() { return arr[ptr]; }
    int size() { return ptr + 1; }
    bool empty() { return ptr == -1; }
    void clear() { ptr = -1; }
    T* begin() { return arr; }
    T* end() { return arr + ptr + 1; }
};
//endtemplate staticstack