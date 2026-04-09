// 人外有人，天外有天
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fi first
#define se second
#define pb push_back
using lng = long long;
using lll = __int128;
template<typename T> 
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int const INF32 = 0x3f3f3f3f;
lng const INF64 = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n, k;
    cin >> n >> k;
    int x, y;
    cin >> x >> y;
    vector<int> A(n + 1);
    A[y] = 2;
    for (int i = 0; i < k; i++) {
        int a;
        cin >> a;

        A[a] = 1;
    }
    vector<vector<int>> adjl(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        adjl[u].pb(v);
        adjl[v].pb(u);
    }
    
    
    vector<int> par(n + 1);
    auto getA = [&](int cur, int prv, auto &&getA) -> void {
        par[cur] = prv;
        for (int nxt : adjl[cur]) {
            if (nxt == prv)
                continue;

            getA(nxt, cur, getA);

            A[cur] |= A[nxt];
        }
    
        return;
    };

    // root at x
    getA(x, x, getA);

    // for (int x : A)
    //     cout << x << ' ';
    // cout << endl;

    vector<int> B(n + 1);
    auto dfs = [&](int cur, auto &&dfs) -> void {
        for (int nxt : adjl[cur]) {
            if (nxt == par[cur])
                continue;

            if (A[nxt] == 0)
                continue;

            dfs(nxt, dfs);
            B[cur] += B[nxt] + 2;
        }

        return;
    };

    dfs(x, dfs);

    int ans = B[x];
    while (y != x) {
        ans--;
        y = par[y];
    }

    // for (int x : B)
    //     cout << x << ' ';
    // cout << endl;

    cout << ans << endl;

    return;
}   

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}