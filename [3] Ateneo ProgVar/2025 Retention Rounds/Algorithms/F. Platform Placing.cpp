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
    lng n, s, k;
    cin >> n >> s >> k;
    vector<lng> A;
    A.pb(-INF64);
    for (int i = 0; i < n; i++) {
        lng a;
        cin >> a;

        A.pb(2 * a);
    }
    A.pb(INF64);

    sort(A.begin(), A.end());

    for (int i = 1; i < A.size(); i++)
        if (A[i] - A[i - 1] < 2 * s) {
            cout << -1 << endl;
            return;
        }

    lng ans = 0, cur = -INF64 + s;
    for (int i = 1; i <= n; i++) {
        lng l = A[i] - cur;
        lng r = A[i + 1] - A[i] - s;
        lng to_add = min({l, r, k});
        
        // cout << to_add << ' ';
        ans += to_add;
        cur = A[i] + to_add;
    }
    // cout << endl;

    cout << ans << endl;

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