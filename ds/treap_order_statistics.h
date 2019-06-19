#pragma once

#include "stdincludes.h"

//begintemplate treaporderstatistics
//description Split-Merge Treap with order statistics BST functionality
mt19937 gen(time(NULL));
uniform_int_distribution<int> dis;
template <typename T>
struct Node {
    T val; int pri, sz; Node<T> *l, *r;
    Node(T val0) : val(val0), pri(dis(gen)), sz(1), l(nullptr), r(nullptr) {}
};
template <typename T>
struct SMTreapOS {
    Node<T>* root;
    SMTreapOS() : root(nullptr) {}
    Node<T>*& which(Node<T>* &cur, bool cond) { return cond ? cur->r : cur->l; }
    int sz(Node<T>* &cur) { return cur ? cur->sz : 0; }
    void upd(Node<T>* &cur) { if (cur) cur->sz = sz(cur->l) + sz(cur->r) + 1; }
    void split(Node<T>* cur, T val, Node<T>* &l, Node<T>* &r) {
        if (!cur) l = r = nullptr;
        else if (cur->val > val) { split(cur->l, val, l, cur->l); r = cur; }
        else { split(cur->r, val, cur->r, r); l = cur; }
        upd(cur);
    }
    void merge(Node<T>* &cur, Node<T>* l, Node<T>* r) {
        if (!l || !r) cur = l ? l : r;
        else if (l->pri > r->pri) { merge(l->r, l->r, r); cur = l; }
        else { merge(r->l, l, r->l); cur = r; }
        upd(cur);
    }
    void insert(Node<T>* &cur, Node<T>* node) {
        if (!cur) cur = node;
        else if (cur->pri > node->pri) { split(cur, node->val, node->l, node->r); cur = node; }
        else insert(which(cur, node->val >= cur->val), node);
        upd(cur);
    }
    void remove(Node<T>* &cur, T val) {
        if (!cur) return;
        else if (cur->val == val) { merge(cur, cur->l, cur->r); }
        else remove(which(cur, val >= cur->val), val);
        upd(cur);
    }
    int indexOf(Node<T>* &cur, T val, int idx = 0) {
        if (!cur) return -1;
        else if (cur->val == val) { int ot = indexOf(cur->l, val, idx); return ot != -1 ? ot : idx + sz(cur->l) + 1; };
        return indexOf(which(cur, val >= cur->val), val, idx + (val < cur->val ? 0 : sz(cur->l) + 1));
    }
    Node<T>* kth(Node<T>* &cur, int idx) {
        if (idx == sz(cur->l) + 1) return cur;
        return kth(which(cur, idx > sz(cur->l)), idx - (idx > sz(cur->l) ? sz(cur->l) + 1 : 0));
    }
    void inOrder(Node<T>* &cur) {
        if (!cur) return;
        inOrder(cur->l); cout << cur->val << " "; inOrder(cur->r);
    }
};
//endtemplate treaporderstatistics

//TODO: Order Statistics Tree Tests (Already tested on DS4) (https://dmoj.ca/src/1484730)