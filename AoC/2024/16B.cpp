#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef tuple<int, int, int, int> iiii;

// You need to have a decent understanding of how dijkstra's work to exploit it's properties for this qn. Notice that
// we can tell if a path is taken (shortest path) iff dist[u] + w == dist[v] for every edge we traverse in the path AND
// most importantly, the dist we obtain at E == the ans we obtained from 16A. After using 16A as a subroutine to
// compute the dist array, we do a DFS to trace the path according to the above conditions. Use the visited array
// cleverly so that if we come across a path that we have already checked and it was indeed one of the shortest paths
// to E, we use this information and avoid recursing down that path again. Once the inner DFS returns true inside, we
// know that this particular outgoing path is correct and hence our current node is also correct.

// up right down left
int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int min_dist;
ii start, e;

bool dfs(vector<string>& grid, vector<vector<vi>>& dist, vector<vector<vi>>& visited, int x, int y, int dir) {
    if (x == e.first && y == e.second) {
        if (dist[x][y][dir] == min_dist) {
            visited[x][y][dir] = true;
            return true;
        }
        return false;
    }
    int d = dist[x][y][dir];
    bool can = false;
    for (int i = 0, curr_dir = dir; i < 4; i++, curr_dir = (curr_dir + 1) % 4) {
        auto& dire = dirs[curr_dir];
        if (i == 0) {
            int new_x = x + dire[0];
            int new_y = y + dire[1];
            if (grid[new_x][new_y] == '#') continue;
            if (dist[new_x][new_y][curr_dir] != d + 1) continue;
            if (visited[new_x][new_y][curr_dir] || dfs(grid, dist, visited, new_x, new_y, curr_dir)) {
                can = visited[x][y][curr_dir] = true;
            }
        } else if (i == 1 || i == 3) {
            if (dist[x][y][curr_dir] != d + 1000) continue;
            if (visited[x][y][curr_dir] || dfs(grid, dist, visited, x, y, curr_dir)) {
                can = visited[x][y][curr_dir] = true;
            }
        } else {
            if (dist[x][y][curr_dir] != d + 2000) continue;
            if (visited[x][y][curr_dir] || dfs(grid, dist, visited, x, y, curr_dir)) {
                can = visited[x][y][curr_dir] = true;
            }
        }
    }
    return can;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    vector<string> grid;
    while (cin >> s) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'S') start = make_pair(grid.size(), i);
            else if (s[i] == 'E') e = make_pair(grid.size(), i);
        }
        grid.push_back(s);
    }
    int ans = 0, m = grid.size(), n = grid[0].size();
    vector<vector<vi>> dist(m, vector<vi>(n, vi(4, INT_MAX))), visited(m, vector<vi>(n, vi(4)));
    dist[start.first][start.second][1] = 0;
    priority_queue<iiii, vector<iiii>> pq;
    pq.emplace(0, start.first, start.second, 1);
    while (!pq.empty()) {
        auto [d, x, y, dir] = pq.top(); pq.pop();
        if (d > dist[x][y][dir]) continue;
        for (int i = 0, curr_dir = dir; i < 4; i++, curr_dir = (curr_dir + 1) % 4) {
            auto& dire = dirs[curr_dir];
            if (i == 0) {
                int new_x = x + dire[0];
                int new_y = y + dire[1];
                if (grid[new_x][new_y] == '#') continue;
                if (dist[new_x][new_y][curr_dir] <= d + 1) continue;
                dist[new_x][new_y][curr_dir] = d + 1;
                pq.emplace(d + 1, new_x, new_y, curr_dir);
            } else if (i == 1 || i == 3) {
                if (dist[x][y][curr_dir] <= d + 1000) continue;
                dist[x][y][curr_dir] = d + 1000;
                pq.emplace(d + 1000, x, y, curr_dir);
            } else {
                if (dist[x][y][curr_dir] <= d + 2000) continue;
                dist[x][y][curr_dir] = d + 2000;
                pq.emplace(d + 2000, x, y, curr_dir);
            }
        }
    }
    visited[start.first][start.second][1] = true;
    sort(dist[e.first][e.second].begin(), dist[e.first][e.second].end());
    min_dist = dist[e.first][e.second][0];
    dfs(grid, dist, visited, start.first, start.second, 1);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            bool can = false;
            for (int k = 0; k < 4; k++) can |= visited[i][j][k];
            ans += can;
        }
    }
    cout << ans << '\n';
}
