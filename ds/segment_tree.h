#pragma once

#include "template_tests/global_includes.h"

//begintemplate segtree
//description Recursive Segment Tree (Interval Tree)
/*
 * Segment Tree template, supports querying and updating of
 */
template <int MN, typename T>
struct SegmentTree {
    int n; T seg[MN << 2];
    virtual void setVal(T& a, T b) = 0;
    virtual T merge(T a, T b) = 0;
    virtual void push(int i, int l, int r) = 0;
    virtual T getDefault() = 0;
    T build(int i, int l, int r, T* arr){
        if(l == r) return seg[i] = arr[l];
        int mid = (l + r) >> 1;
        return seg[i] = merge(build(i << 1, l, mid, arr), build(i << 1 | 1, mid + 1, r, arr));
    }
    T _query(int i, int bl, int br, int ql, int qr){
        if(br < ql || bl > qr) return getDefault();
        push(i, bl, br);
        if(bl >= ql && br <= qr) return seg[i];
        int mid = (bl + br) >> 1;
        return merge(_query(i << 1, bl, mid, ql, qr), _query(i << 1 | 1, mid + 1, br, ql, qr));
    }
    T _update(int i, int bl, int br, int ql, int qr, T v){
        push(i, bl, br);
        if(qr < bl || ql > br) return seg[i];
        if(bl >= ql && br <= qr) { setVal(seg[i], v); return seg[i]; }
        int mid = (bl + br) >> 1;
        return seg[i] = merge(_update(i << 1, bl, mid, ql, qr, v), _update(i << 1 | 1, mid + 1, br, ql, qr, v));
    }
    void init(int n0) { n = n0; for (int i = 0; i < 4 * n; i++) seg[i] = getDefault(); }
    void init(int n0, T* arr) { n = n0; build(1, 1, n, arr); }
    T query(int l, int r) { return _query(1, 1, n, l, r); }
    void update(int l, int r, T v) { _update(1, 1, n, l, r, v); }
};
//endtemplate segtree

namespace __segment_tree_tests {
    struct TestSegmentTree : SegmentTree<rsq_tests::N, int> {
        using ST = SegmentTree<rsq_tests::N, int>; using ST::seg;
        int lazy[rsq_tests::N << 3];
        int merge(int a, int b) override { return a + b; }
        void setVal(int &a, int b) override { a += b; }
        void push(int i, int l, int r) override {

        }

        int getDefault() override {
            return 0;
        }
    };

    void segment_tree_tests() {

    }
}

using __segment_tree_tests::segment_tree_tests;
