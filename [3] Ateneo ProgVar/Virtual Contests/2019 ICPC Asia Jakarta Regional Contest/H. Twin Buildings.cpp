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
 
int const INF32 = 0x3f3f3f3f;
lng const INF64 = 0x3f3f3f3f3f3f3f3f;
 
void solve() {
    int n;
    cin >> n;
    vector<pair<lng, lng>> A(n);
    for (auto &[l, w] : A) {
        cin >> l >> w;
        
        if (l < w)
            swap(l, w);
    }
 
    sort(A.begin(), A.end());
 
    lng ans = 0;
    // one plot of land
    for (auto &[l, w] : A)
        ans = max(ans, l * w);
    
    // two plots of land
    vector<lng> w_suf(n + 1);
    for (int i = n - 1; i >= 0; i--)
        w_suf[i] = max(w_suf[i + 1], A[i].se);
 
    for (int i = 0; i < n; i++) 
        ans = max(ans, 2 * A[i].fi * min(A[i].se, w_suf[i + 1]));
 
    cout << ans / 2 << (ans % 2 ? ".5" : ".0") << endl;
 
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