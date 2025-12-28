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
    vector<tuple<int, int, int>> points;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;

        points.pb({x, y, i});
    }

    sort(points.begin(), points.end());

    vector<int> quadrant(n + 1);
    for (int i = 0; i < n; i++) 
        quadrant[get<2>(points[i])] += ((i < n / 2) << 1);

    for (int i = 0; i < n; i++)
        swap(get<0>(points[i]), get<1>(points[i]));

    sort(points.begin(), points.end());

    for (int i = 0; i < n; i++) 
        quadrant[get<2>(points[i])] += (i < n / 2);

    vector<vector<int>> indices(4);
    for (int i = 1; i <= n; i++)
        indices[quadrant[i]].pb(i);

    // for (int i = 0; i < 4; i++) {
    //     cout << i << ": ";
    //     for (int x : indices[i])    
    //         cout << x << ' ';
    //     cout << endl;
    // }

    assert(indices[0].size() == indices[3].size());
    assert(indices[1].size() == indices[2].size());

    for (int i = 0; i < indices[0].size(); i++)
        cout << indices[0][i] << ' ' << indices[3][i] << endl;
    for (int i = 0; i < indices[1].size(); i++)
        cout << indices[1][i] << ' ' << indices[2][i] << endl;

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