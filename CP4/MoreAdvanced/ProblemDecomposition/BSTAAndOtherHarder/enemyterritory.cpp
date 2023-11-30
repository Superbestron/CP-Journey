#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;

int direc[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
int N, X, Y, xi, yi, xr, yr, length;
vvi global_enemy_dist(X, vi(Y, 1e9));
queue<ii> q;

bool can(int x) {
  // already too close from the start
  if (global_enemy_dist[xi][yi] < x) return false;
  vvi dist(X, vi(Y, 1e9));
  dist[xi][yi] = 0;
  q.emplace(xi, yi);
  while (!q.empty()) {
    auto [x1, y1] = q.front(); q.pop();
    for (auto &dir : direc) {
      int new_x = x1 + dir[0];
      int new_y = y1 + dir[1];
      if (new_x < 0 || new_x >= X || new_y < 0 || new_y >= Y) continue;
      if (global_enemy_dist[new_x][new_y] < x) continue;
      if (dist[new_x][new_y] != 1e9) continue;
      dist[new_x][new_y] = dist[x1][y1] + 1;
      q.emplace(new_x, new_y);
    }
  }
  length = dist[xr][yr];
  return length != 1e9;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> X >> Y >> xi >> yi >> xr >> yr;
  global_enemy_dist.assign(X, vi(Y, 1e9));
  for (int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    global_enemy_dist[x][y] = 0;
    q.emplace(x, y);
  }
  while (!q.empty()) {
    auto [x1, y1] = q.front(); q.pop();
    for (auto &dir : direc) {
      int new_x = x1 + dir[0];
      int new_y = y1 + dir[1];
      if (new_x < 0 || new_x >= X || new_y < 0 || new_y >= Y) continue;
      if (global_enemy_dist[new_x][new_y] != 1e9) continue;
      global_enemy_dist[new_x][new_y] = global_enemy_dist[x1][y1] + 1;
      // keep track of all nearest dist to enemy bases
      global_enemy_dist[new_x][new_y] = min(global_enemy_dist[new_x][new_y], global_enemy_dist[new_x][new_y]);
      q.emplace(new_x, new_y);
    }
  }
  int lo = 0, hi = 2000;
  while (hi > lo) {
    int mid = lo + (hi - lo + 1) / 2;
    can(mid) ? lo = mid : hi = mid - 1;
  }
  can(lo);
  cout << lo << ' ' << length << '\n';
}
