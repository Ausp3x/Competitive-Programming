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

// 1 Algebra

// 1.1 Fundamentals

// 1.1.1 Binary Exponentiation

// T: O(log(n)), M: O(1)
lng modPow(lng a, lng b, lng mod = INF64)  {
    if (b < 0) {
        return -1;}
    
    a = (a % mod + mod) % mod;
    lng res = 1 % mod;
    while (b > 0) {
        if (b & 1) {
            res = lll(res) * a % mod;}
        
        a = lll(a) * a % mod;
        b >>= 1;
    }

    return res;
}

// 1.1.3 Extended Euclidean Algorithm

// T: O(log(n)), M: O(1)
lng exGcd(lng a, lng b, lng &x, lng &y) {
    x = 1, y = 0;
    lng X = 0, Y = 1;
    while (b != 0) {
        lng q = a / b;
        x = exchange(X, x - q * X);
        y = exchange(Y, y - q * Y);
        a = exchange(b, a - q * b);
    }

    return a;
}

// 1.2 Prime Numbers

// 1.2.1 Sieve of Eratosthenes

// S: O(n * loglog(n)), U: NA, Q: O(1), M: O(n)
struct SieveOfErath {
    int n;
    vector<bool> is_prime;

    SieveOfErath(int N) {
        n = N;
        is_prime.assign(n + 1, true);
        
        if (n >= 0) {
            is_prime[0] = false;}
        if (n >= 1) {
            is_prime[1] = false;}
        for (lng i = 2; i * i <= n; i++) {
            if (!is_prime[i]) {
                continue;}
            
            for (lng j = i * i; j <= n; j += i) {
                is_prime[j] = false;}
        }
    }
};

// 1.2.2 Linear Sieve

// S: O(n), U: NA, Q: O(1), M: O(n)
struct LinearSieve {
    int n;
    vector<lng> prms, spf;
    vector<lng> num_div, sum_div, phi, mu;
    
    LinearSieve(int N) {
        n = N;
        spf.assign(n + 1, -1);

        for (lng i = 2; i <= n; i++) {
            if (spf[i] == -1) {
                prms.pb(i);
                spf[i] = i;
            }

            for (lng p : prms) {
                if (i * p > n) {
                    break;}
                
                spf[i * p] = p;
    
                if (i % p == 0) {
                    break;}
            }
        }
    }

    void getNumDiv() {
        num_div.assign(n + 1, 0);
        vector<lng> spf_exp(n + 1, 0);

        if (n >= 1) {
            num_div[1] = 1;}
        for (lng i = 2; i <= n; i++) {
            lng p = spf[i];
            lng j = i / p;
            
            if (j % p == 0) {
                spf_exp[i] = spf_exp[j] + 1;
                num_div[i] = num_div[j] / (spf_exp[j] + 1) * (spf_exp[i] + 1);
            } else {
                spf_exp[i] = 1;
                num_div[i] = num_div[j] * 2;
            }
        }
    }

    void getSumDiv() {
        sum_div.assign(n + 1, 0);
        vector<lng> spf_exp_sum(n + 1, 0);

        if (n >= 1) {
            sum_div[1] = 1;
            spf_exp_sum[1] = 1;
        }
        for (lng i = 2; i <= n; i++) {
            lng p = spf[i];
            lng j = i / p;
            
            if (j % p == 0) {
                spf_exp_sum[i] = spf_exp_sum[j] * p + 1;
                sum_div[i] = sum_div[j] / spf_exp_sum[j] * spf_exp_sum[i];
            } else {
                spf_exp_sum[i] = p + 1;
                sum_div[i] = sum_div[j] * (p + 1);
            }
        }
    }    

    void getPhi() {
        phi.assign(n + 1, 0);
        
        if (n >= 1) {
            phi[1] = 1;}
        for (lng i = 2; i <= n; i++) {
            lng p = spf[i];
            lng j = i / p;
            
            if (j % p == 0) {
                phi[i] = phi[j] * p;
            } else {
                phi[i] = phi[j] * (p - 1);
            }
        }
    }

    void getMu() {
        mu.assign(n + 1, 0);

        if (n >= 1) {
            mu[1] = 1;}
        for (lng i = 2; i <= n; i++) {
            lng p = spf[i];
            lng j = i / p;
            
            if (j % p == 0) {
                mu[i] = 0;
            } else {
                mu[i] = -mu[j];
            }
        }
    }

    // Q: O(log(n))
    vector<lng> getPrimeFac(lng a) {
        assert(a <= n);

        vector<lng> res;
        while (a > 1) {
            res.pb(spf[a]);
            a /= spf[a];
        }

        return res;
    }
};

// 1.2.3 Primality Tests

// T: O(log(n)), M: O(1)
bool isPrimeMR(lng n) { // Miller-Rabin
    if (n < 2) {
        return false;}

    if (n == 2 || n == 3) {
        return true;}

    if (n % 2 == 0) {
        return false;}
    
    int s = 0;
    lng d = n - 1;
    while (!(d & 1)) {
        s++;
        d >>= 1;
    }

    vector<lng> A = {2, 325, 9'375, 28'178, 450'775, 9'780'504, 1'795'265'022};
    for (lng a : A) {
        if (a % n == 0) {
            continue;}

        a %= n;
        lng b = d, x = 1;
        while (b > 0) {
            if (b & 1) {
                x = lll(x) * a % n;}

            a = lll(a) * a % n;
            b >>= 1;
        }

        if (x == 1 || x == n - 1) {
            continue;}

        bool is_composite = true;
        for (int i = 1; i < s; i++) {
            x = lll(x) * x % n;
            if (x == n - 1) {
                is_composite = false;
                break;
            }

            if (x == 1) {
                return false;}
        }

        if (is_composite) {
            return false;}
    }

    return true;
}

// 1.2.4 Integer Factorization

// T: O(n^(1/2)), M: O(log(n))
vector<lng> getPrimeFacSlow(lng n) {
    vector<lng> res;
    for (int p : {2, 3, 5}) {
        while (n % p == 0) {
            res.pb(p);
            n /= p;
        }
    }

    int j = 0;
    static const vector<int> inc = {4, 2, 4, 2, 4, 6, 2, 6};
    for (lng i = 7; i * i <= n; i += inc[j], j = (j + 1) & 7) {
        while (n % i == 0) {
            res.pb(i);
            n /= i;
        }
    }
    if (n > 1) {
        res.pb(n);}

    sort(res.begin(), res.end());
    
    return res;
}

// T: O(n^(1/4)), M: O(1)
lng getOneFacBPR(lng n, lng x0 = 2, lng c = 1) { // Brent's Pollard's Rho
    auto f = [](lng x, lng c, lng mod) -> lng {
        return (lll(x) * x + c) % mod;
    };
    
    int m = 128, l = 1;
    lng x = x0, xs = -1, y = -1, g = 1, q = 1;
    while (g == 1) {
        y = x;
        int k = 0;
        while (g == 1 && k < l) {
            xs = x;
            for (int i = 0; i < min(m, l - k); i++) {
                x = f(x, c, n);
                q = lll(q) * abs(y - x) % n;
            }

            g = gcd(q, n);
            k += m;
        }

        l *= 2;
    }

    if (g == n) {
        do {
            xs = f(xs, c, n);
            g = gcd(abs(xs - y), n);
        } while (g == 1);
    }

    return g;
}

// T: O(n^(1/4)), M: O(log(n))
Random rnd;
void getPrimeFacFast(lng n, vector<lng> &res) { 
    if (n <= 1) {
        return;}

    if (isPrimeMR(n)) {
        res.pb(n);
        return;
    } 

    static const vector<lng> prms = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    for (int p : prms) {
        if (n % p == 0) {
            res.pb(p);
            getPrimeFacFast(n / p, res);
            return;
        }
    }

    lng div = n, x0 = rnd.randLng(2, n - 1), c = rnd.randLng(1, n - 1);
    while (div == n) {
        div = getOneFacBPR(n, x0, c);
        if (div == n) {
            x0 = rnd.randLng(2, n - 1);
            c = rnd.randLng(1, n - 1);
        }
    } 

    getPrimeFacFast(div, res);
    getPrimeFacFast(n / div, res);
}

// T: O(n^(1/2)) to O(n^(1/4)), M: O(d(n))
vector<lng> getAllFac(lng n, bool opt = 0) {
    if (n <= 0) {
        return {};}

    if (n == 1) {
        return {1};}

    vector<lng> prms;
    //*
    if (!opt) {
        prms = getPrimeFacSlow(n);}//*/
    //*
    if (opt) {
        getPrimeFacFast(n, prms);}//*/
    
    sort(prms.begin(), prms.end());

    int i = 0;
    vector<lng> res = {1}; 
    while (i < prms.size()) {
        vector<lng> pows = {prms[i]};
        i++;
        while (i < prms.size() && prms[i] == pows[0]) {
            pows.pb(pows.back() * pows[0]);
            i++;
        }

        int len = res.size();
        for (int j = 0; j < len; j++) {
            for (lng p : pows) {
                res.pb(res[j] * p);}}
    }

    sort(res.begin(), res.end());

    return res;
}

// 1.3 Number-theoretic Functions

// 1.3.1 Euler's Totient Function

// T: O(n^(1/2)), M: O(1)
lng getPhi(lng n) {
    lng res = n;
    for (lng i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;}
            
            res -= res / i;
        }
    }
    if (n > 1) {
        res -= res / n;}
    
    return res;
}

// 1.3.2 Number of Divisors, Sum of Divisors

// T: O(n^(1/2)), M: O(1)
lng getNumDiv(lng n) {
    lng res = 1;
    for (lng i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int exp = 0;
            do {
                exp++;
                n /= i;
            } while (n % i == 0);
            
            res *= exp + 1;
        }
    }
    if (n > 1) {
        res *= 2;}
        
    return res;
}

// T: O(n^(1/2)), M: O(1)
lng getSumDiv(lng n) {
    lng res = 1;
    for (lng i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            lng pow = 1, sum = 1;
            do {
                pow *= i;
                sum += pow;
                n /= i;
            } while (n % i == 0);

            res *= sum;
        }
    }
    if (n > 1) {
        res *= (1 + n);}

    return res;
}

// 1.4 Modular Arithmetic

// 1.4.1 Modular Inverse

// T: O(log(n)), M: O(1)
lng getInvE(lng n, lng mod) {
    n = (n % mod + mod) % mod;
    if (n == 0) {
        return -1;}

    lng x, y;
    lng g = exGcd(n, mod, x, y);
    if (g != 1) {
        return -1;}

    return (x % mod + mod) % mod;
}

// T: O(n^(1/3)), M: O(log(n))
lng getInvP(lng n, lng mod) { // Pierce Expansion
    return n <= 1 ? n : mod - lll(mod) / n * getInvP(mod % n, mod) % mod;
}

// 1.4.3 Chinese Remainder Theorem

// T: O(n^2 * log(n)) slow, M: O(n)
iint exChiRemThm(const vector<pair<lng, lng>> &cong) {
    if (cong.empty()) {
        return 0;}

    iint a = cong[0].fi, m = cong[0].se;
    for (int i = 1; i < cong.size(); i++) {
        iint a_i = cong[i].fi, m_i = cong[i].se;
        
        iint d = a_i - a, x, y;
        iint g = exGcd(m, m_i, x, y);
        if (d % g != 0) {
            return -1;} 

        m_i /= g;
        x = (x % m_i + m_i) % m_i * ((d / g) % m_i + m_i) % m_i;

        a += x * m;
        m *= m_i;
    }

    return (a % m + m) % m;
}

// 1.4.4 Garner's Algorithm

// T: O(n^2 * log(n)) fast, M: O(n^2)
iint garner(const vector<pair<lng, lng>> &cong) {
    if (cong.empty()) {
        return 0;}

    int n = cong.size();
    vector<vector<lng>> R(n, vector<lng>(n));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            R[i][j] = getInvE(cong[i].se, cong[j].se);
            if (R[i][j] == -1) {
                return -1;}
        }
    }

    vector<lng> X(n);
    for (int i = 0; i < n; i++) {
        X[i] = (cong[i].fi % cong[i].se + cong[i].se) % cong[i].se;
        for (int j = 0; j < i; j++) {
            X[i] = (lll(R[j][i]) * (X[i] - X[j]) % cong[i].se + cong[i].se) % cong[i].se;}
    }

    iint res = 0, mul = 1;
    for (int i = 0; i < n; i++) {
        res += mul * X[i];
        mul *= cong[i].se;
    }

    return res;
}

// 1.4.6 Discrete Logarithm

