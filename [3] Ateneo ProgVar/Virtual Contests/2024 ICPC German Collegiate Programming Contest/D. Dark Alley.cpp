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
typedef long long    lng;
typedef __int128     lll;
template<class T> 
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T> // lower_bound and upper_bound are broken
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
int ModInt::MOD = 1'000'000'007;

int N = 200'001;

void solve() {
    int n, q;
    cin >> n >> q;
    float p_o;
    cin >> p_o;
    ModInt p = int(p_o * 1'000'000);
    p /= 1'000'000;

    ModInt s = 1 - p;
    vector<ModInt> s_pows(N);
    s_pows[0] = 1;
    for (int i = 1; i < N; i++)
        s_pows[i] = s_pows[i - 1] * s;

    // for (auto x : r_pows) 
    //     cout << x << ' ';
    // cout << endl;

    int cnt = 630, len = 318;
    vector<ModInt> B(N), L(N), R(N);
    while (q--) {
        char c;
        cin >> c;

        if (c == '+') {
            ModInt b;
            int x;
            cin >> b >> x;

            B[x] += b;

            int l = (x / len) * len, r = l + len - 1;
            L[l] = B[l];
            for (int i = l + 1; i <= r; i++)
                L[i] = L[i - 1] * s + B[i];
            R[r] = B[r];
            for (int i = r - 1; i >= l; i--)
                R[i] = R[i + 1] * s + B[i];
        } else if (c == '-') {
            ModInt b;
            int x;
            cin >> b >> x;

            B[x] -= b;

            int l = (x / len) * len, r = l + len - 1;
            L[l] = B[l];
            for (int i = l + 1; i <= r; i++)
                L[i] = L[i - 1] * s + B[i];
            R[r] = B[r];
            for (int i = r - 1; i >= l; i--)
                R[i] = R[i + 1] * s + B[i];
        } else if (c == '?') {
            int x;
            cin >> x;

            ModInt ans = 0;
            for (int i = 0; i < cnt; i++) {
                int l = i * len, r = l + len - 1;
                if (r < x) {
                    ans += L[r] * s_pows[x - r];
                } else if (l <= x && x <= r) {
                    if (l < x) 
                        ans += L[x - 1] * s;
                    ans += B[x];
                    if (x < r)
                        ans += R[x + 1] * s;
                } else if (x < l) {
                    ans += R[l] * s_pows[l - x];
                }
            }

            cout << ans << endl;
        }

        // for (int i = 0; i <= n; i++) 
        //     cout << B[i] << ' ';
        // cout << endl;
        // for (int i = 0; i <= n; i++) 
        //     cout << L[i] << ' ';
        // cout << endl;
        // for (int i = 0; i <= n; i++) 
        //     cout << R[i] << ' ';
        // cout << endl << endl;
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