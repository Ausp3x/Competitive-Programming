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
    int w, l;
    cin >> w >> l;
    vector<int> A(w + 1);
    for (int i = 1; i < w; i++)
        cin >> A[i];
    A[w] = INF32;

    int j = 0;
    vector<int> B(w + 1);
    B[0] = INF32;
    for (int i = 0; i < w; i++) {
        j = max(j, i + 1);
        while (j <= w && j - i <= l && B[i] > 0) {
            int m = min(B[i], A[j]);
            A[j] -= m;
            B[i] -= m;
            B[j] += m;

            if (A[j] == 0)
                j++;
        }

        // for (int x : B)
        //     cout << x << ' ';
        // cout << endl;
    }

    cout << B[w] << endl;


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