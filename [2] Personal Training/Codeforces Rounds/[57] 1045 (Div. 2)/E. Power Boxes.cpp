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

    int j;
    vector<int> A(n + 1), B(n + 1), J(n + 3);
    for (int i = n - 1; i >= 1; i--) {
        if (A[i + 1] == 0) {
            cout << "throw " << i << endl;

            int j;
            cin >> j;
            A[i] = 3 - j + J[i + 2];
            B[i + 1] = 3 - j + J[i + 2];

            cout << "swap " << i << endl;
            cout << "throw " << i << endl;
            
            cin >> j;
            A[i + 1] = 3 - j + J[i + 2];
            B[i] = 3 - j + J[i + 2];

            J[i + 1] = J[i + 1 + B[i + 1]] + 1;
            J[i] = J[i + B[i]] + 1;
            
            continue;
        } 

        if (J[i + 1] != J[i + 2]) {
            cout << "throw " << i << endl;

            int j;
            cin >> j;
            
            if (j == J[i + 1] + 1) {
                A[i] = 1;
                B[i] = 1;
                J[i] = J[i + 1] + 1;
            } else if (j == J[i + 2] + 1) {
                A[i] = 2;
                B[i] = 2;
                J[i] = J[i + 2] + 1;
            }
            
            continue;
        }

        if (i == 1) {
            cout << "swap " << 1 << endl;

            swap(B[1], B[2]);
            
            cout << "throw " << 2 << endl;

            int j;
            cin >> j;

            if (j == J[3] + 1) {
                A[1] = 1;
                B[2] = 1;
                J[2] = J[3] + 1;
            } else if (j == J[4] + 1) {
                A[1] = 2;
                B[2] = 2;
                J[2] = J[4] + 1;
            }
            J[1] = J[1 + B[1]] + 1;
            
            continue;
        }
    }

    cout << "! ";
    for (int i = 1; i <= n; i++)
        cout << A[i] << ' ';
    cout << endl;

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