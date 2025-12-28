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

struct Point {
    double x = 0, y = 0;

    Point () {}

    Point (double x, double y): x(x), y(y) {}

    bool operator==(Point const &other) const {
        return x == other.x && y == other.y;
    }
};

double getEucDistance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void solve() {
    int C;
    cin >> C;
    vector<Point> arr;
    for (int i = 0; i < C; i++) {
        int x, y;
        cin >> x >> y;

        arr.pb(Point(x, y));
    }

    double ans = 0;
    for (int i = 0; i < C; i++)
        for (int j = i + 1; j < C; j++)
            ans = max(ans, getEucDistance(arr[i], arr[j]));

    cout << setprecision(15) << ans << endl;

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