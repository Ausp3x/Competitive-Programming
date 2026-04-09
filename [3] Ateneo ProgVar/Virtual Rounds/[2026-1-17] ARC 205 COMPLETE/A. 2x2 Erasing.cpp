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

struct FenTree {
    int D, X, Y;
    vector<lng> bit;

    FenTree(int x, int y): D(2), X(x), Y(y), bit((X + 1) * (Y + 1)) {
        assert(x > 0 && y > 0);
    }

    template<typename T>
    FenTree(int x, int y, const vector<vector<T>> &arr): FenTree(x, y) {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                pointAddUpdate(i + 1, j + 1, arr[i][j]);
            }
        }
    }

    inline int getIdx(int i, int j) const {
        assert(D == 2);
        
        return i * (Y + 1) + j;
    }

    void pointAddUpdate(int i_cur, int j_cur, lng del) {
        assert(D == 2);
        for (int i = i_cur; i <= X; i += i & -i) {
            for (int j = j_cur; j <= Y; j += j & -j) {
                bit[getIdx(i, j)] += del;
            }
        }
    }

    lng prefixSumQuery(int i_cur, int j_cur) const {
        assert(D == 2);
        lng sum = 0;
        for (int i = i_cur; i > 0; i -= i & -i) {
            for (int j = j_cur; j > 0; j -= j & -j) {
                sum += bit[getIdx(i, j)];
            }
        }
        
        return sum;
    }

    lng rangeSumQuery(int x1, int y1, int x2, int y2) const {
        assert(D == 2);
        if (x1 > x2 || y1 > y2) {
            return 0;
        }

        return prefixSumQuery(x2, y2)
             - prefixSumQuery(x1 - 1, y2) - prefixSumQuery(x2, y1 - 1)
             + prefixSumQuery(x1 - 1, y1 - 1);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<vector<char>> grid(n + 1, vector<char>(n + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> grid[i][j];

    FenTree fnw(n + 1, n + 1);
    for (int i = 1; i < n; i++)
        for (int j = 1; j < n; j++)
            if (grid[i][j] == '.' && grid[i][j + 1] == '.' && grid[i + 1][j] == '.' && grid[i + 1][j + 1] == '.')
                fnw.pointAddUpdate(i, j, 1);

    while (q--) {
        int u, d, l, r;
        cin >> u >> d >> l >> r;
        // u--; d--; l--; r--;
        
        cout << fnw.rangeSumQuery(u, l, d - 1, r - 1) << endl;
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