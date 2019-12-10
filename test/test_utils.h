#pragma once

#include "global_includes.h"

// Variadic static_assert, from https://stackoverflow.com/questions/13562823/parameter-pack-aware-stdis-base-of
// Given a variadic number of constexprs, return if all are true
template <bool... b> struct static_all_of;
template <bool... tail> struct static_all_of<true, tail...> : static_all_of<tail...> {};
template <bool... tail> struct static_all_of<false, tail...> : false_type {};
template <> struct static_all_of<> : true_type {};

// Comparison
template <typename T> bool vector_equals(vector<T> a, vector<T> b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); i++)
        if (a[i] != b[i])
            return false;
    return true;
}

template <typename T> bool vector_equals(vector<T> a, vector<T> b, function<bool(T, T)> eq_fun) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); i++)
        if (!eq_fun(a[i], b[i]))
            return false;
    return true;
}

bool double_equals(double a, double b, const double eps = numeric_limits<double>::epsilon()) {
    return abs(a - b) <= eps;
}

// Functional and sequence-based operations
/**
 * Data type that represents a range.  Consists of a beginning and end iterator.  Iterators must be random access
 * iterators.  It functions very similarly to Golang slices
 *
 * Each range has two iterators, begin and end, which represent the contiguous range [begin, end)
 * @tparam T The data type that this range represents.
 */
template <typename T> struct Range {
    using It = iterator<random_access_iterator_tag, T>;
    It _begin, _end;

    /**
     * Constructor using iterators
     * @param _begin0 Begin iterator
     * @param _end0 End iterator
     */
    Range(It _begin0, It _end0) : _begin(_begin0), _end(_end0) {}

    /**
     * Constructor using a vector.  It sets _begin to vector.begin() and _end to vector.end()
     * @param vec The vector
     */
    Range(vector<T> &vec) : _begin(vec.begin()), _end(vec.end()) {}

    /**
     * Constructor using a vector.  It sets the range such that it corresponds to the range [L, R) in the vector
     * @param vec The vector
     * @param L The left bound (inclusive) of the range
     * @param R The right bound (exclusive) of the range
     */
    Range(vector<T> &vec, int L, int R) : _begin(vec.begin() + L), _end(vec.begin() + R) {}

    /**
     * Converts the range to a vector
     * @return Returns the range as a vector
     */
    vector<T> to_vec() { return vector<T>(_begin, _end); }

    /**
     * Accesses the element at that point in the same way you do with a vector
     * @param idx The index of the element
     * @return A reference to the element at that point
     */
    T& operator[](size_t idx) { return *(_begin + idx); }

    /**
     * Returns the begin iterator
     * @return The begin iterator
     */
    It begin() { return _begin; }

    /**
     * Returns the end iterator
     * @return The end iterator
     */
    It end() { return _end; }

    /**
     * Returns a new range where the iterators are shifted to the right by a specified amount (left if the amount is negative)
     * @param amount The amount to shift the iterators in the new range by
     * @return A new range object, as specified
     */
    Range<T> shift(int amount) { return Range<T>(_begin + amount, _end + amount); }
};

/**
 * Creates a range out of the
 * @tparam T The
 * @param vec
 * @param L
 * @param R
 * @return
 */
template <typename T> Range<T> sublist(vector<T> &vec, int L, int R) {
    return Range<T>(vec);
}

template <typename T> vector<T> map(vector<T> &vec, function<T(T)> f) {
    vector<T> ret;
    for (auto e : vec)
        ret.push_back(f(e));
    return ret;
}

template <typename T> T reduce(Range<T> , function<T(T, T)> f) {

}
