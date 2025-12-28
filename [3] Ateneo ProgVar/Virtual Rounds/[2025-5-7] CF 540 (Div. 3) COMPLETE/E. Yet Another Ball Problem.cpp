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
    int n;
    lng k;
    cin >> n >> k;
    
    if (k * (k - 1) < n) {
        cout << "NO" << endl;
        return;
    }
    
    map<pair<int, int>, bool> vst;
    vector<pair<int, int>> ans;
    for (int i = 1; i < k; i++) {
        for (int j = 1; j <= k; j++) {
            pair<int, int> cur = {j, j + i};
            while (cur.se > k)
                cur.se -= k;
            
            ans.pb(cur);
            if (ans.size() == n)
                goto exit;
        }
    }
    
exit:
    cout << "YES" << endl;
    for (int i = 0; i < n; i++)
        cout << ans[i].fi << ' ' << ans[i].se << endl;
    
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