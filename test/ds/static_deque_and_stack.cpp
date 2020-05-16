#include "../helper.h"
#include "../../templates/ds/static_deque.h"
#include "../../templates/ds/static_stack.h"
using namespace std;

const int Q = 300000;

stack<int> stk_check;
StaticStack<int, Q> stk;
deque<int> dq_check;
StaticDeque<int, Q> dq;

void stk_push_check(int v) {
    stk_check.push(v);
    stk.push(v);
}
void stk_pop_check() {
    check(stk.pop() == stk_check.top(), "stk pop");
    stk_check.pop();
}

void check_dq_same() {
    if (!dq_check.empty()) {
        check(dq.front() == dq_check.front(), "dq circular");
        check(dq.back() == dq_check.back(), "dq circular");
    }
    else
        check(dq.empty(), "dq circular - empty");
}

int main() {
    init_rng();

    // standard
    for (int _ = 0; _ < Q; _++) {
        int t = rnd.next(0, 3), v = rnd.next(0, int(1e9));
        if (t == 0) {
            dq.push_front(v);
            dq_check.push_front(v);
            stk_push_check(v);
        }
        else if (t == 1) {
            dq.push_back(v);
            dq_check.push_back(v);
            stk_push_check(v);
        }
        else {
            if (dq_check.empty()) {
                assert(stk_check.empty());
                check(dq.empty(), "dq empty");
                check(!stk.size(), "stk empty");
            }
            else {
                if (t == 2) {
                    check(dq.pop_front() == dq_check.front(), "dq pop front");
                    dq_check.pop_front();
                }
                else {
                    check(dq.pop_back() == dq_check.back(), "dq pop back");
                    dq_check.pop_back();
                }
                stk_pop_check();
            }
        }
    }

    // capacity
    dq.clear();
    stk.clear();
    for (int i = 0; i < Q; i++) {
        dq.push_back(i);
        stk.push(i);
    }

    // circular check (deque)
    // basically making sure that when the pointers wrap around from the beginning to the end (and vice versa), that the queue still works properly
    dq.clear();
    dq_check.clear();

    for (int i = 0; i < 5 * Q; i++) {
        int vs[2] = {rnd.next(0, int(1e9)), rnd.next(0, int(1e9))};
        for (int j = 0; j < 2; j++) {
            dq.push_back(vs[j]);
            dq_check.push_back(vs[j]);
            check_dq_same();
        }
        for (int j = 0; j < 2; j++) {
            dq.pop_front();
            dq_check.pop_front();
            check_dq_same();
        }
    }
    for (int i = 0; i < 5 * Q; i++) {
        int vs[2] = {rnd.next(0, int(1e9)), rnd.next(0, int(1e9))};
        for (int j = 0; j < 2; j++) {
            dq.push_front(vs[j]);
            dq_check.push_front(vs[j]);
            check_dq_same();
        }
        for (int j = 0; j < 2; j++) {
            dq.pop_back();
            dq_check.pop_back();
            check_dq_same();
        }
    }

    cout << "OK";

    return 0;
}
