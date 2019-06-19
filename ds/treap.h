#include "stdincludes.h"

//begintemplate treap
//description Basic Split-Merge Treap
mt19937 gen(time(NULL));
uniform_int_distribution<int> dis;
template <typename T>
struct Node {
    T val; int pri; Node<T> *l, *r;
    Node(T val0) : val(val0), pri(dis(gen)), l(nullptr), r(nullptr) {}
};
template <typename T>
struct SMTreap {
    Node<T>* root;
    SMTreap() : root(nullptr) {}
    Node<T>*& which(Node<T>* &cur, bool cond) { return cond ? cur->r : cur->l; }
    void split(Node<T>* cur, T val, Node<T>* &l, Node<T>* &r) {
        if (!cur) l = r = nullptr;
        else if (cur->val > val) { split(cur->l, val, l, cur->l); r = cur; }
        else { split(cur->r, val, cur->r, r); l = cur; }
    }
    void merge(Node<T>* &cur, Node<T>* l, Node<T>* r) {
        if (!l || !r) cur = l ? l : r;
        else if (l->pri > r->pri) { merge(l->r, l->r, r); cur = l; }
        else { merge(r->l, l, r->l); cur = r; }
    }
    void insert(Node<T>* &cur, Node<T>* node) {
        if (!cur) cur = node;
        else if (cur->pri > node->pri) { split(cur, node->val, node->l, node->r); cur = node; }
        else insert(which(cur, node->val >= cur->val), node);
    }
    void remove(Node<T>* &cur, T val) {
        if (!cur) return;
        else if (cur->val == val) { merge(cur, cur->l, cur->r); }
        else remove(which(cur, val >= cur->val), val);
    }
    Node<T>* search(Node<T>* &cur, T val) {
        if (!cur) return nullptr;
        else if (cur->val == val) { return cur; };
        return search(which(cur, val >= cur->val), val);
    }
    void inOrder(Node<T>* &cur) {
        if (!cur) return;
        inOrder(cur->l); cout << cur->val << " "; inOrder(cur->r);
    }
};
//endtemplate

//TODO: Basic Treap Tests (Already tested on Utrka/coci14c2p2) (https://dmoj.ca/src/1484732)