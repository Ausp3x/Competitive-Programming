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

template<lng MOD>
struct ModInt {
    lng n;

    ModInt(lng N = 0): n(N % MOD) {
        if (n < 0) { 
            n += MOD;}
    }
    
    ModInt &operator++() {
        n++;
        if (n == MOD) {
            n = 0;}
        
        return *this;
    }

    ModInt &operator--() {
        if (n == 0) {
            n = MOD;}
        n--;
        
        return *this;
    }

    ModInt operator++(int) {
        ModInt res = *this;
        ++*this;
        
        return res;
    }

    ModInt operator--(int) {
        ModInt res = *this;
        --*this;

        return res;
    }

    ModInt &operator+=(const ModInt &other) {
        n += other.n;
        if (n >= MOD) {
            n -= MOD;}

        return *this;
    }
    
    ModInt &operator-=(const ModInt &other) {
        n -= other.n;
        if (n < 0) {
            n += MOD;}

        return *this;
    }
    
    ModInt &operator*=(const ModInt &other) {
        n = n * other.n % MOD;

        return *this;
    }

    ModInt &operator/=(const ModInt &other) {
        n = n * other.inv().n % MOD;

        return *this;
    }

    ModInt operator+() const {
        return *this;
    }
    
    ModInt operator-() const {
        return ModInt() - *this;
    }

    friend ModInt operator+(const ModInt &a, const ModInt &b) {
        return ModInt(a) += b;
    }
    
    friend ModInt operator-(const ModInt &a, const ModInt &b) {
        return ModInt(a) -= b;
    }

    friend ModInt operator*(const ModInt &a, const ModInt &b) {
        return ModInt(a) *= b;
    }
    
    friend ModInt operator/(const ModInt &a, const ModInt &b) {
        return ModInt(a) /= b;
    }

    friend bool operator==(const ModInt &a, const ModInt &b) {
        return a.n == b.n;
    }

    friend bool operator!=(const ModInt &a, const ModInt &b) {
        return a.n != b.n;
    }

    friend istream &operator>>(istream &is, ModInt &a) {
        lng b;
        is >> b;
        a = ModInt(b);

        return is;
    }

    friend ostream &operator<<(ostream &os, const ModInt &a) {
        return os << a.n;
    }

    ModInt inv() const {
        assert(n != 0);

        lng a = n, b = MOD, x = 1, y = 0;
        while (b > 0) {
            lng q = a / b;
            a = exchange(b, a - q * b);
            x = exchange(y, x - q * y);
        }

        return ModInt(x);
    }

    ModInt pow(lng b) const {
        assert(b >= 0);
        
        ModInt a = *this;
        ModInt res = 1;
        while (b > 0) {
            if (b & 1) {
                res *= a;}
            
            a *= a;
            b >>= 1;
        }

        return res;
    }
};
using mint = ModInt<998'244'353>;

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
    int n;
    cin >> n;
    vector<lng> A(n);
    for (lng &a : A)
        cin >> a;

    vector<lng> B = A;
    sort(B.begin(), B.end());

    map<lng, deque<int>> I;
    for (int i = 0; i < n; i++)
        I[B[i]].pb(i);

    indexed_set<lng> S;
    unique_ptr<SegTree> segt = make_unique<SegTree>(0, n - 1, vector<lng>(n));

    auto getLR = [&](int i) -> pair<lng, lng> {
        int len = S.size();
        lng L = 0, R = 0;
        if (i >= 2) {
            int j = *S.find_by_order(i - 2);
            L = (i - 1) * B[*S.find_by_order(i - 1)] - segt->rangeSumQuery(0, j);
        }
        if (i <= len - 3) {
            int j = *S.find_by_order(i + 2);
            R = segt->rangeSumQuery(j, n - 1) - (len - i - 2) * B[*S.find_by_order(i + 1)];
        }

        return {L, R};
    };

    for (int i = 0; i < n; i++) {
        S.insert(I[A[i]][0]);
        segt->rangeAddUpdate(I[A[i]][0], I[A[i]][0], A[i]); 
        I[A[i]].pop_front();
        if (i < 2)
            continue;

        int len = S.size();
        int l = -1, r = len;
        while (r - l > 1) {
            int md = (l + r) / 2;
            
            auto [L, R] = getLR(md);

            if (R > L) {
                l = md;
            } else {
                r = md;
            }            
        }

        auto [L1, R1] = getLR(l);
        auto [L2, R2] = getLR(r);

        // cout << l << ' ' << L1 << ' ' << R1 << endl;
        // cout << r << ' ' << L2 << ' ' << R2 << endl;

        cout << mint(min(max(L1, R1), max(L2, R2))) / mint(len - 2) << endl;
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