#pragma once

#include "bits/stdc++.h"
using namespace std;

//begintemplate segtree
//description Recursive Segment Tree (Interval Tree)
/*
 * Segment Tree template, supports range query and point update of associative operations in logN time.
 * Functions to implement:
 * - setVal(T &a, T b): Updates the value (i.e. if updates increase values, you would do a += b)
 * - merge(T a, T b): The operation of this segtree.  Note that a is on the left and b is on the right
 * - getDefault(): The default value in the segtree (i.e. 0 for sum)
 */
template <typename T>
struct SegmentTree {
    int N; vector<T> seg;
    virtual void setVal(T &a, T b) = 0;
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
    void init(int n0, T* arr) { init(n0); build(1, 1, N, arr); }
    T query(int l, int r) { return _query(1, 1, N, l, r); }
    void update(int q, T v) { _update(1, 1, N, q, v); }
};
//endtemplate segtree

//begintemplate lazysegtree
//description Lazy Recursive Segment Tree (Interval Tree)
/*
 * Segment Tree template, supports range query and range update of associative operations in logN time.
 * Functions to implement:
 * - setVal(T &a, T b): Updates the value (i.e. if updates increase values, you would do a += b)
 * - merge(T a, T b): The operation of this segtree.  Note that a is on the left and b is on the right
 * - getDefault(): The default value in the segtree (i.e. 0 for sum)
 * - getLazyDefault(): The default value in this segtree for the lazy array (i.e. 0 for range increment)
 * - mergeLazy(Lazy_T &to, Lazy_T &from): Merges the second lazy value into the first lazy value
 * - applyLazy(T &to, Lazy_T &from, int l, int r): Applies a lazy value onto a segtree value
 */
template <typename T, typename Lazy_T>
struct LazySegmentTree {
    int N; vector<T> seg; vector<Lazy_T> lazy;
    virtual T merge(T a, T b) = 0;
    virtual T getDefault() = 0;
    virtual Lazy_T getLazyDefault() = 0;
    virtual void mergeLazy(Lazy_T &to, Lazy_T &from) = 0;
    virtual void applyLazy(T &to, Lazy_T &from, int l, int r) = 0;
    T build(int i, int l, int r, T* arr){
        if (l == r) return seg[i] = arr[l];
        int mid = (l + r) >> 1;
        return seg[i] = merge(build(i * 2, l, mid, arr), build(i * 2 + 1, mid + 1, r, arr));
    }
    void push(int i, int l, int r) {
        if (lazy[i] != getLazyDefault()) {
            applyLazy(seg[i], lazy[i], l, r);
            if (i * 2 < 4 * N) mergeLazy(lazy[i * 2], lazy[i]);
            if (i * 2 + 1 < 4 * N) mergeLazy(lazy[i * 2 + 1], lazy[i]);
            lazy[i] = getLazyDefault();
        }
    }
    T _query(int i, int l, int r, int ql, int qr){
        if (r < ql || l > qr) return getDefault();
        push(i, l, r);
        if (l >= ql && r <= qr) return seg[i];
        int mid = (l + r) >> 1;
        return merge(_query(i * 2, l, mid, ql, qr), _query(i * 2 + 1, mid + 1, r, ql, qr));
    }
    T _update(int i, int l, int r, int ql, int qr, Lazy_T v){
        push(i, l, r);
        if (qr < l || ql > r) return seg[i];
        if (l >= ql && r <= qr) {
            mergeLazy(lazy[i], v);
            push(i, l, r);
            return seg[i];
        }
        int mid = (l + r) >> 1;
        return seg[i] = merge(_update(i * 2, l, mid, ql, qr, v), _update(i * 2 + 1, mid + 1, r, ql, qr, v));
    }
    void init(int n0) { N = n0; seg.assign(N * 4, getDefault()); lazy.assign(N * 4, getLazyDefault()); }
    void init(int n0, T* arr) { init(n0); build(1, 1, N, arr); }
    T query(int l, int r) { return _query(1, 1, N, l, r); }
    void update(int l, int r, Lazy_T v) { _update(1, 1, N, l, r, v); }
};
//endtemplate lazysegtree

