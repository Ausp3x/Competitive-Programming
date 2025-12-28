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

struct MaxSegTree {    
    int l, r;
    lng ttl_sum = 0, max_sum = 0, mxprf_sum = 0, mxsuf_sum = 0;
    MaxSegTree *l_child, *r_child;

    template<class T> 
    MaxSegTree(int l, int r, const vector<T> &arr): l(l), r(r) {
        if (l == r) {
            ttl_sum = arr[l];
            max_sum = arr[l];
            mxprf_sum = arr[l];
            mxsuf_sum = arr[l];
            l_child = r_child = nullptr;
        } else {
            int m = (l + r) / 2;
            l_child = new MaxSegTree(l, m, arr);
            r_child = new MaxSegTree(m + 1, r, arr);
            pull();
        }

        return;
    }

    // pull states up from children
    void pull() {
        if (l_child != nullptr && r_child != nullptr) {
            ttl_sum = l_child->ttl_sum + r_child->ttl_sum;
            max_sum = max({l_child->max_sum, r_child->max_sum, l_child->mxsuf_sum + r_child->mxprf_sum});
            mxprf_sum = max(l_child->mxprf_sum, l_child->ttl_sum + r_child->mxprf_sum);
            mxsuf_sum = max(r_child->mxsuf_sum, r_child->ttl_sum + l_child->mxsuf_sum);
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
            mxprf_sum = x;
            mxsuf_sum = x;
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
            return {ttl_sum, max_sum, mxprf_sum, mxsuf_sum};
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
             << ", mxprf_sum " << mxprf_sum
             << ", and mxsuf_sum " << mxsuf_sum << endl;
        if (l_child != nullptr && r_child != nullptr) {
            l_child->debugPrint(depth + 1);
            r_child->debugPrint(depth + 1);
        }

        return;
    }
};

struct MinSegTree {    
    int l, r;
    lng ttl_sum = 0, min_sum = 0, mnprf_sum = 0, mnsuf_sum = 0;
    MinSegTree *l_child, *r_child;

    template<class T> 
    MinSegTree(int l, int r, const vector<T> &arr): l(l), r(r) {
        if (l == r) {
            ttl_sum = arr[l];
            min_sum = arr[l];
            mnprf_sum = arr[l];
            mnsuf_sum = arr[l];
            l_child = r_child = nullptr;
        } else {
            int m = (l + r) / 2;
            l_child = new MinSegTree(l, m, arr);
            r_child = new MinSegTree(m + 1, r, arr);
            pull();
        }

        return;
    }

    // pull states up from children
    void pull() {
        if (l_child != nullptr && r_child != nullptr) {
            ttl_sum = l_child->ttl_sum + r_child->ttl_sum;
            min_sum = min({l_child->min_sum, r_child->min_sum, l_child->mnsuf_sum + r_child->mnprf_sum});
            mnprf_sum = min(l_child->mnprf_sum, l_child->ttl_sum + r_child->mnprf_sum);
            mnsuf_sum = min(r_child->mnsuf_sum, r_child->ttl_sum + l_child->mnsuf_sum);
        }

        return;
    }

    void singleValUpdate(int cur, lng x) {
        if (r < cur || cur < l) {
            return;
        }
        
        if (cur == l && r == cur) {
            ttl_sum = x;
            min_sum = x;
            mnprf_sum = x;
            mnsuf_sum = x;
            return;
        }
        
        l_child->singleValUpdate(cur, x);
        r_child->singleValUpdate(cur, x);
        pull();

        return;
    }

    array<lng, 4> rangeMinQuery(int cur_l, int cur_r) {
        if (cur_l > cur_r || (r < cur_l || cur_r < l)) {
            return {0, INF64, INF64, INF64};
        }
        
        if (cur_l <= l && r <= cur_r) {
            return {ttl_sum, min_sum, mnprf_sum, mnsuf_sum};
        }

        array<lng, 4> L = l_child->rangeMinQuery(cur_l, cur_r);
        array<lng, 4> R = r_child->rangeMinQuery(cur_l, cur_r);
        array<lng, 4> res = {
            L[0] + R[0],
            min({L[1], R[1], L[3] + R[2]}),
            min(L[2], L[0] + R[2]),
            min(R[3], R[0] + L[3])
        };

        return res;
    }

    void debugPrint(int depth = 0) {
        for (int t = 0; t < depth; t++) {
            cout << '\t';
        }
        cout << "[" << l << ", " << r << "] has ttl_sum " << ttl_sum 
             << ", min_sum " << min_sum
             << ", mnprf_sum " << mnprf_sum
             << ", and mnsuf_sum " << mnsuf_sum << endl;
        if (l_child != nullptr && r_child != nullptr) {
            l_child->debugPrint(depth + 1);
            r_child->debugPrint(depth + 1);
        }

        return;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> A(n);
    for (int &a : A)
        cin >> a;

    MaxSegTree *mx_segt = new MaxSegTree(0, n - 1, A);
    MinSegTree *mn_segt = new MinSegTree(0, n - 1, A);

    // mx_segt->debugPrint();
    // mn_segt->debugPrint();

    lng ans = 0;
    for (int i = 0; i < n - 1; i++) {
        ans = max(ans, abs(mx_segt->rangeMaxQuery(0, i)[3] - mn_segt->rangeMinQuery(i + 1, n - 1)[2]));
        ans = max(ans, abs(mn_segt->rangeMinQuery(0, i)[3] - mx_segt->rangeMaxQuery(i + 1, n - 1)[2]));
    }

    cout << ans << endl;
    
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

