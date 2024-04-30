#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

int dx[] = {0, 1, 0, -1}, dy[] = {-1, 0, 1, 0}; // N/E/S/W

void gradientDescent() {
  // for floats
  ld cx = 5000.0, cy = 5000.0;
  for (ld d = 5000.0; d > 1e-12; d *= 0.99) {   // decreasing search range
    for (int dir = 0; dir < 4; dir++) {         // 4 directions are enough
      ld nx = cx + dx[dir] * d, ny = cy + dy[dir] * d;
      if (f(nx, ny) < f(cx, cy))                // if a local DESCENT step
        tie(cx, cy) = {nx, ny};                 // a local move
    }
  }
  // for integers
  int cx = 0, cy = 0;
  while (true) {
    bool change = false;
    for (int dir = 0; dir < 4; ++dir) { // 4 directions are enough
      int nx = dx[dir] + cx, ny = dy[dir] + cy;
      if (nx < 0 || nx == x || ny < 0 || ny == y) continue;
      if (f(nx, ny) < f(cx, cy))
        tie(cx, cy) = {nx, ny};
    }
    if (!change) break;
  }
}