// T: O(n^(1/2)), M: O(n^(1/2))
lng modLog(lng a, lng b, lng mod, lng k = 1) { // a^x ≡ b mod m
    a = (a % mod + mod) % mod; 
    b = (b % mod + mod) % mod;

    lng add = 0, g;
    while ((g = gcd(a, mod)) > 1) {
        if (b == k) {
            return add;}

        if (b % g != 0) {
            return -1;}

        b /= g; 
        mod /= g;
        k = lll(k) * a / g % mod;
        add++;
    }

    lng n = sqrt(mod) + 1, an = 1;
    for (lng i = 0; i < n; i++) {
        an = lll(an) * a % mod;}
    safe_unordered_map<lng, lng> Q;
    for (lng q = 0, rhs = b; q <= n; q++) {
        Q[rhs] = q;
        rhs = lll(rhs) * a % mod;
    }
    for (lng p = 1, lhs = k; p <= n; p++) {
        lhs = lll(lhs) * an % mod;
        if (Q.count(lhs)) {
            return n * p - Q[lhs] + add;}
    }

    return -1;
}

// 1.4.7 Primitive Root

// T: O(n^(1/2) * log(n)), M: O(log(n))
lng getPrimRoot(lng mod) {
    if (mod <= 0) {
        return -1;}

    if (mod == 1 || mod == 2 || mod == 4) {
        return mod - 1;}
    
    if (mod % 4 == 0) { 
        return -1;}

    lng m = mod;
    if (m % 2 == 0) {
        m /= 2;}
    for (lng i = 3; i * i <= m; i += 2) {
        if (m % i == 0) {
            while (m % i == 0) {
                m /= i;}

            if (m > 1) {
                return -1;} 
            
            break;
        }
    }

    lng phi = getPhi(mod);
    vector<lng> prms = getPrimeFacSlow(phi);
    prms.erase(unique(prms.begin(), prms.end()), prms.end());
    
    for (lng res = 2; res < mod; res++) {
        if (gcd(res, mod) != 1) {
            continue;}
            
        bool chk = true;
        for (int i = 0; i < prms.size() && chk; i++) {
            if (modPow(res, phi / prms[i], mod) == 1) {
                chk = false;}}
        
        if (chk) {
            return res;}
    }

    return -1;
}

// 1.4.8 Discrete Root

// T: O(n^(1/2)), M: O(n^(1/2))
vector<lng> modRoot(lng a, lng b, lng mod) { // x^a ≡ b mod m
    if (b == 0) {
        return {0};}
    
    lng g = getPrimRoot(mod);
    if (g == -1) {
        return {};}
        
    lng k = modLog(g, b, mod);
    if (k == -1) {
        return {};} 

    lng phi = getPhi(mod), x, y;
    lng d = exGcd(a, phi, y, x);
    if (k % d != 0) {
        return {};}
    
    y = (lll(y) % phi + phi) % phi * (k / d) % phi;
    vector<lng> res;
    for (lng i = 0; i < d; i++) {
        res.pb(modPow(g, y + i * (phi / d), mod));}
    
    sort(res.begin(), res.end());
    res.erase(unique(res.begin(), res.end()), res.end());
    
    return res;
}

// 1.4.9 Montgomery Multiplication

// S: O(1), U: NA, Q: O(1), M: O(1)
struct Montgomery {
    using ulng = unsigned long long;
    using ulll = unsigned __int128;

    ulng mod, inv, r_sq;

    Montgomery(ulng n = 1): mod(n), inv(n) {
        for (int i = 0; i < 5; i++) {
            inv *= 2 - mod * inv;}
        inv = -inv; 
        
        r_sq = -ulll(mod) % mod;
    }

    ulng red(ulll x) const {
        ulng q = ulng(x) * inv;
        ulng res = (x + ulll(q) * mod) >> 64; 
        if (res >= mod) {
            res -= mod;}
            
        return res;
    }

    ulng init(ulng x) const {
        return red(ulll(x) * r_sq);
    }

    ulng mul(ulng a, ulng b) const {
        return red(ulll(a) * b);
    }
    
    // Q: O(log(n))
    ulng pow(ulng a, ulng b) const {
        a = init(a);
        ulng res = init(1);
        while (b > 0) {
            if (b & 1) {
                res = mul(res, a);}
            
            a = mul(a, a);
            b >>= 1;
        }
        
        return red(res);
    }
};

// 1.4.10 Modulo Integer

// T: O(1), M: O(1)
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

    // T: O(log(n))
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

    // T: O(log(n))
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

// 1.5 Miscellaneous

// 1.5.3 Arbitrary-Precision Arithmetic

// T: O(n), M: O(n)
struct InfInt {
    using ulng = unsigned long long;
    static constexpr int BASE = 1'000'000'000;
    static constexpr int BASE_DIGS = 9;
    static constexpr int BIT_BASE = 1 << 30;
    
    int sgn;
    bool is_inf = false;
    vector<int> n;

    InfInt(): sgn(1) {}
    
    InfInt(lng N) { 
        *this = N; 
    }
    
    InfInt(const string &N) {
        read(N); 
    }

    InfInt(const vector<int> &a, int b, int s = 1) {
        *this = 0;
        for (int i = int(a.size()) - 1; i >= 0; i--) {
            *this *= b;
            *this += a[i];
        }
        sgn = s;

        trim();
    }

    bool isNil() const { 
        return !is_inf && (n.empty() || (n.size() == 1 && n[0] == 0)); 
    }

    void read(const string &s) {
        sgn = 1; 
        is_inf = false; 
        n.clear();
        
        int pos = 0;
        while (pos < s.size() && (s[pos] == '+' || s[pos] == '-')) {
            if (s[pos] == '-') { 
                sgn *= -1;}
            
            pos++;
        }

        assert(pos < s.size() && "InfInt read error: String contains no numbers.");

        if (s.size() - pos == 3 && (s.compare(pos, 3, "INF") == 0 || s.compare(pos, 3, "inf") == 0)) {
            is_inf = true; 
            return;
        }

        for (int i = pos; i < s.size(); i++) {
            assert('0' <= s[i] && s[i] <= '9' && "InfInt read error: Invalid character found.");}
        
        int len = (s.size() - pos + BASE_DIGS - 1) / BASE_DIGS;
        n.reserve(len);
        for (int i = s.size() - 1; i >= pos; i -= BASE_DIGS) {
            int x = 0;
            for (int j = max(pos, i - BASE_DIGS + 1); j <= i; j++) {
                x = x * 10 + (s[j] - '0');}

            n.pb(x);
        }
        
        trim();
    }

    void trim() {
        if (is_inf) { 
            n.clear(); 
            return; 
        } 

        while (n.size() > 1 && n.back() == 0) { 
            n.pop_back();}
        
        if (n.empty() || (n.size() == 1 && n[0] == 0)) { 
            sgn = 1;}
    }
    
    InfInt &operator=(lng N) {
        sgn = N < 0 ? -1 : 1;
        is_inf = false;
        ulng uN = N < 0 ? -ulng(N) : N;
        
        n.clear();
        do { 
            n.pb(uN % BASE); 
            uN /= BASE; 
        } while (uN > 0);
        
        return *this;
    }

    InfInt &operator=(string const &N) {
        read(N);

        return *this;
    }

    InfInt &operator++() { 
        return *this += 1; 
    }
    
    InfInt &operator--() { 
        return *this -= 1; 
    }

    InfInt operator++(int) { 
        InfInt res = *this; 
        *this += 1; 
        
        return res; 
    }

    InfInt operator--(int) { 
        InfInt res = *this; 
        *this -= 1; 
        
        return res; 
    }

    InfInt &operator+=(const InfInt &o) {
        if (is_inf || o.is_inf) {
            if (is_inf && o.is_inf && sgn != o.sgn) {
                return *this = 0;}

            if (o.is_inf) { 
                sgn = o.sgn;
                is_inf = true;
            }
            n.clear(); 
            
            return *this;
        }

        if (sgn != o.sgn) { 
            return *this -= -o;}
        
        for (int i = 0, carry = 0; i < o.n.size() || carry; i++) {
            if (i == n.size()) { 
                n.pb(0);}
            
            n[i] += carry + (i < o.n.size() ? o.n[i] : 0);
            carry = n[i] >= BASE;
            if (carry) { 
                n[i] -= BASE;}
        }
        
        return *this;
    }

    InfInt &operator-=(const InfInt &o) {
        if (is_inf || o.is_inf) {
            if (is_inf && o.is_inf && sgn == o.sgn) {
                return *this = 0;}

            if (o.is_inf) { 
                sgn = -o.sgn;
                is_inf = true;
            }
            n.clear(); 
            
            return *this;
        }

        if (sgn != o.sgn) { 
            return *this += -o;}
        
        if (magLess(*this, o)) {
            InfInt res = o; 
            res -= *this; 
            *this = res; 
            sgn = -sgn; 
            return *this;
        }

        for (int i = 0, carry = 0; i < o.n.size() || carry; i++) {
            n[i] -= carry + (i < o.n.size() ? o.n[i] : 0);
            carry = n[i] < 0;
            if (carry) { 
                n[i] += BASE;}
        }

        trim(); 
        
        return *this;
    }

    InfInt &operator*=(lng o) {
        if (isNil() || o == 0) {
            return *this = 0;}

        if (is_inf) { 
            sgn *= o < 0 ? -1 : 1;
            n.clear(); 
            return *this;
        }
        
        sgn = o < 0 ? -1 : 1;
        ulng uo = o < 0 ? -ulng(o) : o;

        lll carry = 0;
        for (int i = 0; i < n.size() || carry; i++) {
            if (i == n.size()) { 
                n.pb(0);}
            
            lll cur = lll(n[i]) * uo + carry;
            n[i] = int(cur % BASE);
            carry = cur / BASE;
        }

        trim(); 
        
        return *this;
    }

    // T: O(n^1.58)
    static void karatsuba(int len, const lng *a, const lng *b, lll *res, lng *tmp_a, lng *tmp_b, lll *tmp_res) {
        if (len <= 64) {
            fill(res, res + 2 * len, 0);
            for (int i = 0; i < len; i++) {
                for (int j = 0; j < len; j++) {
                    res[i + j] += lll(a[i]) * b[j];}}

            return;
        }

        int k = len / 2;

        karatsuba(k, a, b, res, tmp_a, tmp_b, tmp_res);
        karatsuba(k, a + k, b + k, res + 2 * k, tmp_a, tmp_b, tmp_res);

        for (int i = 0; i < k; i++) {
            tmp_a[i] = a[i] + a[i + k];
            tmp_b[i] = b[i] + b[i + k];
        }

        karatsuba(k, tmp_a, tmp_b, tmp_res, tmp_a + k, tmp_b + k, tmp_res + 2 * k);

        for (int i = 0; i < 2 * k; i++) {
            tmp_res[i] -= res[i] + res[i + 2 * k];}
        for (int i = 0; i < 2 * k; i++) {
            res[i + k] += tmp_res[i];}
    }

    // T: O(n^1.58)
    InfInt &operator*=(const InfInt &o) {
        if (isNil() || o.isNil()) { 
            return *this = 0;}
        
        if (is_inf || o.is_inf) { 
            sgn *= o.sgn; 
            is_inf = true;
            n.clear(); 
            return *this; 
        }
        
        int len = 1;
        while (len < max(n.size(), o.n.size())) {
            len <<= 1;}

        vector<lng> a(n.begin(), n.end());
        a.resize(len); 
        vector<lng> b(o.n.begin(), o.n.end());
        b.resize(len);
        vector<lll> res(2 * len);
        vector<lng> tmp_a(len);
        vector<lng> tmp_b(len);
        vector<lll> tmp_res(2 * len);

        karatsuba(len, a.data(), b.data(), res.data(), tmp_a.data(), tmp_b.data(), tmp_res.data());
        
        len = n.size() + o.n.size();
        sgn *= o.sgn;
        n.clear();

        lll carry = 0;
        for (int i = 0; i < len || carry; i++) {
            lll cur = (i < res.size() ? res[i] : 0) + carry;
            n.pb(int(cur % BASE));
            carry = cur / BASE;
        } 
        
        trim(); 
        
        return *this;
    }
    
    InfInt &operator/=(lng o) {
        assert(o != 0 && "InfInt lng division error: Division by zero.");

        if (is_inf) { 
            sgn *= o < 0 ? -1 : 1;
            n.clear(); 
            return *this; 
        }

        sgn *= o < 0 ? -1 : 1;
        ulng uo = o < 0 ? -ulng(o) : o;
        
        lll rem = 0;
        for (int i = int(n.size()) - 1; i >= 0; i--) {
            lll cur = n[i] + rem * BASE;
            n[i] = int(cur / uo);
            rem = cur % uo;
        }

        trim(); 
        
        return *this;
    }

