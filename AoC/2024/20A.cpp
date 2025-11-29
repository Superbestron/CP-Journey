#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Very ambiguous, or should I say completely wrong problem statement. In fact when I first read it, I thought disabling
// collision for 2 picoseconds means that one can possibly go through 2 walls at once, but that is not the case. One
// needs to start at an empty position and the next position must be a wall to be qualified as a "cheat". Once you got
// that down, another important piece of information is that they is originally only 1 way to complete the maze.
// Keeping that in mind, you can first figure out the actual path taken without cheating, then figure out all possible
// cheats, then simulate BFS for each cheat.

int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int m, n, len = 0;
ii start, fin;
set<ii> st;

bool dfs(vector<string>& grid, vector<vi>& visited, vector<vi>& path, int x, int y) {
    visited[x][y] = true;
    if (x == fin.first && y == fin.second) {
        len++;
        path[x][y] = true;
        return true;
    }
    bool ans = false;
    for (auto &dir : dirs) {
        int new_x = x + dir[0];
        int new_y = y + dir[1];
        if (new_x < 0 || new_x >= m || new_y < 0 || new_y >= n) continue;
        if (grid[new_x][new_y] == '#' || visited[new_x][new_y]) continue;
        ans |= dfs(grid, visited, path, new_x, new_y);
    }
    if (ans) {
        path[x][y] = true;
        len++;
    }
    return ans;
}

void bfs(vector<string>& grid, vector<vi>& path) {
    vector<vector<bool>> dist(m, vector<bool>(n));
    dist[start.first][start.second] = true;
    queue<ii> q;
    q.emplace(start.first, start.second);
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        if (x == fin.first && y == fin.second) break;
        for (auto &dir : dirs) {
            int new_x = x + dir[0];
            int new_y = y + dir[1];
            if (new_x < 0 || new_x >= m || new_y < 0 || new_y >= n) continue;
            if (grid[new_x][new_y] == '#') st.emplace(new_x, new_y);
            if (!path[new_x][new_y] || dist[new_x][new_y]) continue;
            dist[new_x][new_y] = true;
            q.emplace(new_x, new_y);
        }
    }
}

int bfs(vector<string>& grid) {
    vector<vi> dist(n, vi(n, -1));
    dist[start.first][start.second] = 0;
    queue<ii> q;
    q.emplace(start.first, start.second);
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        if (x == fin.first && y == fin.second) break;
        for (auto & dir : dirs) {
            int new_x = x + dir[0];
            int new_y = y + dir[1];
            if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= n) continue;
            if (grid[new_x][new_y] == '#' || dist[new_x][new_y] >= 0) continue;
            dist[new_x][new_y] = dist[x][y] + 1;
            q.emplace(new_x, new_y);
        }
    }
    return dist[fin.first][fin.second];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    vector<string> grid;
    while (cin >> s) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'S') start = make_pair(grid.size(), i);
            else if (s[i] == 'E') fin = make_pair(grid.size(), i);
        }
        grid.push_back(s);
    }
    m = grid.size(), n = grid[0].size();
    int ans = 0;
    vector<vi> path(m, vi(n)), visited(m, vi(n));
    dfs(grid, visited, path, start.first, start.second);
    bfs(grid, path);
    char temp = '.';
    for (auto& [x, y] : st) {
        swap(temp, grid[x][y]);
        int now = bfs(grid);
        if (len - now >= 100) ans++;
        swap(temp, grid[x][y]);
    }
    cout << ans << '\n';
}
