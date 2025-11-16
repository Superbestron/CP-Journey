#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Probably one of the more difficult questions. Notice that the number of corners equals the number of turns equals
// the number of straight-line fences. Thus, finding the perimeter reduces to checking the number of corners in a
// region, and what constitutes as a corner, please refer to the function analyse_corner().

// up, right, down, left
int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int corners[4][3][2] = {
    {{-1, -1}, {-1, 0}, {0, -1}}, // top left
    {{-1, 1}, {-1, 0}, {0, 1}}, // top right
    {{1, -1}, {1, 0}, {0, -1}}, // btm left
    {{1, 1}, {1, 0},  {0, 1}} // btm right
};
int m, n;

bool inside(int i, int j) {
    return i >= 0 && i < m && j >= 0 && j < n;
}

int analyse_corner(vector<string>& grid, int x, int y) {
    int peri = 0;
    for (auto& cnr : corners) {
        int x1 = x + cnr[0][0], y1 = y + cnr[0][1];
        int x2 = x + cnr[1][0], y2 = y + cnr[1][1];
        int x3 = x + cnr[2][0], y3 = y + cnr[2][1];
        char c1 = inside(x1, y1) ? grid[x1][y1] : '-';
        char c2 = inside(x2, y2) ? grid[x2][y2] : '-';
        char c3 = inside(x3, y3) ? grid[x3][y3] : '-';
        char c4 = grid[x][y];
        if (c4 != c3 && c4 != c2) peri++;
        else if (c4 == c3 && c4 == c2 && c4 != c1) peri++;
    }
    return peri;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    int ans = 0;
    vector<string> grid;
    while (cin >> s) grid.push_back(s);
    m = grid.size(), n = grid[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (!visited[i][j]) {
                int area = 1, peri = 0;
                char c = grid[i][j];
                visited[i][j] = true;
                queue<ii> q;
                q.emplace(i, j);
                while (!q.empty()) {
                    auto [x, y] = q.front(); q.pop();
                    peri += analyse_corner(grid, x, y);
                    for (auto& dir : dirs) {
                        int new_x = x + dir[0];
                        int new_y = y + dir[1];
                        // invalid grid
                        if (inside(new_x, new_y) && grid[new_x][new_y] == c) {
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
