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

struct ModInt {
    lng val;
    static int MOD;

    ModInt(lng x = 0) {
        val = x % MOD;
        if (val < 0) { 
            val += MOD;
        }
    }

    ModInt(const ModInt &other) : val(other.val) {}
    
    static void setMod(int mod) {
        assert(1 <= mod);
        MOD = mod;
    }
    
    ModInt &operator++() {
        val++;
        if (val == MOD) {
            val = 0;
        }
        
        return *this;
    }

    ModInt &operator--() {
        if (val == 0) {
            val = MOD;
        }
        val--;
        
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

    ModInt &operator=(const ModInt &other) {
        val = other.val;
        
        return *this;
    }

    ModInt &operator+=(const ModInt &other) {
        val += other.val;
        if (val >= MOD) {
            val -= MOD;
        }

        return *this;
    }
    
    ModInt &operator-=(const ModInt &other) {
        val -= other.val;
        if (val < 0) {
            val += MOD;
        }

        return *this;
    }
    
    ModInt &operator*=(const ModInt &other) {
        val = (val * other.val) % MOD;

        return *this;
    }
    
    ModInt inv() const {
        assert(gcd(val, MOD) == 1);
        lng x = val, y = MOD, a = 1, b = 0, t;
        while (y > 0) {
            t = x / y;
            x -= t * y;
            a -= t * b;
            swap(x, y);
            swap(a, b);
        }

        return ModInt(a);
    }
    
    ModInt &operator/=(const ModInt &other) {
        val = (val * other.inv().val) % MOD;

        return *this;
    }

    ModInt pow(long long exp) const {
        assert(0 <= exp);
        ModInt bse = *this, res = 1;
        while (exp > 0) {
            if (exp & 1) {
                res *= bse;
            }
            
            bse *= bse;
            exp >>= 1;
        }

        return res;
    }

    ModInt operator+() const {
        return *this;
    }
    
    ModInt operator-() const {
        return ModInt() - *this;
    }

    friend ModInt operator+(const ModInt &x, const ModInt &y) {
        return ModInt(x) += y;
    }
    
    friend ModInt operator-(const ModInt &x, const ModInt &y) {
        return ModInt(x) -= y;
    }

    friend ModInt operator*(const ModInt &x, const ModInt &y) {
        return ModInt(x) *= y;
    }
    
    friend ModInt operator/(const ModInt &x, const ModInt &y) {
        return ModInt(x) /= y;
    }

    friend bool operator==(const ModInt &x, const ModInt &y) {
        return x.val == y.val;
    }

    friend bool operator!=(const ModInt &x, const ModInt &y) {
        return x.val != y.val;
    }

    friend istream &operator>>(istream &is, ModInt &x) {
        lng y;
        is >> y;
        x = ModInt(y);

        return is;
    }

    friend ostream &operator<<(ostream &os, const ModInt &x) {
        return os << x.val;
    }
};
int ModInt::MOD = 998'244'353;

struct ModFac {
    int n;
    vector<ModInt> fac, inv_fac;

    ModFac(int n): n(n) {
        fac.resize(n + 1);
        fac[0] = 1;
        for (int i = 1; i <= n; i++) {
            fac[i] = fac[i - 1] * i;
        }

        inv_fac.resize(n + 1);
        inv_fac[n] = fac[n].inv();
        for (int i = n - 1; i >= 0; i--) {
            inv_fac[i] = inv_fac[i + 1] * (i + 1);
        }
    }

    ModInt rangeFac(int x, int y) const {
        if (y > x || y < 0) {
            return ModInt(0);
        }

        return fac[x] * inv_fac[y];
    }

    ModInt combiNR(int x, int y) const {
        if (y > x || y < 0) {
            return ModInt(0);
        }

        assert(x <= n);

        return fac[x] * inv_fac[y] * inv_fac[x - y];
    }

    ModInt combiWR(int x, int y) const {
        if (x < 1 || y < 0) {
            return ModInt(0);
        }

        assert(x + y - 1 <= n);

        return fac[x + y - 1] * inv_fac[y] * inv_fac[x - 1];
    }

    ModInt permuNR(int x, int y) const {
        if (y > x || y < 0) {
            return ModInt(0);
        }

        assert(x <= n);   

        return fac[x] * inv_fac[x - y];
    }

