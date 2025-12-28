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

void solve() {
    int r, c;
    cin >> r >> c;
    vector<int> cnts(26);
    for (int i = 0; i < r * c; i++) {
        char c;
        cin >> c;

        cnts[c - 'a']++;
    }
    
    // for (int x : cnts)
    //     cout << x << ' ';
    // cout << endl;

    vector<vector<int>> memo(26, vector<int>(2 * r * c + 1, -1));
    vector<vector<bool>> loc(26, vector<bool>(2 * r * c + 1, 1));
    function<int(int, int)> dp = [&](int l, int w) {
        if (l == -1)
            return 0;
        
        if (memo[l][w] != -1)
            return memo[l][w];

        int res = dp(l - 1, w) + cnts[l];
        if (w >= cnts[l])
            if (dp(l - 1, w - cnts[l]) < res) {
                res = dp(l - 1, w - cnts[l]);
                loc[l][w] = 0;
            }

        return memo[l][w] = res;
    };

    int A_min = INF32, rp = -1, cp = -1;
    for (int i = r; i <= 2 * r; i++) {
        for (int j = c; j <= 2 * c; j++) {
            int A = i * j;
            if (A > A_min)
                continue;
            
            int w = (i * j + 1) / 2, b = (i * j) / 2;
            if (b < dp(25, w))
                continue;

            if (A < A_min) {
                A_min = A;
                rp = i;
                cp = j;
            }
        }
    }

    int wp = (rp * cp + 1) / 2;
    vector<queue<int>> Q(2);
    for (int i = 25; i >= 0; i--) {
        if (cnts[i] == 0)
            continue;

        Q[loc[i][wp]].push(i); 
        
        if (loc[i][wp] == 0)
            wp -= cnts[i];
    }

    cout << rp << ' ' << cp << endl;
    vector<vector<char>> ans(rp, vector<char>(cp, '.'));
    for (int i = 0; i < rp; i++) {
        for (int j = 0; j < cp; j++) { 
            int m = (i + j) % 2;

            if (Q[m].empty()) {
                cout << '.';
                continue;
            }

            if (cnts[Q[m].front()] == 0) 
                Q[m].pop();

            if (Q[m].empty()) {
                cout << '.';
                continue;
            }

            cout << char('a' + Q[m].front());
            cnts[Q[m].front()]--;
        }
        cout << '\n';
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