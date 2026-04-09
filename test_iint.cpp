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

        return *this = divMod(*this, o).first; 
    }
    
    InfInt &operator%=(const InfInt &o) { 
        if (is_inf) {
            return *this = 0;}

        if (o.is_inf) {
            return *this;}

        return *this = divMod(*this, o).second; 
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
    
    friend InfInt operator*(InfInt a, const InfInt &b) { 
        return a *= b; 
    }

    friend InfInt operator/(InfInt a, lng b) { 
        return a /= b; 
    }
    
    friend InfInt operator/(InfInt a, const InfInt &b) { 
        return a /= b; 
    }

    friend lng operator%(InfInt a, lng b) { 
        return a %= b; 
    }

    friend InfInt operator%(InfInt a, const InfInt &b) { 
        return a %= b; 
    }

    friend InfInt abs(InfInt a) { 
        a.sgn = 1;

        return a; 
    }

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
    
    friend InfInt sqrt(const InfInt &a0) {
        assert(a0.sgn == 1 && "InfInt sqrt error: Cannot compute square root of negative number.");

        if (a0.isNil()) {
            return 0;}

        if (a0.is_inf) {
            return a0;}

        InfInt a = a0;
        while (a.n.empty() || a.n.size() % 2 == 1) {
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
        while (a.n.empty() || a.n.size() % 2 == 1) { 
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

    InfInt &operator<<=(int s) { 
        return *this = *this << s; 
    }
    
    InfInt &operator>>=(int s) { 
        return *this = *this >> s; 
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

int main() {
    // Fast I/O is critical for stress testing massive I/O pipelines
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string op, a_str, b_str;
    while (cin >> op) {
        if (op == "add") { cin >> a_str >> b_str; cout << (iint(a_str) + iint(b_str)) << endl; }
        else if (op == "sub") { cin >> a_str >> b_str; cout << (iint(a_str) - iint(b_str)) << endl; }
        else if (op == "mul") { cin >> a_str >> b_str; cout << (iint(a_str) * iint(b_str)) << endl; }
        else if (op == "div") { cin >> a_str >> b_str; cout << (iint(a_str) / iint(b_str)) << endl; }
        else if (op == "mod") { cin >> a_str >> b_str; cout << (iint(a_str) % iint(b_str)) << endl; }
        else if (op == "pow") { cin >> a_str >> b_str; cout << pow(iint(a_str), stoll(b_str)) << endl; }
        else if (op == "sqrt") { cin >> a_str; cout << sqrt(iint(a_str)) << endl; }
        else if (op == "shl") { cin >> a_str >> b_str; cout << (iint(a_str) << stoi(b_str)) << endl; }
        else if (op == "shr") { cin >> a_str >> b_str; cout << (iint(a_str) >> stoi(b_str)) << endl; }
        else if (op == "and") { cin >> a_str >> b_str; cout << (iint(a_str) & iint(b_str)) << endl; }
        else if (op == "or")  { cin >> a_str >> b_str; cout << (iint(a_str) | iint(b_str)) << endl; }
        else if (op == "xor") { cin >> a_str >> b_str; cout << (iint(a_str) ^ iint(b_str)) << endl; }
        else if (op == "bin") { cin >> a_str; cout << bin(iint(a_str)) << endl; }
        else if (op == "ctz") { cin >> a_str; cout << ctz(iint(a_str)) << endl; }
        else if (op == "popcnt") { cin >> a_str; cout << popcount(iint(a_str)) << endl; }
        else if (op == "exgcd") { 
            cin >> a_str >> b_str; 
            iint x, y; 
            iint g = exGcd(iint(a_str), iint(b_str), x, y);
            cout << g << " " << x << " " << y << endl; 
        }
        else if (op == "inv") { cin >> a_str >> b_str; cout << inv(iint(a_str), iint(b_str)) << endl; }
    }
    return 0;
}