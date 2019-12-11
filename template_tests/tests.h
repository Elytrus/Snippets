#pragma once

/**
 * A single test suite
 * @tparam TestData The type of test data, used to pass input into the testing function
 */
template <typename TestData>
class Test {
public:
    /**
     * Constructor for test object
     * @param generate_func0 A function that returns some generated test data
     * @param run_test_func0
     * @param name0
     * @param num_tests0
     */

    virtual string get_name() = 0;
    virtual int get_num_tests() { return 20; }
    virtual TestData generate_data() = 0;
    virtual bool run_test(TestData test) = 0;

    /**
     * Runs the test cases
     * @return Whether the cases passed or not
     */
    bool run() {
        int num_tests = get_num_tests();
        cout << "Beginning test cases \"" << get_name() << "\"..." << endl;

        int fail = 0;
        for (int i = 0; i < num_tests; i++) {
            bool result = run_test(generate_data());
            fail += !result;
        }

        if (fail > 0)
            cout << "Failed " << fail << " tests out of " << num_tests << "!" << endl;
        else
            cout << "Passed all " << num_tests << " tests!" << endl;

        return fail > 0;
    }
};
