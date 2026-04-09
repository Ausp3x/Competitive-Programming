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
    lng h, w;
    cin >> h >> w;
    string s;
    cin >> s;

    // d, r;
    pair<lng, lng> req = {h - 1, w - 1};
    for (char c : s)
        if (c == 'D')
            req.fi--;
        else if (c == 'R')
            req.se--;

    // cout << req.fi << ' ' << req.se << endl;

    int d = req.fi, r = req.se;
    pair<lng, lng> I = {0, 0};
    vector<lng> CH(w, INF64);
    CH[0] = 0;
    for (char c : s) {
        if (c == 'D') {
            I.fi++;
        } else if (c == 'R') {
            I.se++;
        } else if (c == '?') {
            if (r > 0) {
                I.se++;
                r--;
            } else if (d > 0) {
                I.fi++;
                d--;
            }
        }
        CH[I.se] = min(CH[I.se], I.fi);
    }

    // for (int x : CH)
    //     cout << x << ' ';
    // cout << endl;

    d = req.fi; 
    r = req.se;
    I = {0, 0};
    vector<lng> CL(w, -1);
    CL[0] = 0;
    for (char c : s) {
        if (c == 'D') {
            I.fi++;
        } else if (c == 'R') {
            I.se++;
        } else if (c == '?') {
            if (d > 0) {
                I.fi++;
                d--;
            } else if (r > 0) {
                I.se++;
                r--;
            }
        }
        CL[I.se] = max(CL[I.se], I.fi);
    }

    // for (int x : CL)
    //     cout << x << ' ';
    // cout << endl;

    lng ans = 0;
    for (int i = 0; i < w; i++)
        ans += abs(CH[i] - CL[i]) + 1;

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