    lng operator%=(lng o) {
        assert(o != 0 && "InfInt lng modulo error: Modulo by zero.");

        if (is_inf) {
            return 0;}
        
        sgn = o < 0 ? -1 : 1;
        ulng uo = o < 0 ? -ulng(o) : o;

        lll rem = 0;
        for (int i = int(n.size()) - 1; i >= 0; i--) {
            rem = (n[i] + rem * BASE) % uo;}
        
        return sgn * lng(rem);
    }

    // T: O(n^2)
    friend pair<InfInt, InfInt> divMod(const InfInt &a0, const InfInt &b0) {
        assert(!b0.isNil() && "InfInt divMod error: Division/modulo by zero.");

        int norm = BASE / (b0.n.back() + 1);
        InfInt a = abs(a0) * norm, b = abs(b0) * norm, q, r;
        q.n.resize(a.n.size());
        for (int i = int(a.n.size()) - 1; i >= 0; i--) {
            if (!r.isNil()) {
                r.n.insert(r.n.begin(), a.n[i]);
            } else {
                r = a.n[i];
            }

            int s1 = b.n.size()     < r.n.size() ? r.n[b.n.size()]     : 0;
            int s2 = b.n.size() - 1 < r.n.size() ? r.n[b.n.size() - 1] : 0;

            lng d = (lng(s1) * BASE + s2) / b.n.back();
            if (d >= BASE) {
                d = BASE - 1;}
            
            r -= b * d;
            while (r < 0) { 
                r += b; 
                d--;
            }
            q.n[i] = d;
        }

        q.sgn = a0.sgn * b0.sgn; 
        r.sgn = a0.sgn;
        r /= norm;
        q.trim(); 
        r.trim();

        return {q, r};
    }
    
    // T: O(n^2)
    InfInt &operator/=(const InfInt &o) { 
        if (is_inf || o.is_inf) {
            if (is_inf && o.is_inf) {
                return *this = sgn * o.sgn;}

            if (o.is_inf) { 
                return *this = 0;}
            
            sgn *= o < 0 ? -1 : 1;
            n.clear(); 
            
            return *this;
        }

        return *this = divMod(*this, o).fi; 
    }
    
    // T: O(n^2)
    InfInt &operator%=(const InfInt &o) { 
        if (is_inf) {
            return *this = 0;}

        if (o.is_inf) {
            return *this;}

        return *this = divMod(*this, o).se; 
    }
    
    InfInt operator+() const { 
        return *this; 
    }
    
    InfInt operator-() const { 
        InfInt res = *this; 
        res.sgn = -res.sgn; 
        
        return res; 
    }

    friend InfInt operator+(InfInt a, const InfInt &b) { 
        return a += b; 
    }

    friend InfInt operator-(InfInt a, const InfInt &b) { 
        return a -= b; 
    }

    friend InfInt operator*(InfInt a, lng b) {
        return a *= b;
    }

    friend InfInt operator*(lng b, InfInt a) {
        return a *= b;
    }
    
    // T: O(n^1.58)
    friend InfInt operator*(InfInt a, const InfInt &b) { 
        return a *= b; 
    }

    friend InfInt operator/(InfInt a, lng b) { 
        return a /= b; 
    }
    
    // T: O(n^2)
    friend InfInt operator/(InfInt a, const InfInt &b) { 
        return a /= b; 
    }

    friend lng operator%(InfInt a, lng b) { 
        return a %= b; 
    }

    // T: O(n^2)
    friend InfInt operator%(InfInt a, const InfInt &b) { 
        return a %= b; 
    }

    friend InfInt abs(InfInt a) { 
        a.sgn = 1;

        return a; 
    }

    // T: O(n^2)
    friend InfInt exGcd(InfInt a, InfInt b, InfInt &x, InfInt &y) {
        if (a.is_inf) {
            x = 0;
            y = 1;
            return b;
        }
        
        if (b.is_inf) {
            x = 1;
            y = 0;
            return a;
        }
    
        x = 1, y = 0;
        InfInt X = 0, Y = 1;
        while (b != 0) {
            auto [q, r] = divMod(a, b);
            a = exchange(b, r);
            x = exchange(X, x - q * X);
            y = exchange(Y, y - q * Y);
        }

        return a;
    }

    // T: O(n^2)
    friend InfInt inv(InfInt a, InfInt mod) {
        a %= mod; 
        a += mod; 
        a %= mod;
        if (a == 0) {
            return -1;}
        
        InfInt x, y;
        InfInt g = exGcd(a, mod, x, y);
        if (g != 1) {
            return -1;}
        
        x %= mod;
        x += mod; 
        x %= mod;

        return x;
    }

    // T: O(n^1.58 * log(n)), M: O(n^2)
    friend InfInt pow(InfInt a, lng b) {
        assert(b >= 0 && "InfInt pow error: Exponent must be >= 0.");
        
        if (a.is_inf) {
            if (b == 0) {
                return 1;}

            if (b % 2 == 0) {
                a.sgn = 1;}

            return a;
        }

        InfInt res = 1;
        while (b > 0) {
            if (b & 1) {
                res *= a;}
            
            a *= a;
            b >>= 1;
        }

        return res;
    }
    
    // T: O(n^2)
    friend InfInt sqrt(const InfInt &a0) {
        assert(a0.sgn == 1 && "InfInt sqrt error: Cannot compute square root of negative number.");

        if (a0.isNil()) {
            return 0;}

        if (a0.is_inf) {
            return a0;}

        InfInt a = a0;
        while (a.n.empty() || a.n.size() % 2 != 0) {
            a.n.pb(0);}

        int sz = a.n.size();
        lng x = lng(a.n[sz - 1]) * BASE + a.n[sz - 2];
        lng d0 = std::sqrt(x);
        while (d0 * d0 > x) {
            d0--;}
        while ((d0 + 1) * (d0 + 1) <= x) {
            d0++;}
        int norm = BASE / (d0 + 1);
        
        a *= norm; 
        a *= norm;
        while (a.n.empty() || a.n.size() % 2 != 0) { 
            a.n.pb(0);}

        sz = a.n.size();
        x = lng(a.n[sz - 1]) * BASE + a.n[sz - 2];
        d0 = std::sqrt(x);
        while (d0 * d0 > x) {
            d0--;}
        while ((d0 + 1) * (d0 + 1) <= x) {
            d0++;}

        InfInt res, b = lng(a.n[sz - 1]) * BASE + a.n[sz - 2];
        int q = d0;
        for (int i = sz / 2 - 1; i >= 0; i--) {
            InfInt b1;
            for (; ; q--) {
                b1 = b - (res * (2ll * BASE) + q) * q;
                if (b1 >= 0) {
                    break;}
            }

            InfInt db = res * (2ll * BASE) + (2 * q + 1);
            while (b1 >= db) {
                b1 -= db;
                q++;
                db += 2;
            }

            b = b1;
            if (i > 0) {
                b *= lng(BASE) * BASE;
                b += lng(a.n[2 * i - 1]) * BASE + a.n[2 * i - 2];
            }

            if (!res.isNil()) {
                res.n.insert(res.n.begin(), q);
            } else {
                res = q;
            }
            if (i > 0) {
                int d1 = res.n.size() + 2 < b.n.size() ? b.n[res.n.size() + 2] : 0;
                int d2 = res.n.size() + 1 < b.n.size() ? b.n[res.n.size() + 1] : 0;
                int d3 = res.n.size()     < b.n.size() ? b.n[res.n.size()]     : 0;
                q = (lll(d1) * BASE * BASE + lll(d2) * BASE + d3) / (2ll * d0);
                if (q >= BASE) {
                    q = BASE - 1;}
            }
        }
        
        res.trim(); 
        res /= norm;

        return res;
    }

    explicit operator bool() const { 
        return !isNil(); 
    }

    bool operator!() const {
        return isNil();
    }

    bool operator==(const InfInt &o) const { 
        if (is_inf || o.is_inf) {
            return sgn == o.sgn && is_inf == o.is_inf;}
        
        return sgn == o.sgn && n == o.n; 
    }

    bool operator!=(const InfInt &o) const { 
        return !(*this == o);
    }

    friend bool magLess(const InfInt &a, const InfInt &b) {
        if (a.is_inf || b.is_inf) {
            return !a.is_inf;}

        if (a.n.size() != b.n.size()) { 
            return a.n.size() < b.n.size();}

        for (int i = int(a.n.size()) - 1; i >= 0; i--) {
            if (a.n[i] != b.n[i]) { 
                return a.n[i] < b.n[i];}}
        
        return false;
    }

    bool operator<(const InfInt &o) const {
        if (is_inf && o.is_inf) {
            return sgn < o.sgn;}

        if (is_inf) {
            return sgn < 0;}

        if (o.is_inf) {
            return o.sgn > 0;}              
        
        if (sgn != o.sgn) { 
            return sgn < o.sgn;}

        return sgn == 1 ? magLess(*this, o) : magLess(o, *this);
    }

    bool operator>(const InfInt &o) const { 
        return o < *this;
    }

    bool operator<=(const InfInt &o) const { 
        return !(o < *this); 
    }

    bool operator>=(const InfInt &o) const { 
        return !(*this < o); 
    }

    InfInt operator~() const { 
        return -(*this) - 1; 
    }

    InfInt operator<<(int shf) const {
        if (is_inf || isNil() || shf == 0) {
            return *this;}
        
        return *this * pow(InfInt(2), shf); 
    }
    
    InfInt operator>>(int shf) const {
        if (is_inf || isNil() || shf == 0) {
            return *this;}
            
        if (shf >= n.size() * 30 + 30) {
            return sgn == -1 ? -1 : 0;}

        auto [q, r] = divMod(*this, pow(InfInt(2), shf));
        
        return q - (sgn == -1 && !r.isNil());
    }

    static vector<int> convBase(InfInt a, int b) {
        assert(!a.is_inf && "InfInt convBase error: Base conversion on infinity.");
        assert(b >= 2 && "InfInt convBase error: Base must be >= 2.");

        vector<int> res; 
        a = abs(a);
        while (!a.isNil()) { 
            res.pb(a % b); 
            a /= b; 
        }
        if (res.empty()) {
            res.pb(0);}
        
        return res;
    }

    static vector<int> convTwosComp(const InfInt &a) {
        vector<int> res = convBase(a, BIT_BASE);
        if (a.sgn == 1) {
            return res;}
        
        int carry = 1;
        for (int i = 0; i < res.size(); i++) {
            lng cur = (BIT_BASE - 1 - res[i]) + carry;
            res[i] = int(cur & (BIT_BASE - 1));
            carry = cur >> 30;
        }
        if (carry) {
            res.pb(carry);}
            
        return res;
    }

    static InfInt fromTwosComp(vector<int> &blks, int ext) {
        int sgn = 1;
        if (ext != 0) { 
            sgn = -1;
            int carry = 1;
            for (int i = 0; i < blks.size(); i++) {
                lng cur = (BIT_BASE - 1 - blks[i]) + carry;
                blks[i] = int(cur & (BIT_BASE - 1));
                carry = cur >> 30;
            }
        }

        return InfInt(blks, BIT_BASE, sgn);
    }

    InfInt operator&(const InfInt &o) const {
        assert(!is_inf && !o.is_inf && "InfInt bitwise AND error: Bitwise AND on infinity.");
        
        auto a = convTwosComp(*this), b = convTwosComp(o);
        int a_ext = sgn == -1   ? BIT_BASE - 1 : 0;
        int b_ext = o.sgn == -1 ? BIT_BASE - 1 : 0;
        vector<int> res(max(a.size(), b.size()), 0);
        for (int i = 0; i < res.size(); i++) {
            res[i] = (i < a.size() ? a[i] : a_ext) & (i < b.size() ? b[i] : b_ext);}
            
        return fromTwosComp(res, a_ext & b_ext);
    }

    InfInt operator|(const InfInt &o) const {
        assert(!is_inf && !o.is_inf && "InfInt bitwise OR error: Bitwise OR on infinity.");
        
        auto a = convTwosComp(*this), b = convTwosComp(o);
        int a_ext = sgn == -1   ? BIT_BASE - 1 : 0;
        int b_ext = o.sgn == -1 ? BIT_BASE - 1 : 0;
        vector<int> res(max(a.size(), b.size()), 0);
        for (int i = 0; i < res.size(); i++) {
            res[i] = (i < a.size() ? a[i] : a_ext) | (i < b.size() ? b[i] : b_ext);}
            
        return fromTwosComp(res, a_ext | b_ext);
    }

