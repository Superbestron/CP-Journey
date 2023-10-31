#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> v;
int n, x, y;

int f(int cx, int cy) {
  int cost = 0;
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      cost += v[i][j] * (abs(cx - i) + abs(cy - j));
    }
  }
  return cost;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  int dx[] = {0, 1, 0,-1}, dy[] = {-1, 0, 1, 0}; // N/E/S/W
  while (n--) {
    cin >> y >> x;
    v.assign(x, vector<int>(y));
    for (auto &r : v) {
      for (int &i : r) cin >> i;
    }
    int cx = 0, cy = 0;
    while (true) {
      bool change = false;
      for (int dir = 0; dir < 4; ++dir) { // 4 directions are enough
        int nx = dx[dir] + cx, ny = dy[dir] + cy;
        if (nx < 0 || nx == x || ny < 0 || ny == y) continue;
        if (f(nx, ny) < f(cx, cy)) {
          change = true;
          tie(cx, cy) = {nx, ny}; // a local move
          break;
        }
      }
      if (!change) break;
    }
    cout << f(cx, cy) << " blocks\n";
  }
}
