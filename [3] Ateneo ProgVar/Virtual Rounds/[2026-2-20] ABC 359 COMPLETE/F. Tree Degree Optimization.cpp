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
    vector<lng> A(n);
    for (lng &a : A)
        cin >> a;

    sort(A.begin(), A.end(), greater<lng>());

    vector<lng> D(n, 2);
    D[0] = D[1] = 1;
    priority_queue<pair<lng, int>, vector<pair<lng, int>>, greater<pair<lng, int>>> pq;
    for (int i = 2; i < n; i++) 
        pq.push({(2 * D[i] + 1) * A[i], i});

    for (int i = 2; i < n; i++) {
        while (!pq.empty())
            if (pq.top().se <= i)
                pq.pop();
            else
                break;

        if (pq.empty())
            break;

        lng sub = (2 * D[i] - 1) * A[i];
        if (pq.top().fi >= sub)
            break;

        int j = pq.top().se;
        pq.pop();
        D[i]--;
        D[j]++;
        pq.push({(2 * D[j] + 1) * A[j], j});
    }

    lng ans = 0;
    for (int i = 0; i < n; i++)
        ans += (D[i] * D[i]) * A[i];

    // for (lng a : A)
    //     cout << a << ' ';
    // cout << endl;
    // for (lng d : D)
    //     cout << d << ' ';
    // cout << endl;

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