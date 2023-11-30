#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int, int> iiii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<vvvi> vvvvi;

int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T, r, c;
  string s;
  cin >> T;
  while (T--) {
    cin >> r >> c;
    vector<string> v;
    int start_x, start_y;
    for (int i = 0; i < r; i++) {
      cin >> s;
      for (int j = 0; j < c; j++) {
        if (s[j] == 'R') {
          start_x = i;
          start_y = j;
        }
      }
      v.push_back(std::move(s));
    }

    queue<iiii> q;
    vvvvi dist(r, vvvi(c, vvi(5, vi(5, -1))));

    // x, y, prev_dir
    // dir: 0 => N, 1 => S, 2 => E, 3 => W
    dist[start_x][start_y][4][4] = 0;
    q.emplace(start_x, start_y, 4, 4);
    bool found = false;
    while (!q.empty()) {
      auto &[x, y, prev_prev_dir, prev_dir] = q.front(); q.pop();
      int forbidden_dir = prev_dir ^ 1; // smart toggle
      for (int i = 0; i < 4; i++) {
        // can't go in same direc more than twice
        if (prev_prev_dir == prev_dir && prev_dir == i) continue;
        if (forbidden_dir == i) continue;
        auto &dir = directions[i];
        int new_x = x + dir[0];
        int new_y = y + dir[1];
        if (new_x < 0 || new_x >= r || new_y < 0 || new_y >= c) continue;
        if (dist[new_x][new_y][prev_dir][i] != -1) continue;
        if (v[new_x][new_y] == 'B') continue;
        dist[new_x][new_y][prev_dir][i] = dist[x][y][prev_prev_dir][prev_dir] + 1;
        if (v[new_x][new_y] == 'D') {
          found = true;
          cout << dist[new_x][new_y][prev_dir][i] << '\n';
          goto done;
        }
        q.emplace(new_x, new_y, prev_dir, i);
      }
    }
    done:
    if (!found) cout << -1 << '\n';
  }
}
