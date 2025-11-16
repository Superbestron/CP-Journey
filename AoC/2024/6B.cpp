#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Brute-force try each possible point for the obstacle and simulate like 6A. The stopping condition requires a clever
// insight. You can only visit a grid a maximum of 4 times (4 cardinal directions) if you are not caught in an infinite
// loop.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string> grid;
    string s;
    int ans = 0;
    pair<int, int> start;
    while (cin >> s) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '^') start = make_pair(grid.size(), i);
        }
        grid.push_back(s);
    }
    int m = grid.size(), n = grid[0].size();
    vector<vi> ori_visited(m, vi(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '^' || grid[i][j] == '#') continue;
            grid[i][j] = '#';
            int x = start.first, y = start.second, dir = 0;
            vector<vi> visited = ori_visited;
            visited[x][y]++;
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
                        visited[x][y]++;
                        if (visited[x][y] > 4) {
                            ans++;
                            break;
                        }
                    }
                } else break;
            }
            grid[i][j] = '.';
        }
    }
    cout << ans << '\n';
}
