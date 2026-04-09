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
                l_child->sum = l_child->getRange() * set_upd;
                l_child->mn_idx = l_child->mx_idx = l_child->l;
                
                r_child->add_upd = 0;
                r_child->set_upd = set_upd;
                r_child->set_flag = true;
                r_child->mn = r_child->mx = set_upd;
                r_child->sum = r_child->getRange() * set_upd;
                r_child->mn_idx = r_child->mx_idx = r_child->l;
                
                set_upd = 0;
                set_flag = false;
            }

            if (add_upd != 0) {
                l_child->add_upd += add_upd;
                l_child->mn += add_upd;
                l_child->mx += add_upd;
                l_child->sum += l_child->getRange() * add_upd;
                
                r_child->add_upd += add_upd;
                r_child->mn += add_upd;
                r_child->mx += add_upd;
                r_child->sum += r_child->getRange() * add_upd;

                add_upd = 0;
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

            sum = l_child->sum + r_child->sum;
        }
    }

    void rangeAddUpdate(int l_cur, int r_cur, lng x) {
        if (l_cur > r_cur || (r < l_cur || r_cur < l)) {
            return;
        }
        
        if (l_cur <= l && r <= r_cur) {
            if (set_flag) {
                set_upd += x;
            } else { 
                add_upd += x; 
            }
            mn += x;
            mx += x;
            sum += getRange() * x;            
            return;
        }
        
        push();
        l_child->rangeAddUpdate(l_cur, r_cur, x);
        r_child->rangeAddUpdate(l_cur, r_cur, x);
        pull();
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
            sum = getRange() * x;
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

        return l_child->rangeSumQuery(l_cur, r_cur) + r_child->rangeSumQuery(l_cur, r_cur);
    }

    lng getRange() const {
        return r - l + 1;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector A(n + 2, vector<lng>(m + 2));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> A[i][j];

    vector S(n + 2, vector<lng>(m + 2, -INF64));
    S[1][0] = 0;
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= m; j++) 
            S[i][j] = A[i][j] + max(S[i - 1][j], S[i][j - 1]);

    vector E(n + 2, vector<lng>(m + 2, -INF64));
    E[n][m + 1] = 0;
    for (int i = n; i >= 1; i--)
        for (int j = m; j >= 1; j--)
            E[i][j] = A[i][j] + max(E[i + 1][j], E[i][j + 1]);

    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= m; j++) {
    //         cout << S[i][j] << ' ';
    //     }
    //     cout << endl;
    // }

    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= m; j++) {
    //         cout << E[i][j] << ' ';
    //     }
    //     cout << endl;
    // }

    int cnt = 1;
    vector<lng> B = {0};
    vector<pair<int, int>> ran(n + m + 1, {INF32, -INF32});
    for (int t = 2; t <= n + m; t++)
        for (int i = min(n, t - 1), j = max(1, t - min(n, t - 1)); i >= 1 && j <= m; i--, j++) {
            B.pb(S[i][j] + E[i][j] - A[i][j]);
            ran[t].fi = min(ran[t].fi, cnt);
            ran[t].se = max(ran[t].se, cnt);
            cnt++;
        }

    assert(cnt == n * m + 1);

    cnt = 1;
    lng ans = INF64;
    unique_ptr<SegTree> segt = make_unique<SegTree>(1, n * m, B);
    for (int t = 2; t <= n + m; t++)
        for (int i = min(n, t - 1), j = max(1, t - min(n, t - 1)); i >= 1 && j <= m; i--, j++) {
            segt->rangeSetUpdate(cnt, cnt, B[cnt] - 2 * A[i][j]);
            ans = min(ans, segt->rangeMaxQuery(ran[i + j].fi, ran[i + j].se).fi);
            segt->rangeSetUpdate(cnt, cnt, B[cnt]);
            cnt++;
        }

    cout << ans << endl;

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