    ModInt permuWR(int x, int y) const {
        if (y < 0) {
            return ModInt(0);
        }
        
        return ModInt(x).pow(y);
    }
};

struct SegTree {
    int l, r;
    ModInt mul = 0;
    int asc = 0, dec = 0;
    ModFac *mf;
    SegTree *l_child, *r_child;

    SegTree(int l, int r, const vector<ModInt> &arr, ModFac *mf): l(l), r(r) {
        if (l == r) {
            this->mf = mf;
            mul = arr[l];
            l_child = r_child = nullptr;
        } else {
            this->mf = mf;
            int m = (l + r) / 2;
            l_child = new SegTree(l, m, arr, mf);
            r_child = new SegTree(m + 1, r, arr, mf);
            pull();
        }
    }

    // push updates down to children
    void push() {
        if (l_child != nullptr && r_child != nullptr) {
            if (asc != 0 || dec != 0) {
                l_child->asc = asc;
                l_child->dec = dec;
                l_child->mul = l_child->recalculateMul();

                r_child->asc = (asc == 0 ? 0 : asc + l_child->getRange());
                r_child->dec = (dec == 0 ? 0 : dec - l_child->getRange());
                r_child->mul = r_child->recalculateMul();
                
                asc = 0;
                dec = 0;
            }
        }
    }

    // pull states up from children
    void pull() {
        assert(asc == 0 && dec == 0);
        if (l_child != nullptr && r_child != nullptr) {
            mul = l_child->mul * r_child->mul;
        }
    }

    void rangeFacAscUpdate(int l_cur, int r_cur) {
        if (l_cur > r_cur || (r < l_cur || r_cur < l)) {
            return;
        }
        
        if (l_cur <= l && r <= r_cur) {
            push();

            asc = l - l_cur + 2;
            mul = mf->rangeFac(asc + getRange() - 1, asc - 1);
            // cout << l_cur << ' ' << l << ' ' << r << ' ' << r_cur << ' ' << asc << ' ' << mul << endl;
            return;
        }
        
        push();
        l_child->rangeFacAscUpdate(l_cur, r_cur);
        r_child->rangeFacAscUpdate(l_cur, r_cur);
        pull();
    }

    void rangeFacDecUpdate(int l_cur, int r_cur) {
        if (l_cur > r_cur || (r < l_cur || r_cur < l)) {
            return;
        }
        
        if (l_cur <= l && r <= r_cur) {
            push();

            dec = r_cur - l + 2;
            mul = mf->rangeFac(dec, dec - getRange());
            // cout << l_cur << ' ' << l << ' ' << r << ' ' << r_cur << ' ' << dec << ' ' << mul << endl;
            return;
        }
        
        push();
        l_child->rangeFacDecUpdate(l_cur, r_cur);
        r_child->rangeFacDecUpdate(l_cur, r_cur);
        pull();
    }

    ModInt rangeMulQuery(int l_cur, int r_cur) {
        if (l_cur > r_cur || (r < l_cur || r_cur < l)) {
            return 1;
        } 
        
        if (l_cur <= l && r <= r_cur) {
            return mul;
        } 
        
        push();

        return l_child->rangeMulQuery(l_cur, r_cur) * r_child->rangeMulQuery(l_cur, r_cur);
    }

    lng getRange() const {
        return r - l + 1;
    }

    ModInt recalculateMul() const {
        assert(asc == 0 || dec == 0);
        if (asc != 0) {
            return mf->rangeFac(asc + getRange() - 1, asc - 1);
        } else if (dec != 0) {
            return mf->rangeFac(dec, dec - getRange());
        }
    }
};

void solve() {
    int n;
    cin >> n;
    vector<ModInt> A(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
        A[i]++;
    }

    ModFac mf(200'005);
    SegTree *segt = new SegTree(1, n, A, &mf);

    int q;
    cin >> q;
    while (q--) {
        char c;
        cin >> c;
        if (c == '?') {
            int l, r;
            cin >> l >> r;
            
            cout << segt->rangeMulQuery(l, r) - ModInt(1) << endl;
        } else if (c == '!') {
            int l, r;
            char x;
            cin >> l >> r >> x;
            
            if (x == 'A') {
                segt->rangeFacAscUpdate(l, r);
            } else if (x == 'D') {
                segt->rangeFacDecUpdate(l, r);
            }

            // for (int i = 1; i <= n; i++)
            //     cout << segt->rangeMulQuery(i, i) << ' ';
            // cout << endl << endl;
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