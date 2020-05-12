# Snippets
Data Structure and Algorithm Snippets

All snippets are written in C++

## Automated tester

After installing the prerequisites from `requirements.txt`, simply run `python test_lib/main.py` to test all templates at once.  Alternatively, you can run `python test_lib/main.py <file_name>` to test a single template.  Note that `<file_name>` must be the name of a source file in the `test/` directory (it doesn't have to be the full path, the program will try to match `<file_name>` to the correct test file to compile and run).

Examples:

- `python test_lib/main.py` will test all templates
- `python test_lib/main.py bit.cpp` will test the BIT template using the test file `test/ds/bit.cpp`.
- `python test_lib/main.py graph_ds/unionfind.cpp` will test the unionfind template using the test file `test/graph_ds/unionfind.cpp`.  Note that simply specifying `unionfind` or `unionfind.cpp` in place of `graph_ds/unionfind.cpp` would have worked as well.

Note that in the case of multiple file paths matching the given `<file_name>` argument, the one that comes first in the `PROBLEMS` constant in `test_lib/main.py` will be used.

## Planned Templates/Other To-Dos

* DS
    * Dynamic Square Root Decomposition: [Maintaining Some Coins](https://dmoj.ca/problem/cpc19c1p6)
    * BIT Binary Search Technique: [Wowow](https://dmoj.ca/problem/cco10p3)
    * N-Dimensional BIT: [Inaho 2](https://dmoj.ca/problem/inaho2)
    * ALL DS and graph template: switch to using constructors instead of init function (when possible)
* Algorithms
    * Centroid Tree (Flexible template, similar to trie)
    * Kruskal MST
* Utilities
    * Fast Clearing Array (An array that can reset itself in O(1) time.  Useful for centroid decomposition problems
    * Fast Clearing Array 2 (An alternative to the Fast Clearing Array that sets everything back by using a vector to track changes, clear runs in amortized O(1))

* Stuff Learned
    * CRT
    * Miller-Rabin Primality Test
    * Pollard-Rho Factoring (?)
    * CDQ
    * Difference Array on Euler Tour for bit queries

## Templates that need to be ported

* Prefix Sum/Max/Min array, Difference Array