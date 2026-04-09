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
    int D, X, Y, Z;
    vector<lng> B1, B2, bit;

    FenTree(int x): D(1), X(x), B1(X + 1), B2(X + 1) {
        assert(x > 0);
    }
    
    FenTree(int x, int y): D(2), X(x), Y(y), bit((X + 1) * (Y + 1)) {
        assert(x > 0 && y > 0);
    }
    
    FenTree(int x, int y, int z): D(3), X(x), Y(y), Z(z), bit((X + 1) * (Y + 1) * (Z + 1)) {
        assert(x > 0 && y > 0 && z > 0);
    }

    template<typename T>
    FenTree(int x, const vector<T> &arr): FenTree(x) {
        for (int i = 0; i < x; i++) {
            rangeAddUpdate(i + 1, i + 1, arr[i]);
        }
    }

    template<typename T>
    FenTree(int x, int y, const vector<vector<T>> &arr): FenTree(x, y) {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                pointAddUpdate(i + 1, j + 1, arr[i][j]);
            }
        }
    }

    template<typename T>
    FenTree(int x, int y, int z, const vector<vector<vector<T>>> &arr): FenTree(x, y, z) {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                for (int k = 0; k < z; k++) {
                    pointAddUpdate(i + 1, j + 1, k + 1, arr[i][j][k]);
                }
            }
        }
    }

    // 1D methods
    inline void _add(int i_cur, lng del, vector<lng> &B) {
        for (int i = i_cur; i <= X; i += i & -i) {
            B[i] += del;
        }
    }

    inline lng _sum(int i_cur, const vector<lng> &B) const {
        lng sum = 0;
        for (int i = i_cur; i > 0; i -= i & -i) {
            sum += B[i];
        }

        return sum;
    }

    void rangeAddUpdate(int l, int r, lng del) {
        assert(D == 1);
        _add(l,     del,           B1);
        _add(r + 1, -del,          B1);
        _add(l,     del * (l - 1), B2);
        _add(r + 1, -del * r,      B2);
    }

    lng prefixSumQuery(int i) const {
        assert(D == 1);

        return _sum(i, B1) * i - _sum(i, B2);
    }

    lng rangeSumQuery(int l, int r) const {
        assert(D == 1);
        if (l > r) {
            return 0;
        }
        
        return prefixSumQuery(r) - prefixSumQuery(l - 1);
    }

    // 2D methods
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

    // 3D methods
    inline int getIdx(int i, int j, int k) const {
        assert(D == 3);

        return (i * (Y + 1) + j) * (Z + 1) + k;
    }

    void pointAddUpdate(int i_cur, int j_cur, int k_cur, lng del) {
        assert(D == 3);
        for (int i = i_cur; i <= X; i += i & -i) {
            for (int j = j_cur; j <= Y; j += j & -j) {
                for (int k = k_cur; k <= Z; k += k & -k) {
                    bit[getIdx(i, j, k)] += del;
                }
            }
        }
    }

    lng prefixSumQuery(int i_cur, int j_cur, int k_cur) const {
        assert(D == 3);
        lng sum = 0;
        for (int i = i_cur; i > 0; i -= i & -i) {
            for (int j = j_cur; j > 0; j -= j & -j) {
                for (int k = k_cur; k > 0; k -= k & -k) {
                    sum += bit[getIdx(i, j, k)];
                }
            }
        }
        
        return sum;
    }

    lng rangeSumQuery(int x1, int y1, int z1, int x2, int y2, int z2) const {
        assert(D == 3);
        if (x1 > x2 || y1 > y2 || z1 > z2) {
            return 0;
        }
        
        return prefixSumQuery(x2, y2, z2)
             - prefixSumQuery(x1 - 1, y2, z2)     - prefixSumQuery(x2, y1 - 1, z2)     - prefixSumQuery(x2, y2, z1 - 1)
             + prefixSumQuery(x1 - 1, y1 - 1, z2) + prefixSumQuery(x1 - 1, y2, z1 - 1) + prefixSumQuery(x2, y1 - 1, z1 - 1)
             - prefixSumQuery(x1 - 1, y1 - 1, z1 - 1);
    }
};

void solve() {
    int n, q, c;
    cin >> n >> q >> c;

    vector P(c + 1, FenTree(105, 105));
    for (int i = 0; i < n; i++) {
        int x, y, s;
        cin >> x >> y >> s;

        for (int j = 0; j <= c; j++)
            P[j].pointAddUpdate(x, y, (s + j) % (c + 1));
    }

    while (q--) {
        int t, x1, y1, x2, y2;
        cin >> t >> x1 >> y1 >> x2 >> y2;
        
        t %= c + 1;

        cout << P[t].rangeSumQuery(x1, y1, x2, y2) << endl;
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