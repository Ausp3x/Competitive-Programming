// 人外有人，天外有天
// author: Ausp3x
// g++ -Wall -Wextra -o <name> <name>.cpp
// <name>.exe < in > out

#pragma GCC optimize("O3, fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fi first
#define se second
#define pb push_back
// #define DEBUG
using lng = long long;
using lll = __int128;
template<typename T> 
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T> // lower_bound and upper_bound are broken
using indexed_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

int const INF32 = 0x3f3f3f3f;
lng const INF64 = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n;
    cin >> n;
    vector<int> A(n + 1), cnts(3);
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
        
        cnts[A[i]]++;
    }
    vector<vector<int>> adjl(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        adjl[u].pb(v);
        adjl[v].pb(u);
    }

    int ans = 0;
    vector<pair<int, int>> V(n + 1);
    auto dfs = [&](int cur, int prv, auto &&dfs) -> void {
        if (A[cur] == 1)
            V[cur].fi = 1;
        else if (A[cur] == 2)
            V[cur].se = 1;
        for (int nxt : adjl[cur]) {
            if (nxt == prv)
                continue;
            
            dfs(nxt, cur, dfs);
            V[cur].fi += V[nxt].fi;
            V[cur].se += V[nxt].se;
        }

        if ((V[cur].fi == cnts[1] && V[cur].se == 0) || (V[cur].fi == 0 && V[cur].se == cnts[2]))
            ans++;
    };

    dfs(1, 1, dfs);

    cout << ans << endl;
    
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}