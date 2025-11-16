#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Brute-force simulate the route and keep track of visited points using Hashmap.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string> grid;
    string s;
    int ans = 0, dir = 0;
    pair<int, int> start;
    while (cin >> s) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '^') start = make_pair(grid.size(), i);
        }
        grid.push_back(s);
    }
    int m = grid.size(), n = grid[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n));
    visited[start.first][start.second] = true;
    int x = start.first, y = start.second;
    while (true) {
        if (dir == 0) x--;
        else if (dir == 1) y++;
        else if (dir == 2) x++;
        else y--;
        if (x >= 0 && x < m && y >= 0 && y < n) {
            if (grid[x][y] == '#') {
                if (dir == 0) x++;
                else if (dir == 1) y--;
                else if (dir == 2) x--;
                else y++;
                dir = (dir + 1) % 4;
            } else {
                visited[x][y] = true;
            }
        } else break;
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (visited[i][j]) ans++;
        }
    }
    cout << ans << '\n';
}
