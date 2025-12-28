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

struct SegTree {    
    int l, r;
    lng ttl_sum = 0, max_sum = 0, mprf_sum = 0, msuf_sum = 0;
    SegTree *l_child, *r_child;

    template<class T> 
    SegTree(int l, int r, const vector<T> &arr): l(l), r(r) {
        if (l == r) {
            ttl_sum = arr[l];
            max_sum = arr[l];
            mprf_sum = arr[l];
            msuf_sum = arr[l];
            l_child = r_child = nullptr;
        } else {
            int m = (l + r) / 2;
            l_child = new SegTree(l, m, arr);
            r_child = new SegTree(m + 1, r, arr);
            pull();
        }

        return;
    }

    // pull states up from children
    void pull() {
        if (l_child != nullptr && r_child != nullptr) {
            ttl_sum = l_child->ttl_sum + r_child->ttl_sum;
            max_sum = max({l_child->max_sum, r_child->max_sum, l_child->msuf_sum + r_child->mprf_sum});
            mprf_sum = max(l_child->mprf_sum, l_child->ttl_sum + r_child->mprf_sum);
            msuf_sum = max(r_child->msuf_sum, r_child->ttl_sum + l_child->msuf_sum);
        }

        return;
    }

    void singleValUpdate(int cur, lng x) {
        if (r < cur || cur < l) {
            return;
        }
        
        if (cur == l && r == cur) {
            ttl_sum = x;
            max_sum = x;
            mprf_sum = x;
            msuf_sum = x;
            return;
        }
        
        l_child->singleValUpdate(cur, x);
        r_child->singleValUpdate(cur, x);
        pull();

        return;
    }

    array<lng, 4> rangeMaxQuery(int cur_l, int cur_r) {
        if (cur_l > cur_r || (r < cur_l || cur_r < l)) {
            return {0, -INF64, -INF64, -INF64};
        }
        
        if (cur_l <= l && r <= cur_r) {
            return {ttl_sum, max_sum, mprf_sum, msuf_sum};
        }

        array<lng, 4> L = l_child->rangeMaxQuery(cur_l, cur_r);
        array<lng, 4> R = r_child->rangeMaxQuery(cur_l, cur_r);
        array<lng, 4> res = {
            L[0] + R[0],
            max({L[1], R[1], L[3] + R[2]}),
            max(L[2], L[0] + R[2]),
            max(R[3], R[0] + L[3])
        };

        return res;
    }

    void debugPrint(int depth = 0) {
        for (int t = 0; t < depth; t++) {
            cout << '\t';
        }
        cout << "[" << l << ", " << r << "] has ttl_sum " << ttl_sum 
             << ", max_sum " << max_sum
             << ", mprf_sum " << mprf_sum
             << ", and msuf_sum " << msuf_sum << endl;
        if (l_child != nullptr && r_child != nullptr) {
            l_child->debugPrint(depth + 1);
            r_child->debugPrint(depth + 1);
        }

        return;
    }
};

struct Opr {
    lng l = -1, r = -1, x = 0;
};

struct Qry {
    int i = -1;
    lng k = -1, s = -1, t = -1;

    bool operator<(Qry &x) {
        return k < x.k;
    }
};

void solve() {
    int N, M;
    cin >> N >> M;
    vector<Opr> O(M + 1);
    for (int i = 1; i <= M; i++)
        cin >> O[i].l >> O[i].r >> O[i].x;
    int Q;
    cin >> Q;
    vector<Qry> V(Q);
    for (int i = 0; i < Q; i++) {
        V[i].i = i;
        cin >> V[i].k >> V[i].s >> V[i].t;
    }

    vector<vector<int>> change_to_val(N + 2), change_to_zer(N + 2);
    for (int i = 1; i <= M; i++) {
        change_to_val[O[i].l].pb(i);
        change_to_zer[O[i].r + 1].pb(i);
    }

    sort(V.begin(), V.end());

    int prv = 0;
    SegTree *segt = new SegTree(1, M, vector<lng>(M + 1, 0));
    vector<lng> ans(Q);
    for (int i = 0; i < Q; i++) {
        int cur = V[i].k;
        while (prv + 1 <= cur) {
            prv++;
            for (int oi : change_to_val[prv]) 
                segt->singleValUpdate(oi, O[oi].x);
            for (int oi : change_to_zer[prv])
                segt->singleValUpdate(oi, 0);
        }

        ans[V[i].i] = segt->rangeMaxQuery(V[i].s, V[i].t)[1];
    }

    for (lng x : ans)
        cout << x << '\n';

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