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

    explicit operator lng() const {
        return n;
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

    ModInt &operator+=(const ModInt &o) {
        n += o.n;
        if (n >= MOD) {
            n -= MOD;}

        return *this;
    }
    
    ModInt &operator-=(const ModInt &o) {
        n -= o.n;
        if (n < 0) {
            n += MOD;}

        return *this;
    }
    
    ModInt &operator*=(const ModInt &o) {
        n = lng(n) * o.n % MOD;

        return *this;
    }

    ModInt &operator/=(const ModInt &o) {
        n = lng(n) * inv(o).n % MOD;

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

    friend ModInt inv(ModInt a) {
        assert(a != 0);

        lng n = a.n, b = MOD, x = 1, y = 0;
        while (b > 0) {
            lng q = n / b;
            n = exchange(b, n - q * b);
            x = exchange(y, x - q * y);
        }

        return ModInt(x);
    }

    friend ModInt pow(ModInt a, lng b) {
        if (b < 0) {
            return pow(inv(a), -b);}
        
        ModInt res = 1;
        while (b > 0) {
            if (b & 1) {
                res *= a;}
            
            a *= a;
            b >>= 1;
        }

        return res;
    }

    bool operator==(const ModInt &o) const {
        return n == o.n;
    }

    bool operator!=(const ModInt &o) const {
        return n != o.n;
    }

    bool operator<(const ModInt &o) const {
        return n < o.n;
    }

    bool operator>(const ModInt &o) const { 
        return o.n < n;
    }

    bool operator<=(const ModInt &o) const { 
        return !(o < *this); 
    }

    bool operator>=(const ModInt &o) const { 
        return !(*this < o); 
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
};
using mint = ModInt<998'244'353>;

// T: O(n * log(n)), M: O(n)
struct Poly {
    using cld = complex<long double>;
    static constexpr long double pi = 3.14159265358979323846;

    // ascending powers 
    vector<lng> v;

    Poly(int n = 1): v(max(1, n), 0) {}

    Poly(const vector<lng> &a): v(a) { 
        trim();
    }

    int deg() const { 
        return v.size() - 1; 
    }

    lng lead() const { 
        return v.empty() ? 0 : v.back(); 
    }

    void trim() {
        while (v.size() > 1 && v.back() == 0) {
            v.pop_back();}
            
        if (v.empty()) {
            v.pb(0);}
    }

    lng &operator[](int i) { 
        return v[i]; 
    }
    
    lng operator[](int i) const { 
        return v[i]; 
    }

    int size() const { 
        return v.size(); 
    }

    Poly &operator+=(const Poly &o) {
        if (o.size() > size()) {
            v.resize(o.size(), 0);}

        for (int i = 0; i < o.size(); i++) {
            v[i] += o[i];}
        trim();

        return *this;
    }

    Poly &operator-=(const Poly &o) {
        if (o.size() > size()) {
            v.resize(o.size(), 0);}

        for (int i = 0; i < o.size(); i++) {
            v[i] -= o[i];}
        trim();

        return *this;
    }

    Poly &operator*=(lng o) {
        for (lng &x : v) {
            x *= o;}
        trim();

        return *this;
    }

    static void fft(vector<cld> &a, bool is_inv) {
        int n = a.size();
        vector<int> rev(n);
        for (int i = 1; i < n; i++) {
            rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? (n >> 1) : 0);
            if (i < rev[i]) {
                swap(a[i], a[rev[i]]);}
        }

        long double ang = 2 * pi / n * (is_inv ? -1 : 1);
        vector<cld> w(n / 2, 1);
        for (int i = 1; i < n / 2; i++) {
            w[i] = cld(cos(ang * i), sin(ang * i));}

        for (int len = 2; len <= n; len <<= 1) {
            for (int i = 0; i < n; i += len) {
                for (int j = 0; j < len / 2; j++) {
                    cld u = a[i + j];
                    cld v = a[i + j + len / 2] * w[n / len * j];
                    
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                }
            }
        }
        if (is_inv) {
            for (cld &x : a) {
                x /= n;}}
    }

    Poly &operator*=(const Poly &o) {
        if (o.size() == 1) {
            for (lng &x : v) {
                x *= o[0];}
            trim();

            return *this;
        }

        vector<cld> fa(v.begin(), v.end()), fb(o.v.begin(), o.v.end());
        int n = 1;
        while (n < size() + o.size() - 1) {
            n <<= 1;}
            
        fa.resize(n);
        fb.resize(n);

        fft(fa, false);
        fft(fb, false);
        for (int i = 0; i < n; i++) {
            fa[i] *= fb[i];}
        fft(fa, true);

        v.resize(n);
        for (int i = 0; i < n; i++) {
            v[i] = round(fa[i].real());}
        trim();
        
        return *this;
    }

    Poly operator+() const { 
        return *this; 
    }
    
    Poly operator-() const { 
        Poly res = *this; 
        for (lng &x : res.v) {
            x = -x;}
        
        return res; 
    }

    friend Poly operator+(Poly a, const Poly &b) { 
        return a += b; 
    }
    
    friend Poly operator-(Poly a, const Poly &b) { 
        return a -= b; 
    }

    friend Poly operator*(Poly a, lng b) {
        return a *= b;
    }

    friend Poly operator*(lng b, Poly a) {
        return a *= b;
    }

    friend Poly operator*(Poly a, const Poly &b) { 
        return a *= b;
    }

    // T: O(n)
    friend lng eval(const Poly &a, lng x) {
        lng res = 0;
        for (int i = a.size() - 1; i >= 0; i--) {
            res = res * x + a[i];}
        
        return res;
    }

    // T: O(n * log(n)^2)
    friend Poly pow(Poly a, lng b, int deg) {
        assert(b >= 0);

        Poly res(vector<lng>({1}));
        while (b > 0) {
            if (b & 1) {
                res *= a;
                if (res.size() > deg + 1) {
                    res.v.resize(deg + 1);}
                res.trim();
            }

            b >>= 1;
            if (b == 0) {
                break;}

            a *= a;
            if (a.size() > deg + 1) {
                a.v.resize(deg + 1);}
            a.trim();
        }

        return res;
    }

    bool operator==(const Poly &o) const { 
        return v == o.v; 
    }

    bool operator!=(const Poly &o) const { 
        return !(*this == o); 
    }

    friend ostream &operator<<(ostream &os, const Poly &a) {
        if (a.size() == 0) {
            return os << 0;}
        for (int i = 0; i < a.size(); i++) {
            os << a[i] << ' ';}
        
        return os;
    }
};

// T: O(n * log(n)), M: O(n)
struct Moly {
    static constexpr int MOD = 998'244'353; 
    static constexpr int proot = 3;

    // ascending powers 
    vector<mint> v;

    Moly(int n = 1): v(max(1, n), mint(0)) {}

    Moly(const vector<mint> &a): v(a) { 
        trim(); 
    }

    int deg() const { 
        return v.size() - 1; 
    }

    mint lead() const { 
        return v.empty() ? mint(0) : v.back(); 
    }

    void trim() {
        while (v.size() > 1 && v.back() == mint(0)) {
            v.pop_back();}
            
        if (v.empty()) {
            v.pb(mint(0));}
    }

    mint &operator[](int i) { 
        return v[i]; 
    }
    
    mint operator[](int i) const { 
        return v[i]; 
    }

    int size() const { 
        return v.size(); 
    }

    Moly &operator+=(const Moly &o) {
        if (o.size() > size()) {
            v.resize(o.size(), mint(0));}

        for (int i = 0; i < o.size(); i++) {
            v[i] += o[i];}
        trim();

        return *this;
    }

    Moly &operator-=(const Moly &o) {
        if (o.size() > size()) {
            v.resize(o.size(), mint(0));}

        for (int i = 0; i < o.size(); i++) {
            v[i] -= o[i];}
        trim();

        return *this;
    }

    Moly &operator*=(mint o) {
        for (mint &x : v) {
            x *= o;}
        trim();

        return *this;
    }

    static void ntt(vector<mint> &a, bool is_inv) {
        int n = a.size();
        vector<int> rev(n);
        for (int i = 1; i < n; i++) {
            rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? (n >> 1) : 0);
            if (i < rev[i]) {
                swap(a[i], a[rev[i]]);}
        }

        mint root = pow(mint(proot), (MOD - 1) / n);
        if (is_inv) {
            root = inv(root);}
        
        vector<mint> w(n / 2, 1);
        for (int i = 1; i < n / 2; i++) {
            w[i] = w[i - 1] * root;}

        for (int len = 2; len <= n; len <<= 1) {
            for (int i = 0; i < n; i += len) {
                for (int j = 0; j < len / 2; j++) {
                    mint u = a[i + j];
                    mint v = a[i + j + len / 2] * w[n / len * j];
                    
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                }
            }
        }
        if (is_inv) {
            mint n_inv = inv(mint(n));
            for (mint &x : a) {
                x *= n_inv;}
        }
    }

    Moly &operator*=(const Moly &o) {
        if (o.size() == 1) {
            for (mint &x : v) {
                x *= o[0];}
            trim();

            return *this;
        }

        vector<mint> fa = v, fb = o.v;
        int n = 1;
        while (n < size() + o.size() - 1) {
            n <<= 1;}
            
        fa.resize(n);
        fb.resize(n);

        ntt(fa, false);
        ntt(fb, false);
        for (int i = 0; i < n; i++) {
            fa[i] *= fb[i];}
        ntt(fa, true);

        v = fa;
        trim();
        
        return *this;
    }

    friend pair<Moly, Moly> divMod(const Moly &a, const Moly &b) {
        if (a.size() < b.size()) {
            return {Moly(vector<mint>{0}), a};}
        
        Moly a_rev = a, b_rev = b;
        reverse(a_rev.v.begin(), a_rev.v.end());
        reverse(b_rev.v.begin(), b_rev.v.end());        
        
        int len = a.size() - b.size() + 1;
        a_rev.v.resize(len);
        b_rev.v.resize(len);
        
        Moly q = a_rev * inv(b_rev, len - 1);
        q.v.resize(len);
        reverse(q.v.begin(), q.v.end());
        q.trim();
        
        Moly r = a - q * b;
        r.trim();
        
        return {q, r};
    }

    Moly &operator/=(const Moly &o) {
        return *this = divMod(*this, o).fi;
    }

    Moly &operator%=(const Moly &o) {
        return *this = divMod(*this, o).se;
    }

    Moly operator+() const { 
        return *this; 
    }
    
    Moly operator-() const { 
        Moly res = *this; 
        for (mint &x : res.v) {
            x = -x;}
        
        return res; 
    }

    friend Moly operator+(Moly a, const Moly &b) { 
        return a += b; 
    }
    
    friend Moly operator-(Moly a, const Moly &b) { 
        return a -= b;
    }

    friend Moly operator*(Moly a, mint b) {
        return a *= b;
    }

    friend Moly operator*(mint b, Moly a) {
        return a *= b;
    }

    friend Moly operator*(Moly a, const Moly &b) { 
        return a *= b;
    }

    friend Moly operator/(Moly a, const Moly &b) {
        return a /= b;
    }

    friend Moly operator%(Moly a, const Moly &b) {
        return a %= b;
    }

    friend Moly deriv(const Moly &a) {
        if (a.size() <= 1) {
            return Moly(vector<mint>({0}));}

        Moly res(a.size() - 1);
        for (int i = 1; i < a.size(); i++) {
            res[i - 1] = a[i] * mint(i);}
        res.trim();

        return res;
    }

    // T: O(n)
    friend mint eval(const Moly &a, mint x) {
        mint res = 0;
        for (int i = a.size() - 1; i >= 0; i--) {
            res = res * x + a[i];}
        
        return res;
    }

    // T: O(n * log(n)^2)
    friend vector<mint> eval(const Moly &a, const vector<mint> &x) {
        if (x.empty()) {
            return {};}
            
        int n = x.size();
        vector<Moly> segt(4 * n);
        
        auto build = [&](auto &&build, int cur, int l, int r) -> void {
            if (l == r) {
                segt[cur] = Moly(vector<mint>{-x[l], mint(1)});
                return;
            }

            int md = l + (r - l) / 2;
            build(build, 2 * cur, l, md);
            build(build, 2 * cur + 1, md + 1, r);
            segt[cur] = segt[2 * cur] * segt[2 * cur + 1];
        };
        
        build(build, 1, 0, n - 1);

        vector<mint> res(n);
        
        auto solve = [&](auto &&solve, int cur, int l, int r, Moly p) -> void {
            p %= segt[cur]; // Modulo drastically reduces the degree
            if (l == r) {
                res[l] = p.size() > 0 ? p[0] : mint(0);
                return;
            }

            int mid = l + (r - l) / 2;
            solve(solve, 2 * cur, l, mid, p);
            solve(solve, 2 * cur + 1, mid + 1, r, p);
        };

        solve(solve, 1, 0, n - 1, a);
        
        return res;
    }

    friend Moly exp(const Moly &a, int deg) {
        assert(a.size() == 0 || a[0] == mint(0)); 
        
        Moly res(vector<mint>({1}));
        for (int len = 2; len / 2 < deg + 1; len <<= 1) {
            Moly cur(vector<mint>(a.v.begin(), a.v.begin() + min(int(a.size()), len)));
            Moly dif = cur - log(res, len - 1);
            dif.v.resize(len, mint(0));
            dif[0] += mint(1);
            
            res *= dif;
            res.v.resize(len, mint(0));
            res.trim();
        }
        res.v.resize(deg + 1, mint(0));
        res.trim();
        
        return res;
    }

    friend Moly integ(const Moly &a) {
        Moly res(a.size() + 1);
        for (int i = 1; i <= a.size(); i++) {
            res[i] = a[i - 1] * inv(mint(i));}
        res.trim();

        return res;
    }

    friend Moly inv(const Moly &a, int deg) {
        assert(a[0] != mint(0));

        Moly res(vector<mint>({inv(a[0])}));
        for (int len = 2; len / 2 < deg + 1; len <<= 1) {
            int n = len << 1;
            vector<mint> fa(a.v.begin(), a.v.begin() + min(int(a.size()), len));
            vector<mint> fb = res.v;

            fa.resize(n);
            fb.resize(n);

            ntt(fa, false);
            ntt(fb, false);

            for (int i = 0; i < n; i++) {
                fb[i] = fb[i] * (mint(2) - fa[i] * fb[i]);}

            ntt(fb, true);

            res.v.assign(fb.begin(), fb.begin() + len);
        }
        res.v.resize(deg + 1, mint(0));
        res.trim();
        
        return res;
    }

    friend Moly log(const Moly &a, int deg) {
        assert(a.size() > 0 && a[0] == mint(1)); 
        
        Moly res = integ(deriv(a) * inv(a, deg));
        res.v.resize(deg + 1, mint(0));
        res.trim();
        
        return res;
    }

    friend Moly pow(Moly a, lng b, int deg) {
        assert(b >= 0);

        if (b == 0) {
            return Moly(vector<mint>({1}));}
        
        if (a.size() == 0) {
            return Moly(vector<mint>({0}));}

        int pos = 0;
        while (pos < a.size() && a[pos] == mint(0)) {
            pos++;}

        if (pos == a.size() || (pos > 0 && b > deg / pos)) {
            return Moly(vector<mint>({0}));}

        mint c_inv = inv(a[pos]);
        Moly A(a.size() - pos);
        for (int i = pos; i < a.size(); i++) {
            A[i - pos] = a[i] * c_inv;}

        A = log(A, deg - pos * b);
        A *= mint(b);
        A = exp(A, deg - pos * b);

        mint c_pow = pow(a[pos], b); 
        Moly res(deg + 1);
        for(int i = 0; i < A.size() && i + pos * b <= deg; i++) {
            res[i + pos * b] = A[i] * c_pow;}
        res.trim();
        
        return res;
    }

    // T: O(n * log(n)^2)
    static Moly inter(const vector<mint> &x, const vector<mint> &y) {
        assert(x.size() == y.size());
        if (x.empty()) {
            return Moly(vector<mint>{0});}
            
        int n = x.size();
        vector<Moly> segt(4 * n);

        auto build = [&](auto &&build, int cur, int l, int r) -> void {
            if (l == r) {
                segt[cur] = Moly(vector<mint>{-x[l], mint(1)});
                return;
            }

            int md = l + (r - l) / 2;
            build(build, 2 * cur, l, md);
            build(build, 2 * cur + 1, md + 1, r);
            segt[cur] = segt[2 * cur] * segt[2 * cur + 1];
        };
        
        build(build, 1, 0, n - 1);

        vector<mint> m_eval = eval(deriv(segt[1]), x);

        auto solve = [&](auto& self, int cur, int l, int r) -> Moly {
            if (l == r) {
                return Moly(vector<mint>{y[l] * inv(m_eval[l])});}

            int md = l + (r - l) / 2;
            Moly l_res = self(self, 2 * cur, l, md);
            Moly r_res = self(self, 2 * cur + 1, md + 1, r);
            
            return segt[2 * cur] * r_res + segt[2 * cur + 1] * l_res;
        };
        
        return solve(solve, 1, 0, n - 1);
    }

    bool operator==(const Moly &o) const { 
        return v == o.v; 
    }

    bool operator!=(const Moly &o) const { 
        return !(*this == o); 
    }

    friend ostream &operator<<(ostream &os, const Moly &a) {
        if (a.size() == 0) {
            return os << 0;}
        for (int i = 0; i < a.size(); i++) {
            os << a[i] << ' ';}
        
        return os;
    }
};

