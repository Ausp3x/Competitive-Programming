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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> W(n);
    for (int i = 0; i < n; i++) {
        int l;
        cin >> l;

        W[i].resize(l);
        for (int j = 0; j < l; j++) {
            cin >> W[i][j];       
            W[i][j] += m;
        }
    }

    // for (auto x : W) {
    //     for (int y : x) 
    //         cout << y << ' ';
    //     cout << endl;
    // }

    set<int> req;
    vector<vector<int>> adjl(2 * m + 1);
    for (int i = 0; i < n - 1; i++) {
        int l = min(W[i].size(), W[i + 1].size());
        for (int j = 0; j < l; j++) {
            if (W[i][j] == W[i + 1][j])
                continue;
            
            if (W[i][j] > W[i + 1][j]) {
                req.insert(W[i][j]);
            } else {
                adjl[W[i + 1][j]].pb(W[i][j]);
            }
            break;
        }
    }

    queue<int> q;
    vector<int> vst(2 * m + 1);
    for (int x : req) {
        q.push(x);
        vst[x] = true;
    }
    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        req.insert(cur);

        for (int nxt : adjl[cur]) {
            if (vst[nxt])
                continue;

            q.push(nxt);
            vst[nxt] = true;
        }
    }

    // for (int x : req)
    //     cout << x << ' ';
    // cout << endl;

    for (int i = 0; i < n; i++) {
        for (int &x : W[i])
            if (req.find(x) != req.end())
                x -= m;
    }

    for (int i = 0; i < n - 1; i++)
        if (W[i] > W[i + 1]) {
            cout << "No" << endl;
            return;
        }

    cout << "Yes" << endl;
    cout << req.size() << endl;
    for (int x : req)
        cout << x - m << ' ';
    cout << endl;

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