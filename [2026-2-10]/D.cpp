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

void solve() {
    int n;
    cin >> n;
    lng a_sum = 0;
    vector<lng> A(n);
    for (lng &a : A) {
        cin >> a;
        a_sum += a;
    }
    int m;
    cin >> m;
    lng b_sum = 0;
    vector<lng> B(m);
    for (lng &b : B) {
        cin >> b;
        b_sum += b;
    }

    lng ans = abs(b_sum - a_sum);    
    int k = 0;
    vector<pair<int, int>> V;
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++) 
            if (abs(b_sum - a_sum + 2 * A[i] - 2 * B[j]) < ans) {
                ans = abs(b_sum - a_sum + 2 * A[i] - 2 * B[j]);
                k = 1;
                V.clear();
                V.pb({i + 1, j + 1});
            }

    auto print = [&]() -> void {
        cout << ans << endl;
        cout << k << endl;
        for (auto &[a, b] : V)
            cout << a << ' ' << b << endl;
        
        return;
    };

    if (n == 1 || m == 1) {
        print();
        return;
    }

    vector<tuple<lng, lng, lng>> AP;
    AP.pb({-INF64, 0, 0});
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) 
            AP.pb({2 * (A[i] + A[j]), i + 1, j + 1});
    AP.pb({INF64, 0, 0});

    sort(AP.begin(), AP.end());

    vector<tuple<lng, lng, lng>> BP;
    BP.pb({-INF64, 0, 0});
    for (int i = 0; i < m; i++)
        for (int j = i + 1; j < m; j++)
            BP.pb({-2 * (B[i] + B[j]), i + 1, j + 1});
    BP.pb({INF64, 0, 0});
    
    sort(BP.begin(), BP.end());

    // for (auto &[s, a, b] : AP) 
    //     cout << s << ' ' << a << ' ' << b << endl;
    // cout << endl;
    // for (auto &[s, a, b] : BP) 
    //     cout << s << ' ' << a << ' ' << b << endl;
    // cout << endl;

    auto binSearch = [&](lng cur) -> pair<int, int> {
        int l = 0, r = BP.size() - 1;
        while (r - l > 1) {
            int md = (l + r) / 2;

            if (get<0>(BP[md]) >= cur)
                r = md;
            else
                l = md;
        }

        return {l, r};
    };

    for (auto [as, a1, a2] : AP) {
        lng cur = -(b_sum - a_sum + as);

        auto [l, r] = binSearch(cur);
        auto [bsl, b1l, b2l] = BP[l];
        auto [bsr, b1r, b2r] = BP[r];

        if (b1l != 0 && abs(-cur + bsl) < ans) {
            ans = abs(-cur + bsl);
            k = 2;
            V.clear();
            V.pb({a1, b1l});
            V.pb({a2, b2l});
        } 

        if (b1r != 0 && abs(-cur + bsr) < ans) {
            ans = abs(-cur + bsr);
            k = 2;
            V.clear();
            V.pb({a1, b1r});
            V.pb({a2, b2r});
        } 
    }

    print();

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