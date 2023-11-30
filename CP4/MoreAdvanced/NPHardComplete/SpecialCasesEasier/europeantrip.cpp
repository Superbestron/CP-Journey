#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

vector<pair<int, int>> v;

inline ld f(ld nx, ld ny) {
  ld dist = 0;
  for (auto &[x, y] : v) {
    dist += hypot(nx - x, ny - y);
  }
  return dist;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int x, y;
  for (int i = 0; i < 3; i++) {
    cin >> x >> y;
    v.emplace_back(x, y);
  }
  int dx[] = {0, 1, 0, -1}, dy[] = {-1, 0, 1, 0}; // N/E/S/W
  ld cx = 500, cy = 500;
  for (ld d = 5000.0; d > 1e-12; d *= 0.99) { // decreasing search range
    for (int dir = 0; dir < 4; ++dir) { // 4 directions are enough
      ld nx = cx + dx[dir] * d, ny = cy + dy[dir] * d;
      if (f(nx, ny) < f(cx, cy)) // if a local DESCENT step
        tie(cx, cy) = {nx, ny}; // a local move
    } // for this example, the final (cx, cy) = (4989.97, 5230.79)
  } // with final f(cx, cy) = 353490.894604066151
  cout << fixed << setprecision(4) << cx << ' ' << cy;
}
