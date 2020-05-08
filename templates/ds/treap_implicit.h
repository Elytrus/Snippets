#include "test/global_includes.h"

//begintemplate implicittreap
//description Implicit Treap Data Structure
/*
POSITIONS ARE 1-INDEXED

SPLIT(idx) -> LHS: [1, idx], RHS: [idx+1, N]
INSERT(idx, x) -> Insert (x) after pos [idx]
*/
ll seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 gen(seed);
uniform_int_distribution<int> dis;
struct Node {
    int pri, sz, val; Node *l, *r;
    Node(int val0) : pri(dis(gen)), sz(1), l(nullptr), r(nullptr), val(val0) { }
};
struct ImplicitTreap {
    Node* root;
    ImplicitTreap() : root(nullptr) {}
    inline int sz(Node* &cur) { return cur ? cur->sz : 0; }
    void pushDown(Node* cur) {
        assert(("Not implemented yet!", 0));
        if (cur) {
            // IMPLEMENT THIS
        }
    }
    void upd(Node* cur) {
        if (cur) {
            pushDown(cur->l); pushDown(cur->r); // MUST INCLUDE THIS OR YOU LITERALLY DIE (WA) (REQUIRED FOR REVERSE OPERATION)
            cur->sz = sz(cur->l) + sz(cur->r) + 1;

            assert(("Not implemented yet!", 0));
        }
    }
    void split(Node* cur, int key, Node* &l, Node* &r) {
        pushDown(cur);
        if (!cur) l = r = nullptr;
        else if (key < sz(cur->l) + 1) { split(cur->l, key, l, cur->l); r = cur; }
        else { split(cur->r, key - sz(cur->l) - 1, cur->r, r); l = cur; }
        upd(cur);
    }
    void merge(Node* &cur, Node* l, Node* r) {
        pushDown(l); pushDown(r);
        if (!l || !r) cur = l ? l : r;
        else if (l->pri > r->pri) { merge(l->r, l->r, r); cur = l; }
        else { merge(r->l, l, r->l); cur = r; }
        upd(cur);
    }
    void insert(Node* &cur, int key, Node* node) {
        Node* rhs;
        split(cur, key, cur, rhs);
        merge(cur, cur, node);
        merge(cur, cur, rhs);
    }
    void remove(Node* &cur, int key) {
        pushDown(cur);
        if (!cur) return;
        int cKey = sz(cur->l) + 1;
        if (key == cKey) { merge(cur, cur->l, cur->r); }
        else { key > cKey ? remove(cur->r, key - cKey) : remove(cur->l, key); }
        upd(cur);
    }
    Node* kth(Node* &cur, int idx) {
        pushDown(cur);
        int cKey = sz(cur->l) + 1;
        if (idx == cKey) return cur;
        auto ret = idx < cKey ? kth(cur->l, idx) : kth(cur->r, idx - cKey);
        upd(cur);
        return ret;
    }
    void inOrder(Node* &cur) {
        if (!cur) return;
        inOrder(cur->l); cout << cur->val << " "; inOrder(cur->r);
    }
};
//endtemplate implicittreap
