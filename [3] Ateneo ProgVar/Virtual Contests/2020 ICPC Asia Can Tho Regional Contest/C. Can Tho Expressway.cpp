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

struct Point {
    lng x, y;

    Point() {}
};

void solve() {
    lng a, b;
    array<lng, 2> c;
    cin >> a >> b >> c[0] >> c[1];

    function<lng(Point, int)> getRelHeight = [&](Point p, int l) {
        return a * p.x + b * p.y - c[l];
    };

    int k;
    cin >> k;
    vector<Point> P(k);
    for (auto &p : P)
        cin >> p.x >> p.y;

    for (int i = 0; i < k; i++) {
        int j = (i + 1) % k;
        for (int l = 0; l < 2; l++)
            if (getRelHeight(P[i], l) * getRelHeight(P[j], l) < 0) {
                cout << "YES" << endl;
                return;
            }
    }

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            if (j == i)
                continue;

            if (getRelHeight(P[i], 0) == 0 && getRelHeight(P[j], 1) == 0) {
                cout << "YES" << endl;
                return;
            }
        }

    for (int i = 0; i < k; i++)
        if (getRelHeight(P[i], 0) * getRelHeight(P[i], 1) < 0) {
            cout << "YES" << endl;
            return;
        }

    cout << "NO" << endl;

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