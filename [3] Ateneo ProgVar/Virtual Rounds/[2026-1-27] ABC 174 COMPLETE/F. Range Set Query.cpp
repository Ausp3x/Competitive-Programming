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

    template<typename T>
    FenTree(int x, const vector<T> &arr): FenTree(x) {
        for (int i = 0; i < x; i++) {
            rangeAddUpdate(i + 1, i + 1, arr[i]);
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
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> A(n + 1);
    FenTree fnwt(n);
    map<int, deque<int>> M;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];

        if (M.find(A[i]) == M.end())
            fnwt.rangeAddUpdate(i, i, 1);
        M[A[i]].pb(i);
    }
    deque<tuple<int, int, int>> Q(q);
    for (int i = 0; i < q; i++) {
        cin >> get<0>(Q[i]) >> get<1>(Q[i]);
        get<2>(Q[i]) = i;
    }

    sort(Q.begin(), Q.end());

    vector<int> ans(q);
    for (int i = 1; i <= n; i++) {
        while (!Q.empty()) {
            auto [l, r, j] = Q[0];
            if (l > i)
                break;
            Q.pop_front();

            // cout << l << ' ' << r << ' ' << j << endl;
            // for (int i = 1; i <= n; i++)
            //     cout << fnwt.rangeSumQuery(i, i) << ' ';
            // cout << endl;
            
            ans[j] = fnwt.rangeSumQuery(l, r);
        }

        fnwt.rangeAddUpdate(i, i, -1);
        M[A[i]].pop_front();
        if (!M[A[i]].empty())
            fnwt.rangeAddUpdate(M[A[i]][0], M[A[i]][0], 1);
    }

    for (int x : ans)
        cout << x << endl;

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