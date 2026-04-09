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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> A(n);
    for (int &a : A)
        cin >> a;

    vector<int> L(n);
    stack<int> s;
    for (int i = 0; i < n; i++) {
        while (!s.empty() && A[s.top()] > A[i])
            s.pop();

        if (s.empty()) {
            L[i] = -1;
            s.push(i);
            continue;
        }

        L[i] = s.top();
        s.push(i);
    }

    while (!s.empty())
        s.pop();

    vector<int> R(n);
    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty() && A[s.top()] >= A[i])
            s.pop();

        if (s.empty()) {
            R[i] = n;
            s.push(i);
            continue;
        }

        R[i] = s.top();
        s.push(i);
    }

    mint S = 0;
    for (int i = 0; i < n; i++) {
        S += mint(1ll * (i + 1) * (n - i)) / A[i];}

    vector<pair<int, lng>> V(n);
    for (int i = 0; i < n; i++)
        V[i] = {A[i], 1ll * (i - L[i]) * (R[i] - i)};

    sort(V.begin(), V.end());

    vector<int> B;
    vector<mint> prf = {0}; 
    vector<mint> prf_b = {0}; 
    vector<mint> prf_invb = {0};

    for (int i = 0; i < n; ) {
        int j = i;
        mint cnt = 0;
        while (j < n && V[j].fi == V[i].fi) {
            cnt += V[j].se;
            j++;
        }

        int b = V[i].fi;
        B.pb(b);
        prf.pb(prf.back() + cnt);
        prf_b.pb(prf_b.back() + cnt * b);
        prf_invb.pb(prf_invb.back() + cnt / b);

        i = j;
    }

    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;

        int j = upper_bound(B.begin(), B.end(), k + 1) - B.begin();
        mint ans = S;
        ans += (k + 2) * prf[j];
        ans -= prf_b[j];
        ans -= prf_invb[j];
        ans += k * (prf_invb.back() - prf_invb[j]);

        cout << ans << endl;
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