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
    lng xpy = INF64, ymx = INF64;
    vector<pair<lng, lng>> A(n);
    for (auto &[x, y] : A) {
        cin >> x >> y;
        xpy = min(xpy, x + y);
        ymx = min(ymx, y - x);
    }
    
    lng s;

    cout << "? L " << 1000000000 << endl;
    cin >> s;
    cout << "? L " << 1000000000 << endl;
    cin >> s;
    cout << "? D " << 1000000000 << endl;
    cin >> s;
    cout << "? D " << 1000000000 << endl;
    cin >> s;
    
    lng dpc = xpy - s;

    cout << "? R " << 1000000000 << endl;
    cin >> s;
    cout << "? R " << 1000000000 << endl;
    cin >> s;
    cout << "? R " << 1000000000 << endl;
    cin >> s;
    cout << "? R " << 1000000000 << endl;
    cin >> s;

    lng dmc = ymx - s;

    lng c = (dpc - dmc) / 2;
    lng d = (dpc + dmc) / 2 + 4000000000;
    
    cout << "! " << c << ' ' << d << endl;

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