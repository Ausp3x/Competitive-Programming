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
template<class T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int const INF32 = 0x3f3f3f3f;
lng const INF64 = 0x3f3f3f3f3f3f3f3f;

struct SegTree {    
    int l, r;
    lng mx, mn;
    SegTree *l_child, *r_child;

    SegTree(int l, int r, const vector<int> &arr): l(l), r(r) {
        if (l == r) {
            mx = arr[l];
            mn = arr[l];
            l_child = r_child = nullptr;
        } else {
            int m = (l + r) / 2;
            l_child = new SegTree(l, m, arr);
            r_child = new SegTree(m + 1, r, arr);
            pull();
        }
    }

    // pull states up from children
    void pull() {
        if (l_child != nullptr && r_child != nullptr) {
            mx = max(l_child->mx, r_child->mx);
            mn = min(l_child->mn, r_child->mn);
        }

        return;
    }

    lng rangeMaxQuery(int cur_l, int cur_r) {
        if (cur_l > cur_r || (r < cur_l || cur_r < l)) {
            return 0;
        } 
        
        if (cur_l <= l && r <= cur_r) {
            return mx;
        } 
        
        return max(l_child->rangeMaxQuery(cur_l, cur_r), r_child->rangeMaxQuery(cur_l, cur_r));
    }

    lng rangeMinQuery(int cur_l, int cur_r) {
        if (cur_l > cur_r || (r < cur_l || cur_r < l)) {
            return INF32;
        } 
        
        if (cur_l <= l && r <= cur_r) {
            return mn;
        } 
        
        return min(l_child->rangeMinQuery(cur_l, cur_r), r_child->rangeMinQuery(cur_l, cur_r));
    }

    void debugPrint(int depth = 0) {
        for (int t = 0; t < depth; t++) {
            cout << '\t';
        }
        cout << "[" << l << ", " << r << "] has mx " << mx << " and mn " << mn << endl;
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
    
    vector<int> ans;
    SegTree *segt = new SegTree(0, n - 1, A);
    for (int i = 0; i < n; i++) {
        int l = segt->rangeMaxQuery(0, i - 1);
        int r = segt->rangeMinQuery(i + 1, n - 1);

        if (l <= A[i] && A[i] <= r)
            ans.pb(A[i]);
    }

    cout << ans.size() << ' ';
    for (int i = 0; i < min<int>(ans.size(), 100); i++)
        cout << ans[i] << ' ';
    cout << endl;
    
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