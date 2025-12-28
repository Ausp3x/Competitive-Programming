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

vector<int> p2 = {1, 2, 4, 8, 16, 32};
vector<int> p6 = {1, 6, 36, 216, 1296, 7776};
vector<vector<int>> I(32, vector<int>(5));

void solve() {
    vector<int> A(6);
    for (int &a : A) 
        cin >> a;

    auto chk = [&](int cur, int prv) -> bool {
        for (int i = 0; i < 5; i++) 
            if (cur / p2[i] % 2 > prv / p2[i] % 2)
                return false;

        return true;
    };

    vector<vector<vector<double>>> E(4, vector<vector<double>>(7776, vector<double>(32)));
    for (int msk = 0; msk < 7776; msk++) {
        map<int, int> cnts;
        for (int i = 0; i < 5; i++)
            cnts[A[msk / p6[i] % 6]]++;

        for (int i = 0; i < 32; i++)
            for (auto [a, c] : cnts)
                E[3][msk][i] = max(E[3][msk][i], double(1) * c * a); 
    }
    for (int k = 2; k >= 1; k--) {
        vector<vector<double>> S(7776, vector<double>(32));
        for (int rol = 0; rol < 32; rol++) {
            for (int msk = 0; msk < 7776; msk++) {
                int fixed_msk = 0;
                for (int i = 0; i < 5; i++)
                    if (!I[rol][i]) 
                        fixed_msk += msk / p6[i] % 6 * p6[i];
    
                S[fixed_msk][rol] += E[k + 1][msk][rol];
            }

            for (int msk = 0; msk < 7776; msk++) {
                int fixed_msk = 0;
                for (int i = 0; i < 5; i++)
                    if (!I[rol][i]) 
                        fixed_msk += msk / p6[i] % 6 * p6[i];

                if (msk == fixed_msk)
                    continue;
                
                S[msk][rol] = S[fixed_msk][rol];
            }
        }

        for (int msk = 0; msk < 7776; msk++)
            for (int prv_rol = 0; prv_rol < 32; prv_rol++) 
                for (int rol = 0; rol < 32; rol++)
                    if (chk(rol, prv_rol)) 
                        E[k][msk][prv_rol] = max(E[k][msk][prv_rol], S[msk][rol] / p6[accumulate(I[rol].begin(), I[rol].end(), 0)]);
    }
    for (int msk = 0; msk < 7776; msk++) 
        E[0][0][31] += E[1][msk][31];

    cout << setprecision(20) << E[0][0][31] / 7776 << endl;

    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 0; i < 32; i++) 
        for (int j = 0; j < 5; j++)
            if (i & (1 << j)) 
                I[i][j] = 1;

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}