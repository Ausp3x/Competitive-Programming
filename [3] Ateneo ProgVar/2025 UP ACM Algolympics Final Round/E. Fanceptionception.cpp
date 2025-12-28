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
    vector<vector<lng>> grid_add(n + 2, vector<lng>(3 * n + 2)), grid_min(n + 2, vector<lng>(3 * n + 2));
    for (int i = 1; i <= n; i++)
        for (int j = n + 1; j <= 2 * n; j++) {
            cin >> grid_add[i][j];
            grid_min[i][j + 1] = grid_add[i][j];
        }

    // column (j) add n
    vector<vector<short>> A(n + 2, vector<short>(3 * n + 2)), B(n + 2, vector<short>(3 * n + 2));
    for (int i = 1; i <= n; i++) {
        for (int j = n + 1; j <= 2 * n; j++) {
            A[i + 1][j - 1] += -1;
            int r1 = min<int>({i + grid_add[i][j] + 1, n + 1});
            A[r1][i + j - r1] += 1;

            B[i + 1][j + 1] += -1;
            int r2 = min<int>({i + grid_min[i][j] + 1, n + 1});
            B[r2][j + r2 - i] += 1;
        }
    }

    for (int j = n + 1; j <= 3 * n; j++) {
        for (int i = 1; i <= n + 1; i++) {
            A[i][j - i + 1] += A[i - 1][j - i + 2];
            grid_add[i][j - i + 1] += grid_add[i - 1][j - i + 2] + A[i][j - i + 1];
        }
    }

    for (int j = 1; j <= 2 * n; j++) {
        for (int i = 1; i <= n + 1; i++) {
            B[i][j + i - 1] += B[i - 1][j + i - 2];
            grid_min[i][j + i - 1] += grid_min[i - 1][j + i - 2] + B[i][j + i - 1];
        }
    }

    for (int i = 1; i <= n; i++) {
        grid_add[i][0] -= grid_min[i][0];
        for (int j = 1; j <= 3 * n + 1; j++) {
            grid_add[i][j] += grid_add[i][j - 1] - grid_min[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = n + 1; j <= 2 * n; j++) 
            cout << grid_add[i][j] << ' ';
        cout << endl;
    }

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