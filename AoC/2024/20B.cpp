#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// My approach for 20A was clearly not extensible to 20B. Again, now their example is different from 20A, where now the
// endpoint is an empty square while the first 5 points can possibly be walls. Getting the idea is not difficult; once
// you have the path and distances travelled so far for each point, then for each point, you can actually check all
// possibly "jumps" to another point in the path, as this has the equivalent effect of cheating through walls. The
// implementation here is a bit tricky, basically you can imagine a diamond where the point that you are currently
// considering is in the centre, and you are able to jump to any point in this diamond, where the manhattan distance
// between the former and latter point is <= 20. Sum your current distance, the manhattan distance you have covered,
// and the remaining distance to the end, and contrast with the actual distance without cheating. Count the number of
// unique point you can jump to, which is equivalent to a "cheat".

int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int m, n, len = 0;
ii start, fin;

bool dfs(vector<string>& grid, vector<vi>& dist, vector<vi>& path, int x, int y) {
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
        if (grid[new_x][new_y] == '#' || dist[new_x][new_y] != -1) continue;
        dist[new_x][new_y] = dist[x][y] + 1;
        ans |= dfs(grid, dist, path, new_x, new_y);
    }
    if (ans) {
        path[x][y] = true;
        len++;
    }
    return ans;
}

int bfs(vector<vi>& path, vector<vi>& dist) {
    queue<ii> q;
    q.emplace(start.first, start.second);
    int ans = 0;
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        int d = dist[x][y];
        if (x == fin.first && y == fin.second) break;
        int nn = 41, mid = nn / 2;
        for (int i = 0; i < nn; ++i) {
            int di = abs(i - mid);
            int width = nn - 2 * di;
            int start = mid - width / 2;
            int new_x = x - mid + i;
            if (new_x < 0 || new_x >= m) continue;
            for (int j = start; j < start + width; ++j) {
                int new_y = y - mid + j;
                if (new_y < 0 || new_y >= n) continue;
                if (!path[new_x][new_y]) continue;
                int new_d = dist[new_x][new_y];
                int d_from_centre = abs(i - mid) + abs(j - mid);
                if (len - (d + d_from_centre + (len - new_d)) >= 100) {
                    ans++;
                }
            }
        }
        for (auto &dir : dirs) {
            int new_x = x + dir[0];
            int new_y = y + dir[1];
            if (new_x < 0 || new_x >= m || new_y < 0 || new_y >= n) continue;
            if (!path[new_x][new_y] || dist[x][y] > dist[new_x][new_y]) continue;
            q.emplace(new_x, new_y);
        }

    }
    return ans;
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
    vector<vi> dist(m, vi(n, -1)), path(m, vi(n));
    dist[start.first][start.second] = 0;
    dfs(grid, dist, path, start.first, start.second);
    cout << bfs(path, dist) << '\n';
}
