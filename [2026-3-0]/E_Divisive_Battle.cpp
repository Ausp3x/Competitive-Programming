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

struct SieveOfErath {
    int n;
    vector<bool> is_prime;
    vector<lng> factors, phi;

    // T: O(nloglog(n)), M: O(n)
    SieveOfErath(int N) {
        n = N;
        is_prime.clear();
        is_prime.resize(n + 1, true);
        factors.clear();
        factors.resize(n + 1, 1);

        is_prime[0] = false;
        is_prime[1] = false;
        for (lng i = 2; i <= n; i++) {
            if (!is_prime[i]) {
                continue;}

            factors[i] = i;
            for (lng j = i * i; j <= n; j += i) {
                is_prime[j] = false;
                factors[j] = i;
            }
        }
    }

    // T: O(nloglog(n)), M: O(n)
    void runPhi(int N) {
        n = N;
        phi.clear();
        phi.resize(n + 1);
        iota(phi.begin(), phi.end(), 0);

        for (lng i = 2; i <= n; i++) {
            if (phi[i] < i) {
                continue;}
            
            for (lng j = i; j <= n; j += i) {
                phi[j] -= phi[j] / i;}
        }

    }

    // T: O(log(n)), M: O(n)
    vector<lng> getFac(lng a) {
        assert(a <= n);

        vector<lng> res;
        while (a > 1) {
            res.pb(factors[a]);
            a /= factors[a];
        }

        sort(res.begin(), res.end());

        return res;
    }
};

int N = 1'000'005;
SieveOfErath se(N);

void solve() {
    int n;
    cin >> n;
    vector<int> A(n); 
    for (int &a : A)
        cin >> a;

    vector<int> B = A;
    sort(B.begin(), B.end());

    if (A == B) {
        cout << "Bob" << endl;
        return;
    }

    vector<lng> C;
    for (int a : A) {
        if (a == 1) {
            C.pb(a);
            continue;
        }
        
        vector<lng> f = se.getFac(a);
        if (f[0] != f.back()) {
            cout << "Alice" << endl;
            return;
        }

        C.insert(C.end(), f.begin(), f.end());
    }

    vector<lng> D = C;
    sort(D.begin(), D.end());

    cout << (C == D ? "Bob" : "Alice") << endl;

    return;
}   

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // for (int x : se.getFac(100)) 
    //     cout << x << ' ';
    // cout << endl;

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}