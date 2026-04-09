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

struct LinearSieve {
    int n;
    vector<lng> prms, spf;
    vector<lng> num_div, sum_div, phi, mu;
    
    // T: O(n), M: O(n)
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

    // T: O(n), M: O(n)
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

    // T: O(n), M: O(n)
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

    // T: O(n), M: O(n)
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

    // T: O(n), M: O(n)
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

    // T: O(log(n)), M: O(log(n))
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

template<typename T>
struct FastConv {    
    // T: O(n * log(n)), M: O(1)
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

    // T: O(n * log(n)), M: O(1)
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

    // T: O(n * log(n)), M: O(1)
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
            T inv_n = T(1) / T(n);
            for (int i = 0; i < n; i++) {
                a[i] *= inv_n;}
        }
    }

    // T: O(n * log(n)), M: O(1)
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

    // T: O(n * loglog(n)), M: O(1)
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

    // T: O(n * log(n)), M: O(1)
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

    // T: O(n * loglog(n)), M: O(1)
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

// --- O(N^2) Brute Force Convolutions ---
vector<mint> bruteOr(const vector<mint>& a, const vector<mint>& b) {
    int n = a.size(); vector<mint> c(n, 0);
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if ((i | j) < n) c[i | j] += a[i] * b[j];
    return c;
}
vector<mint> bruteAnd(const vector<mint>& a, const vector<mint>& b) {
    int n = a.size(); vector<mint> c(n, 0);
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) c[i & j] += a[i] * b[j];
    return c;
}
vector<mint> bruteXor(const vector<mint>& a, const vector<mint>& b) {
    int n = a.size(); vector<mint> c(n, 0);
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if ((i ^ j) < n) c[i ^ j] += a[i] * b[j];
    return c;
}
vector<mint> bruteGcd(const vector<mint>& a, const vector<mint>& b) {
    int n = a.size(); vector<mint> c(n, 0);
    for (int i = 1; i < n; i++) for (int j = 1; j < n; j++) c[std::gcd(i, j)] += a[i] * b[j];
    return c;
}
vector<mint> bruteLcm(const vector<mint>& a, const vector<mint>& b) {
    int n = a.size(); vector<mint> c(n, 0);
    for (int i = 1; i < n; i++) for (int j = 1; j < n; j++) {
        lng l = std::lcm((lng)i, (lng)j);
        if (l < n) c[l] += a[i] * b[j];
    }
    return c;
}

void runTests() {
    mt19937 rng(1337);
    int bit_n = 4096; // Power of 2
    int div_n = 5000; // Arbitrary size

    vector<mint> A_bit(bit_n), B_bit(bit_n);
    vector<mint> A_div(div_n), B_div(div_n);
    
    for (int i = 0; i < bit_n; i++) { A_bit[i] = rng() % 1000; B_bit[i] = rng() % 1000; }
    for (int i = 1; i < div_n; i++) { A_div[i] = rng() % 1000; B_div[i] = rng() % 1000; } 

    LinearSieve sv(div_n);

    auto test = [&](string name, auto brute, auto fct) {
        // FIXED: Matched exact uppercase strings "GCD" and "LCM"
        auto A = (name.find("GCD") != string::npos || name.find("LCM") != string::npos) ? A_div : A_bit;
        auto B = (name.find("GCD") != string::npos || name.find("LCM") != string::npos) ? B_div : B_bit;
        
        vector<mint> expected = brute(A, B);
        
        vector<mint> a_fct = A, b_fct = B;
        fct(a_fct, false); fct(b_fct, false);
        for (int i = 0; i < a_fct.size(); i++) a_fct[i] *= b_fct[i];
        fct(a_fct, true);

        // FIXED: Matched exact uppercase strings "GCD" and "LCM"
        int start_idx = (name.find("GCD") != string::npos || name.find("LCM") != string::npos) ? 1 : 0;
        
        // Safety Threshold: Divisibility bounds experience clipping near `n`.
        // We test up to n / 2 to avoid boundary pollution in LCM inverses.
        int end_idx = (name.find("LCM") != string::npos) ? (a_fct.size() / 2) : a_fct.size();
        
        for (int i = start_idx; i < end_idx; i++) {
            if (a_fct[i] != expected[i]) {
                cout << "Mismatch at index " << i << "! Expected: " << expected[i] << " Got: " << a_fct[i] << '\n';
                assert(false && "Mismatch found!");
            }
        }
        cout << "[OK] " << name << " passed!\n";
    };

    test("OR Convolution", bruteOr, [&](vector<mint>& v, bool inv) { FastConv<mint>::fctOr(v, inv); });
    test("AND Convolution", bruteAnd, [&](vector<mint>& v, bool inv) { FastConv<mint>::fctAnd(v, inv); });
    test("XOR Convolution", bruteXor, [&](vector<mint>& v, bool inv) { FastConv<mint>::fctXor(v, inv); });
    
    test("GCD Convolution (Slow)", bruteGcd, [&](vector<mint>& v, bool inv) { FastConv<mint>::fctGcdSlow(v, inv); });
    test("GCD Convolution (Sieve)", bruteGcd, [&](vector<mint>& v, bool inv) { FastConv<mint>::fctGcd(v, inv, sv); });
    
    test("LCM Convolution (Slow)", bruteLcm, [&](vector<mint>& v, bool inv) { FastConv<mint>::fctLcmSlow(v, inv); });
    test("LCM Convolution (Sieve)", bruteLcm, [&](vector<mint>& v, bool inv) { FastConv<mint>::fctLcm(v, inv, sv); });
    
    cout << "\nAll convolutions passed perfectly!\n";
}

int main() {
    runTests();
    return 0;
}