#pragma once

#include "stdincludes.h"

// WIP -- BROKEN
#ifdef __THIS_IS_DEFINITELY_UNDEFINED
////begintemplate staticdeque
////description A static, array based deque that's very fast
template <int MAX, typename T> // Note that MAX is the max number of push operations
struct StaticDeque {
    T arr[MAX]; int lptr = 0, rptr = 0;
    void push(T v) { arr[rptr++] = v; }
    void pushfront(T v) { lptr = (lptr - 1 + MAX) % MAX; arr[lptr] = v; }
    T pop() { return arr[ptr--]; }
    T popfront() { return arr[ptr--]; }
    T back() { return arr[ptr]; }
    T front() { return arr[ptr]; }
    int size() { return rptr - lptr; }
    bool empty() { return lptr == rptr; }
    void clear() { lptr = rptr = 0; }
    T* begin() { return arr + lptr; }
    T* end() { return arr + rptr; }
};
////endtemplate staticdeque
#endif