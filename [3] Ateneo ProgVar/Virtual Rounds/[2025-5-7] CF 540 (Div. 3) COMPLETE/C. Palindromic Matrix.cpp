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
    map<int, int> cnts;
    for (int i = 0; i < n * n; i++) {
        int a;
        cin >> a;

        cnts[a]++;
    }

    auto getRect = [&](int i, int j) -> vector<pair<int, int>> {
        assert(0 <= i && i < n && 0 <= j && j < n);
        
        set<pair<int, int>> S;
        S.insert({i, j});
        S.insert({i, n - j - 1});
        S.insert({n - i - 1, j});
        S.insert({n - i - 1, n - j - 1});
        
        vector<pair<int, int>> res;
        for (auto &[a, b] : S)
            res.pb({a, b});
    
        return res;
    };

    if (n % 2 == 0) {
        for (auto &[a, cnt] : cnts) 
            if (cnt % 4 != 0) {
                cout << "NO" << endl;
                return;
            }
        
        vector<vector<int>> grid(n, vector<int>(n, -1));
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < n; j++) {
                if (grid[i][j] != -1)
                    continue;

                auto [a, cnt] = *cnts.begin();
                vector<pair<int, int>> I = getRect(i, j);
                for (auto [i2, j2] : I)
                    grid[i2][j2] = a;
                
                cnts[a] -= 4;
                if (cnts[a] == 0)
                    cnts.erase(a);
            }
        
        cout << "YES" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << grid[i][j] << ' ';
            cout << endl;
        }

        return;
    }

    int one = -1;
    vector<int> two;
    for (auto &[a, cnt] : cnts) {
        if (cnt % 4 == 1) {
            if (one == -1) {
                one = a;
                continue;
            } else {
                cout << "NO" << endl;
                return;
            }
        }

        if (cnt % 4 == 2) {
            if (two.size() < n - 1) {
                two.pb(a);
                continue;
            } else {
                cout << "NO" << endl;
                return;
            }
        }

        if (cnt % 4 == 3) {
            if (one == -1 && two.size() < n - 1) {
                one = a;
                two.pb(a);
                continue;
            } else {
                cout << "NO" << endl;
                return;
            }
        }
    }

    reverse(two.begin(), two.end());

    int m = n / 2;
    vector<vector<int>> grid(n, vector<int>(n, -1));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (grid[i][j] != -1)
                continue;

            if (i == m && j == m) {
                grid[i][j] = one;

                cnts[one]--;
                if (cnts[one] == 0)
                    cnts.erase(one);
            } else if (i == m || j == m) {
                if (!two.empty()) {
                    vector<pair<int, int>> I = getRect(i, j);
                    for (auto &[i2, j2] : I)
                        grid[i2][j2] = two.back();
                    
                    cnts[two.back()] -= 2;
                    if (cnts[two.back()] == 0)
                        cnts.erase(two.back());
                    two.pop_back();
                } else {
                    auto [a, cnt] = *cnts.begin();
                    vector<pair<int, int>> I = getRect(i, j);
                    for (auto [i2, j2] : I)
                        grid[i2][j2] = a;
                    
                    cnts[a] -= 2;
                    if (cnts[a] == 0)
                        cnts.erase(a);
                }
            } 
        }

    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) {
            if (grid[i][j] != -1 || i == m || j == m)
                continue;

            auto [a, cnt] = *cnts.begin();
            vector<pair<int, int>> I = getRect(i, j);
            for (auto [i2, j2] : I)
                grid[i2][j2] = a;
            
            cnts[a] -= 4;
            if (cnts[a] == 0)
                cnts.erase(a);
        }
            
    cout << "YES" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << grid[i][j] << ' ';
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