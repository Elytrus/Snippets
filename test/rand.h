#pragma once

#include "global_includes.h"

namespace charsets {
    const string LOWER = "abcdefghijklmnopqrstuvwxyz";
    const string UPPER = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string DIGS = "0123456789";
    const string ALPHA = LOWER + UPPER;
    const string ALPHANUM = ALPHA + DIGS;
    const string SYMBOLS = ".,/<>?!@#$%^&*()-=_+`~[]{};':\"\\|";
    const string SPACE = " ";
    const string ALL = ALPHANUM + SYMBOLS;
    const string ALL_SPACE = ALL + SPACE;

    /**
     * Converts string to vector<char>
     * @param s The string
     * @return The string, as a vector<char>
     */
    vector<char> string_to_vector(string s) {
        return vector<char>(s.begin(), s.end());
    }

    // All of the default available charsets
#define CHARSET_STRING_TO_VECTOR(name, string) const vector<char> name = string_to_vector(string)
    CHARSET_STRING_TO_VECTOR(lower, LOWER); // lowercase letters
    CHARSET_STRING_TO_VECTOR(upper, UPPER); // uppercase letters
    CHARSET_STRING_TO_VECTOR(digs, DIGS); // digits
    CHARSET_STRING_TO_VECTOR(alpha, ALPHA); // lowercase and uppercase letters
    CHARSET_STRING_TO_VECTOR(alphanum, ALPHANUM); // all alphanumeric
    CHARSET_STRING_TO_VECTOR(symbols, SYMBOLS); // all symbols (on a standard qwerty keyboard)
    CHARSET_STRING_TO_VECTOR(space, SPACE); // the space
    CHARSET_STRING_TO_VECTOR(all, ALL); // symbols and alphanumeric
    CHARSET_STRING_TO_VECTOR(all_space, ALL_SPACE); // `all` with space also


    /**
     * Concatenates charsets (vector<char>)s
     * @tparam Ts Any value charset type (with base class vector<char>)
     * @param first_charset The first charset
     * @param charsets The other charsets
     * @return The concatenation of the charsets
     */
    template <typename... Ts> vector<char> concat(vector<char> first_charset, Ts... charsets) {
        // Checks if all the charsets are derived from vector<char>
        static_assert(static_all_of<is_base_of<vector<char>, Ts>::value...>::value, "T must derive from std::vector<char>!");

        for (vector<char> charset : vector<vector<char>>{charsets...})
            first_charset.insert(first_charset.end(), charset.begin(), charset.end());
        return first_charset;
    }

    /**
     * Same as the above function but treats a string as a charset
     * @param charset The first charset
     * @param chars_to_append The chars to append (only one parameter is allowed here as concatenating strings is trivial)
     * @return The concatenation of the charsets
     */
    vector<char> concat(const vector<char> &charset, const string &chars_to_append) {
        return concat(charset, string_to_vector(chars_to_append));
    }
}

namespace __rand {
    mt19937 mt;
    mt19937_64 mt64;

    /**
     * Inits RNG with set seed
     * @param seed The seed
     */
    void rand_init(ll seed) {
        mt = mt19937(seed);
        mt64 = mt19937_64(seed);
    }

    /**
     * Inits RNG with a seed determined by the current system time in ms
     */
    void rand_init() {
        rand_init(timeMs());
    }

    // NUMBERS

    /**
     * Analogous to Python's random.randint
     * @param l Left bound
     * @param r Right bound
     * @return A random integer in range [l, r]
     */
    int randint(int l, int r) {
        return uniform_int_distribution<int>(l, r)(mt);
    }

    /**
     * Randint but for 64-bit values
     * @param l Left bound
     * @param r Right bound
     * @return A random integer in the range [l, r]
     */
    ll randlong(ll l, ll r) {
        return uniform_int_distribution<ll>(l, r)(mt64);
    }

    /**
     * Random floating point between l and r
     * @param l Left bound
     * @param r Right bound
     * @return A random floating-point value in the range [l, r]
     */
    double randdouble(double l, double r) {
        return uniform_real_distribution<double>(l, r)(mt64);
    }

    /**
     * Returns a function that generates a random int in the range [l, r]
     * @param l Left bound
     * @param r Right bound
     * @return A function that generates a random int in the range [l, r]
     */
    function<int()> randintfunc(int l, int r) {
        return bind(randint, l, r);
    }

