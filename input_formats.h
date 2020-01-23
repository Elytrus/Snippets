//begintemplate multiple_cases
//description Input with multiple test cases
void solve() {
    $3
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T; cin >> T;
    while (T--) {
        // Input
        $1

        // Reset
        $2

        solve();
    }
}
//endtemplate multiple_cases

//begintemplate usaco
//description usaco-style File I/O.  Assumes that -DLOCAL is passed when compiling locally
void init_file_io() {
    const string PROBLEM_ID = "${1:prob}";
    freopen((PROBLEM_ID + ".in").c_str(), "r", stdin);
    freopen((PROBLEM_ID + ".out").c_str(), "w", stdout);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef LOCAL
    init_file_io();
#endif

    $2
}
//endtemplate usaco

//begintemplate usacoheader
//description USACO training site file header.  Personalize this to fit your own needs
/*
ID: moses1
LANG: C++14
TASK: ${1:prob}
*/
$2
//endtemplate usacoheader