    InfInt operator^(const InfInt &o) const {
        assert(!is_inf && !o.is_inf && "InfInt bitwise XOR error: Bitwise XOR on infinity.");

        auto a = convTwosComp(*this), b = convTwosComp(o);
        int a_ext = sgn == -1   ? BIT_BASE - 1 : 0;
        int b_ext = o.sgn == -1 ? BIT_BASE - 1 : 0;
        vector<int> res(max(a.size(), b.size()), 0);
        for (int i = 0; i < res.size(); i++) {
            res[i] = (i < a.size() ? a[i] : a_ext) ^ (i < b.size() ? b[i] : b_ext);}

        return fromTwosComp(res, a_ext ^ b_ext);
    }

    InfInt &operator<<=(int shf) { 
        return *this = *this << shf; 
    }
    
    InfInt &operator>>=(int shf) { 
        return *this = *this >> shf; 
    }

    InfInt &operator&=(const InfInt &o) { 
        return *this = *this & o; 
    }
    
    InfInt &operator|=(const InfInt &o) { 
        return *this = *this | o; 
    }
    
    InfInt &operator^=(const InfInt &o) { 
        return *this = *this ^ o; 
    }

    friend string bin(const InfInt &a) {
        assert(!a.is_inf && "InfInt bin error: Binary conversion on infinity.");
        
        if (a.isNil()) {
            return "0";}
        
        vector<int> blks = convBase(a, BIT_BASE);
        string res = "";
        for (int i = 0; i < blks.size(); i++) {
            int cur = blks[i];
            for (int j = 0; j < 30; j++) {
                if (i == blks.size() - 1 && cur == 0) {
                    break;}

                res += '0' + (cur & 1);
                cur >>= 1;
            }
        }
        if (a.sgn == -1) {
            res += '-';}
        
        reverse(res.begin(), res.end());
        
        return res;
    }
    
    friend int ctz(const InfInt &a) {
        assert(!a.is_inf && "InfInt ctz error: Ctz on infinity.");
        
        if (a.isNil()) {
            return 0;}
        
        int cnt = 0;
        for (int x : convBase(a, BIT_BASE)) {
            if (x == 0) { 
                cnt += 30;
            } else { 
                cnt += __builtin_ctz(x); 
                break;
            }
        }

        return cnt;
    }

    friend int popcount(const InfInt &a) {
        assert(!a.is_inf && "InfInt popcount error: Popcount on infinity.");

        int cnt = 0;
        for (int x : convBase(a, BIT_BASE)) { 
            cnt += __builtin_popcount(x);}

        return cnt;
    }

    friend istream &operator>>(istream &is, InfInt &a) {
        string s; 
        is >> s; 
        a.read(s); 
        
        return is;
    }

    friend ostream &operator<<(ostream &os, const InfInt &a) {
        if (a.sgn == -1) {
            os << '-';}

        if (a.is_inf) { 
            return os << "inf";}

        os << (a.n.empty() ? 0 : a.n.back());

        char buf[BASE_DIGS + 1];
        buf[BASE_DIGS] = '\0';
        for (int i = int(a.n.size()) - 2; i >= 0; i--) {
            int x = a.n[i];
            for (int j = BASE_DIGS - 1; j >= 0; j--) {
                buf[j] = '0' + (x % 10); 
                x /= 10;
            }

            os << buf;
        }

        return os;
    }
};
using iint = InfInt;

// 1.5.4 Fast Fourier Transform

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

// 1.5.6 Continued Fractions

// 2 Data Structures

// 2.1 Fundamentals

// 2.1.2 Sparse Table

// S: O(n * log(n)), U: NA, Q: O(1), M: O(n * log(n))
template<typename T, typename F>
struct SparseTable {
    int h, n;
    vector<vector<T>> v;
    F f;

    SparseTable(const vector<T> &a, const F &fnc): n(a.size()), f(fnc) {
        if (n == 0) {
            h = 0;
            return;
        }
        
        h = __lg(n) + 1;
        v.assign(h, vector<T>(n));

        for (int i = 0; i < n; i++) {
            v[0][i] = a[i];}
        for (int i = 1; i < h; i++) {
            for (int j = 0; j + (1 << i) <= n; j++) {
                v[i][j] = f(v[i - 1][j], v[i - 1][j + (1 << (i - 1))]);}}
    }

    T queryFast(int l, int r) const {
        assert(0 <= l && l <= r && r < n);

        int i = __lg(r - l + 1);

        return f(v[i][l], v[i][r - (1 << i) + 1]);
    }

    // Q: O(log(n))
    T querySlow(int l, int r) const {
        assert(0 <= l && l <= r && r < n);
        
        int len = r - l + 1;
        T res;
        for (int i = __lg(len), non = true; i >= 0; i--) {
            if ((len >> i) & 1) {
                if (non) {
                    res = v[i][l];
                    non = false;
                } else {
                    res = f(res, v[i][l]);
                }
                
                l += 1 << i;
            }
        }

        return res;
    }
};

// 2.2 Trees

// 2.2.1 Disjoint Set Union

// S: O(n), U: O(a(n)), Q: O(a(n)), M: O(n)
struct DSU {
    int n, ncon;
    vector<int> par, siz, esz;
    vector<lng> dis;
    vector<bool> is_bip;

    DSU(int N): n(N), ncon(N) {
        par.resize(n);
        iota(par.begin(), par.end(), 0);
        siz.assign(n, 1);
        esz.assign(n, 0);
        dis.assign(n, 0);
        is_bip.assign(n, true);
    }

    bool uniteSets(int u, int v, lng w = 1) {
        int ru = findSet(u);
        int rv = findSet(v);

        if (ru == rv) {
            esz[ru]++;
            if ((dis[u] - dis[v] - w) % 2 != 0) {
                is_bip[ru] = false;}
            return false;
        }

        if (siz[ru] < siz[rv]) {
            swap(ru, rv);
            swap(u, v);
            w = -w;
        }

        ncon--;
        par[rv] = ru;
        siz[ru] += siz[rv];
        esz[ru] += esz[rv] + 1;
        dis[rv] = dis[u] - dis[v] - w;
        is_bip[ru] = is_bip[ru] && is_bip[rv];

        return true;
    }

    int findSet(int u) {
        if (u != par[u]) {
            int p = par[u];
            par[u] = findSet(p);
            dis[u] += dis[p];
        }

        return par[u];
    }

    int getDis(int u) {
        findSet(u);

        return dis[u];
    }
    
    int getEsiz(int u) {
        return esz[findSet(u)];
    }

    int getSize(int u) {
        return siz[findSet(u)];
    }

    bool isBipartite(int u) {
        return is_bip[findSet(u)];
    }

    bool isSameSet(int u, int v) {
        return findSet(u) == findSet(v);
    }
};

// 2.2.2 Fenwick Tree

// S: O(n), U: O(log(n)), Q: O(log(n)), M: O(n)
template<typename T>
struct FenTreeRangeAdd1D {
    int n;
    vector<T> v1, v2;

    FenTreeRangeAdd1D(int N): n(N), v1(N, T(0)), v2(N, T(0)) {}

    FenTreeRangeAdd1D(const vector<T> &a): n(a.size()), v1(a), v2(a.size(), T(0)) {
        for (int i = 0; i < n; i++) {
            int j = i | (i + 1);
            if (j < n) {
                v1[j] += v1[i];}
        }
    }

    void _add(int i_cur, T x1, T x2) {
        for (int i = i_cur; i < n; i |= i + 1) {
            v1[i] += x1;
            v2[i] += x2;
        }
    }

    void addUpdate(int l, int r, T x) {
        if (l > r) {
            return;}
        
        _rangeAdd(l,     -x * T(l - 1), x);
        _rangeAdd(r + 1, x * T(r),      -x);
    }

    T _sum(int i_cur) const {
        if (i_cur < 0) {
            return T(0);}

        T r1 = T(0), r2 = T(0);
        for (int i = i_cur; i >= 0; i = (i & (i + 1)) - 1) {
            r1 += v1[i];
            r2 += v2[i];
        }

        return r2 * i_cur + r1;
    }

    T sumQuery(int l, int r) const {
        if (l > r) {
            return T(0);}
        
        return _sum(r) - _sum(l - 1);
    }
};

// S: O(n^d), U: O(log(n)^d), Q: O(log(n)^d), M: O(n^d)
template<typename T, typename F = std::plus<T>, typename F_inv = std::minus<T>>
struct FenTree {
    int d, x, y, z;
    vector<T> v;
    T id;
    F f;
    F_inv f_inv;

    FenTree(int X,               T ID = T(0), F f_ = F(), F_inv f_inv_ = F_inv()): 
        d(1), x(X), y(0), z(0), v(X, ID),         id(ID), f(f_), f_inv(f_inv_) {}

    FenTree(int X, int Y,        T ID = T(0), F f_ = F(), F_inv f_inv_ = F_inv()): 
        d(2), x(X), y(Y), z(0), v(X * Y, ID),     id(ID), f(f_), f_inv(f_inv_) {}

    FenTree(int X, int Y, int Z, T ID = T(0), F f_ = F(), F_inv f_inv_ = F_inv()): 
        d(3), x(X), y(Y), z(Z), v(X * Y * Z, ID), id(ID), f(f_), f_inv(f_inv_) {}

    FenTree(const vector<T> &a, T ID = T(0), F f_ = F(), F_inv f_inv_ = F_inv()): 
        FenTree(a.size(), ID, f_, f_inv_) {
        for (int i = 0; i < x; i++) {
            v[i] = a[i];}
        
        for (int i = 0; i < x; i++) {
            int p = i | (i + 1);
            if (p < x) {
                v[p] = f(v[p], v[i]);}
        }
    }