// --- Random Number Generator ---
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
lng rand_int(lng min, lng max) {
    return uniform_int_distribution<lng>(min, max)(rng);
}

// ==========================================
// NAIVE POLY IMPLEMENTATIONS (BRUTE FORCE)
// ==========================================
vector<lng> naive_poly_mul(const vector<lng>& a, const vector<lng>& b) {
    if (a.empty() || b.empty()) return {0};
    vector<lng> c(a.size() + b.size() - 1, 0);
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b.size(); ++j) {
            c[i + j] += a[i] * b[j];
        }
    }
    while (c.size() > 1 && c.back() == 0) c.pop_back();
    if (c.empty()) c.pb(0);
    return c;
}

vector<lng> naive_poly_pow(vector<lng> a, lng b, int deg) {
    vector<lng> res = {1};
    while (b > 0) {
        if (b & 1) {
            res = naive_poly_mul(res, a);
            if (res.size() > deg + 1) res.resize(deg + 1);
            while (res.size() > 1 && res.back() == 0) res.pop_back();
        }
        a = naive_poly_mul(a, a);
        if (a.size() > deg + 1) a.resize(deg + 1);
        while (a.size() > 1 && a.back() == 0) a.pop_back();
        b >>= 1;
    }
    if (res.empty()) res.pb(0);
    return res;
}

