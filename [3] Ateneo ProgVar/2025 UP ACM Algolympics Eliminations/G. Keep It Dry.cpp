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

vector<pair<int, int>> di_dj = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

void solve() {
    int h, w;
    cin >> h >> w;
    int i_R = -1, j_R = -1;
    vector<pair<int, int>> ij_W;
    vector<vector<char>> grid(h + 2, vector<char>(w + 2, '#'));
    for (int i = 1; i <= h; i++)
        for (int j = 1; j <= w; j++) {
            cin >> grid[i][j];
            
            if (grid[i][j] == 'R') {
                i_R = i;
                j_R = j;
            }
            
            if (grid[i][j] == 'W') {
                ij_W.pb({i, j});
            }
        }
    
    int cur = 0;
    queue<array<int, 3>> qR, qW;
    vector<vector<bool>> vst_R(h + 2, vector<bool>(w + 2));
    vector<vector<bool>> vst_W(h + 2, vector<bool>(w + 2));
    qR.push({i_R, j_R, 0});
    vst_R[i_R][j_R] = true;
    for (auto &[i_W, j_W] : ij_W) {
        qW.push({i_W, j_W, 0});
        vst_W[i_W][j_W] = true;
    }
    while (!qR.empty()) {
        while (!qR.empty()) {
            if (qR.front()[2] > cur)
                break;

            auto [i_cur, j_cur, d] = qR.front();
            qR.pop();

            if (grid[i_cur][j_cur] != 'R')
                continue;

            for (auto &[di, dj] : di_dj) {
                int i_nxt = i_cur + di;
                int j_nxt = j_cur + dj;

                if (grid[i_nxt][j_nxt] == 'E') {
                    cout << d + 1 << endl;
                    return;
                }

                if (grid[i_nxt][j_nxt] != '.' || vst_R[i_nxt][j_nxt])
                    continue;
                vst_R[i_nxt][j_nxt] = true;
                
                grid[i_nxt][j_nxt] = 'R';
                qR.push({i_nxt, j_nxt, d + 1});
            }
        }
        
        // for (int i = 1; i <= h; i++) {
        //     for (int j = 1; j <= w; j++)
        //         cout << grid[i][j];
        //     cout << endl;
        // }
        // cout << endl;

        while (!qW.empty()) {
            if (qW.front()[2] > cur)
                break;

            auto [i_cur, j_cur, d] = qW.front();
            qW.pop();

            for (auto &[di, dj] : di_dj) {
                int i_nxt = i_cur + di;
                int j_nxt = j_cur + dj;

                if (grid[i_nxt][j_nxt] == '#' || vst_W[i_nxt][j_nxt])
                    continue;
                vst_W[i_nxt][j_nxt] = true;
                
                grid[i_nxt][j_nxt] = 'W';
                qW.push({i_nxt, j_nxt, d + 1});
            }
        }

        // for (int i = 1; i <= h; i++) {
        //     for (int j = 1; j <= w; j++)
        //         cout << grid[i][j];
        //     cout << endl;
        // }
        // cout << endl;
        
        cur++;
    }

    cout << -1 << endl;

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