    FenTree(const vector<vector<T>> &a, T ID = T(0), F f_ = F(), F_inv f_inv_ = F_inv()): 
        FenTree(a.size(), a.empty() ? 0 : a[0].size(), ID, f_, f_inv_) {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                v[getIdx(i, j)] = a[i][j];}}

        for (int i = 0; i < x; i++) {
            int p = i | (i + 1);
            if (p < x) {
                for (int j = 0; j < y; j++) {
                    v[getIdx(p, j)] = f(v[getIdx(p, j)], v[getIdx(i, j)]);}}
        }
        
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                int p = j | (j + 1);
                if (p < y) {
                    v[getIdx(i, p)] = f(v[getIdx(i, p)], v[getIdx(i, j)]);}
            }
        }
    }

    FenTree(const vector<vector<vector<T>>> &a, T ID = T(0), F f_ = F(), F_inv f_inv_ = F_inv()): 
        FenTree(a.size(), a.empty() ? 0 : a[0].size(), (a.empty() || a[0].empty()) ? 0 : a[0][0].size(), ID, f_, f_inv_) {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                for (int k = 0; k < z; k++) {
                    v[getIdx(i, j, k)] = a[i][j][k];}}}
        
        for (int i = 0; i < x; i++) {
            int p = i | (i + 1);
            if (p < x) {
                for (int j = 0; j < y; j++) {
                    for (int k = 0; k < z; k++) {
                        v[getIdx(p, j, k)] = f(v[getIdx(p, j, k)], v[getIdx(i, j, k)]);}}}
        }
        
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                int p = j | (j + 1);
                if (p < y) {
                    for (int k = 0; k < z; k++) {
                        v[getIdx(i, p, k)] = f(v[getIdx(i, p, k)], v[getIdx(i, j, k)]);}}
            }
        }
        
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                for (int k = 0; k < z; k++) {
                    int p = k | (k + 1);
                    if (p < z) {
                        v[getIdx(i, j, p)] = f(v[getIdx(i, j, p)], v[getIdx(i, j, k)]);}
                }
            }
        }
    }

    // 1D
    void update(int i_cur, T a) {
        assert(d == 1);

        for (int i = i_cur; i < x; i |= i + 1) {
            v[i] = f(v[i], a);}
    }

    T _query(int i_cur) const {
        assert(d == 1);
        
        T res = id;
        for (int i = i_cur; i >= 0; i = (i & (i + 1)) - 1) {
            res = f(res, v[i]);}
        
        return res;
    }

    T query(int l, int r) const {
        assert(d == 1);

        if (l > r) {
            return id;}
        
        return f_inv(_query(r), (l > 0 ? _query(l - 1) : id));
    }

    int lowerBound(T a) const {
        assert(d == 1);

        if (a <= id || x == 0) {
            return 0;}

        int cur = 0;
        for (int i = __lg(max(1, x)); i >= 0; i--) {
            int nxt = cur + (1 << i);
            if (nxt <= x && v[nxt - 1] < a) {
                a = f_inv(a, v[nxt - 1]);
                cur = nxt;
            }
        }

        return cur;
    }

    // 2D
    inline int getIdx(int i, int j) const {
        return i * y + j;
    }

    void update(int i_cur, int j_cur, T a) {
        assert(d == 2);

        for (int i = i_cur; i < x; i |= i + 1) {
            for (int j = j_cur; j < y; j |= j + 1) {
                v[getIdx(i, j)] = f(v[getIdx(i, j)], a);}}
    }

    T _query(int i_cur, int j_cur) const {
        assert(d == 2);
        
        if (i_cur < 0 || j_cur < 0) {
            return id;}
        
        T res = id;
        for (int i = i_cur; i >= 0; i = (i & (i + 1)) - 1) {
            for (int j = j_cur; j >= 0; j = (j & (j + 1)) - 1) {
                res = f(res, v[getIdx(i, j)]);}}
        
        return res;
    }

    T query(int x1, int y1, int x2, int y2) const {
        assert(d == 2);

        if (x1 > x2 || y1 > y2) {
            return id;}
        
        T res = _query(x2, y2);
        res   = f_inv(res, _query(x1 - 1, y2));
        res   = f_inv(res, _query(x2, y1 - 1));
        res   = f(res, _query(x1 - 1, y1 - 1));
        
        return res;
    }

    // 3D
    inline int getIdx(int i, int j, int k) const {
        return (i * y + j) * z + k;
    }

    void update(int i_cur, int j_cur, int k_cur, T a) {
        assert(d == 3);

        for (int i = i_cur; i < x; i |= i + 1) {
            for (int j = j_cur; j < y; j |= j + 1) {
                for (int k = k_cur; k < z; k |= k + 1) {
                    v[getIdx(i, j, k)] = f(v[getIdx(i, j, k)], a);}}}
    }

    T _query(int i_cur, int j_cur, int k_cur) const {
        assert(d == 3);
        
        if (i_cur < 0 || j_cur < 0 || k_cur < 0) {
            return id;}
        
        T res = id;
        for (int i = i_cur; i >= 0; i = (i & (i + 1)) - 1) {
            for (int j = j_cur; j >= 0; j = (j & (j + 1)) - 1) {
                for (int k = k_cur; k >= 0; k = (k & (k + 1)) - 1) {
                    res = f(res, v[getIdx(i, j, k)]);}}}
        
        return res;
    }

    T query(int x1, int y1, int z1, int x2, int y2, int z2) const {
        assert(d == 3);

        if (x1 > x2 || y1 > y2 || z1 > z2) {
            return id;}

        T res = _query(x2, y2, z2);
        res   = f_inv(res, _query(x1 - 1, y2, z2));
        res   = f_inv(res, _query(x2, y1 - 1, z2));
        res   = f_inv(res, _query(x2, y2, z1 - 1));
        res   = f(res, _query(x1 - 1, y1 - 1, z2));
        res   = f(res, _query(x1 - 1, y2, z1 - 1));
        res   = f(res, _query(x2, y1 - 1, z1 - 1));
        res   = f_inv(res, _query(x1 - 1, y1 - 1, z1 - 1));

        return res;
    }
};

// 2.2.3 Square Root Decomposition

// S: O(n), U: O(sqrt(n)), Q: O(sqrt(n)), M: O(n)
template<typename T, typename F = std::plus<T>>
struct SqrtDecomp {
    int n, m;
    vector<T> v, blks;
    T id;
    F f;

    SqrtDecomp(int N, T ID = T(0), F f_ = F()): 
        n(N), m(sqrt(max(1, N))), v(N, ID), blks((N + m - 1) / m, ID), id(ID), f(f_) {}

    SqrtDecomp(const vector<T> &a, T ID = T(0), F f_ = F()): 
        SqrtDecomp(a.size(), ID, f_) {
        for (int i = 0; i < n; i++) {
            v[i] = a[i];
            blks[i / m] = f(blks[i / m], v[i]);
        }
    }

    inline void _rebuild(int b_i) {
        blks[b_i] = id;
        int l = b_i * m;
        int r = min(n, l + m);
        for (int i = l; i < r; i++) {
            blks[b_i] = f(blks[b_i], v[i]);}
    }

    void opeUpdate(int i, T x) {
        v[i] = f(v[i], x);
        _rebuild(i / m);
    }

    void setUpdate(int i, T x) {
        v[i] = x;
        _rebuild(i / m);
    }

    T query(int l, int r) const {
        if (l > r) {
            return id;}

        T res = id;
        int l_blk = l / m, r_blk = r / m;
        if (l_blk == r_blk) {
            for (int i = l; i <= r; i++) { 
                res = f(res, v[i]);}
        } else {
            for (int i = l; i < (l_blk + 1) * m; i++) { 
                res = f(res, v[i]);}
            for (int i = l_blk + 1; i < r_blk; i++) { 
                res = f(res, blks[i]);}
            for (int i = r_blk * m; i <= r; i++) { 
                res = f(res, v[i]);}
        }

        return res;
    }
};

// S: O(q * log(q)), U: NA, Q: O(n * sqrt(q)), M: O(q)
struct Mo {
    struct Query {
        int l, r, i;
        lng hil_ord;
    };

    int n, q;
    vector<Query> Q;

    Mo(int N): n(N), q(0) {}

    static lng getHilOrd(int x, int y, int pow, int rot) {
        if (pow == 0) {
            return 0;}
            
        int hpow = 1 << (pow - 1);
        int seg = ((x < hpow ? (y < hpow ? 0 : 3) : (y < hpow ? 1 : 2)) + rot) & 3;
        
        const int rot_del[4] = {3, 0, 0, 1};

        int nx = x & (x ^ hpow);
        int ny = y & (y ^ hpow);
        int nrot = (rot + rot_del[seg]) & 3;
        
        lng sub_sq_sz = lng(1) << (2 * pow - 2);
        lng res = seg * sub_sq_sz;
        lng add = getHilOrd(nx, ny, pow - 1, nrot);
        
        res += (seg == 1 || seg == 2) ? add : sub_sq_sz - add - 1;
        
        return res;
    }

    void addQuery(int l, int r) {
        Q.pb({l, r, q++, getHilOrd(l, r, 20, 0)});
    }

    template<typename Add, typename Del, typename Ret>
    void solve(Add add, Del del, Ret ret) {
        if (q == 0) {
            return;}

        sort(Q.begin(), Q.end(), [&](const Query &a, const Query &b) {
            return a.hil_ord < b.hil_ord;
        });

        int l = 0, r = -1;
        for (const Query &cur : Q) {
            while (l > cur.l) { 
                l--; 
                add(l); 
            }
            while (r < cur.r) {
                r++; 
                add(r); 
            }
            
            while (l < cur.l) { 
                del(l); 
                l++; 
            }
            while (r > cur.r) { 
                del(r); 
                r--;
            }
            
            ret(cur.i);
        }
    }
};

// 2.2.4 Segment Tree

struct STTAlg {
    struct S { 
        lng sum;
        lng mx, mn;
        int mx_i, mn_i;
        int len;
    };

    struct F {
        lng a, b;
        
        bool operator==(const F &o) const {
            return a == o.a && b == o.b;
        }

        bool operator!=(const F &o) const {
            return !(*this == o);
        }
    };

    static S idS() {
        return {0, -INF64, INF64, -1, -1, 0};
    }

    static F idF() {
        return {1, 0};
    }
    
    static S defR(int l, int r) {
        return {0, 0, 0, l, l, r - l + 1};
    }

    static S init(int i, lng x) {
        return {x, x, x, i, i, 1};
    }

    static S ope(const S &a, const S &b) {
        if (a.len == 0) {
            return b;}

        if (b.len == 0) {
            return a;}
        
        S res;
        res.sum = a.sum + b.sum;
        if (a.mx >= b.mx) {
            res.mx = a.mx;
            res.mx_i = a.mx_i;
        } else {
            res.mx = b.mx;
            res.mx_i = b.mx_i;
        }
        if (a.mn <= b.mn) {
            res.mn = a.mn;
            res.mn_i = a.mn_i;
        } else {
            res.mn = b.mn;
            res.mn_i = b.mn_i;
        }
        res.len = a.len + b.len;

        return res;
    }

    static S map(const F &f, const S &a) {
        if (a.len == 0) {
            return a;}
        
        S res = a;
        res.sum = f.a * a.sum + f.b * a.len;
        if (f.a < 0) {
            res.mx = f.a * a.mn + f.b;
            res.mn = f.a * a.mx + f.b;
            res.mx_i = a.mn_i;
            res.mn_i = a.mx_i;
        } else {
            res.mx = f.a * a.mx + f.b;
            res.mn = f.a * a.mn + f.b;
        }
        
        return res;
    }

    static F cmp(const F &f, const F &g) {
        return {f.a * g.a, f.a * g.b + f.b};
    }

    /*
    void addUpdate(int l, int r, lng x) { 
        update(l, r, {1, x});
    }

    void mulUpdate(int l, int r, lng x) { 
        update(l, r, {x, 0});
    }

    void setUpdate(int l, int r, lng x) { 
        update(l, r, {0, x});
    }
    */
};

struct STTBin {
    struct S { 
        lng And, Or, Xor;
        int len;
    };

    struct F { 
        lng a, b; 
        
        bool operator==(const F &o) const { 
            return a == o.a && b == o.b; 
        }
        
        bool operator!=(const F &o) const { 
            return !(*this == o); 
        }
    };

    static S idS() { 
        return {~0LL, 0, 0, 0}; 
    }
    
    static F idF() { 
        return {~0LL, 0}; 
    }

    static S defR(int l, int r) {
        return {0, 0, 0, r - l + 1};
    }

    static S init(int i, lng x) {
        return {x, x, x, 1};
    }

    static S ope(const S &a, const S &b) {
        if (a.len == 0) {
            return b;}

        if (b.len == 0) {
            return a;}

        return {a.And & b.And, a.Or | b.Or, a.Xor ^ b.Xor, a.len + b.len};
    }

    static S map(const F &f, const S &a) {
        if (a.len == 0) {
            return a;}

        S res;
        res.And = ((a.And & f.a) & ~f.b) | (~(a.Or & f.a) & f.b);
        res.Or  = ((a.Or & f.a) & ~f.b) | (~(a.And & f.a) & f.b);
        res.Xor = (a.Xor & f.a) ^ (a.len & 1 ? f.b : 0);
        res.len = a.len;
        
        return res;
    }

    static F cmp(const F &f, const F &g) {
        return {g.a & f.a, (g.b & f.a) ^ f.b};
    }

    /*
    void andUpdate(int l, int r, lng x) { 
        update(l, r, {x, 0});
    }

    void orUpdate(int l, int r, lng x)  { 
        update(l, r, {~x, x}); 
    }
    
    void xorUpdate(int l, int r, lng x) { 
        update(l, r, {~0LL, x}); 
    }
    
    void setUpdate(int l, int r, lng x) { 
        update(l, r, {0, x}); 
    }
    */
};

template<bool get_lcm = false>
struct STTGcd {
    struct S { 
        lng Gcd, Lcm;
        int len;
    };

    struct F { 
        lng a, b; 

        bool operator==(const F &o) const { 
            return a == o.a && b == o.b; 
        }
        
        bool operator!=(const F &o) const { 
            return !(*this == o); 
        }
    };

    static S idS() { 
        if constexpr (get_lcm) { 
            return {0, 1, 0};}
        
        return {0, 0, 0}; 
    }
    
    static F idF() { 
        return {0, 1}; 
    }

    static S defR(int l, int r) {
        if constexpr (get_lcm) {
            return {0, 1, r - l + 1};}

        return {0, 0, r - l + 1};
    }

    static S init(int i, lng x) {
        if constexpr (get_lcm) {
            return {x, x, 1};}

        return {x, 0, 1};
    }

    static S ope(const S &a, const S &b) {
        if (a.len == 0) {
            return b;}

        if (b.len == 0) {
            return a;}

        S res;
        res.Gcd = std::gcd(a.Gcd, b.Gcd);
        if constexpr (get_lcm) {
            res.Lcm = std::lcm(a.Lcm, b.Lcm);}
        res.len = a.len + b.len;
        
        return res;
    }

    static S map(const F &f, const S &a) {
        if (a.len == 0) {
            return a;}

        S res;
        res.Gcd = std::lcm(std::gcd(a.Gcd, f.a), f.b);
        if constexpr (get_lcm) {
            res.Lcm = std::lcm(std::gcd(a.Lcm, f.a), f.b);}
        res.len = a.len;
        
        return res;
    }