lng naive_poly_eval(const vector<lng>& a, lng x) {
    lng res = 0, cur = 1;
    for (int i = 0; i < a.size(); ++i) {
        res += a[i] * cur;
        cur *= x;
    }
    return res;
}

// ==========================================
// NAIVE MOLY IMPLEMENTATIONS (BRUTE FORCE)
// ==========================================
mint naive_moly_eval(const vector<mint>& a, mint x) {
    mint res = 0, cur = 1;
    for (int i = 0; i < a.size(); ++i) {
        res += a[i] * cur;
        cur *= x;
    }
    return res;
}

vector<mint> naive_moly_mul(const vector<mint>& a, const vector<mint>& b) {
    if (a.empty() || b.empty()) return {mint(0)};
    vector<mint> c(a.size() + b.size() - 1, mint(0));
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b.size(); ++j) {
            c[i + j] += a[i] * b[j];
        }
    }
    while (c.size() > 1 && c.back() == mint(0)) c.pop_back();
    if (c.empty()) c.pb(mint(0));
    return c;
}

vector<mint> naive_moly_inv(const vector<mint>& A, int deg) {
    vector<mint> B(deg + 1, mint(0));
    B[0] = inv(A[0]);
    for (int i = 1; i <= deg; ++i) {
        mint sum = 0;
        for (int j = 1; j <= min(i, (int)A.size() - 1); ++j) {
            sum += A[j] * B[i - j];
        }
        B[i] = -sum * B[0];
    }
    while (B.size() > 1 && B.back() == mint(0)) B.pop_back(); 
    return B;
}

