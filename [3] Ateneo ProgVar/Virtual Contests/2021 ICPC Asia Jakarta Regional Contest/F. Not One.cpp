// 人外有人，天外有天
// author: Ausp3x

#pragma GCC optimize("O1, O2, O3, Ofast, unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fi first
#define se second
#define pb push_back
// #define DEBUG
typedef long long    lng;
typedef __int128     lll;
template<class T> 
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T> // lower_bound and upper_bound are broken
using indexed_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

int const INF32 = 0x3f3f3f3f;
lng const INF64 = 0x3f3f3f3f3f3f3f3f;

struct UnionFind {
    int n;
    vector<int> link, node_size, edge_size;

    UnionFind(int n): n(n) {
        link.resize(n + 1);
        iota(link.begin(), link.end(), 0);
        node_size.resize(n + 1, 1);
        edge_size.resize(n + 1);
    }

    int findSet(int u) {
        if (u == link[u]) {
            return link[u];
        }
            
        return link[u] = findSet(link[u]);
    }

    bool isSameSet(int a, int b) {
        return findSet(a) == findSet(b);
    }

    void uniteSets(int a, int b) {
        a = findSet(a);
        b = findSet(b);
        if (node_size[a] < node_size[b]) {
            swap(a, b);
        }

        if (a == b) {
            edge_size[a]++;
            return;
        }

        node_size[a] += node_size[b];
        edge_size[a] += edge_size[b] + 1;
        link[b] = a;

        return;
    }
};

int N = 100'005, a_max = 1'000'005;
vector<bool> is_prime(a_max, true);
vector<int> prime_fac(a_max, -1);
UnionFind uf(N);

void solve() {
    int n;
    cin >> n;
    vector<int> A(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> A[i];
    vector<vector<int>> adjl(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        adjl[u].pb(v);
        adjl[v].pb(u);
    }
    
    vector<vector<int>> U(a_max);
    vector<unordered_set<int>> US(a_max);
    for (int i = 1; i <= n; i++) {
        int a = A[i];
        while (prime_fac[a] != -1) {
            int p = prime_fac[a];
            U[p].pb(i);
            US[p].insert(i);
            while (a % p == 0)
                a /= p;
        }
    }

    int ans = 0;
    for (int p = 0; p < a_max; p++) {
        if (U[p].empty())
            continue;
        
        unordered_map<int, bool> vst;
        for (auto &cur : U[p]) {
            vst[cur] = true;
            for (auto &nxt : adjl[cur]) { 
                if (vst[nxt])
                    continue;

                if (US[p].find(nxt) != US[p].end())
                    uf.uniteSets(cur, nxt);
            }
        }

        for (auto &cur : U[p])
            ans = max(ans, uf.node_size[cur]);

        for (auto &cur : U[p]) {
            uf.link[cur] = cur;
            uf.node_size[cur] = 1;
            uf.edge_size[cur] = 0;
        }
    }   

    cout << ans << endl;

    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    is_prime[0] = is_prime[1] = false;
    for (lng i = 2; i < a_max; i++) {
        if (!is_prime[i])
            continue;
        prime_fac[i] = i;

        for (lng j = i * i; j < a_max; j += i) {
            is_prime[j] = false;
            prime_fac[j] = i;
        }
    }

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}