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
    int root = -1;
    vector<int> par(n + 1);
    vector<vector<int>> adjl(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> par[i];

        if (i == par[i]) {
            root = i;
            continue;
        }

        adjl[par[i]].pb(i);
        adjl[i].pb(par[i]);
    }

    if (n == 1) {
        cout << 1 << endl;
        cout << 1 << endl;
        cout << 1 << endl;
        cout << endl;
        return;
    }

    // for (int i = 1; i <= n; i++) {
    //     cout << i << ": ";
    //     for (int x : adjl[i])
    //         cout << x << ' ';
    //     cout << endl;
    // }

    queue<int> q;
    vector<bool> vst(n + 1);
    vector<vector<int>> ans(n + 1);
    for (int i = 1; i <= n; i++) {
        if (i == root)
            continue;

        if (adjl[i].size() == 1) {
            q.push(i);
            vst[i] = true;
            ans[i].pb(i);
        }
    }

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        if (!vst[par[cur]]) {
            ans[cur].swap(ans[par[cur]]);
            
            q.push(par[cur]);
            vst[par[cur]] = true;
            ans[par[cur]].pb(par[cur]);
        }
    }

    sort(ans.begin(), ans.end(), greater<vector<int>>());
    while (ans.back().empty())
        ans.pop_back();

    cout << ans.size() << endl;
    for (auto x : ans) {
        reverse(x.begin(), x.end());

        cout << x.size() << endl;
        for (int y : x)
            cout << y << ' ';
        cout << endl;
    }
    cout << endl;

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