#pragma once

#include "stdincludes.h"

namespace STOP_CONFICTS_4 {
//begintemplate extendedeuclidianalgorithm
//description Extended Euclidian algorithm template with Divmod and MMI
ll pa_, pb_;
void extEuclid(ll a, ll b){
    if (!b) { pa_ = 1; pb_ = 0; }
    else {
        extEuclid(b, a % b);
        ll tmp = pa_; pa_ = pb_; pb_ = tmp - a / b * pb_;
    }
}
ll modInv(ll x, ll mod) { extEuclid(x % mod, mod); return (pa_ + mod) % mod; }
ll divMod(ll x, ll y, ll mod) { return (x * modInv(y, mod)) % mod; }
//endtemplate extendedeuclidianalgorithm
}