pair<vector<mint>, vector<mint>> naive_moly_divmod(vector<mint> A, vector<mint> B) {
    while (A.size() > 1 && A.back() == mint(0)) A.pop_back();
    while (B.size() > 1 && B.back() == mint(0)) B.pop_back();
    if (A.size() < B.size()) return {{mint(0)}, A};
    
    int q_deg = A.size() - B.size();
    vector<mint> Q(q_deg + 1, mint(0));
    mint invB = inv(B.back());
    
    for (int i = q_deg; i >= 0; --i) {
        if (A.size() - 1 == B.size() - 1 + i) {
            Q[i] = A.back() * invB;
            for (int j = 0; j < B.size(); ++j) {
                A[j + i] -= Q[i] * B[j];
            }
            while (A.size() > 1 && A.back() == mint(0)) A.pop_back();
        }
    }
    if (A.empty()) A.push_back(mint(0));
    return {Q, A};
}

vector<mint> naive_moly_deriv(const vector<mint>& a) {
    if (a.size() <= 1) return {mint(0)};
    vector<mint> res(a.size() - 1);
    for (int i = 1; i < a.size(); i++) res[i - 1] = a[i] * mint(i);
    
    // Add trimming to match the struct!
    while (res.size() > 1 && res.back() == mint(0)) res.pop_back();
    if (res.empty()) res.push_back(mint(0));
    
    return res;
}

