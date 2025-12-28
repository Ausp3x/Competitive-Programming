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
    int n, c;
    cin >> n >> c;
    vector<int> S(n);
    for (int &s : S)
        cin >> s;
    vector<int> W(c + 1);
    for (int i = 1; i <= c; i++)
        cin >> W[i];

    int ans = 1, acc = 0;
    while (true) {
        for (int i = 0; i < n; i++) {
            if (W[S[i]] > 0) {
                W[S[i]] -= min(W[S[i]], 5);
            } else {
                acc += 1;
            }
        }

        int W_sum = 0;
        for (int i = 1; i <= c; i++)
            W_sum += W[i];

        if (W_sum <= acc) {
            break;
        }

        ans += 1;
    }

    cout << ans << endl;
    
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