    static F cmp(const F &f, const F &g) {
        return {std::gcd(g.a, f.a), std::lcm(std::gcd(g.b, f.a), f.b)};
    }

    /*
    void gcdUpdate(int l, int r, lng x) { 
        update(l, r, {x, 1});
    }
    
    void lcmUpdate(int l, int r, lng x) { 
        update(l, r, {0, x}); 
    }
    
    void setUpdate(int l, int r, lng x) { 
        update(l, r, {1, x}); 
    }
    */
};

struct STTSet {
    struct S { 
        // states
        int len;
    };

    struct F { 
        bool to_set; 
        lng set_upd;

        bool operator==(const F &o) const { 
            return to_set == o.to_set && set_upd == o.set_upd;
        }

        bool operator!=(const F &o) const {
            return !(*this == o);
        }
    };

    static S idS() {
        return {0};
    }

    static F idF() {
        return {false, 0};
    }

    static S defR(int l, int r) {
        return {r - l + 1};
    }

    static S init(int i, lng x) {
        return {1};
    }

    static S ope(const S &a, const S &b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;
        
        S res;
        // ope states
        res.len = a.len + b.len;

        return res;
    }

    static S map(const F &f, const S &a) {
        if (a.len == 0 || !f.to_set) return a;
        
        S res = a;
        // map states

        return res;
    }

    static F cmp(const F &f, const F &g) {
        return f.to_set ? f : g;
    }
};

// S: O(n), U: O(log(n)), Q: O(log(n)), M: O(n)
template<typename STT>
struct SegTree {
    using S = typename STT::S;
    using F = typename STT::F;

    int n;
    vector<S> tree;
    vector<F> lazy;

    template<typename T>
    SegTree(const vector<T> &a): n(a.size()), tree(4 * a.size(), STT::idS()), lazy(4 * a.size(), STT::idF()) {
        build(1, 0, n - 1, a);
    }

    template<typename T>
    void build(int i, int l, int r, const vector<T> &a) {
        if (l == r) {
            tree[i] = STT::init(l, a[l]);
            return;
        }

        int m = l + (r - l) / 2;
        build(2 * i,     l,     m, a);
        build(2 * i + 1, m + 1, r, a);
        tree[i] = STT::ope(tree[2 * i], tree[2 * i + 1]);
    }

    inline void apply(int i, F f) {
        tree[i] = STT::map(f, tree[i]);
        lazy[i] = STT::cmp(f, lazy[i]);
    }

    inline void push(int i) {
        if (lazy[i] == STT::idF()) {
            return;}
        
        apply(2 * i,     lazy[i]);
        apply(2 * i + 1, lazy[i]);
        lazy[i] = STT::idF();
    }

    void _update(int i, int l, int r, int ql, int qr, F f) {
        if (ql <= l && r <= qr) {
            apply(i, f);
            return;
        }

        push(i);
        
        int m = l + (r - l) / 2;
        if (ql <= m) {
            _update(2 * i,     l,     m, ql, qr, f);}
        if (qr > m)  {
            _update(2 * i + 1, m + 1, r, ql, qr, f);}
        tree[i] = STT::ope(tree[2 * i], tree[2 * i + 1]);
    }

    void update(int l, int r, F f) { 
        if (l >= 0 && l <= r && r < n) {
            _update(1, 0, n - 1, l, r, f);}
    }

    template<class G>
    int _maxR(int i, int l, int r, int ql, G &g, S &acc) {
        if (r < ql) {
            return -1;}
        
        if (ql <= l) {
            S nac = STT::ope(acc, tree[i]);
            if (g(nac)) {
                acc = nac;
                return -1;
            }
        }

        if (l == r) {
            return l - 1;} 

        push(i);
        int m = l + (r - l) / 2;
        int res = _maxR(2 * i, l, m, ql, g, acc);
        if (res != -1) {
            return res;}
        
        return _maxR(2 * i + 1, m + 1, r, ql, g, acc);
    }

    template<class G>
    int maxR(int l, G g) { // Returns max r in [l, n - 1] where g(query(l, r)) is true. If g(a[l]) is false, returns l - 1.
        if (l < 0 || l > n - 1) {
            return l - 1;}

        S acc = STT::idS();
        int res = _maxR(1, 0, n - 1, l, g, acc);
        
        return res == -1 ? n - 1 : res;
    }

    template<class G>
    int _minL(int i, int l, int r, int qr, G &g, S &acc) {
        if (l > qr) {
            return -1;}
        
        if (r <= qr) {
            S nac = STT::ope(tree[i], acc);
            if (g(nac)) {
                acc = nac;
                return -1;
            }
        }

        if (l == r) {
            return l + 1;}

        push(i);
        int m = l + (r - l) / 2;
        int res = _minL(2 * i + 1, m + 1, r, qr, g, acc);
        if (res != -1) {
            return res;}

        return _minL(2 * i, l, m, qr, g, acc);
    }
    
    template<class G>
    int minL(int r, G g) { // Returns min l in [0, r] where g(query(l, r)) is true. If g(a[r]) is false, returns r + 1.
        if (r < 0 || r > n - 1) {
            return r + 1;}

        S acc = STT::idS();
        int res = _minL(1, 0, n - 1, r, g, acc);
        
        return res == -1 ? 0 : res;
    }

    S _query(int i, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return tree[i];}
        
        push(i);
        
        int m = l + (r - l) / 2;
        if (qr <= m) {
            return _query(2 * i,     l,     m, ql, qr);}
        if (ql > m)  {
            return _query(2 * i + 1, m + 1, r, ql, qr);}
        
        return STT::ope(_query(2 * i, l, m, ql, qr), _query(2 * i + 1, m + 1, r, ql, qr));
    }

    S query(int l, int r) { 
        if (l < 0 || r > n - 1 || l > r) {
            return STT::idS();}
        
        return _query(1, 0, n - 1, l, r); 
    }

    // Q: O(1)
    S queryAll() {
        return tree[1];
    }
};

// S: O(q * log(n)), U: O(log(n)), Q: O(log(n)), M: O(q * log(n))
template<typename STT>
struct DynSegTree {
    using S = typename STT::S;
    using F = typename STT::F;

    struct Node {
        S val;
        F lzy;
        int lc = -1, rc = -1;

        Node(lng l, lng r): val(STT::defR(l, r)), lzy(STT::idF()) {}
    };

    lng n;
    int root = -1;
    vector<Node> tree;
    
    DynSegTree(lng N): n(N) {
        tree.reserve(500'000);
        root = createNode(0, n - 1);
    }

    template<typename T>
    DynSegTree(const vector<T> &a): n(a.size()) {
        tree.reserve(4 * n);
        root = build(0, n - 1, a);
    }

    // S: O(n)
    template<typename T>
    int build(lng l, lng r, const vector<T> &a) {
        int cur = createNode(l, r);
        
        if (l == r) {
            tree[cur].val = STT::init(l, a[l]);
            return cur;
        }

        lng m = l + (r - l) / 2;
        int nlc = build(l,     m, a);
        tree[cur].lc = nlc;
        int nrc = build(m + 1, r, a);
        tree[cur].rc = nrc;
        tree[cur].val = STT::ope(tree[nlc].val, tree[nrc].val);

        return cur;
    }

    int createNode(lng l, lng r) {
        tree.emplace_back(l, r);
        
        return tree.size() - 1;
    }

    inline void apply(int i, F f) {
        tree[i].val = STT::map(f, tree[i].val);
        tree[i].lzy = STT::cmp(f, tree[i].lzy);
    }

    inline void push(int i, lng l, lng r) {
        if (tree[i].lzy == STT::idF()) {
            return;}
        
        lng m = l + (r - l) / 2;
        if (tree[i].lc == -1) {
            int nlc = createNode(l, m);
            tree[i].lc = nlc;
        }
        if (tree[i].rc == -1) {
            int nrc = createNode(m + 1, r);
            tree[i].rc = nrc;
        }

        apply(tree[i].lc, tree[i].lzy);
        apply(tree[i].rc, tree[i].lzy);
        tree[i].lzy = STT::idF();
    }

    void _update(int i, lng l, lng r, lng ql, lng qr, F f) {
        if (ql <= l && r <= qr) {
            apply(i, f);
            return;
        }

        push(i, l, r);
        
        lng m = l + (r - l) / 2;
        if (ql <= m) {
            if (tree[i].lc == -1) {
                int nlc = createNode(l, m);
                tree[i].lc = nlc;
            }

            _update(tree[i].lc, l,     m, ql, qr, f);
        }
        if (qr > m) {
            if (tree[i].rc == -1) {
                int nrc = createNode(m + 1, r);
                tree[i].rc = nrc;
            }

            _update(tree[i].rc, m + 1, r, ql, qr, f);
        }

        S l_val = tree[i].lc != -1 ? tree[tree[i].lc].val : STT::defR(l, m);
        S r_val = tree[i].rc != -1 ? tree[tree[i].rc].val : STT::defR(m + 1, r);
        tree[i].val = STT::ope(l_val, r_val);
    }

    void update(lng l, lng r, F f) { 
        if (l >= 0 && l <= r && r < n) {
            _update(root, 0, n - 1, l, r, f);}
    }

    template<class G>
    lng _maxR(int i, lng l, lng r, lng ql, G &g, S &acc) {
        if (r < ql) {
            return -1;}
        
        if (ql <= l) {
            S nac = STT::ope(acc, i == -1 ? STT::defR(l, r) : tree[i].val);
            if (g(nac)) {
                acc = nac;
                return -1;
            }
        }

        if (l == r) {
            return l - 1;}

        if (i != -1) {
            push(i, l, r);}

        lng m = l + (r - l) / 2;
        lng res = _maxR(i == -1 ? -1 : tree[i].lc, l, m, ql, g, acc);
        if (res != -1) {
            return res;}
        
        return _maxR(i == -1 ? -1 : tree[i].rc, m + 1, r, ql, g, acc);
    }

    template<class G>
    lng maxR(lng l, G g) { // Returns max r in [l, n - 1] where g(query(l, r)) is true. If g(a[l]) is false, returns l - 1.
        if (l < 0 || l > n - 1) {
            return l - 1;}

        S acc = STT::idS();
        lng res = _maxR(root, 0, n - 1, l, g, acc);

        return res == -1 ? n - 1 : res;
    }

    template<class G>
    lng _minL(int i, lng l, lng r, lng qr, G &g, S &acc) {
        if (l > qr) {
            return -1;}
        
        if (r <= qr) {
            S nac = STT::ope(i == -1 ? STT::defR(l, r) : tree[i].val, acc);
            if (g(nac)) {
                acc = nac;
                return -1;
            }
        }

        if (l == r) {
            return l + 1;}

        if (i != -1) {
            push(i, l, r);}

        lng m = l + (r - l) / 2;
        lng res = _minL(i == -1 ? -1 : tree[i].rc, m + 1, r, qr, g, acc);
        if (res != -1) {
            return res;}
        
        return _minL(i == -1 ? -1 : tree[i].lc, l, m, qr, g, acc);
    }

    template<class G>
    lng minL(lng r, G g) { // Returns min l in [0, r] where g(query(l, r)) is true. If g(a[r]) is false, returns r + 1.
        if (r < 0 || r > n - 1) {
            return r + 1;}
        
        S acc = STT::idS();
        lng res = _minL(root, 0, n - 1, r, g, acc);
        
        return res == -1 ? 0 : res;
    }

    S _query(int i, lng l, lng r, lng ql, lng qr) {
        if (i == -1) {
            if (max(l, ql) > min(r, qr)) {
                return STT::idS();}

            return STT::defR(max(l, ql), min(r, qr));
        }

        if (ql <= l && r <= qr) {
            return tree[i].val;}
        
        push(i, l, r);
        
        lng m = l + (r - l) / 2;
        if (qr <= m) {
            return _query(tree[i].lc, l    , m, ql, qr);}
        if (ql > m) {
            return _query(tree[i].rc, m + 1, r, ql, qr);}
        
        return STT::ope(_query(tree[i].lc, l, m, ql, qr), _query(tree[i].rc, m + 1, r, ql, qr));
    }

    S query(lng l, lng r) { 
        if (l < 0 || r > n - 1 || l > r) {
            return STT::idS();}

        return _query(root, 0, n - 1, l, r); 
    }

    // Q: O(1)
    S queryAll() {
        return root == -1 ? STT::defR(0, n - 1) : tree[root].val;
    }
};

// S: O(q * log(n)), U: O(log(n)), Q: O(log(n)), M: O(q * log(n))
template<typename STT>
struct PerSegTree {
    using S = typename STT::S;
    using F = typename STT::F;

