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
    string s;
    cin >> s;

    int cnt = 0;
    for (int i = 0; i < k - 1; i++)
        cnt += s[i] == '1';

    for (int i = k - 1; i < n; i++) {
        cnt += s[i] == '1';
        if (cnt == k) {
            cout << "NO" << endl;
            return;
        }
        cnt -= s[i - k + 1] == '1';
    }

    cout << "YES" << endl; 
    
    vector<int> ans(n), cur(n);
    iota(cur.begin(), cur.end(), 1);
    for (int i = 0; i < n; i++) 
        if (s[i] == '0') {
            ans[i] = cur.back();
            cur.pop_back();
        }
    for (int i = 0; i < n; i++) 
        if (s[i] == '1') {
            ans[i] = cur.back();
            cur.pop_back();
        }

    for (int x : ans)
        cout << x << ' ';
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