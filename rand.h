#pragma once

#include "stdincludes.h"

namespace rand_h_priv {
    mt19937 mt;
    mt19937_64 mt64;

    int randint(int a, int b) {
        return uniform_int_distribution<int>(a, b)(mt);
    }

    long long randlong(long long a, long long b) {
        return uniform_int_distribution<long long>(a, b)(mt);
    }
}

using rand_h_priv::randint;
using rand_h_priv::randlong;
