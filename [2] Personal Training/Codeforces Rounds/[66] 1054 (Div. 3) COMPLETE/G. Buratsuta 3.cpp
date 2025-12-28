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

struct SegTree {
    int l, r;
    pair<int, int> a, b;
    unique_ptr<SegTree> l_child, r_child;

    template<typename T> 
    SegTree(int l, int r, const vector<T> &arr): l(l), r(r) {
        if (l == r) {
            assert(-INF64 <= arr[l] && arr[l] <= INF64);
            a = {arr[l], 1};
        
            // cout << l << ' ' << r << ' ' << a.fi << ' ' << a.se << ' ' << b.fi << ' ' << b.se << endl;
        } else {
            int m = (l + r) / 2;
            l_child = make_unique<SegTree>(l, m, arr);
            r_child = make_unique<SegTree>(m + 1, r, arr);
            pull();

            // cout << l << ' ' << r << ' ' << a.fi << ' ' << a.se << ' ' << b.fi << ' ' << b.se << endl;
        }
    }

    // pull states up from children
    void pull() {
        if (l_child && r_child) {
            map<int, int> M;
            M[l_child->a.fi] += l_child->a.se; 
            M[l_child->b.fi] += l_child->b.se; 
            M[r_child->a.fi] += r_child->a.se; 
            M[r_child->b.fi] += r_child->b.se; 
        
            set<pair<int, int>> S;
            for (auto &[x, cnt] : M)
                S.insert({cnt, x});

            if (!S.empty()) {
                a = {S.rbegin()->se, S.rbegin()->fi};
                S.erase(prev(S.end()));
            }
            
            if (!S.empty()) {
                b = {S.rbegin()->se, S.rbegin()->fi};
                S.erase(prev(S.end()));
            }

            if (!S.empty()) {
                a.se -= S.rbegin()->fi;
                if (a.se == 0)
                    a = {0, 0};
                b.se -= S.rbegin()->fi;
                if (b.se == 0)
                    b = {0, 0};
            }
        }
    }

    pair<pair<int, int>, pair<int, int>> rangeQuery(int l_cur, int r_cur) {
        if (l_cur > r_cur || (r < l_cur || r_cur < l)) {
            return {{0, 0}, {0, 0}};
        } 
        
        if (l_cur <= l && r <= r_cur) {
            return {a, b};
        }

        auto [l_a, l_b] = l_child->rangeQuery(l_cur, r_cur);
        auto [r_a, r_b] = r_child->rangeQuery(l_cur, r_cur);

        map<int, int> M;
        M[l_a.fi] += l_a.se; 
        M[l_b.fi] += l_b.se; 
        M[r_a.fi] += r_a.se; 
        M[r_b.fi] += r_b.se;
    
        set<pair<int, int>> S;
        for (auto &[x, cnt] : M)
            S.insert({cnt, x});

        pair<int, int> A, B;
        if (!S.empty()) {
            A = {S.rbegin()->se, S.rbegin()->fi};
            S.erase(prev(S.end()));
        }
        
        if (!S.empty()) {
            B = {S.rbegin()->se, S.rbegin()->fi};
            S.erase(prev(S.end()));
        }

        if (!S.empty()) {
            A.se -= S.rbegin()->fi;
            if (A.se == 0)
                A = {0, 0};
            B.se -= S.rbegin()->fi;
            if (B.se == 0)
                B = {0, 0};
        }
        
        return {A, B};
    }

    lng getRange() const {
        return r - l + 1;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> A(n);
    map<int, indexed_set<int>> A_idxs;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        
        A_idxs[A[i]].insert(i);
    }
    for (auto &[a, I] : A_idxs)
        I.insert(n);
    
    unique_ptr<SegTree> segt = make_unique<SegTree>(0, n - 1, A);

    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;

        auto [a, b] = segt->rangeQuery(l, r);

        int req = (r - l + 1) / 3;
        vector<int> ans;
        if (a.fi != 0) 
            if (A_idxs[a.fi].order_of_key(r + 1) - A_idxs[a.fi].order_of_key(l) > req)
                ans.pb(a.fi);
        
        if (b.fi != 0) 
            if (A_idxs[b.fi].order_of_key(r + 1) - A_idxs[b.fi].order_of_key(l) > req)
                ans.pb(b.fi);

        sort(ans.begin(), ans.end());

        if (ans.empty()) {
            cout << -1 << endl;
            continue;
        }

        for (int x : ans)
            cout << x << ' ';
        cout << endl;
    }

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