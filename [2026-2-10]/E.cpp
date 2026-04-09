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

struct SegTree {
    int l, r;
    lng mn = INF64, mx = -INF64, sum = 0;
    int mn_idx = -1, mx_idx = -1;
    lng add_upd = 0, set_upd = 0;
    bool set_flag = false;
    unique_ptr<SegTree> l_child, r_child;

    template<typename T> 
    SegTree(int l, int r, const vector<T> &arr): l(l), r(r) {
        if (l == r) {
            assert(-INF64 <= arr[l] && arr[l] <= INF64);
            mn = mx = sum = arr[l];
            mn_idx = mx_idx = l;
        } else {
            int m = (l + r) / 2;
            l_child = make_unique<SegTree>(l, m, arr);
            r_child = make_unique<SegTree>(m + 1, r, arr);
            pull();
        }
    }

    // push updates down to children
    void push() {
        if (l_child && r_child) {
            if (set_flag) {
                l_child->add_upd = 0;
                l_child->set_upd = set_upd;
                l_child->set_flag = true;
                l_child->mn = l_child->mx = set_upd;
                l_child->sum = set_upd;
                l_child->mn_idx = l_child->mx_idx = l_child->l;
                
                r_child->add_upd = 0;
                r_child->set_upd = set_upd;
                r_child->set_flag = true;
                r_child->mn = r_child->mx = set_upd;
                r_child->sum = set_upd;
                r_child->mn_idx = r_child->mx_idx = r_child->l;
                
                set_upd = 0;
                set_flag = false;
            }
        }
    }

    // pull states up from children
    void pull() {
        assert(add_upd == 0 && set_upd == 0 && !set_flag);
        if (l_child && r_child) {
            if (l_child->mn <= r_child->mn) {
                mn = l_child->mn;
                mn_idx = l_child->mn_idx;
            } else {
                mn = r_child->mn;
                mn_idx = r_child->mn_idx;
            }

            if (l_child->mx >= r_child->mx) {
                mx = l_child->mx;
                mx_idx = l_child->mx_idx;
            } else {
                mx = r_child->mx;
                mx_idx = r_child->mx_idx;
            }

            sum = l_child->sum | r_child->sum;
        }
    }

    void rangeSetUpdate(int l_cur, int r_cur, lng x) {
        if (l_cur > r_cur || (r < l_cur || r_cur < l)) {
            return;
        }
        
        if (l_cur <= l && r <= r_cur) {
            add_upd = 0;
            set_upd = x;
            set_flag = true;
            mn = mx = x;
            sum = x;
            mn_idx = mx_idx = l;
            return;
        }
        
        push();
        l_child->rangeSetUpdate(l_cur, r_cur, x);
        r_child->rangeSetUpdate(l_cur, r_cur, x);
        pull();
    }

    pair<lng, int> rangeMaxQuery(int l_cur, int r_cur) {
        if (l_cur > r_cur || (r < l_cur || r_cur < l)) {
            return {-INF64, -1};
        }

        if (l_cur <= l && r <= r_cur) {
            return {mx, mx_idx};
        }
        
        push();
        auto l_res = l_child->rangeMaxQuery(l_cur, r_cur);
        auto r_res = r_child->rangeMaxQuery(l_cur, r_cur);
        if (l_res.fi >= r_res.fi) {
            return l_res;
        } else {
            return r_res;
        }
    }

    pair<lng, int> rangeMinQuery(int l_cur, int r_cur) {
        if (l_cur > r_cur || (r < l_cur || r_cur < l)) {
            return {INF64, -1};
        }

        if (l_cur <= l && r <= r_cur) {
            return {mn, mn_idx};
        }
        
        push();
        auto l_res = l_child->rangeMinQuery(l_cur, r_cur);
        auto r_res = r_child->rangeMinQuery(l_cur, r_cur);
        if (l_res.fi <= r_res.fi) {
            return l_res;
        } else {
            return r_res;
        }
    }

    lng rangeSumQuery(int l_cur, int r_cur) {
        if (l_cur > r_cur || (r < l_cur || r_cur < l)) {
            return 0;
        } 
        
        if (l_cur <= l && r <= r_cur) {
            return sum;
        } 
        
        push();

        return l_child->rangeSumQuery(l_cur, r_cur) | r_child->rangeSumQuery(l_cur, r_cur);
    }
};

struct EulerTourTree {
    int n, root;
    vector<lng> arr;
    vector<vector<int>> adjl;

    int timer = 0;
    vector<int> t_in, t_out, time_to_orig;
    vector<lng> euler;
    unique_ptr<SegTree> segt;

    EulerTourTree(int n, int root, const vector<lng> &arr, const vector<vector<int>> &adjl) : n(n), root(root), arr(arr), adjl(adjl) {
        assert(0 <= root && root < n);
        assert(arr.size() == n && adjl.size() == n);
        t_in.resize(n, -1);
        t_out.resize(n, -1);
        time_to_orig.resize(n);
        euler.resize(n);
        
        dfs(root, -1);

        segt = make_unique<SegTree>(0, n - 1, euler);
    }

    void dfs(int cur, int prv) {
        t_in[cur] = timer;
        time_to_orig[timer] = cur;
        euler[timer] = arr[cur];
        timer++;

        for (int nxt : adjl[cur]) {
            if (nxt == prv) {
                continue;
            }

            dfs(nxt, cur);
        }

        t_out[cur] = timer - 1;
    }

    // void subtreeAddUpdate(int u, lng x, bool u_only = false) {
    //     segt->rangeAddUpdate(t_in[u], (u_only ? t_in[u] : t_out[u]), x);
    // }

    void subtreeSetUpdate(int u, lng x, bool u_only = false) {
        segt->rangeSetUpdate(t_in[u], (u_only ? t_in[u] : t_out[u]), x);
    }

    pair<lng, int> subtreeMaxQuery(int u, bool u_only = false) {
        auto res = segt->rangeMaxQuery(t_in[u], (u_only ? t_in[u] : t_out[u]));
        res.se = time_to_orig[res.se];

        return res;
    }
    
    pair<lng, int> subtreeMinQuery(int u, bool u_only = false) {
        auto res = segt->rangeMinQuery(t_in[u], (u_only ? t_in[u] : t_out[u]));
        res.se = time_to_orig[res.se];

        return res;
    }

    lng subtreeSumQuery(int u, bool u_only = false) {
        return segt->rangeSumQuery(t_in[u], (u_only ? t_in[u] : t_out[u]));
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<lng> color(n);
    for (int i = 0; i < n; i++) {
        lng c;
        cin >> c;
        color[i] = (1ll << (c - 1));
    }
    vector<vector<int>> adjl(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;

        adjl[u].pb(v);
        adjl[v].pb(u);
    }
    
    EulerTourTree ett(n, 0, color, adjl);

    while (m--) {
        int t;
        cin >> t;
        
        if (t == 1) {
            int v, c;
            cin >> v >> c;
            v--;

            ett.subtreeSetUpdate(v, 1ll << (c - 1)); 
        } else if (t == 2) {
            int v;
            cin >> v;
            v--;

            // cout << v << ' ' << ett.subtreeSumQuery(v) << endl;

            cout << __builtin_popcountll(ett.subtreeSumQuery(v)) << endl;
        }
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