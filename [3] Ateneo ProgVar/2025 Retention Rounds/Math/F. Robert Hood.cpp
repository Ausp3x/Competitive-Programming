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

int orientation(Point a, Point b, Point c) {
    double v = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
    if (v < 0) { // clockwise
        return -1;
    }  
    
    if (v > 0) { // counter-clockwise
        return +1;
    }

    return 0;
}

bool isClockwise(Point a, Point b, Point c, bool include_collinear) {
    int o = orientation(a, b, c);

    return o < 0 || (include_collinear && o == 0);
}

bool isCollinear(Point a, Point b, Point c) {
    return orientation(a, b, c) == 0;
}

void convexHull(vector<Point> &arr, bool include_collinear = false) {
    Point p0 = *min_element(arr.begin(), arr.end(), [](const Point &a, const Point &b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });

    sort(arr.begin(), arr.end(), [&p0](const Point &a, const Point &b) {
        int o = orientation(p0, a, b);
        if (o == 0) {
            return (p0.x - a.x) * (p0.x - a.x) + (p0.y - a.y) * (p0.y - a.y)
                 < (p0.x - b.x) * (p0.x - b.x) + (p0.y - b.y) * (p0.y - b.y);
        }

        return o < 0;
    });

    if (include_collinear) {
        int i = arr.size() - 1;
        while (i >= 0 && isCollinear(p0, arr[i], arr.back())) {
            i--;
        }

        reverse(arr.begin() + i + 1, arr.end());
    }

    vector<Point> hull;
    for (int i = 0; i < arr.size(); i++) {
        while (hull.size() > 1 && !isClockwise(hull[hull.size() - 2], hull.back(), arr[i], include_collinear)) {
            hull.pop_back();
        }

        hull.push_back(arr[i]);
    }

    if (!include_collinear && hull.size() == 2 && hull[0] == hull[1]) {
        hull.pop_back();
    }

    arr = hull;
}

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

    convexHull(arr);

    // for (auto &[a, b] : arr)
    //     cout << a << ' ' << b << endl;

    int len = arr.size();
    double ans = 0, cur = 0;
    for (int i = 0; i < len; i++) 
        for (int j = 0; j < len; j++)
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