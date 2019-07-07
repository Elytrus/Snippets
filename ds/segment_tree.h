#pragma once

#include "../stdincludes.h"

/*
 * Function Signatures:
 * T merge(T left, T right);
 */

//begintemplate segtree
//description Recursive Segment Tree (Interval Tree)
template <int MAX, typename T>
struct SegmentTree {
    int n; T defaultV, tree[MAX << 2]; T (*merge)(T, T);
    SegmentTree(int n0, T defaultV0, T (*merge0)(T, T)) : n(n0), defaultV(defaultV0), merge(merge0) {}
    T build(int i, int l, int r, T* arr){
        if(l == r) return tree[i] = arr[l];

        int mid = (l + r) >> 1;
        return tree[i] = merge(build(i << 1, l, mid, arr), build(i << 1 | 1, mid + 1, r, arr));
    }
    T query(int i, int bl, int br, int ql, int qr){
        if(br < ql || bl > qr) return defaultV;
        if(bl >= ql && br <= qr) return tree[i];

        int mid = (bl + br) >> 1;
        return merge(query(i << 1, bl, mid, ql, qr), query(i << 1 | 1, mid + 1, br, ql, qr));
    }
    T update(int i, int bl, int br, int q, T v){
        if(q < bl || q > br) return tree[i];
        if(bl == q && br == q) return tree[i] = assert(("Needs to be implemented!", 0));;

        int mid = (bl + br) >> 1;
        return tree[i] = merge(update(i << 1, bl, mid, q, v), update(i << 1 | 1, mid + 1, br, q, v));
    }
};
//endtemplate segtree

/*
 * Function Signatures:
 * T merge(T left, T right);
 * void updLazy(T& lazyv, T& treev, T& lhslazyv, T& rhslazyv);
 */

//begintemplate lazysegtree
//description Recursive Lazy Propagating Segment Tree (Interval Tree)
template <int MAX, typename T>
struct LazySegmentTree {
    int n; T defaultV, tree[MAX << 2], lazy[MAX << 3]; T (*merge)(T, T); void (*updLazy)(T&, T&, T&, T&);
    LazySegmentTree(int n0, T defaultV0, T (*merge0)(T, T), void (*updLazy0)(T&, T&, T&, T&)) : n(n0), defaultV(defaultV0), merge(merge0), updLazy(updLazy0) {}
    T build(int i, int l, int r, T* arr){
        if(l == r) return tree[i] = arr[l];

        int mid = (l + r) >> 1;
        return tree[i] = merge(build(i << 1, l, mid, arr), build(i << 1 | 1, mid + 1, r, arr));
    }
    T query(int i, int bl, int br, int ql, int qr){
        updLazy(lazy[i], tree[i], lazy[i << 1], lazy[i << 1 | 1]);
        if(br < ql || bl > qr) return defaultV;
        if(bl >= ql && br <= qr) return tree[i];

        int mid = (bl + br) >> 1;
        return merge(query(i << 1, bl, mid, ql, qr), query(i << 1 | 1, mid + 1, br, ql, qr));
    }
    T update(int i, int bl, int br, int q, T v){
        updLazy(lazy[i], tree[i], lazy[i << 1], lazy[i << 1 | 1]);
        if(q < bl || q > br) return tree[i];
        if(bl == q && br == q) {
            lazy[i] = v;
            updLazy(lazy[i], tree[i], lazy[i << 1], lazy[i << 1 | 1]);
            return tree[i];
        }

        int mid = (bl + br) >> 1;
        return tree[i] = merge(update(i << 1, bl, mid, q, v), update(i << 1 | 1, mid + 1, br, q, v));
    }
};
//endtemplate lazysegtree