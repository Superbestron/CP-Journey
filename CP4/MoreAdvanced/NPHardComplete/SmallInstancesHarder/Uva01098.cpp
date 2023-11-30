#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int tc = 1, n, m;
vector<tuple<int, int, int>> checkpoints;
int direc[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
vector<vector<bool>> visited, n_visited;

int n_dfs(int x, int y) {
  int cnt = 1;
  for (auto &dir : direc) {
    int new_x = x + dir[0];
    int new_y = y + dir[1];
    if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= m) continue;
    if (visited[new_x][new_y] || n_visited[new_x][new_y]) continue;
    n_visited[new_x][new_y] = true;
    cnt += n_dfs(new_x, new_y);
  }
  return cnt;
}

int dfs(int x, int y, int steps) {
  if (steps == n * m) return 1;
  else if (steps == 3 * n * m / 4) {
    if (x != get<0>(checkpoints[2]) || y != get<1>(checkpoints[2])) return 0;
  } else if (steps == n * m / 2) {
    if (x != get<0>(checkpoints[1]) || y != get<1>(checkpoints[1])) return 0;
  } else if (steps == n * m / 4) {
    if (x != get<0>(checkpoints[0]) || y != get<1>(checkpoints[0])) return 0;
  }
  else {
    for (int i = 0; i <= 3; i++) {
      if (x == get<0>(checkpoints[i]) && y == get<1>(checkpoints[i])) return 0;
      // check reachable using manhattan distance
      int dist = abs(x - get<0>(checkpoints[i])) + abs(y - get<1>(checkpoints[i]));
      int left = get<2>(checkpoints[i]) - steps;
      if (left > 0 && left < dist) return 0;
    }
  }
  n_visited.assign(n, vector<bool>(m));
  n_visited[x][y] = true;
  n_visited[0][1] = true;
  int reachable_pts = n_dfs(0, 1);
  if (reachable_pts != n * m - steps) return 0;

  int cnt = 0;
  for (auto &dir : direc) {
    int new_x = x + dir[0];
    int new_y = y + dir[1];
    if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= m) continue;
    if (visited[new_x][new_y]) continue;
    visited[new_x][new_y] = true;
    cnt += dfs(new_x, new_y, steps + 1);
    visited[new_x][new_y] = false;
  }
  return cnt;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  while (cin >> n >> m) {
    if (n == 0 && m == 0) break;
    visited.assign(n, vector<bool>(m));
    checkpoints.assign(3, {});
    for (auto &[n1, n2, n3] : checkpoints) {
      cin >> n1 >> n2;
    }
    get<2>(checkpoints[0]) = n * m / 4;
    get<2>(checkpoints[1]) = n * m / 2;
    get<2>(checkpoints[2]) = 3 * n * m / 4;
    checkpoints.emplace_back(0, 1, n * m);
    visited[0][0] = true;
    printf("Case %d: %d\n", tc++, dfs(0, 0, 1));
  }
}
