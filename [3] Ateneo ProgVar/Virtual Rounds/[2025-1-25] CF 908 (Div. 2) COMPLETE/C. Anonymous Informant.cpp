// 人外有人，天外有天
// author: Ausp3x

#pragma GCC optimize("O3, fast-math")
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

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> B(n);
    for (int &b : B)
        cin >> b;

    if (n == 1) {
        cout << (B[0] <= n ? "Yes" : "No") << endl;
        return;
    }

    vector<vector<int>> adjl(n);
    for (int i = 0; i < n; i++) {
        if (B[i] > n)
            continue;

        int a = (i + n - (B[i] - 1)) % n;
        int b = (a + B[i]) % n;
        adjl[b].pb(a);
    }

    int max_dis = 0;
    queue<int> q;
    vector<int> dis(n, -1);
    q.push(0);
    dis[0] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (int nxt : adjl[cur]) {
            if (dis[nxt] != -1) {
                cout << "Yes" << endl;
                return;
            }

            q.push(nxt);
            dis[nxt] = dis[cur] + 1;
            max_dis = max(max_dis, dis[nxt]);
        }
    }

    cout << (max_dis >= k ? "Yes" : "No") << endl;

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