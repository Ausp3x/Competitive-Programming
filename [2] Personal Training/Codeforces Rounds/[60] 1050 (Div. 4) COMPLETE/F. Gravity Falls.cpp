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
    vector<vector<int>> A(n);
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;

        A[i].resize(k);
        for (int &a : A[i])
            cin >> a;
    }

    int prv = 0;
    vector<int> ans;
    do {
        sort(A.begin(), A.end());

        prv = A[0].size();
        for (int a : A[0])
            ans.pb(a);
        
        vector<vector<int>> B;
        for (auto &x : A) {
            if (x.size() <= prv)
                continue;

            B.pb({});
            for (int i = prv; i < x.size(); i++)
                B.back().pb(x[i]);
        }

        A = B;
    } while (!A.empty());

    for (int x : ans)
        cout << x << ' ';
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