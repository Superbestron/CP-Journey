#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// For each character x, for each pair of x's, mark their antinodes down in a Hashmap.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string> grid;
    map<char, vector<ii>> pos;
    string s;
    while (cin >> s) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != '.') pos[s[i]].emplace_back(grid.size(), i);
        }
        grid.push_back(s);
    }
    int ans = 0, m = grid.size(), n = grid[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n));
    for (auto& [c, v] : pos) {
        sort(v.begin(), v.end());
        for (int i = 0; i < v.size(); i++) {
            auto& [x1, y1] = v[i];
            for (int j = i + 1; j < v.size(); j++) {
                auto& [x2, y2] = v[j];
                int new_x1 = x1 - (x2 - x1);
                int new_x2 = x2 + (x2 - x1);
                if (y1 < y2) {
                    int new_y1 = y1 - abs(y2 - y1);
                    int new_y2 = y2 + abs(y2 - y1);
                    if (new_x1 >= 0 && new_y1 >= 0) visited[new_x1][new_y1] = true;
                    if (new_x2 < m && new_y2 < n) visited[new_x2][new_y2] = true;
                } else {
                    int new_y1 = y1 + abs(y2 - y1);
                    int new_y2 = y2 - abs(y2 - y1);
                    if (new_x1 >= 0 && new_y1 < n) visited[new_x1][new_y1] = true;
                    if (new_x2 < m && new_y2 >= 0) visited[new_x2][new_y2] = true;
                }
            }
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (visited[i][j]) ans++;
        }
    }
    cout << ans << '\n';
}
