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
typedef __int128     lll;
template<class T> 
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T> // lower_bound and upper_bound are broken
using indexed_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

int const INF32 = 0x3f3f3f3f;
lng const INF64 = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int m;
    cin >> m;

    int all_xor = 0;
    for (int i = 1; i <= m; i++)
        all_xor ^= i;

    if (all_xor == m) {
        cout << m << endl;
        for (int i = 1; i <= m; i++)
            cout << i << ' ';
        cout << endl;
        return;
    }

    int almost_all_xor = all_xor;
    for (int i = 1; i <= m; i++) {
        almost_all_xor ^= i;

        if (almost_all_xor == m) {
            cout << m - 1 << endl;
            for (int j = 1; j <= m; j++) {
                if (j == i)
                    continue;

                cout << j << ' ';
            }
            cout << endl;
            return;
        }

        almost_all_xor ^= i;
    }
    
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