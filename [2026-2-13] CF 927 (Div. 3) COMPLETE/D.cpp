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
    char t;
    cin >> t;
    vector<string> S(2 * n);
    for (auto &s : S)
        cin >> s;

    vector<int> I(2 * n);
    iota(I.begin(), I.end(), 0);

    auto chk = [&](int i, int j) -> pair<int, int> {
        if (S[i][1] != S[j][1] && S[i][1] != t && S[j][1] != t)
            return {-1, -1};

        if (S[i][1] != S[j][1]) {
            if (S[i][1] == t)
                swap(i, j);
        } else {
            if (S[i][0] > S[j][0])
                swap(i, j);
        }

        return {i, j};
    };

    map<vector<int>, vector<pair<int, int>>> M; 
    auto dfs = [&](vector<int> cur, auto &&dfs) -> void {
        if (cur.empty() || !M[cur].empty())
            return;

        int len = cur.size();
        for (int i = 0; i < len; i++)
            for (int j = i + 1; j < len; j++) {
                auto [a, b] = chk(cur[i], cur[j]);
                // cout << i << ' ' << j << ' ' << cur[i] << ' ' << cur[j] << ' ' << a << ' ' << b << endl;
                if (a == -1)
                    continue;

                vector<int> nxt;
                for (int x : cur)
                    if (x != a && x != b)
                        nxt.pb(x);

                dfs(nxt, dfs);
                
                if (M[nxt] != vector<pair<int, int>>({{-1, -1}})) {
                    M[cur] = M[nxt];
                    M[cur].pb({a, b});
                    return;
                }
            }
        M[cur] = {{-1, -1}};

        return;
    };

    dfs(I, dfs);

    // for (auto &[k, v] : M) {
    //     for (int x : k)
    //         cout << x << ' ';
    //     cout << ": ";
    //     for (auto &[a, b] : v)
    //         cout << '(' << a << ',' << b << ") ";
    //     cout << endl; 
    // }

    if (M[I] == vector<pair<int, int>>({{-1, -1}})) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    for (auto &[a, b] : M[I]) 
        cout << S[a] << ' ' << S[b] << endl; 
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