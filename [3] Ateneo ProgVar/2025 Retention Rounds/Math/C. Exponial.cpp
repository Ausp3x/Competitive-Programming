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

lng getPhi(lng n) {
    lng phi = n;
    for (lng i = 2; i * i <= n; i++) {
        if (n % i != 0) 
            continue;
        
        while (n % i == 0)
            n /= i;
        
        phi -= phi / i;
    }

    if (n > 1)
        phi -= phi / n;
    
    return phi;
}

lng modPow(lng bse, lng exp, lng mod) {
    bse %= mod;
    
    lng res = 1;
    while (exp > 0) {
        if (exp & 1)
            res = res * bse % mod;
        
        bse = bse * bse % mod;
        exp >>= 1;
    }

    return res;
}

vector<lng> base_cases = {1, 1, 2, 9, 262144};

lng exponial(lng n, lng m) {
    if (m == 1)
        return 0;

    if (n <= 4)
        return base_cases[n] % m;
    
    lng phi_m = getPhi(m);
    lng exp = exponial(n - 1, phi_m);
    
    return modPow(n, phi_m + exp, m);
}

void solve() {
    lng n, m;
    cin >> n >> m;
    
    cout << exponial(n, m) << endl;
    
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