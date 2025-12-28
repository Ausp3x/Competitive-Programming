// 人外有人，天外有天
// author: Ausp3x
// g++ -Wall -Wextra -o <name> <name>.cpp
// <name>.exe < in > out

#pragma GCC optimize("O3, fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fi first
#define se second
#define pb push_back
// #define DEBUG
using lng = long long;
using lll = __int128;
template<typename T> 
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T> // lower_bound and upper_bound are broken
using indexed_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

int const INF32 = 0x3f3f3f3f;
lng const INF64 = 0x3f3f3f3f3f3f3f3f;

void solve() {
    vector<lng> R(2);
    vector<lng> C(2);
    cin >> R[0] >> C[0] >> R[1] >> C[1];
    lng n, m, l;
    cin >> n >> m >> l;
    vector<pair<char, lng>> S(m);
    for (auto &[s, a] : S)
        cin >> s >> a;
    vector<pair<char, lng>> T(l);
    for (auto &[t, b] : T)
        cin >> t >> b;

    lng cur = 0;
    priority_queue<tuple<lng, int, char, lng>, vector<tuple<lng, int, char, lng>>, greater<tuple<lng, int, char, lng>>> pq;
    for (int i = 0; i < m; i++) {
        if (i > 0) 
            cur += S[i - 1].se;
        pq.push({cur, 0, S[i].fi, S[i].se});
    }
    cur = 0;
    for (int i = 0; i < l; i++) {
        if (i > 0)
            cur += T[i - 1].se;
        pq.push({cur, 1, T[i].fi, T[i].se});
    }

    //*
    lng ans = 0, timer = 0;
    vector<char> M(2);
    vector<lng> Q(2);
    while (!pq.empty()) {
        while (!pq.empty()) {
            auto [t, p, m, q] = pq.top();
            if (t != timer) {
                assert(t > timer);
                break; 
            }
            pq.pop();

            M[p] = m;
            Q[p] = q;
        }

        // cout << M[0] << ' ' << Q[0] << ' ' << M[1] << ' ' << Q[1] << endl;

        lng q = min(Q[0], Q[1]);
        
        // Same direction
        if (M[0] == M[1]) { 
            if (R[0] == R[1] & C[0] == C[1])
                ans += q;

            if (M[0] == 'U') {
                R[0] -= q;
                R[1] -= q;
            } else if (M[0] == 'D') {
                R[0] += q;
                R[1] += q;
            } else if (M[0] == 'L') {
                C[0] -= q;
                C[1] -= q;
            } else if (M[0] == 'R') {
                C[0] += q;
                C[1] += q;
            }
        }

        // Opposite direction
        if (M[0] == 'U' && M[1] == 'D') {
            if (C[0] == C[1] && R[0] > R[1] && (R[0] - R[1]) % 2 == 0 && 2 * q >= (R[0] - R[1]))
                ans++;

            R[0] -= q;
            R[1] += q;
        }
        if (M[0] == 'D' && M[1] == 'U') {
            if (C[0] == C[1] && R[1] > R[0] && (R[1] - R[0]) % 2 == 0 && 2 * q >= (R[1] - R[0]))
                ans++;

            R[0] += q;
            R[1] -= q;
        }
        if (M[0] == 'L' && M[1] == 'R') {
            if (R[0] == R[1] && C[0] > C[1] && (C[0] - C[1]) % 2 == 0 && 2 * q >= (C[0] - C[1]))
                ans++;

            C[0] -= q;
            C[1] += q;
        }
        if (M[0] == 'R' && M[1] == 'L') {
            if (R[0] == R[1] && C[1] > C[0] && (C[1] - C[0]) % 2 == 0 && 2 * q >= (C[1] - C[0]))
                ans++;

            C[0] += q;
            C[1] -= q;
        }

        // Perpendicular direction
        if (M[0] == 'U') {
            if (M[1] == 'L') {
                if (C[1] > C[0] && R[0] + C[0] - C[1] == R[1] && q >= C[1] - C[0])
                    ans++;

                R[0] -= q;
                C[1] -= q;
            } else if (M[1] == 'R') {
                if (C[0] > C[1] && R[0] + C[1] - C[0] == R[1] && q >= C[0] - C[1])
                    ans++;

                R[0] -= q;
                C[1] += q;
            }
        }
        if (M[0] == 'D') {
            if (M[1] == 'L') {
                if (C[1] > C[0] && R[0] - C[0] + C[1] == R[1] && q >= C[1] - C[0])
                    ans++;

                R[0] += q;
                C[1] -= q;
            } else if (M[1] == 'R') {
                if (C[0] > C[1] && R[0] - C[1] + C[0] == R[1] && q >= C[0] - C[1])
                    ans++;

                R[0] += q;
                C[1] += q;
            }
        }
        if (M[0] == 'L') {
            if (M[1] == 'U') {
                if (R[1] > R[0] && C[0] + R[0] - R[1] == C[1] && q >= R[1] - R[0])
                    ans++;

                C[0] -= q;
                R[1] -= q;
            } else if (M[1] == 'D') {
                if (R[0] > R[1] && C[0] + R[1] - R[0] == C[1] && q >= R[0] - R[1])
                    ans++;

                C[0] -= q;
                R[1] += q;
            }
        }
        if (M[0] == 'R') {
            if (M[1] == 'U') {
                if (R[1] > R[0] && C[0] - R[0] + R[1] == C[1] && q >= R[1] - R[0])
                    ans++;

                C[0] += q;
                R[1] -= q;
            } else if (M[1] == 'D') {
                if (R[0] > R[1] && C[0] - R[1] + R[0] == C[1] && q >= R[0] - R[1])
                    ans++;

                C[0] += q;
                R[1] += q;
            }
        }
        
        timer += q;
        Q[0] -= q;
        Q[1] -= q;
    }
    
    cout << ans << endl;
    //*/

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