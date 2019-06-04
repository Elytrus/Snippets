#pragma once

#include "../stdincludes.h"

//begintemplate gcd
//description Basic GCD template
namespace GCD {
    ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
}
//endtemplate gcd