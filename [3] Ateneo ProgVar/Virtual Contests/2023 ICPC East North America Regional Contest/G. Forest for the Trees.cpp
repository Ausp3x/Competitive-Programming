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
template<class T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int const INF32 = 0x3f3f3f3f;
lng const INF64 = 0x3f3f3f3f3f3f3f3f;

void rotate90(int &x, int &y) {
    swap(x, y);
    x = -x;

    return;
}

int nt, ns, r_max;
vector<pair<int, int>> XYt;
vector<pair<int, int>> XYs;
vector<tuple<int, int, int>> ans;
void calc(int rotations) {
    for (int i = 0; i < nt; i++) {
        int x = XYt[i].fi - XYs[0].fi;
        int y = XYt[i].se - XYs[0].se;

        vector<pair<int, int>> detected;
        detected.pb(XYs[0]);  
        for (int j = 0; j < nt; j++) {
            if (j == i)
                continue;

            if (abs(XYt[j].fi - x) + abs(XYt[j].se - y) <= r_max)
                detected.pb({XYt[j].fi - x, XYt[j].se - y});
        }

        if (detected.size() != XYs.size())
            continue;

        sort(detected.begin(), detected.end());

        if (detected == XYs) {
            for (int i = 0; i < 4 - rotations; i++)
                rotate90(x, y);

            ans.pb({x, y, rotations});
        }
    }
}

void solve() {
    cin >> nt >> ns >> r_max;
    XYt.clear();
    XYt.resize(nt);
    map<pair<int, int>, bool> in_XYt;
    for (auto &[xt, yt] : XYt) {
        cin >> xt >> yt;
        in_XYt[{xt, yt}] = true;
    }
    XYs.clear();
    XYs.resize(ns);
    for (auto &[xs, ys] : XYs)
        cin >> xs >> ys;
    
    sort(XYs.begin(), XYs.end());

    for (int i = 0; i < 4; i++) {
        calc(i);

        for (auto &[xt, yt] : XYt)
            rotate90(xt, yt);
    }

    if (ans.empty()) {
        cout << "Impossible" << endl;
        return;
    }

    if (ans.size() > 1) {
        cout << "Ambiguous" << endl;
        return;
    }

    if (in_XYt[{get<0>(ans[0]), get<1>(ans[0])}]) {
        cout << "Impossible" << endl;
        return;
    }

    cout << get<0>(ans[0]) << ' ' << get<1>(ans[0]) << endl;

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