vector<mint> naive_moly_integ(const vector<mint>& a) {
    vector<mint> res(a.size() + 1, mint(0));
    for (int i = 0; i < a.size(); i++) res[i + 1] = a[i] * inv(mint(i + 1));
    return res;
}

vector<mint> naive_moly_log(const vector<mint>& A, int deg) {
    vector<mint> derivA = naive_moly_deriv(A);
    vector<mint> invA = naive_moly_inv(A, deg);
    vector<mint> prod = naive_moly_mul(derivA, invA);
    vector<mint> res = naive_moly_integ(prod);
    if (res.size() > deg + 1) res.resize(deg + 1);
    while (res.size() > 1 && res.back() == mint(0)) res.pop_back();
    if (res.empty()) res.push_back(mint(0));
    return res;
}

vector<mint> naive_moly_exp(const vector<mint>& A, int deg) {
    // Computes Exp in O(N^2) using the differential eq: E' = E * A'
    vector<mint> E(deg + 1, mint(0));
    E[0] = mint(1);
    for (int i = 0; i < deg; ++i) {
        mint sum = 0;
        for (int j = 0; j <= i; ++j) {
            if (i - j + 1 < A.size()) {
                sum += E[j] * A[i - j + 1] * mint(i - j + 1);
            }
        }
        E[i + 1] = sum * inv(mint(i + 1));
    }
    while (E.size() > 1 && E.back() == mint(0)) E.pop_back();
    return E;
}

