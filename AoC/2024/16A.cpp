#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef tuple<int, int, int, int> iiii;

// Simple Application of Dijkstra's, once you figured out that the graph is actually m * n * 4, where there is an
// extra factor of 4 to account for the 4 cardinal directions.

// up right down left
int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    vector<string> grid;
    ii start, end;
    while (cin >> s) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'S') start = make_pair(grid.size(), i);
            else if (s[i] == 'E') end = make_pair(grid.size(), i);
        }
        grid.push_back(s);
    }
    int m = grid.size(), n = grid[0].size();
    vector<vector<vi>> dist(m, vector<vi>(n, vi(4, INT_MAX)));
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
    sort(dist[end.first][end.second].begin(), dist[end.first][end.second].end());
    cout << dist[end.first][end.second][0] << '\n';
}
