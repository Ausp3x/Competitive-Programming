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
vector cnts(N, vector<int>(11));

int S(int x) {
    int y = x, sum = 0;
    while (y > 0) {
        cnts[x][y % 10]++;
        sum += y % 10;
        y /= 10;
    }

    return sum;
}

void solve() {
    string s;
    cin >> s;

    if (s.size() == 1) {
        cout << s << endl;
        return;
    }
    
    vector<int> C(10);
    for (char c : s)
        C[c - '0']++;

    for (int i = 0; i < N; i++) {
        bool chk = true;
        vector<int> D = C;
        for (int j = 0; j < 10; j++) {
            D[j] = C[j] - cnts[i][j];
            chk &= D[j] >= 0;
        }

        if (!chk)
            continue;

        int sum = 0;
        for (int j = 0; j < 10; j++)
            sum += D[j] * j;
        
        if (sum != i)
            continue;

        for (int j = 9; j >= 0; j--)
            cout << string(D[j], char('0' + j));
        int k = i;
        while (k > 0) {
            cout << k;
            k = cnts[k][10];
        }
        cout << endl;
        
        return;
    }

    return;
}   

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 1; i < 10; i++) {
        cnts[i][i] = 1;}
    for (int i = 10; i < N; i++) {
        int j = S(i);
        for (int k = 0; k < 10; k++)
            cnts[i][k] += cnts[j][k];
        cnts[i][10] = j;
    }

    // for (int i = 75; i < 76; i++) {
    //     for (int j = 0; j < 10; j++)
    //         cout << cnts[i][j] << ' ';
    //     cout << endl;
    // }

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}