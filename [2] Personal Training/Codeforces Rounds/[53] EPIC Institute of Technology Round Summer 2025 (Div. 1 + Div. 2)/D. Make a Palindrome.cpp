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
    int n, k;
    cin >> n >> k;
    map<int, vector<int>> idxs;
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        idxs[A[i]].pb(i);
    }

    if (k == 1) {
        cout << "YES" << endl;
        return;
    }

    int cur = 0;
    set<pair<int, int>> S;
    while (cur + idxs.begin()->se.size() < k) {
        auto [x, I] = *idxs.begin();
        
        cur += I.size();
        for (int i : I)
            S.insert({i, x});

        idxs.erase(idxs.begin());
    }

    vector<pair<int, int>> SV;
    for (auto x : S)
        SV.pb(x);

    int len = SV.size();
    for (int i = 0; i < len; i++) 
        if (SV[i].se != SV[len - i - 1].se) {
            cout << "NO" << endl;
            return;
        }

    if (len >= k - 1) {
        cout << "YES" << endl;
        return;
    }

    vector<int> bars = {-1};
    for (int i = 0; i < len; i++)
        bars.pb(SV[i].fi);
    bars.pb(n);    

    set<int> stars;
    for (int i : idxs.begin()->se)
        stars.insert(i);

    int len2 = bars.size();
    if (len2 % 2 == 0) {
        int i = len2 / 2 - 1;
        while (stars.lower_bound(bars[i]) != stars.end()) {
            int j = *stars.lower_bound(bars[i]);

            if (j > bars[i + 1])
                break;

            len++;
            stars.erase(j);
        } 
    }

    if (len >= k - 1) {
        cout << "YES" << endl;
        return;
    }

    for (int i = 0; i < (len2 - 1) / 2; i++) {
        int i2 = len2 - i - 2;
        while (stars.lower_bound(bars[i]) != stars.end() && stars.lower_bound(bars[i2]) != stars.end()) {
            int j = *stars.lower_bound(bars[i]);
            int j2 = *stars.lower_bound(bars[i2]);

            if (j > bars[i + 1] || j2 > bars[i2 + 1])
                break;

            len += 2;
            stars.erase(j);
            stars.erase(j2);
        }
    }

    cout << (len >= k - 1 ? "YES" : "NO") << endl;

    // for (auto [a, b] : SV)
    //     cout << b << ' ';
    // cout << endl;

    // for (int x : bars)
    //     cout << x << ' ';
    // cout << endl;
    
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