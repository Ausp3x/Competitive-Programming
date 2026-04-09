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

vector<vector<string>> S = {
    {}, {}, {},
    {"ABC", "ACB", "BAC", "BCA", "CAB", "CBA"},
    {".ABC", ".ACB", ".BAC", ".BCA", ".CAB", ".CBA", "A.BC", "A.CB", "AB.C", "ABC.", "AC.B", "ACB.", "B.AC", "B.CA", "BA.C", "BAC.", "BC.A", "BCA.", "C.AB", "C.BA", "CA.B", "CAB.", "CB.A", "CBA."},
    {"..ABC", "..ACB", "..BAC", "..BCA", "..CAB", "..CBA", ".A.BC", ".A.CB", ".AB.C", ".ABC.", ".AC.B", ".ACB.", ".B.AC", ".B.CA", ".BA.C", ".BAC.", ".BC.A", ".BCA.", ".C.AB", ".C.BA", ".CA.B", ".CAB.", ".CB.A", ".CBA.", "A..BC", "A..CB", "A.B.C", "A.BC.", "A.C.B", "A.CB.", "AB..C", "AB.C.", "ABC..", "AC..B", "AC.B.", "ACB..", "B..AC", "B..CA", "B.A.C", "B.AC.", "B.C.A", "B.CA.", "BA..C", "BA.C.", "BAC..", "BC..A", "BC.A.", "BCA..", "C..AB", "C..BA", "C.A.B", "C.AB.", "C.B.A", "C.BA.", "CA..B", "CA.B.", "CAB..", "CB..A", "CB.A.", "CBA.."}
};

void solve() {
    int n;
    cin >> n;
    string R;
    cin >> R;
    string C;
    cin >> C;
    
    bool chk = false;
    vector<int> used(n);
    vector<string> grid;

    auto isValid = [&](string s) -> bool {
        for (int i = 0; i < n; i++)
            if (s[i] != '.')
                if (used[i] & (1 << (s[i] - 'A')))
                    return false;

        return true;
    };

    auto getRC = [&]() -> pair<string, string> {
        assert(grid.size() == n);
        
        string r;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] != '.') {
                    r += grid[i][j];
                    break;
                }

        string c;
        for (int j = 0; j < n; j++)
            for (int i = 0; i < n; i++)
                if (grid[i][j] != '.') {
                    c += grid[i][j];
                    break;
                }

        // cout << r << ' ' << c << endl;

        return {r, c};
    };

    auto calc = [&](auto &&calc) {
        if (grid.size() == n) {
            auto [r, c] = getRC();
            if (r == R && c == C) {
                chk = true;
                cout << "Yes" << endl;
                for (int i = 0; i < n; i++)
                    cout << grid[i] << endl;
                // cout << endl;
            }

            return;
        }

        for (auto s : S[n]) {
            if (chk)
                return;

            if (!isValid(s))
                continue;
            
            for (int i = 0; i < n; i++)
                if (s[i] != '.')
                    used[i] += (1 << (s[i] - 'A'));
            grid.push_back(s);
            
            calc(calc);

            for (int i = 0; i < n; i++)
                if (s[i] != '.')
                    used[i] -= (1 << (s[i] - 'A'));
            grid.pop_back();
        }

        return;
    };

    calc(calc);

    if (!chk)
        cout << "No" << endl;

    return;
}   

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // string s = "ABC";
    // sort(s.begin(), s.end());
    // do {
    //     // cout << s << endl;
    //     cout << "\"" << s << "\", ";
    // } while (next_permutation(s.begin(), s.end()));
    // cout << endl;

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}