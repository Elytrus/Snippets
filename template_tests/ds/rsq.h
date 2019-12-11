#pragma once

#include "../global_includes.h"

struct RSQDataSet {
    vector<int> data;
    vector<tuple<int, int, int, int>> queries;
};

namespace rsq_tests {
    const int N = 1000, N2 = 50, Q = 1000, MAX_VAL = 1000;

    pair<int, int> make_lr_pair(int N) {
        int a = randint(1, N), b = randint(1, N);
        if (a > b) swap(a, b);
        return make_pair(a, b);
    }

/**
 * Creates RSQ test data
 * @param make_initial_sequence Whether the initial sequence should be randomized or be all 0s
 * @param range_updates Whether updates should be range updates
 * @param range_queries Whether queries should be range queries
 * @return An RSQ Dataset
 */
    RSQDataSet make_rmq_dataset(bool make_initial_sequence, bool range_updates, bool range_queries) {
        RSQDataSet ret;
        if (make_initial_sequence)
            for (int i = 0; i < N; i++)
                ret.data.push_back(randint(0, MAX_VAL));
        else
            ret.data.assign(N, 0);

        for (int i = 0; i < Q; i++) {
            int type = randint(1, 2); // 1 -> Update, 2 -> Query
            if (type == 1) {
                if (range_updates) {
                    auto[l, r] = make_lr_pair(N);
                    ret.queries.emplace_back(1, l, r, randint(0, MAX_VAL));
                } else
                    ret.queries.emplace_back(1, randint(1, N), randint(0, MAX_VAL), -1);
            }
            else {
                if (range_queries) {
                    auto[l, r] = make_lr_pair(N);
                    ret.queries.emplace_back(2, l, r, -1);
                } else
                    ret.queries.emplace_back(2, randint(1, N), -1, -1);
            }
        }

        return ret;
    }

    struct RSQDummy {
        vector<ll> vec;
        int n;

        void init(int n0) {
            n = n0;
            vec.resize(n + 1);
        }

        void range_set(int l, int r, ll v) {
            for (int i = l; i <= r; i++)
                vec[i] = v;
        }

        void range_update(int l, int r, ll v) {
            for (int i = l; i <= r; i++)
                vec[i] += v;
        }

        ll range_query(int l, int r) {
            ll sum = 0;
            for (int i = l; i <= r; i++)
                sum += vec[i];
            return sum;
        }

        /**
         * Returns the first x such that vec[1] + vec[2] + ... + vec[x] >= sum, or n + 1 if no x exists
         * @param sum The sum
         * @return As specified
         */
        int first_pfxsum_greater_or_equal(ll sum) {
            ll csum = 0;
            for (int i = 1; i <= n; i++) {
                csum += vec[i];
                if (csum >= sum) return i;
            }
            return n + 1;
        }
    };

    struct RSQDummy2D {
        vector<vector<ll>> vec;
        int n, m;

        void init(int n0, int m0) {
            n = n0; m = m0;
            vec.resize(n + 1);
            for (int i = 0; i < n + 1; i++)
                vec[i].resize(m + 1);
        }

        void range_set(int xl, int yl, int xr, int yr, ll v) {
            for (int i = xl; i <= xr; i++)
                for (int j = yl; j <= yr; j++)
                    vec[i][j] = v;
        }

        void range_update(int xl, int yl, int xr, int yr, ll v) {
            for (int i = xl; i <= xr; i++)
                for (int j = yl; j <= yr; j++)
                    vec[i][j] += v;
        }

        ll range_query(int xl, int yl, int xr, int yr) {
            ll sum = 0;
            for (int i = xl; i <= xr; i++)
                for (int j = yl; j <= yr; j++)
                    sum += vec[i][j];
            return sum;
        }
    };
}

using rsq_tests::RSQDummy;
using rsq_tests::RSQDummy2D;
using rsq_tests::make_rmq_dataset;
