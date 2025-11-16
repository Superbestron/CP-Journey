#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// BFS-like question. For area, it's pretty simple, use a visited array to keep track of visited points. For perimeter,
// if target point is not part of the original region, or it's out of bounds, count that in.

int dirs[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    int ans = 0;
    vector<string> grid;
    while (cin >> s) grid.push_back(s);
    int m = grid.size(), n = grid[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (!visited[i][j]) {
                int area = 1;
                int peri = 0;
                char c = grid[i][j];
                visited[i][j] = true;
                queue<ii> q;
                q.emplace(i, j);
                while (!q.empty()) {
                    auto [x, y] = q.front(); q.pop();
                    for (auto& dir : dirs) {
                        int new_x = x + dir[0];
                        int new_y = y + dir[1];
                        // invalid grid
                        if (!(new_x >= 0 && new_x < m && new_y >= 0 && new_y < n)) {
                            peri++;
                        } else if (grid[new_x][new_y] != c) { // not my character
                            peri++;
                        } else {
                            if (!visited[new_x][new_y]) {
                                q.emplace(new_x, new_y);
                                visited[new_x][new_y] = true;
                                area++;
                            }
                        }
                    }
                }
                ans += area * peri;
            }
        }
    }
    cout << ans << '\n';
}
