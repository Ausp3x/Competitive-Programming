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

    int d1 = -1, dep = 0;
    auto dfs1 = [&](int cur, int prv, int cur_dep, auto &&dfs1) -> void {
        if (cur_dep > dep) {
            d1 = cur;
            dep = cur_dep;
        }

        for (int nxt : adjl[cur]) {
            if (nxt == prv)
                continue;
            
            dfs1(nxt, cur, cur_dep + 1, dfs1);
        }
    };

    dfs1(1, 1, 1, dfs1);
    
    int d2 = -1; dep = 0;
    auto dfs2 = [&](int cur, int prv, int cur_dep, auto &&dfs2) -> void {
        if (cur_dep > dep) {
            d2 = cur;
            dep = cur_dep;
        }

        for (int nxt : adjl[cur]) {
            if (nxt == prv)
                continue;
            
            dfs2(nxt, cur, cur_dep + 1, dfs2);
        }
    };

    dfs2(d1, d1, 1, dfs2);

    // cout << dep << ": " << d1 << ' ' << d2 << endl;

    vector<int> siz(n + 1);
    auto isCaterpillar = [&](int cur, int prv, auto &&isCaterpillar) -> bool {
        siz[cur]++;
        vector<int> V;
        for (auto nxt : adjl[cur]) {
            if (nxt == prv)
                continue;

            bool res = isCaterpillar(nxt, cur, isCaterpillar);
            if (!res)
                return false;

            siz[cur] += siz[nxt];
            V.pb(siz[nxt]);
        }

        sort(V.begin(), V.end(), greater<int>());

        if (V.size() > 1)
            if (V[1] > 1)
                return false;

        return true;
    };

    if (!isCaterpillar(d1, d1, isCaterpillar)) {
        cout << -1 << endl;
        return;
    }

    int a;
    vector<int> P;
    auto genPermutation = [&](int cur, int prv, auto &&genPermutation) -> void {
        vector<int> V;
        for (auto nxt : adjl[cur]) {
            if (nxt == prv)
                continue;

            V.pb(siz[nxt]);
        }

        sort(V.begin(), V.end(), greater<int>());

        int len = lng(V.size()) - 1;
        for (int i = a + 1; i <= a + len; i++)
            P.pb(i);
        P.pb(a);
        a += len + 1;

        for (auto nxt : adjl[cur]) {
            if (nxt == prv)
                continue;

            if (siz[nxt] == V[0]) {
                genPermutation(nxt, cur, genPermutation);
                break;
            }
        }        
    };

    a = 1;
    genPermutation(d1, d1, genPermutation);
    
    vector<int> P1 = P;

    // for (int x : P1)
    //     cout << x << ' ';
    // cout << endl;

    siz.clear();
    siz.resize(n + 1);
    isCaterpillar(d2, d2, isCaterpillar);

    a = 1;
    P.clear();
    genPermutation(d2, d2, genPermutation);

    vector<int> P2 = P;

    // for (int x : P2)
    //     cout << x << ' ';
    // cout << endl;

    if (P1 < P2) {
        for (int x : P1)
            cout << x << ' ';
        cout << endl;
    } else {
        for (int x : P2)
            cout << x << ' ';
        cout << endl;
    }

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