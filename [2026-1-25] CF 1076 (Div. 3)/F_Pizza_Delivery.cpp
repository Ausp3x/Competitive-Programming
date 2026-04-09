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
    map<lng, vector<lng>> M;
    lng ax, ay, bx, by;
    cin >> ax >> ay >> bx >> by;
    M[ax].pb(ay);
    M[bx].pb(by);
    vector<lng> X(n);
    for (lng &x : X)
        cin >> x;
    vector<lng> Y(n);
    for (lng &y : Y)
        cin >> y;

    for (int i = 0; i < n; i++)
        M[X[i]].pb(Y[i]);

    lng ans = bx - ax;
    vector<vector<lng>> V;
    for (auto &[x, ys] : M) {
        sort(ys.begin(), ys.end());

        ans += ys.back() - ys[0];
        V.pb({ys[0], ys.back()});
    }
    
    int len = V.size();
    vector<vector<lng>> cur(len, vector<lng>(2));
    for (int i = 1; i < len; i++) {
        for (int j = 0; j < 2; j++)
            cur[i][j] = min(cur[i - 1][1] + abs(V[i][j] - V[i - 1][0]), 
                            cur[i - 1][0] + abs(V[i][j] - V[i - 1][1])); 
    }

    // for (int i = 0; i < len; i++)
    //     cout << i << ": " << cur[i][0] << ' ' << cur[i][1] << endl;

    cout << ans + min(cur[len - 1][0], cur[len - 1][1]) << endl;

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