#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int, int> iiii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
const int INF = 1e9;

int NSEW[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int direc[3][2] = {{0, 1}, {-1, 1}, {1, 1}};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int r, c, n;
  cin >> r >> c >> n;
  vector<vector<int>> grid(r, vector<int>(c));
  vector<vector<bool>> passes(r, vector<bool>(c));
  for (auto &row : grid) {
    for (int &i : row) cin >> i;
  }
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      bool pass = true;
      for (int k = 0; k < 4; k++) {
        auto &dir = NSEW[k];
        int new_r = i + dir[0];
        int new_c = j + dir[1];
        if (new_r < 0 || new_r >= r || new_c < 0 || new_c >= c) {
          pass = false; break;
        }
        if (k & 1) {
          if (grid[new_r][new_c] == -1 || grid[new_r][new_c] <= grid[i][j]) {
            pass = false; break;
          }
        } else {
          if (grid[new_r][new_c] == -1 || grid[new_r][new_c] >= grid[i][j]) {
            pass = false; break;
          }
        }
      }
      passes[i][j] = pass;
    }
  }
  priority_queue<iiii, vector<iiii>, greater<>> pq;
  vvvi dist( r, vvi(c, vi(n + 1, INF)));
  for (int i = 0; i < r; i++) {
    if (grid[i][0] == -1) continue;
    dist[i][0][n] = grid[i][0];
    pq.emplace(0, i, 0, n);
  }
  int ans = INF;
  while (!pq.empty()) { // main loop
    auto [d, x, y, left] = pq.top(); pq.pop(); // shortest unvisited u
    if (d > dist[x][y][left]) continue; // a very important check
    if (y == c - 1 && left == 0) {
      ans = min(ans, dist[x][y][left]);
      continue;
    }
    for (auto &dir : direc) {
      int new_x = x + dir[0];
      int new_y = y + dir[1];
      if (new_x < 0 || new_x >= r || new_y < 0 || new_y >= c) continue;
      if (grid[new_x][new_y] == -1) continue;
      int w = grid[new_x][new_y];
      if (passes[new_x][new_y]) {
        if (left == 0) continue;
        if (dist[x][y][left] + w >= dist[new_x][new_y][left - 1]) continue;
        dist[new_x][new_y][left - 1] = dist[x][y][left] + w;
        pq.emplace(dist[new_x][new_y][left - 1], new_x, new_y, left - 1);
      } else {
        if (dist[x][y][left] + w >= dist[new_x][new_y][left]) continue;
        dist[new_x][new_y][left] = dist[x][y][left] + w;
        pq.emplace(dist[new_x][new_y][left], new_x, new_y, left);
      }
    }
  }
  if (ans != INF) cout << ans << '\n';
  else cout << "impossible\n";
}
