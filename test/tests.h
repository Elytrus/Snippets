#pragma once

/**
 * A single test suite
 * @tparam TestData The type of test data, used to pass input into the testing function
 */
template <typename TestData>
class Test {
private:
    string name;
    int num_tests;
    function<TestData()> generate_func;
    function<bool(TestData)> run_test_func;

public:
    /**
     * Constructor for test object
     * @param generate_func0 A function that returns some generated test data
     * @param run_test_func0
     * @param name0
     * @param num_tests0
     */
    Test(function<TestData()> generate_func0, function<bool(TestData)> run_test_func0, string name0, int num_tests0 = 20) :
    generate_func(generate_func0), run_test_func(run_test_func0), name(name0), num_tests(num_tests0) {}

    /**
     * Runs the test cases
     * @return Whether the cases passed or not
     */
    bool run() {
        cout << "Beginning Test Cases" << name << "..." << endl;
        int fail = 0;
        for (int i = 0; i < num_tests; i++) {
            bool result = run_test_func(generate_func());
            fail += !result;
        }

        if (fail > 0)
            cout << "Failed " << fail << " tests out of " << num_tests << "!" << endl;
        else
            cout << "Passed all " << num_tests << "tests!" << endl;

        return fail > 0;
    }
};