vector<mint> naive_moly_pow(vector<mint> a, lng b, int deg) {
    vector<mint> res = {mint(1)};
    while (b > 0) {
        if (b & 1) {
            res = naive_moly_mul(res, a);
            if (res.size() > deg + 1) res.resize(deg + 1);
            while (res.size() > 1 && res.back() == mint(0)) res.pop_back();
        }
        a = naive_moly_mul(a, a);
        if (a.size() > deg + 1) a.resize(deg + 1);
        while (a.size() > 1 && a.back() == mint(0)) a.pop_back();
        b >>= 1;
    }
    if (res.empty()) res.pb(mint(0));
    return res;
}

vector<mint> naive_moly_inter(const vector<mint>& X, const vector<mint>& Y) {
    int n = X.size();
    if (n == 0) return {mint(0)};
    vector<mint> res = {mint(0)};
    for (int i = 0; i < n; ++i) {
        vector<mint> term = {Y[i]};
        mint denom = 1;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            term = naive_moly_mul(term, {-X[j], mint(1)});
            denom *= (X[i] - X[j]);
        }
        term = naive_moly_mul(term, {inv(denom)});
        if (term.size() > res.size()) res.resize(term.size(), mint(0));
        for(int k = 0; k < term.size(); ++k) res[k] += term[k];
    }
    while (res.size() > 1 && res.back() == mint(0)) res.pop_back();
    if (res.empty()) res.push_back(mint(0));
    return res;
}

// ==========================================
// STRESS TEST RUNNERS
// ==========================================

void stress_test_poly(int iterations) {
    cout << "--- Starting Poly Stress Test ---\n";
    for (int it = 1; it <= iterations; ++it) {
        int n = rand_int(1, 100);
        int m = rand_int(1, 100);
        
        vector<lng> A(n), B(m);
        for(int i = 0; i < n; i++) A[i] = rand_int(-100, 100);
        for(int i = 0; i < m; i++) B[i] = rand_int(-100, 100);
        
        Poly pA(A), pB(B);

        // Test Attributes
        assert(pA.deg() == (pA.v.size() - 1) && "Poly deg() Failed!");
        assert(pA.lead() == pA.v.back() && "Poly lead() Failed!");

        // Test Multiplication
        Poly pMul = pA * pB;
        vector<lng> nMul = naive_poly_mul(A, B);
        assert(pMul.v == nMul && "Poly Multiplication Failed!");

        // Test Pow
        int exp = rand_int(0, 5);
        int deg = rand_int(1, 200);
        Poly pPow = pow(pA, exp, deg);
        vector<lng> nPow = naive_poly_pow(A, exp, deg);
        assert(pPow.v == nPow && "Poly Pow Failed!");

        // Test Eval
        lng x = rand_int(-10, 10);
        lng pEval = eval(pA, x);
        lng nEval = naive_poly_eval(A, x);
        assert(pEval == nEval && "Poly Eval Failed!");
    }
    cout << "Poly: All " << iterations << " tests passed!\n\n";
}

