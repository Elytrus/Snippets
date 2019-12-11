#pragma once

// Macros
#define CATEGORY(x) cout << "-- -- Beginning Test Category: " << x << "\n"
#define WRONG(answer, expected) cout << "Incorrect Test, got " << answer << ", expected " << expected << "\n"

#include "global_includes.h"

// Variadic static_assert, from https://stackoverflow.com/questions/13562823/parameter-pack-aware-stdis-base-of
// Given a variadic number of constexprs, return if all are true
template <bool... b> struct static_all_of;
template <bool... tail> struct static_all_of<true, tail...> : static_all_of<tail...> {};
template <bool... tail> struct static_all_of<false, tail...> : false_type {};
template <> struct static_all_of<> : true_type {};

// Comparison
/**
 * Compars equality between two vectors.  Two vectors are equal if all of their elements are equal
 * @tparam T The data type of the vectors
 * @param a The first vector
 * @param b The second vector
 * @return Whether they are equal
 */
template <typename T> bool vector_equals(vector<T> a, vector<T> b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); i++)
        if (a[i] != b[i])
            return false;
    return true;
}

/**
 * Compars equality between two vectors.  Two vectors are equal if all of their elements are equal
 * @tparam T The data type of the vectors
 * @param a The first vector
 * @param b The second vector
 * @param eq_fun Function to compare equality with
 * @return Whether they are equal
 */
template <typename T> bool vector_equals(vector<T> a, vector<T> b, function<bool(T, T)> eq_fun) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); i++)
        if (!eq_fun(a[i], b[i]))
            return false;
    return true;
}

/**
 * Compares equality between doubles.  It checks whether their difference is within a certain value (epsilon)
 * @param a First double
 * @param b Second double
 * @param eps The precision (epsilon) used for comparison.  Defaults to the epsilon provided by std::numeric_limits
 * @return
 */
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

    /// Converts the range to a vector
    vector<T> to_vec() { return vector<T>(_begin, _end); }

    /**
     * Accesses the element at that point in the same way you do with a vector
     * @param idx The index of the element
     */
    T& operator[](size_t idx) { return *(_begin + idx); }

    /// Returns the begin iterator
    It begin() { return _begin; }

    /// Returns the end iterator
    It end() { return _end; }

    /// Returns the size of the range
    int size() { return _end - _begin; }

    /// Returns whether the range being represented has a size of zero
    bool empty() { return _end == _begin; }

    /**
     * Returns a new range where the iterators are shifted to the right by a specified amount (left if the amount is negative)
     * @param amount The amount to shift the iterators in the new range by
     */
    Range<T> shift(int amount) { return Range<T>(_begin + amount, _end + amount); }

    /**
     * Returns a new range where the begin iterator are shifted to the right by a specified amount (left if the amount is negative)
     * @param amount The amount to shift the begin iterator in the new range by
     */
    Range<T> shift_l(int amount) { return Range<T>(_begin + amount, _end); }

    /**
     * Returns a new range where the end iterator are shifted to the right by a specified amount (left if the amount is negative)
     * @param amount The amount to shift the end iterator in the new range by
     */
    Range<T> shift_r(int amount) { return Range<T>(_begin, _end + amount); }
};

/// Map function similar to those in many functional languages
template <typename T> vector<T> map(vector<T> &vec, function<T(T)> func) {
    vector<T> ret;
    for (auto e : vec)
        ret.push_back(func(e));
    return ret;
}

/// Reduce function with starting value, similar to those in many functional languages
template <typename T> T reduce(Range<T> range, T start, function<T(T, T)> func) {
    T ret = start;
    while (!range.empty()) {
        ret = func(ret, range[0]);
        range = range.shift_l(1);
    }
    return ret;
}

/// Reduce function without starting value, similar to those in many functional languages
template <typename T> T reduce(Range<T> range, function<T(T, T)> func) {
    if (range.empty()) throw out_of_range("range is empty!");
    return reduce(range.shift_l(1), range[0], func);
}

/// Reduce function without starting value, similar to those in many functional languages.  This one converts the vector to a range first
template <typename T> T reduce(vector<T> range, function<T(T, T)> func) { return reduce(Range<T>(range), func); }

/// Reduce function with starting value, similar to those in many functional languages.  This one converts the vector to a range first
template <typename T> T reduce(vector<T> range, T start, function<T(T, T)> func) { return reduce(Range<T>(range), start, func); }
