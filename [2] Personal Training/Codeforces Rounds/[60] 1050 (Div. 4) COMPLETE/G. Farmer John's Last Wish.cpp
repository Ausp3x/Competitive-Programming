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
    int g = 0;
    vector<int> A(n + 1), ans(n + 1), cnts(n + 1);
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];

        g = gcd(g, A[i]);

        ans[i] = ans[i - 1];
        while (!q.empty()) {
            cnts[q.front()]++;
            // cout << i << ' ' << q.front() << ' ' << cnts[q.front()] << endl;
            if (g % q.front() != 0)
                ans[i] = max(ans[i], cnts[q.front()]);
            q.pop();
        }
        for (int j = 1; j * j <= A[i]; j++) {
            if (A[i] % j != 0)
                continue;
            
            if (j != 1) {
                if (cnts[j] + 1 == i) {
                    q.push(j);
                } else {
                    cnts[j]++;
                    // cout << i << ' ' << j << ' ' << cnts[j] << endl;
                    ans[i] = max(ans[i], cnts[j]);
                }
            }

            if (j * j != A[i]) {
                int k = A[i] / j;
                if (cnts[k] + 1 == i) {
                    q.push(k);
                } else {
                    cnts[k]++;
                    // cout << i << ' ' << j << ' ' << cnts[j] << endl;
                    ans[i] = max(ans[i], cnts[k]);
                }
            }
        }
    }

    // for (int i = 1; i <= n; i++)
    //     cout << cnts[i] << ' ';
    // cout << endl;

    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';
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