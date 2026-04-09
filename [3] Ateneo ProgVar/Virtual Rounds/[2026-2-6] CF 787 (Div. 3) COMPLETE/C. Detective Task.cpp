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
    string s;
    cin >> s;

    int n = s.size();
    if (n == 1) {
        cout << 1 << endl;
        return;
    }

    map<char, int> I = {{'0', 0}, {'1', 1}, {'?', 2}};

    vector prf(n, vector<int>(3));
    prf[0][I[s[0]]]++;
    for (int i = 1; i < n; i++) {
        prf[i] = prf[i - 1];
        prf[i][I[s[i]]]++;
    }

    vector suf(n, vector<int>(3));
    suf[n - 1][I[s[n - 1]]]++;
    for (int i = n - 2; i >= 0; i--) {
        suf[i] = suf[i + 1];
        suf[i][I[s[i]]]++;
    }

    int ans = suf[1][1] == 0;
    for (int i = 1; i < n - 1; i++) {
        ans += (prf[i - 1][0] == 0) && (suf[i + 1][1] == 0);
    }
    ans += prf[n - 2][0] == 0;

    cout << ans << endl;

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