#include "bits/stdc++.h"
using namespace std;


/*
Notes:

- ROT ONLY WORKS BECAUSE IT'S BEING CALLED BY SPLAY. ROT DOES NOT UPDATE THE NODES PROPERLY AS IT GOES UP
- Find returns the first node with a key >= search key, or nullptr if all keys are < search key
- Split splits node into two parts: l (<= key) and r (> key)
- Split leaves the left child of r empty
- After splaying a node, the root must be reset
- Always call splay after find and ins operations (not necessary for indexOf as that already splays n)

*/
namespace Splay {
    struct Node {
        int sz;
        // maintain any auxillary information here
        bool rev;
        Node *ch[2], *p;
        Node(int val0) : rev(false), sz(1), p(nullptr) {
            ch[0] = ch[1] = nullptr;
        }
    };
    void debug(Node *n, string c = "=");
    void inOrder(Node *n);

    int sz(Node *n) { return n ? n->sz : 0; }
    bool side(Node *n) { return n->p ? (n == n->p->ch[1]) : false; }
    void setp(Node *n, Node *p) { if (n) n->p = p; }
    void setc(Node *n, Node *c, bool cno) { if (n) n->ch[cno] = c; if (c) c->p = n; } // set child

    void push(Node *n) {
        if (n && n->rev) {
            // todo: implement
        }
    }
    void upd(Node *n) {
        if (n) {
            push(n->ch[0]); push(n->ch[1]);
            n->sz = sz(n->ch[0]) + sz(n->ch[1]) + 1;
        }
    }
    void rot(Node *n) {
        assert(n && n->p);
        push(n->p); push(n); // highest first
        bool dir = side(n), ppdir = side(n->p); // directions
        Node *p = n->p, *pp = n->p->p, *d = n->ch[!dir]; // nodes
        setc(n, p, !dir); setc(pp, n, ppdir); setc(p, d, dir); // rotate
        upd(p); upd(n); // update from lowest to highest.  THIS ONLY WORKS BECAUSE ROT IS ONLY CALLED IN SPLAY
    }
    void splay(Node *n) {
        while (n && n->p) {
            if (n->p->p) {
                if (side(n) == side(n->p)) { rot(n->p); rot(n); }
                else { rot(n); rot(n); }
            }
            else rot(n);
        }
    }
    Node* find(Node *n, int id) {
        if (!n) return nullptr;
        push(n);
        int adj = sz(n->ch[0]) + 1;
        if (id == adj) return n;
        return find(n->ch[id > adj], id - (id > adj) * adj);
    }
    void split(Node *n, int key, Node *&l, Node *&r) { // splits nodes into groups (<= key, > key)
        r = find(n, key + 1); splay(r);
        if (!r) return void(l = n);
        l = r->ch[0]; // set
        setp(l, nullptr); r->ch[0] = nullptr; // break link
        upd(l); upd(r); // upd
    }
    void join(Node *&n, Node *l, Node *r) { // assumes max(l) <= min(r)
        push(l); push(r);
        if (!r) return void(n = l);
        while (r->ch[0]) { r = r->ch[0]; push(r); }
        splay(r);
        setc(r, l, 0); n = r; // set parents and children, and assign n
        upd(n); // upd
    }
    void ins(Node *&n, int id, Node *nn) {
        Node *l, *r;
        split(n, id, l, r);
        setc(nn, l, 0); setc(nn, r, 1);
        n = nn;
        upd(n);
    }
    // Extra stuff
    void debug(Node *n, string c) {
        if (!n) return;
        cout << c;
        if (n->p) cout << '(' << side(n) << ')';
        cout << n << ", l=" << n->ch[0] << ", r=" << n->ch[1] << ", v=" << n->val << ", rev=" << n->rev << ", sz=" << sz(n) << endl;
        debug(n->ch[0], c + "="); debug(n->ch[1], c + "=");
    }
    void inOrder(Node *n) {
        if (!n) return;
        inOrder(n->ch[0]);
        cout << n->val << ' ';
        inOrder(n->ch[1]);
    }
    void del(Node *&n, int key) {
        Node *l, *r;
        split(n, key - 1, l, r);
        setp(r->ch[1], nullptr);
        join(n, l, r->ch[1]);
        delete r;
    }
}
using Splay::Node; using Splay::ins; using Splay::find; using Splay::inOrder;
using Splay::split; using Splay::join; using Splay::del;

