#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef tuple<int, int, int> iii;

int direc[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<string> v(n);
  for (auto &s : v) cin >> s;
  queue<iii> q;
  vector<vi> dist(n, vi(m, 1e9));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (v[i][j] == '#' || dist[i][j] != 1e9) continue;
      dist[i][j] = 0;
      v[i][j] = 'E';
      q.emplace(i, j, 0);
      while (!q.empty()) {
        auto [x1, y1, d] = q.front(); q.pop();
        for (auto &dir : direc) {
          int new_x = x1 + dir[0];
          int new_y = y1 + dir[1];
          if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= m) continue;
          if (v[new_x][new_y] == '#' || dist[new_x][new_y] != 1e9) continue;
          dist[new_x][new_y] = dist[x1][y1] + 1;
          if (dist[new_x][new_y] % 2 == 0) {
            v[new_x][new_y] = 'E';
          }
          q.emplace(new_x, new_y, d ^ 1);
        }
      }
    }
  }

  for (auto &s : v) cout << s << '\n';
}