    /**
     * Returns a function that generates a random long in the range [l, r]
     * @param l Left bound
     * @param r Right bound
     * @return A function that generates a random long in the range [l, r]
     */
    function<ll()> randlongfunc(ll l, ll r) {
        return bind(randlong, l, r);
    }

    /**
     * Returns a function that generates a random floating point value in the range [l, r]
     * @param l Left bound
     * @param r Right bound
     * @return A function that generates a random floating point value in the range [l, r]
     */
    function<double()> randdoublefunc(double l, double r) {
        return bind(randdouble, l, r);
    }

    // LISTS (VECTORS)
    /**
     * Returns a random position in a specified vector
     * @tparam T The data type of the vector
     * @param vec The vector
     * @return A random position in that vector
     */
    template <typename T> int randpos(vector<T> &vec) {
        return randint(0, vec.size() - 1);
    }

    /**
     * Returns a random element in a specified vector
     * @tparam T The data type of the vector
     * @param vec The vector
     * @return A random element in a specified vector
     */
    template <typename T> T choice(vector<T> &vec) {
        return vec[randpos(vec)];
    }

    /**
     * Shuffles a specified vector (in-place)
     * @tparam T The data type of the vector
     * @param vec The vector
     */
    template <typename T> void shuffle(vector<T> &vec) {
        for (size_t i = 0; i < vec.size(); i++) {
            int a = randpos(vec), b = randpos(vec);
            swap(vec[a], vec[b]);
        }
    }

    /**
     * Generates a random vector of size N using the function provided
     * @tparam T The data type of the vector
     * @param N The size of the vector
     * @param f The function used to create the elements.  It should return a random element of the specified type every time it's called
     * @return The random vector
     */
    template <typename T> vector<T> randseq(int N, function<T()> f) {
        vector<T> ret;
        while (N--)
            ret.push_back(f());
        return ret;
    }

    /**
     * Generates a random vector of size N using the function provided.  However, all elements in the vector should be unique.
     * Additionally, the data type specified should have the less than comaprison operator defined (to check for duplicates)
     * @tparam T The data type of the vector
     * @param N The size of the vector
     * @param f The function used to create the elements.  It should return a random element of the specified type every time it's called
     * @return The random vector
     */
    template <typename T> vector<T> randuniqueseq(int N, function<T()> f) {
        set<T> vals_unique;
        while (vals_unique.size() < N)
            vals_unique.insert(f());
        vector<T> ret(vals_unique.begin(), vals_unique.end());
        shuffle(ret);
        return ret;
    }

    /**
     * Returns N random elements from a list of choices
     * @tparam T The data type of each choice
     * @param N The amount of elements to return
     * @param choices The available choices
     * @return The N random elements
     */
    template <typename T> vector<T> choices(int N, vector<T> choices) {
        return randseq(N, bind(choice, choices));
    }

    /**
     * Returns N distinct random elements from a list of choices
     * @tparam T The data type of each choice
     * @param N The amount of elements to return
     * @param choices The available choices
     * @return The N random elements
     */
    template <typename T> vector<T> sample(int N, vector<T> choices) {
        return randuniqueseq(N, bind(choice, choices));
    }

    // NUMBER SEQUENCES
    /**
     * Returns a list with the numbers [L, L + step, L + 2 * step, ..., L + M * step] where L + M * step is the largest number <= R
     * @param L The left boundary
     * @param R The right boundary
     * @param step The step, defaults to one
     * @return The list, as stated above
     */
    vector<int> range(int L, int R, int step = 1) {
        vector<int> ret;
        for (int i = L; i <= R; i += step)
            ret.push_back(i);
        return ret;
    }

    /**
     * Returns a random permutation of the integers 1..N
     * @param N N
     * @return The permutation, as stated above
     */
    vector<int> permutation(int N) {
        vector<int> ret = range(1, N);
        shuffle(ret);
        return ret;
    }
}

using __rand::rand_init;

// Numbers
using __rand::randint;
using __rand::randlong;
using __rand::randdouble;
using __rand::randintfunc;
using __rand::randlongfunc;
using __rand::randdoublefunc;

// List (vector) operations
using __rand::randpos;
using __rand::choice;
using __rand::shuffle;
using __rand::randseq;
using __rand::randuniqueseq;
using __rand::choices;
using __rand::sample;

// Sequence operations
using __rand::range;
using __rand::permutation;
