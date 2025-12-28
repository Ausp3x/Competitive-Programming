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
    int r, c;
    cin >> r >> c;
    vector<vector<char>> grid(r, vector<char>(c));
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) 
            cin >> grid[i][j];

    for (int j = 0; j < c; j++) 
        if (grid[r - 1][j] != '#') {
            cout << "No" << endl;
            return;
        }
    
    bool is_fit = false;
    for (int j = 0; j < c; j++) {
        if (grid[0][j] == '#')
            is_fit = true; 
    }
    if (!is_fit) {
        cout << "No" << endl;
        return;
    }

    vector<int> cnts(c);
    for (int j = 0; j < c; j++) {
        for (int i = r - 1; i >= 0; i--) {
            if (grid[i][j] == '#') {
                cnts[j]++;
                if (i < r - 1)
                    if (grid[i + 1][j] != '#') {
                        cout << "No" << endl;
                        return;
                    }
            }
        }
    }

    cout << "Yes" << endl;
    cout << c << endl;
    for (auto x : cnts)
        cout << x << ' ';
    cout << endl;

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