// 人外有人，天外有天
// author: Ausp3x

#pragma GCC optimize("O3, fast-math")
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

int const MOD = 998244353;

lng modPow(lng x, lng y, lng mod) {
    lng res = 1;
    while (y > 0) {
        if (y & 1) {
            res *= x;
            res %= mod;
        }

        y >>= 1;
        x *= x;
        x %= mod;
    }

    return (res + mod) % mod;
}

void solve() {
    int n;
    cin >> n;
    map<lng, lng> a_cnts;
    vector<lng> A(n);
    for (lng &a : A) {
        cin >> a;

        a_cnts[a]++;
    }

    lng M_cnt = 0;
    vector<lng> A_red;
    for (auto &[a, cnt] : a_cnts) {
        (M_cnt += modPow(2, cnt, MOD) - 1) %= MOD;
        (M_cnt += MOD) %= MOD;
        A_red.pb(a);
    }

    int len = A_red.size();
    lng m_cnt = 0;
    for (int i = 0; i < len; i++) {
        lng ext = 0;
        for (int j = i + 1; j < len; j++) {
            if (A_red[j] % A_red[i] != 0)
                continue;

            ext += a_cnts[A_red[j]];
        }

        (m_cnt += (modPow(2, a_cnts[A_red[i]], MOD) + MOD - 1) % MOD * modPow(2, ext, MOD) % MOD) %= MOD;
    }

    cout << M_cnt << ' ' << m_cnt << endl;

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