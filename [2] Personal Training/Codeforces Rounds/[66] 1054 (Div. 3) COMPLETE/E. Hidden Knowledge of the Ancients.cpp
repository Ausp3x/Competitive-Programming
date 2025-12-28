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
    int n, k, l, r;
    cin >> n >> k >> l >> r;
    vector<int> A(n);
    for (int &a : A)
        cin >> a;

    int j1 = -1, j2 = -1;
    lng ans = 0;
    map<int, int> j1_cnts, j2_cnts;
    for (int i = 0; i < n; i++) {
        while (j1 < i || (j1 < n - 1 && j1_cnts.size() < k)) {
            j1_cnts[A[j1 + 1]]++;
            j1++;
        }

        while (j2 < i || (j2 < n && j2_cnts.size() <= k)) {
            if (j2 + 1 < n)
                j2_cnts[A[j2 + 1]]++;
            j2++;
        }

        // for (auto &[k, v] : j1_cnts) 
        //     cout << '(' << k << ',' << v << ')' << ' ';
        // cout << endl;

        // for (auto &[k, v] : j2_cnts) 
        //     cout << '(' << k << ',' << v << ')' << ' ';
        // cout << endl;
        
        if (j1_cnts.size() == k && j2_cnts.size() <= k + 1) {
            ans += max(min(j2, i + r) - max(j1, i + l - 1), 0);
        }

        if (j1_cnts[A[i]] == 1) {
            j1_cnts.erase(A[i]);
        } else {
            j1_cnts[A[i]]--;
        }

        if (j2_cnts[A[i]] == 1) {
            j2_cnts.erase(A[i]);
        } else {
            j2_cnts[A[i]]--;
        }
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