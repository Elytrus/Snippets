#pragma once

#include "bits/stdc++.h"
using namespace std;

//begintemplate segtree
//description Recursive Segment Tree (Interval Tree)
/*
 * Segment Tree template, supports range query and point update of associative operations in logN time.
 */
template <typename T>
struct SegmentTree {
    int N; vector<T> seg;
    virtual void setVal(T& a, T b) = 0;
    virtual T merge(T a, T b) = 0;
    virtual T getDefault() = 0;
    T build(int i, int l, int r, T* arr){
        if (l == r) return seg[i] = arr[l];
        int mid = (l + r) >> 1;
        return seg[i] = merge(build(i * 2, l, mid, arr), build(i * 2 + 1, mid + 1, r, arr));
    }
    T _query(int i, int l, int r, int ql, int qr){
        if (r < ql || l > qr) return getDefault();
        if (l >= ql && r <= qr) return seg[i];
        int mid = (l + r) >> 1;
        return merge(_query(i * 2, l, mid, ql, qr), _query(i * 2 + 1, mid + 1, r, ql, qr));
    }
    T _update(int i, int l, int r, int q, T v){
        if (q < l || q > r) return seg[i];
        if (l == q && r == q) { setVal(seg[i], v); return seg[i]; }
        int mid = (l + r) >> 1;
        return seg[i] = merge(_update(i * 2, l, mid, q, v), _update(i * 2 + 1, mid + 1, r, q, v));
    }
    void init(int n0) { N = n0; seg.assign(N * 4, getDefault()); }
    void init(int n0, T* arr) { N = n0; build(1, 1, N, arr); }
    T query(int l, int r) { return _query(1, 1, N, l, r); }
    void update(int q, T v) { _update(1, 1, N, q, v); }
};
//endtemplate segtree

