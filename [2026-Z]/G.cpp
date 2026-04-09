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

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    
    mint ans = 0;
    mint sum_a = 0, sum_c = 0, sum_p = 0, cnt = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '+' || s[i] == '*')
            continue;
        
        int d = s[i] - '0';
        if (i == 0 || s[i - 1] >= '0') {
            sum_a = 10 * sum_a + sum_p * d + d;
            sum_p++;
        } else if (s[i - 1] == '+') {
            sum_c += sum_a;
            sum_a = cnt * d + d;
            sum_p = cnt + 1;
        } else if (s[i - 1] == '*') {
            sum_p = sum_a + 1;
            sum_a = sum_a * d + d;
        }

        cnt++;
        ans += sum_a + sum_c;
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