void stress_test_moly(int iterations) {
    cout << "--- Starting Moly Stress Test ---\n";
    for (int it = 1; it <= iterations; ++it) {
        int n = rand_int(1, 100);
        int m = rand_int(1, 100);
        
        vector<mint> A(n), B(m);
        for(int i = 0; i < n; i++) A[i] = mint(rand_int(0, Moly::MOD - 1));
        for(int i = 0; i < m; i++) B[i] = mint(rand_int(0, Moly::MOD - 1));
        
        while(A[0] == mint(0)) A[0] = mint(rand_int(1, Moly::MOD - 1));
        while(B.back() == mint(0)) B.back() = mint(rand_int(1, Moly::MOD - 1));

        Moly mA(A), mB(B);

        // Test Attributes
        assert(mA.deg() == (mA.v.size() - 1) && "Moly deg() Failed!");
        assert(mA.lead() == mA.v.back() && "Moly lead() Failed!");

        // 1. Test Mul, DivMod
        Moly mMul = mA * mB;
        assert(mMul.v == naive_moly_mul(A, B) && "Moly Mul Failed!");
        
        pair<Moly, Moly> mDivMod = divMod(mA, mB);
        pair<vector<mint>, vector<mint>> nDivMod = naive_moly_divmod(A, B);
        assert(mDivMod.first.v == nDivMod.first && "Moly Div Failed!");
        assert(mDivMod.second.v == nDivMod.second && "Moly Mod Failed!");

        // 2. Test Deriv, Integ, Inv
        assert(deriv(mA).v == naive_moly_deriv(A) && "Moly Deriv Failed!");
        assert(integ(mA).v == naive_moly_integ(A) && "Moly Integ Failed!");
        
        int deg = rand_int(50, 150);
        assert(inv(mA, deg).v == naive_moly_inv(A, deg) && "Moly Inv Failed!");

        // 3. Test Log & Exp
        A[0] = mint(1); // Log requires P[0] = 1
        assert(log(Moly(A), deg).v == naive_moly_log(A, deg) && "Moly Log Failed!");

        A[0] = mint(0); // Exp requires P[0] = 0
        assert(exp(Moly(A), deg).v == naive_moly_exp(A, deg) && "Moly Exp Failed!");

        // 4. Test O(N log N) Pow (With leading zeros)
        int zeros = rand_int(0, 5);
        vector<mint> C(zeros, mint(0));
        for(int i = 0; i < 20; i++) C.pb(mint(rand_int(1, Moly::MOD - 1)));
        
        lng b = rand_int(0, 1'000'000'000); // Test massive exponent
        int pow_deg = rand_int(10, 100);
        assert(pow(Moly(C), b, pow_deg).v == naive_moly_pow(C, b, pow_deg) && "Moly Pow Failed!");

        // 5. Test Multi-point Eval & Interpolation
        int pts = rand_int(1, 50);
        vector<mint> X(pts), Y(pts);
        set<lng> used;
        for(int i = 0; i < pts; i++) {
            lng val = rand_int(0, Moly::MOD - 1);
            while(used.count(val)) val = rand_int(0, Moly::MOD - 1); // X points must be distinct
            used.insert(val);
            X[i] = mint(val);
            Y[i] = mint(rand_int(0, Moly::MOD - 1));
        }

        vector<mint> mEvals = eval(mA, X);
        vector<mint> nEvals(pts);
        for(int i = 0; i < pts; i++) nEvals[i] = naive_moly_eval(mA.v, X[i]);
        assert(mEvals == nEvals && "Moly Multi-Eval Failed!");

        assert(Moly::inter(X, Y).v == naive_moly_inter(X, Y) && "Moly Inter Failed!");
    }
    cout << "Moly: All " << iterations << " tests passed!\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Keep around 100 for fast local testing, increase to 5000+ for rigorous checks
    int test_cases = 5000; 
    
    stress_test_poly(test_cases);
    stress_test_moly(test_cases);

    return 0;
}