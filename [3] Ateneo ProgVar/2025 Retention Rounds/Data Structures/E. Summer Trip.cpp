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
    lng sum = 0;
    SegTree *l_child, *r_child;

    template<typename T> 
    SegTree(int l, int r, const vector<T> &arr): l(l), r(r) {
        if (l == r) {
            sum = arr[l];
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
            sum = l_child->sum | r_child->sum;
        }
    }

    lng rangeSumQuery(int l_cur, int r_cur) {
        if (l_cur > r_cur || (r < l_cur || r_cur < l)) {
            return 0;
        } 
        
        if (l_cur <= l && r <= r_cur) {
            return sum;
        } 

        return l_child->rangeSumQuery(l_cur, r_cur) | r_child->rangeSumQuery(l_cur, r_cur);
    }

    lng getRange() const {
        return r - l + 1;
    }
};

void solve() {
    string s;
    cin >> s;
    
    int n = s.size();
    vector<int> A(n);
    vector<deque<int>> C(26);
    for (int i = 0; i < n; i++) {
        A[i] = 1 << (s[i] - 'a');
        C[s[i] - 'a'].pb(i);
    }
    for (int i = 0; i < 26; i++)
        C[i].pb(n);

    int ans = 0;
    SegTree *segt = new SegTree(0, n - 1, A);
    for (int i = 0; i < n; i++) {
        assert(C[s[i] - 'a'].front() == i);
        C[s[i] - 'a'].pop_front();

        int j = C[s[i] - 'a'].front();
        if (j - 1 == i)
            continue;
        
        int cur = 0, dis = segt->rangeSumQuery(i + 1, j - 1);
        for (int i = 0; i < 26; i++)
            if (dis & (1 << i))
                cur++;

        // cout << i << ' ' << j - 1 << ' ' << cur << endl;

        ans += cur;
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