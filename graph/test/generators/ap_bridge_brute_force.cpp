#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Defines
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f

// Scan and Debug
void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f,R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

const int MAX = 21;
int a[MAX], b[MAX];

template <int MAX>
struct Graph {
    int n, m, __ba, __bb; vector<int> matrix[MAX];
    void init(int n0, int m0) { n = n0; m = m0; }
    inline void addEdge(int a, int b) { matrix[a].push_back(b); }
    inline auto& adjs(int x) { return matrix[x]; }
    Graph& operator=(const Graph o) { n = o.n; m = o.m; copy(o.matrix, o.matrix + n + 1, matrix); return *this; }
    void input(bool undirected) { // Reads a graph's edges from stdin
        for (int i = 0; i < m; i++) {
            cin >> __ba >> __bb;
            a[i] = __ba; b[i] = __bb;
            addEdge(__ba, __bb);
            if (undirected) addEdge(__bb, __ba);
        }
    }
    auto transpose() { // Transposes the graph into its reversed form
        Graph<MAX> ret; ret.init(n, m);
        for (int i = 1; i <= n; i++)
            for (auto adj : adjs(i))
                ret.addEdge(adj, i);
        return ret;
    }
};

int n, m;
Graph<MAX> g;

void dfsArtic(int cur, int check, bool vis[]) {
    if (cur == check)
        return;
    vis[cur] = true;
    for (int adj : g.adjs(cur))
        if (!vis[adj])
            dfsArtic(adj, check, vis);
}

void dfsBridge(int cur, int sta, int stb, bool vis[]) {
    vis[cur] = true;
    for (int adj : g.adjs(cur))
        if (!vis[adj] && !(cur == sta && adj == stb))
            dfsBridge(adj, sta, stb, vis);
}

bool isArtic(int i) {
    bool vis[n + 1]; memset(vis, false, sizeof vis);
    int cnt = 0;
    for (int adj : g.adjs(i)) {
        if (!vis[adj]) {
            cnt++;
            dfsArtic(adj, i, vis);
        }
    }
    return cnt > 1;
}

bool isBridge(int a, int b) {
    bool vis[n + 1]; memset(vis, false, sizeof vis);
    int cnt = 0;
    dfsBridge(a, a, b, vis);
    return !vis[b];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, m);
    g.init(n, m);
    g.input(true);

    int sz = 0;
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        if (isArtic(i)) {
            sz++;
            ans.push_back(i);
        }
    }
    cout << sz << "\n";
    for (int x : ans)
        cout << x << "\n";

    sz = 0;
    vector<pair<pair<int, int>, int>> ans2;
    for (int i = 0; i < m; i++) {
        if (isBridge(a[i], b[i])) {
            sz++;
            ans2.push_back(make_pair(make_pair(a[i], b[i]), i));
        }
    }
    cout << sz << "\n";
    for (auto x : ans2)
        cout << "edge: " << x.first.first << " " << x.first.second << ", edge_id: " << x.second << "\n";

    return 0;
}