    struct Node {
        S val;
        F lzy;
        int lc = -1, rc = -1;

        Node(lng l, lng r): val(STT::defR(l, r)), lzy(STT::idF()) {}
    };

    lng n;
    vector<int> roots;
    vector<Node> tree;

    PerSegTree(lng N): n(N) {
        tree.reserve(10'000'000); 
        roots.pb(cloneNode(-1, 0, n - 1));
    }

    template<typename T>
    PerSegTree(const vector<T> &a): n(a.size()) {
        tree.reserve(10'000'000); 
        roots.pb(build(0, n - 1, a));
    }

    // S: O(n)
    template<typename T>
    int build(lng l, lng r, const vector<T> &a) {
        int cur = cloneNode(-1, l, r);
        
        if (l == r) {
            tree[cur].val = STT::init(l, a[l]);
            return cur;
        }

        lng m = l + (r - l) / 2;
        int nlc = build(l,     m, a);
        tree[cur].lc = nlc;
        int nrc = build(m + 1, r, a);
        tree[cur].rc = nrc;
        tree[cur].val = STT::ope(tree[nlc].val, tree[nrc].val);

        return cur;
    }

    int cloneNode(int i, lng l, lng r) {
        if (i == -1) {
            tree.emplace_back(l, r);
        } else {
            Node tmp = tree[i];
            tree.pb(tmp);
        }

        return tree.size() - 1;
    }

    inline void apply(int i, F f) {
        tree[i].val = STT::map(f, tree[i].val);
        tree[i].lzy = STT::cmp(f, tree[i].lzy);
    }

    inline void push(int i, lng l, lng r) {
        if (tree[i].lzy == STT::idF()) {
            return;}
        
        lng m = l + (r - l) / 2;
        int nlc = cloneNode(tree[i].lc, l,     m);
        tree[i].lc = nlc;
        int nrc = cloneNode(tree[i].rc, m + 1, r);
        tree[i].rc = nrc;

        apply(tree[i].lc, tree[i].lzy);
        apply(tree[i].rc, tree[i].lzy);
        tree[i].lzy = STT::idF();
    }

    int _modify(int i1, int i2, lng l, lng r, lng ql, lng qr, F acc) {
        if (ql <= l && r <= qr) {
            int j = cloneNode(i2, l, r);
            apply(j, acc);
            return j;
        }

        int j = cloneNode(i1, l, r);
       
        push(j, l, r);

        int lc2 = -1, rc2 = -1;
        F nac = acc;
        if (i2 != -1) {
            lc2 = tree[i2].lc;
            rc2 = tree[i2].rc;
            nac = STT::cmp(acc, tree[i2].lzy);
        }

        lng m = l + (r - l) / 2;
        if (ql <= m) {
            int nlc = _modify(tree[j].lc, lc2, l,     m, ql, qr, nac);
            tree[j].lc = nlc;
        }
        if (qr > m) {
            int nrc = _modify(tree[j].rc, rc2, m + 1, r, ql, qr, nac);
            tree[j].rc = nrc;
        }

        S l_val = tree[j].lc != -1 ? tree[tree[j].lc].val : STT::defR(l, m);
        S r_val = tree[j].rc != -1 ? tree[tree[j].rc].val : STT::defR(m + 1, r);
        tree[j].val = STT::ope(l_val, r_val);

        return j;
    }

    int modify(int ver1, int ver2, lng l, lng r) {
        if (l < 0 || r > n - 1 || l > r) {
            int cur = roots[ver1];
            roots.pb(cur);
            return roots.size() - 1;
        }
        
        int cur = _modify(roots[ver1], roots[ver2], 0, n - 1, l, r, STT::idF());
        roots.pb(cur);
        
        return roots.size() - 1;
    }

    int _update(int i, lng l, lng r, lng ql, lng qr, F f) {
        int j = cloneNode(i, l, r);
        
        if (ql <= l && r <= qr) {
            apply(j, f);
            return j;
        }

        push(j, l, r);
        
        lng m = l + (r - l) / 2;
        if (ql <= m) {
            int nlc = _update(tree[j].lc, l,     m, ql, qr, f);
            tree[j].lc = nlc;
        }
        if (qr > m)  {
            int nrc = _update(tree[j].rc, m + 1, r, ql, qr, f);
            tree[j].rc = nrc;
        }

        S l_val = tree[j].lc != -1 ? tree[tree[j].lc].val : STT::defR(l, m);
        S r_val = tree[j].rc != -1 ? tree[tree[j].rc].val : STT::defR(m + 1, r);
        tree[j].val = STT::ope(l_val, r_val);
        
        return j;
    }

    int update(int ver, lng l, lng r, F f) { 
        if (l < 0 || r > n - 1 || l > r) {
            int cur = roots[ver];
            roots.pb(cur);
            return roots.size() - 1;
        }
        
        int cur = _update(roots[ver], 0, n - 1, l, r, f);
        roots.pb(cur);

        return roots.size() - 1;
    }

    template<class G>
    lng _maxR(int i, lng l, lng r, lng ql, G &g, S &acc, F tac) {
        if (r < ql) {
            return -1;}
        
        if (ql <= l) {
            S val = i == -1 ? STT::defR(l, r) : tree[i].val;
            val = STT::map(tac, val);
            S nac = STT::ope(acc, val);
            if (g(nac)) {
                acc = nac;
                return -1;
            }
        }

        if (l == r) {
            return l - 1;}

        tac = i == -1 ? tac : STT::cmp(tac, tree[i].lzy);
 
        lng m = l + (r - l) / 2;
        lng res = _maxR(i == -1 ? -1 : tree[i].lc, l, m, ql, g, acc, tac);
        if (res != -1) {
            return res;}
        
        return _maxR(i == -1 ? -1 : tree[i].rc, m + 1, r, ql, g, acc, tac);
    }

    template<class G>
    lng maxR(int ver, lng l, G g) { // Returns max r in [l, n - 1] where g(query(l, r)) is true. If g(a[l]) is false, returns l - 1.
        if (l < 0 || l > n - 1) {
            return l - 1;}

        S acc = STT::idS();
        lng res = _maxR(roots[ver], 0, n - 1, l, g, acc, STT::idF());
        
        return res == -1 ? n - 1 : res;
    }

    template<class G>
    lng _minL(int i, lng l, lng r, lng qr, G &g, S &acc, F tac) {
        if (l > qr) {
            return -1;}
        
        if (r <= qr) {
            S val = i == -1 ? STT::defR(l, r) : tree[i].val;
            val = STT::map(tac, val);
            S nac = STT::ope(val, acc);
            if (g(nac)) {
                acc = nac;
                return -1;
            }
        }

        if (l == r) {
            return l + 1;}
        
        tac = i == -1 ? tac : STT::cmp(tac, tree[i].lzy);

        lng m = l + (r - l) / 2;
        lng res = _minL(i == -1 ? -1 : tree[i].rc, m + 1, r, qr, g, acc, tac);
        if (res != -1) {
            return res;}
        
        return _minL(i == -1 ? -1 : tree[i].lc, l, m, qr, g, acc, tac);
    }

    template<class G>
    lng minL(int ver, lng r, G g) { // Returns min l in [0, r] where g(query(l, r)) is true. If g(a[r]) is false, returns r + 1.
        if (r < 0 || r > n - 1) {
            return r + 1;}
        
        S acc = STT::idS();
        lng res = _minL(roots[ver], 0, n - 1, r, g, acc, STT::idF());
        
        return res == -1 ? 0 : res;
    }

    S _query(int i, lng l, lng r, lng ql, lng qr, F acc) {
        if (i == -1) {
            if (max(l, ql) > min(r, qr)) {
                return STT::idS();}

            return STT::map(acc, STT::defR(max(l, ql), min(r, qr))); 
        }

        if (ql <= l && r <= qr) {
            return STT::map(acc, tree[i].val);}

        F nac = STT::cmp(acc, tree[i].lzy); 

        lng m = l + (r - l) / 2;
        if (qr <= m) {
            return _query(tree[i].lc, l,     m, ql, qr, nac);}
        if (ql > m) {
            return _query(tree[i].rc, m + 1, r, ql, qr, nac);}
        
        return STT::ope(_query(tree[i].lc, l, m, ql, qr, nac), _query(tree[i].rc, m + 1, r, ql, qr, nac));
    }

    S query(int ver, lng l, lng r) { 
        if (l < 0 || r > n - 1 || l > r) {
            return STT::idS();}

        return _query(roots[ver], 0, n - 1, l, r, STT::idF()); 
    }

    // Q: O(1)
    S queryAll(int ver) {
        return roots[ver] == -1 ? STT::defR(0, n - 1) : tree[roots[ver]].val;
    }
};

// 2.2.5 Cartesian Tree (Treap)

// S: NA, U: NA, Q: O(1), M: O(1)
struct CustomHash {
    using ulng = unsigned long long;

    static ulng splitMix64(ulng x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;

        return x ^ (x >> 31);
    }

    template<typename T>
    size_t operator()(const T &x) const {
        static const ulng rnd = chrono::steady_clock::now().time_since_epoch().count();
        
        return splitMix64(ulng(x) + rnd);
    }
    
    template<typename T1, typename T2>
    size_t operator()(const pair<T1, T2> &x) const {
        static const ulng rnd = chrono::steady_clock::now().time_since_epoch().count();
        
        return (splitMix64(ulng(x.fi) + rnd) << 3) ^ (splitMix64(ulng(x.se) + rnd) >> 1);
    }

    // Q: O(n)
    template<typename ...Ts>
    size_t operator()(const tuple<Ts...> &x) const {
        static const ulng rnd = chrono::steady_clock::now().time_since_epoch().count();
        
        size_t seed = 0;
        apply(
            [&](const auto &...args) {
                ((seed = ((seed << 3) ^ (splitMix64(ulng(args) + rnd) >> 1)) + 0x9e3779b9), ...);
            }, x
        );
        
        return seed;
    }
};
template<typename K, typename V> 
using safe_unordered_map = unordered_map<K, V, CustomHash>;
template<typename T> 
using safe_unordered_set = unordered_set<T, CustomHash>;

// S: NA, U: NA, Q: O(n * log(n)), M: O(1)
template<typename T>
struct FastConv {
    static void fctOr(vector<T> &a, bool is_inv) {
        int n = a.size();
        for (int len = 1; len < n; len <<= 1) {
            for (int i = 0; i < n; i += 2 * len) {
                for (int j = 0; j < len; j++) {
                    if (is_inv) {
                        a[i + len + j] -= a[i + j];
                    } else {
                        a[i + len + j] += a[i + j];}
                }
            }
        }
    }

    static void fctAnd(vector<T> &a, bool is_inv) {
        int n = a.size();
        for (int len = 1; len < n; len <<= 1) {
            for (int i = 0; i < n; i += 2 * len) {
                for (int j = 0; j < len; j++) {
                    if (is_inv) {
                        a[i + j] -= a[i + len + j];
                    } else {
                        a[i + j] += a[i + len + j];}
                }
            }
        }
    }

    static void fctXor(vector<T> &a, bool is_inv) {
        int n = a.size();
        for (int len = 1; len < n; len <<= 1) {
            for (int i = 0; i < n; i += 2 * len) {
                for (int j = 0; j < len; j++) {
                    T u = a[i + j], v = a[i + len + j];
                    a[i + j] = u + v;
                    a[i + len + j] = u - v;
                }
            }
        }
        if (is_inv) {
            T f_inv_n = T(1) / T(n);
            for (int i = 0; i < n; i++) {
                a[i] *= f_inv_n;}
        }
    }

    static void fctGcdSlow(vector<T> &a, bool is_inv) {
        int n = a.size() - 1;
        if (is_inv) {
            for (int i = n; i >= 1; i--) {
                for (int j = 2 * i; j <= n; j += i) {
                    a[i] -= a[j];}}
        } else {
            for (int i = 1; i <= n; i++) {
                for (int j = 2 * i; j <= n; j += i) {
                    a[i] += a[j];}}
        }
    }

    // Q: O(n * loglog(n))
    //*
    static void fctGcd(vector<T> &a, bool is_inv, const LinearSieve &sv) {
        int n = a.size() - 1;
        for (int p : sv.prms) {
            if (p > n) {
                break;}

            if (is_inv) {
                for (int i = 1; i * p <= n; i++) {
                    a[i] -= a[i * p];}
            } else {
                for (int i = n / p; i >= 1; i--) {
                    a[i] += a[i * p];}
            }
        }
    }//*/

