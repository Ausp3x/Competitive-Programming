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

vector<pair<int, int>> di_dj = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
vector<int> points = {0, 0, 0, 1, 1, 2, 3, 5, 11};  

void solve() {
    int n;
    cin >> n;
    set<string> valid_words;
    set<string> valid_prefs = {""};
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        valid_words.insert(s);
        for (int i = 1; i <= s.size(); i++)
            valid_prefs.insert(s.substr(0, i));
    }
    
    int q;
    cin >> q;
    vector<vector<char>> board(6, vector<char>(6, '.'));
    while (q--) {
        for (int i = 1; i <= 4; i++)
            for (int j = 1; j <= 4; j++)
                cin >> board[i][j];

        set<string> unique_words;
        string longest_word = "";
        for (int i = 1; i <= 4; i++)
            for (int j = 1; j <= 4; j++) {
                string cur_word = "";
                vector<vector<bool>> vst(6, vector<bool>(6));
                
                auto dfs = [&](int i, int j, auto &&dfs) -> void {
                    cur_word += board[i][j];
                    if (cur_word.size() > 8 || !valid_prefs.contains(cur_word)) {
                        cur_word.pop_back();
                        return;
                    }

                    if (valid_words.contains(cur_word)) {
                        unique_words.insert(cur_word);
                        if (cur_word.size() > longest_word.size() || 
                            (cur_word.size() == longest_word.size() && cur_word < longest_word)) 
                            longest_word = cur_word;
                    }

                    for (auto [di, dj] : di_dj) {
                        if (vst[i + di][j + dj] || board[i + di][j + dj] == '.')
                            continue;
                        
                        vst[i + di][j + dj] = true;
                        dfs(i + di, j + dj, dfs);
                        vst[i + di][j + dj] = false;
                    }
                    cur_word.pop_back();
                };
                
                vst[i][j] = true;
                dfs(i, j, dfs);
            }

        int max_score = 0;
        for (auto word : unique_words) 
            max_score += points[word.size()];

        cout << max_score << ' ' << longest_word << ' ' << unique_words.size() << endl;
    }

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