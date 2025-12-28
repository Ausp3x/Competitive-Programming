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

int const MOD = 998'244'353;

struct BridgeAlgo {
    int n, timer = 0;
    vector<bool> vst;
    vector<int> t_in, low;
    set<pair<int, int>> bridges;

    BridgeAlgo(int n, const vector<vector<int>> &adjl): n(n) {
        vst.resize(n);
        t_in.resize(n, -1);
        low.resize(n, -1);

        for (int i = 0; i < n; i++) {
            if (!vst[i]) {
                dfs(i, i, adjl);
            }
        }        
    }

    void dfs(int cur, int prv, const vector<vector<int>> &adjl) {
        vst[cur] = true;
        t_in[cur] = timer;
        low[cur] = timer;
        timer++;
        
        bool prv_skipped = false;
        for (int nxt : adjl[cur]) {
            if (nxt == prv && !prv_skipped) {
                prv_skipped = true;
                continue;
            }

            if (vst[nxt]) {
                low[cur] = min(low[cur], t_in[nxt]);
            } else {
                dfs(nxt, cur, adjl);

                low[cur] = min(low[cur], low[nxt]);
                if (low[nxt] > t_in[cur]) {
                    bridges.insert({min(cur, nxt), max(cur, nxt)});
                }
            }
        }
    }
};

void solve() {
    int n, m;
    lng V;
    cin >> n >> m >> V;
    vector<int> A(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> A[i];
    vector<pair<int, int>> edgl(m);
    vector<vector<int>> adjl(n + 1);
    for (auto &[u, v] : edgl) {
        cin >> u >> v;

        adjl[u].pb(v);
        adjl[v].pb(u);
    }

    BridgeAlgo ba(n + 1, adjl);

    vector<vector<int>> new_adjl(n + 1);
    for (auto [u, v] : edgl) {
        if (ba.bridges.find({min(u, v), max(u, v)}) != ba.bridges.end())
            continue;

        new_adjl[u].pb(v);
        new_adjl[v].pb(u);
    }

    lng ans = 1;
    vector<int> clr(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        if (clr[i] != -1)
            continue;

        bool has_odd_cycle = false;
        vector<int> used;
        queue<pair<int, int>> q;
        q.push({i, -1});
        clr[i] = 0;
        while (!q.empty()) {
            auto [cur, prv] = q.front();
            q.pop();
            
            used.pb(cur);
            for (int nxt : new_adjl[cur]) {
                if (nxt == prv) 
                    continue;
                
                if (clr[nxt] != -1) {
                    if (clr[nxt] != clr[cur] ^ 1)
                        has_odd_cycle = true;
                    continue;
                }

                q.push({nxt, cur});
                clr[nxt] = clr[cur] ^ 1;
            }
        }

        if (used.size() == 1) {
            if (A[i] == -1) {
                ans *= V;
                ans %= MOD;
            }
            
            continue;
        }

        bool is_valid = true;
        int cur = -1;
        for (int u : used) {
            if (A[u] == -1)
                continue;

            if (cur == -1) {
                cur = A[u];
                continue;
            }

            if (A[u] != cur) {
                is_valid = false;
                break;
            }
        }

        if (!is_valid || (cur != -1 && cur != 0 && has_odd_cycle)) {
            ans = 0;
            break;
        }

        if (cur == -1 && !has_odd_cycle) {
            ans *= V;
            ans %= MOD;
            continue;
        }
    }

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