    static void fctLcmSlow(vector<T> &a, bool is_inv) {
        int n = a.size() - 1;
        if (is_inv) {
            for (int i = 1; i <= n; i++) {
                for (int j = 2 * i; j <= n; j += i) {
                    a[j] -= a[i];}}
        } else {
            for (int i = n; i >= 1; i--) {
                for (int j = 2 * i; j <= n; j += i) {
                    a[j] += a[i];}}
        }
    }

    // Q: O(n * loglog(n))
    //*
    static void fctLcm(vector<T> &a, bool is_inv, const LinearSieve &sv) {
        int n = a.size() - 1;
        for (int p : sv.prms) {
            if (p > n) {
                break;}

            if (is_inv) {
                for (int i = n / p; i >= 1; i--) {
                    a[i * p] -= a[i];}
            } else {
                for (int i = 1; i * p <= n; i++) {
                    a[i * p] += a[i];}
            }
        }
    }//*/
};

// T: O(n^2), M: O(n^2)
template<typename T>
struct Matrix {
    int n, m;
    vector<vector<T>> v;

    Matrix(int N = 0, int M = 0): n(N), m(M), v(N, vector<T>(M, T(0))) {
        assert((n == 0 && m == 0) || (n > 0 && m > 0));
    }

    Matrix(const vector<T> &a, int axis = 0) {
        assert(!a.empty());

        if (axis == 0) {
            n = 1;
            m = a.size();
            v = {a};
        } else if (axis == 1) {
            n = a.size();
            m = 1;
            v.resize(n);
            for (int i = 0; i < n; i++) {
                v[i] = {a[i]};}
        }
    }

    Matrix(const vector<vector<T>> &a) {
        if (!a.empty()) {
            assert(!a[0].empty());}

        n = a.size();
        m = a.empty() ? 0 : a[0].size();
        v = a;
    }

    vector<T> &operator[](int i) { 
        return v[i]; 
    }
    
    const vector<T> &operator[](int i) const { 
        return v[i]; 
    }
    
    int size() const { 
        return n; 
    }

    Matrix &operator+=(const Matrix &o) {
        assert(n == o.n && m == o.m);
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                v[i][j] += o[i][j];}}

        return *this;
    }

    Matrix &operator-=(const Matrix &o) {
        assert(n == o.n && m == o.m);
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                v[i][j] -= o[i][j];}}

        return *this;
    }

    Matrix &operator*=(T o) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                v[i][j] *= o;}}

        return *this;
    }

    Matrix &operator*=(const vector<T> &o) {
        return *this = *this * o;
    }

    // T: O(n^3)
    Matrix &operator*=(const Matrix &o) {
        return *this = *this * o;
    }
    
    Matrix &operator/=(T o) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                v[i][j] /= o;}}
        
        return *this;
    }

    // T: O(n^3)
    Matrix &operator/=(const Matrix &o) {
        return *this = *this / o;
    }

    Matrix &operator%=(T o) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                v[i][j] %= o;}}
        
        return *this;
    }

    Matrix operator+() const {
        return *this;
    }

    Matrix operator-() const {
        Matrix res(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res[i][j] = -v[i][j];}}

        return res;
    }

    friend Matrix operator+(Matrix a, const Matrix &b) {
        return a += b;
    }

    friend Matrix operator-(Matrix a, const Matrix &b) {
        return a -= b;
    }

    friend Matrix operator*(Matrix a, T b) {
        return a *= b;
    }

    friend Matrix operator*(T b, Matrix a) {
        return a *= b;
    }

    friend Matrix operator*(const vector<T> &b, Matrix a) {
        return Matrix(b, 0) *= a;
    }

    friend Matrix operator*(Matrix a, const vector<T> &b) {
        return a *= Matrix(b, 1);
    }

    // T: O(n^3)
    friend Matrix operator*(const Matrix &a, const Matrix &b) {
        assert(a.m == b.n);

        Matrix res(a.n, b.m);
        for (int i = 0; i < a.n; i++) {
            for (int k = 0; k < a.m; k++) {
                if (a[i][k] == T(0)) {
                    continue;}
                
                T a_ik = a[i][k]; 
                for (int j = 0; j < b.m; j++) {
                    res[i][j] += a_ik * b[k][j];}
            }
        }

        return res;
    }

    friend Matrix operator/(Matrix a, T b) {
        return a /= b;
    }

    // T: O(n^3)
    friend Matrix operator/(const Matrix &a, const Matrix &b) {
        assert(a.m == b.n);

        return a * inv(b);
    }

    friend Matrix operator%(Matrix a, T b) {
        return a %= b;
    }

    friend Matrix add(const Matrix &a, const Matrix &b, int axis = 0) {
        Matrix res;
        if (axis == 0) {
            assert(a.n == b.n);

            res = Matrix(a.n, a.m + b.m);
            for (int i = 0; i < a.n; i++) {
                for (int j = 0; j < a.m; j++) {
                    res[i][j] = a[i][j];}}
            for (int i = 0; i < b.n; i++) {
                for (int j = 0; j < b.m; j++) {
                    res[i][j + a.m] = b[i][j];}}
        } else if (axis == 1) {
            assert(a.m == b.m);

            res = Matrix(a.n + b.n, a.m);
            for (int i = 0; i < a.n; i++) {
                for (int j = 0; j < a.m; j++) {
                    res[i][j] = a[i][j];}}
            for (int i = 0; i < b.n; i++) {
                for (int j = 0; j < b.m; j++) {
                    res[i + a.n][j] = b[i][j];}}
        }

        return res;
    }

    // T: O(n^3)
    friend T det(Matrix a) {
        static_assert(!std::is_integral_v<T>);
        assert(a.n == a.m);

        T res = 1;
        for (int i = 0; i < a.n; i++) {
            int piv = i;
            while (piv < a.n && a[piv][i] == T(0)) {
                piv++;}
            if (piv == a.n) {
                return T(0);}
            
            if (i != piv) {
                swap(a[i], a[piv]);
                res = -res;
            }
            
            res *= a[i][i];
            T d = T(1) / a[i][i];
            for (int j = i; j < a.n; j++) {
                a[i][j] *= d;}
            
            for (int k = i + 1; k < a.n; k++) {
                if (a[k][i] == T(0)) {
                    continue;}
                
                T a_ki = a[k][i];
                for (int j = i; j < a.n; j++) {
                    a[k][j] -= a[i][j] * a_ki;}
            }
        }

        return res;
    }

    // T: O(n^3)
    friend Matrix inv(Matrix a) {
        static_assert(!std::is_integral_v<T>);
        assert(a.n == a.m);

        Matrix res = eye(a.n, a.n);
        for (int i = 0; i < a.n; i++) {
            int piv = i;
            while (piv < a.n && a[piv][i] == T(0)) {
                piv++;}

            assert(piv < a.n);

            if (i != piv) {
                swap(a[i], a[piv]);
                swap(res[i], res[piv]);
            }

            T d = T(1) / a[i][i];
            for (int j = i; j < a.n; j++) {
                a[i][j] *= d;}
            for (int j = 0; j < a.n; j++) {
                res[i][j] *= d;}

            for (int k = 0; k < a.n; k++) {
                if (k == i) {
                    continue;}

                T a_ki = a[k][i];
                if (a_ki == T(0)) {
                    continue;}
                
                for (int j = i; j < a.n; j++) {
                    a[k][j] -= a[i][j] * a_ki;}
                for (int j = 0; j < a.n; j++) {
                    res[k][j] -= res[i][j] * a_ki;}
            }
        }

        return res;
    }

    // T: O(n^3 * log(n))
    friend Matrix pow(Matrix a, lng b) {
        assert(a.n == a.m && b >= 0);
        
        Matrix res = eye(a.n, a.n);
        while (b > 0) {
            if (b & 1) {
                res *= a;}

            b >>= 1;
            if (b == 0) {
                break;}

            a *= a;
        }

        return res;
    }

    // T: O(n^3)
    friend Matrix ref(Matrix a) {
        static_assert(!std::is_integral_v<T>);
        
        int r = 0;
        for (int c = 0; r < a.n && c < a.m; c++) {
            int piv = r;
            while (piv < a.n && a[piv][c] == T(0)) {
                piv++;}
            
            if (piv == a.n) {
                continue;}
            
            if (r != piv) {
                swap(a[r], a[piv]);}
            
            T d = T(1) / a[r][c];
            for (int j = c; j < a.m; j++) {
                a[r][j] *= d;}
            
            for (int i = r + 1; i < a.n; i++) {
                T a_ic = a[i][c];
                if (a_ic == T(0)) {
                    continue;}
                
                for (int j = c; j < a.m; j++) {
                    a[i][j] -= a[r][j] * a_ic;}
            }
            r++;
        }

        return a;
    }

    // T: O(n^3)
    friend Matrix rref(Matrix a) {
        static_assert(!std::is_integral_v<T>);
        
        int r = 0;
        for (int c = 0; r < a.n && c < a.m; c++) {
            int piv = r;
            while (piv < a.n && a[piv][c] == T(0)) {
                piv++;}
            
            if (piv == a.n) {
                continue;}
            
            if (r != piv) {
                swap(a[r], a[piv]);}
            
            T d = T(1) / a[r][c];
            for (int j = c; j < a.m; j++) {
                a[r][j] *= d;}
            
            for (int i = 0; i < a.n; i++) {
                if (i == r) {
                    continue;}
                
                T a_ic = a[i][c];
                if (a_ic == T(0)) {
                    continue;}
                
                for (int j = c; j < a.m; j++) {
                    a[i][j] -= a[r][j] * a_ic;}
            }
            r++;
        }

        return a;
    }

    friend T trace(const Matrix &a) {
        assert(a.n == a.m);

        T res = 0;
        for (int i = 0; i < a.n; i++) {
            res += a[i][i];}

        return res;
    }

    friend Matrix trp(const Matrix &a) { 
        Matrix res(a.m, a.n);
        for (int i = 0; i < a.m; i++) {
            for (int j = 0; j < a.n; j++) {
                res[i][j] = a[j][i];}}
        
        return res;
    }

    static Matrix cross(const Matrix &a, const Matrix &b, int axis = 0) {
        assert((a.n == 1 || a.m == 1) && max(a.n, a.m) == 3);
        assert((b.n == 1 || b.m == 1) && max(b.n, b.m) == 3);

        auto get = [](const Matrix &x, int i) {
            return x.n == 1 ? x[0][i] : x[i][0];
        };

        T x = get(a, 1) * get(b, 2) - get(a, 2) * get(b, 1);
        T y = get(a, 2) * get(b, 0) - get(a, 0) * get(b, 2);
        T z = get(a, 0) * get(b, 1) - get(a, 1) * get(b, 0);

        return Matrix(vector<T>({x, y, z}), axis);
    }

    static T dot(const Matrix &a, const Matrix &b) {
        assert((a.n == 1 || a.m == 1) && (b.n == 1 || b.m == 1));
        assert(max(a.n, a.m) == max(b.n, b.m));

        auto get = [](const Matrix &x, int i) {
            return x.n == 1 ? x[0][i] : x[i][0];
        };

        T res = 0;
        for (int i = 0; i < max(a.n, a.m); i++) {
            res += get(a, i) * get(b, i);}

        return res;
    }

    static Matrix eye(int N, int M) {
        Matrix res(N, M);
        for (int i = 0; i < min(N, M); i++) {
            res[i][i] = T(1);}      
        
        return res;
    }

    friend bool operator==(const Matrix &a, const Matrix &b) {
        return a.v == b.v;
    }

    friend bool operator!=(const Matrix &a, const Matrix &b) {
        return a.v != b.v;
    }

    friend ostream &operator<<(ostream &os, const Matrix &a) {
        if (a.n == 0 || a.m == 0) {
            return os;}
        
        for (int i = 0; i < a.n; i++) {
            for (int j = 0; j < a.m; j++) {
                os << a[i][j] << ' ';}

            if (i < a.n - 1) {
                os << '\n';}
        }

        return os;
    }
};
using mtx = Matrix<mint>;

// S: O(1), U: NA, Q: O(1), M: O(1)
struct Random {
    mt19937    rng_int;
    mt19937_64 rng_lng; 

    Random(): 
        rng_int(chrono::steady_clock::now().time_since_epoch().count()),
        rng_lng(chrono::steady_clock::now().time_since_epoch().count()) {}

    int randInt(int l, int r) {
        return uniform_int_distribution<int>(l, r)(rng_int);
    }

    lng randLng(lng l, lng r) {
        return uniform_int_distribution<lng>(l, r)(rng_lng);
    }
};

// Convex Hull
// Li-Chao Tree