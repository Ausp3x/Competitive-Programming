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
    lng t;
    cin >> n >> t;
    vector<lng> A(n);
    for (lng &a : A)
        cin >> a;

    if (n <= 20) {
        lng ans = 0;
        for (int i = 0; i < (1 << n); i++) {
            lng sum = 0;
            for (int j = 0; j < n; j++)
                if (i & (1 << j))
                    sum += A[j];

            // cout << sum << endl;

            if (sum <= t && sum > ans) 
                ans = sum;
        }

        cout << ans << endl;

        return;
    }

    vector<lng> S1;
    for (int i = 0; i < (1 << 20); i++) {
        lng sum = 0;
        for (int j = 0; j < 20; j++)
            if (i & (1 << j))
                sum += A[j];

        if (sum <= t)
            S1.push_back(sum);
    }

    sort(S1.begin(), S1.end());

    vector<lng> S2;
    for (int i = 0; i < (1 << (n - 20)); i++) {
        lng sum = 0;
        for (int j = 0; j < n - 20; j++)
            if (i & (1 << j))
                sum += A[j + 20];

        if (sum <= t)
            S2.push_back(sum);
    }

    sort(S2.begin(), S2.end());

    int j = S2.size() - 1;
    lng ans = 0;
    for (int i = 0; i < S1.size(); i++) {
        while (j > 0 && S1[i] + S2[j] > t)
            j--;

        if (S1[i] + S2[j] <= t) 
            ans = max(ans, S1[i] + S2[j]);
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