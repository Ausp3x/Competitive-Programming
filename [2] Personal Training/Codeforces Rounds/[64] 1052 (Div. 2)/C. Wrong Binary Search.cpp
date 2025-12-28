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
    cin >> n;
    string s;
    cin >> s;
    
    if ((s[0] == '0' && s[1] == '1') || (s[n - 2] == '1' && s[n - 1] == '0')) {
        cout << "NO" << endl;
        return;
    }
    for (int i = 1; i < n - 1; i++) 
        if (s[i - 1] == '1' && s[i] == '0' && s[i + 1] == '1') {
            cout << "NO" << endl;
            return;
        }

    vector<pair<char, int>> V;
    V.pb({s[0], 1});
    for (int i = 1; i < n; i++) {
        if (s[i] == V.back().fi) {
            V.back().se++;
        } else {
            V.pb({s[i], 1});
        }
    }

    cout << "YES" << endl;

    int cnt = 0;
    for (int i = 0; i < V.size(); i++) {
        if (V[i].fi == '0') {
            for (int j = cnt + V[i].se; j > cnt; j--)
                cout << j << ' ';
        } else {
            for (int j = cnt + 1; j <= cnt + V[i].se; j++)
                cout << j << ' ';
        }

        cnt += V[i].se;
    }
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