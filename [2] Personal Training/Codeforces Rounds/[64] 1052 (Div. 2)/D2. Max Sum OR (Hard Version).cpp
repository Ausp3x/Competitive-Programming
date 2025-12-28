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
    int L, R;
    cin >> L >> R;

    int l = L, r = R;
    map<int, int> ans;
    while (r >= l) {
        // cout << l << ' ' << r << endl;
        if (l == r) {
            ans[l] = l;
            l++;
            continue;
        }

        int m = 0;
        for (int i = 29; i >= 0; i--) {
            if ((l & (1 << i)) && (r & (1 << i))) {
                m += 1 << i;
            } else if (!(l & (1 << i)) && (r & (1 << i))) {
                m += 1 << i;
                break;
            }
        }

        int d = min(r - m, m - l - 1);
        for (int i = 0; i <= d; i++) {
            ans[m - i - 1] = m + i;
            ans[m + i] = m - i - 1;
        }

        if (l == m - d - 1)
            l = m + d + 1;
        if (r == m + d)
            r = m - d - 2;
    }

    lng sum = 0;
    for (int i = L; i <= R; i++) 
        sum += (i | ans[i]);

    cout << sum << endl;
    for (int i = L; i <= R; i++) 
        cout << ans[i] << ' ';
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