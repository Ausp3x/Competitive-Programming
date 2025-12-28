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
    lng l, r;
    cin >> l >> r;

    vector<lng> P = {2, 3, 5, 7};

    lng ans = 0;
    for (int i = 1; i < 16; i++) {
        int cnt = 0;
        lng q = 1;
        for (int j = 0; j < 4; j++) 
            if (i & (1 << j)) {
                cnt++;
                q *= P[j];
            }

        lng cur = r / q - (l - 1) / q;
        if (cnt % 2) 
            ans += cur;
        else
            ans -= cur;
    }

    cout << r - l + 1 - ans << endl;

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