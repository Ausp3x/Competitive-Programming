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
    int n;
    cin >> n;
    vector<vector<int>> adjl(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        adjl[u].pb(v);
        adjl[v].pb(u);
    }

    int req = (n + 1) / 2, to_pair = -1;
    vector<pair<int, int>> P;
    auto dfs = [&](int cur, int prv, auto &&dfs) -> void {
        if (to_pair != -1) {
            P.pb({to_pair, cur});
            to_pair = -1;
        } else {
            to_pair = cur;
        }

        for (int nxt : adjl[cur]) {
            if (nxt == prv)
                continue;
            
            dfs(nxt, cur, dfs);
        }
    };

    dfs(1, 1, dfs);
    if (to_pair != -1)
        P.pb({to_pair, to_pair});

    // for (auto &[u, v] : P)
    //     cout << u << ' ' << v << endl;
    // cout << endl;

    bool res;
    for (int i = 0; i < P.size() - 1; i++) {
        cout << "? " << P[i].fi << ' ' << P[i].se << endl;        
        cin >> res;

        if (!res) 
            continue;
        
        cout << "? " << P[i].fi << ' ' << P[i].fi << endl;
        cin >> res;

        cout << "! " << (res ? P[i].fi : P[i].se) << endl;    
        return;
    }
    cout << "? " << P.back().fi << ' ' << P.back().fi << endl;
    cin >> res;
    
    cout << "! " << (res ? P.back().fi : P.back().se) << endl;

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