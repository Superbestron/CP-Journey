#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> v;
int n, x, y;

int f(int cx, int cy) {
  int cost = 0;
  for (int i = 0; i < n; i++) {
    cost += (v[i].first - cx) * (v[i].first - cx) + (v[i].second - cy) * (v[i].second - cy);
  }
  return cost;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int dx[] = {0, 1, 0,-1}, dy[] = {-1, 0, 1, 0}; // N/E/S/W
  while (cin >> n && n != 0) {
    v.clear();
    for (int i = 0; i < n; i++) {
      cin >> x >> y;
      v.emplace_back(x, y);
    }
    int cx = 0, cy = 0;
    while (true) {
      bool change = false;
      for (int dir = 0; dir < 4; ++dir) { // 4 directions are enough
        int nx = dx[dir] + cx, ny = dy[dir] + cy;
        if (nx < 0 || nx == 1000 || ny < 0 || ny == 1000) continue;
        int curr = f(cx, cy), new_curr = f(nx, ny);
        if (new_curr < curr || (new_curr == curr && (nx < cx || nx == cx && ny < cy))) {
          change = true;
          tie(cx, cy) = {nx, ny}; // a local move
          break;
        }
      }
      if (!change) break;
    }
    cout << cx << ' ' << cy << '\n';
  }
}
