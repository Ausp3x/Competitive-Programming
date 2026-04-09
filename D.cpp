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

int N = 1'000'000;
// int N = 100;

void solve() {
    int n;
    lng x, y;
    cin >> n >> x >> y;
    vector<lng> A(N + 1), S(N + 1);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;

        A[a]++;
        S[a] += N - a;
    }

    vector<lng> C(N + 1);
    C[0] = A[0];
    for (int i = 1; i <= N; i++) {
        C[i] = C[i - 1] + A[i];
        S[i] += S[i - 1];
    }

    // for (lng x : C)
    //     cout << x << ' ';
    // cout << endl;

    // for (lng x : S)
    //     cout << x << ' ';
    // cout << endl;

    int d = x / y;
    lng ans = INF64;
    for (int i = 2; i <= N; i++) {
        lng cur = 0;
        for (int j = 1; j <= N; j += i) {
            int r = min(j + i - 1, N);
            int l = max(j + i - 1 - d, j);
            int k = i - 1 - (N - j);

            if (l > r) {
                cur += x * (C[r] - C[j - 1]);
            } else {
                cur += y * (S[r] - S[l - 1]);
                cur += y * k * (C[r] - C[l - 1]);
                cur += x * (C[l - 1] - C[j - 1]);
            }
        }

        // cout << i << ' ' << cur << endl;
        
        ans = min(ans, cur);
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