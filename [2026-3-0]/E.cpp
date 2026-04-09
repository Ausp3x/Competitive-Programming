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

struct Random {
    mt19937    rng_int;
    mt19937_64 rng_lng; 

    Random(): 
        rng_int(random_device{}()),
        rng_lng(random_device{}()) {}

    int randInt(int l, int r) {
        return uniform_int_distribution<int>(l, r)(rng_int);
    }

    lng randLng(lng l, lng r) {
        return uniform_int_distribution<lng>(l, r)(rng_lng);
    }
};

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
    /*
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
                res.push_back(res[j] * p);}}
    }

    sort(res.begin(), res.end());

    return res;
}

void solve() {
    lng a, b, c, d;
    cin >> a >> b >> c >> d;
    
    lng p = a * b;
    a++; b++;
    vector<lng> F = getAllFac(p, 1);
    for (lng f1 : F) {
        lng f2 = p / f1;

        if (f1 > c || f2 > d)
            continue;

        // cout << f1 << ' ' << f2 << endl;

        f1 = (a + f1 - 1) / f1 * f1; 
        f2 = (b + f2 - 1) / f2 * f2;
    
        if (f1 > c || f2 > d)
            continue;

        // cout << a << ' ' << c << ' ' << b << ' ' << d << ' ';
        cout << f1 << ' ' << f2 << endl;
        return;
    }

    cout << -1 << ' ' << -1 << endl;
    
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