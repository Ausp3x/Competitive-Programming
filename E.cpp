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

void solve() {
    int n;
    cin >> n;
    vector<int> A(n);
    for (int &a : A)
        cin >> a;

    map<int, int> M;
    for (int a : A) {
        auto pf = getPrimeFacSlow(a);

        map<int, int> C;
        for (int p : pf)
            C[p]++;

        for (auto &[p, c] : C)
            M[p] |= 1 << c;
    }

    map<int, int> SG;
    
    auto calc = [&](int cur, auto &&calc) -> void {
        if (SG.find(cur) != SG.end())
            return;

        int mex = 0;
        for (int i = 1; i < 30; i++) {
            if (cur < (1 << i)) 
                continue;

            int nxt = (cur >> i) | (cur & ((1 << i) - 1));
            
            calc(nxt, calc);
            
            mex |= 1 << SG[nxt];
        }

        while (mex & (1 << SG[cur]))
            SG[cur]++;

        return;
    };

    int ans = 0;
    for (auto &[p, m] : M) { 
        SG[1] = 0;
    
        calc(m, calc);
    
        ans ^= SG[m];
    }

    cout << (ans > 0 ? "Mojtaba" : "Arpa") << endl;

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