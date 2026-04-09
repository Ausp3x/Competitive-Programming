// 人外有人，天外有天
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fi first
#define se second
#define pb push_back
using lng = long long;
using lll = __int128;
template<typename T> 
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int const INF32 = 0x3f3f3f3f;
lng const INF64 = 0x3f3f3f3f3f3f3f3f;

vector<pair<int, int>> di_dj = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

void solve() {
    int h, w;
    cin >> h >> w;
    int Io, Jo, If, Jf;
    map<pair<int, int>, int> type;
    vector<vector<pair<int, int>>> T(26);
    vector<vector<char>> grid(h + 2, vector<char>(w + 2, '#'));
    for (int i = 1; i <= h; i++)
        for (int j = 1; j <= w; j++) {
            cin >> grid[i][j];

            if (grid[i][j] == 'S') {
                Io = i;
                Jo = j;
            } else if (grid[i][j] == 'G') {
                If = i;
                Jf = j;
            } else if (grid[i][j] != '.') {
                type[{i, j}] = grid[i][j] - 'a';
                T[grid[i][j] - 'a'].pb({i, j});               
            }
        }

    queue<pair<int, int>> Q;
    vector<vector<int>> vst(h + 2, vector<int>(w + 2, INF32));
    Q.push({Io, Jo});
    vst[Io][Jo] = 0;
    while (!Q.empty()) {
        auto [i, j] = Q.front();
        Q.pop();

        // cout << i << ' ' << j << endl;

        if (i == If && j == Jf) {
            cout << vst[i][j] << endl;
            return;
        }

        for (auto &[di, dj] : di_dj) {
            if (grid[i + di][j + dj] == '#' || vst[i + di][j + dj] < INF32)
                continue;

            Q.push({i + di, j + dj});
            vst[i + di][j + dj] = vst[i][j] + 1;
        }

        if (type.find({i, j}) == type.end())
            continue;

        for (auto [i_nxt, j_nxt] : T[type[{i, j}]]) {
            if (vst[i_nxt][j_nxt] < INF32)
                continue;

            Q.push({i_nxt, j_nxt});
            vst[i_nxt][j_nxt] = vst[i][j] + 1;
        }
    }

    cout << -1 << endl;

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