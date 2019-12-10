#pragma once

#include "test/global_includes.h"

//begintemplate gcd
//description Basic GCD template
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
//endtemplate gcd

//TODO: GCD TEST