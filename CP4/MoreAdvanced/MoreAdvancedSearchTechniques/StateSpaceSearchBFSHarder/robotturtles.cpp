#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int, int> iiii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<vvvi> vvvvi;
typedef vector<string> vs;
typedef vector<vs> vvs;
typedef vector<vvs> vvvs;
typedef vector<vvvs> vvvvs;

int directions[4][2] = {{0, 1}, {1, 0}, {0, -1},{-1, 0}};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int r = 8, c = 8;
  string s;
  vector<string> v;
  map<pair<int, int>, int> coord_to_idx;
  for (int i = 0; i < r; i++) {
    cin >> s;
    for (int j = 0; j < c; j++) {
      if (s[j] == 'I') {
        coord_to_idx[make_pair(i, j)] = coord_to_idx.size();
      }
    }
    v.push_back(std::move(s));
  }

  queue<iiii> q;
  vvvvs dist(r, vvvs(c, vvs(5, vs(1 << coord_to_idx.size()))));

  // x, y, curr_dir, bitmask of ice castles
  // dir: 0 => N, 1 => E, 2 => S, 3 => W
  int initial_bm = (1 << coord_to_idx.size()) - 1;
  dist[7][0][0][initial_bm] = 'S';
  q.emplace(7, 0, 0, initial_bm);
  bool found = false;
  while (!q.empty()) {
    auto &[x, y, curr_dir, bm] = q.front(); q.pop();
    // turn left
    int left_dir = (curr_dir - 1 + 4) % 4;
    int right_dir = (curr_dir + 1) % 4;
    if (dist[x][y][left_dir][bm].empty()) {
      dist[x][y][left_dir][bm] = dist[x][y][curr_dir][bm] + 'L';
      q.emplace(x, y, left_dir, bm);
    }
    if (dist[x][y][right_dir][bm].empty()) {
      dist[x][y][right_dir][bm] = dist[x][y][curr_dir][bm] + 'R';
      q.emplace(x, y, right_dir, bm);
    }
    int new_x = x + directions[curr_dir][0];
    int new_y = y + directions[curr_dir][1];
    if (!(new_x < 0 || new_x >= r || new_y < 0 || new_y >= c)) {
      if (dist[new_x][new_y][curr_dir][bm].empty() && (v[new_x][new_y] == '.' || v[new_x][new_y] == 'D')) {
        dist[new_x][new_y][curr_dir][bm] = dist[x][y][curr_dir][bm] + 'F';
        if (v[new_x][new_y] == 'D') {
          // print
          dist[new_x][new_y][curr_dir][bm].erase(0, 1);
          cout << dist[new_x][new_y][curr_dir][bm] << '\n';
          found = true;
          break;
        }
        q.emplace(new_x, new_y, curr_dir, bm);
      }
      if (v[new_x][new_y] == 'I') {
        int bm_idx = coord_to_idx[{new_x, new_y}];
        bool is_ice_there = bm & (1 << bm_idx);
        if (!is_ice_there) {
          if (dist[new_x][new_y][curr_dir][bm].empty()) {
            dist[new_x][new_y][curr_dir][bm] = dist[x][y][curr_dir][bm] + 'F';
            q.emplace(new_x, new_y, curr_dir, bm);
          }
        } else {
          int new_bm = bm & ~(1 << bm_idx);
          if (dist[x][y][curr_dir][new_bm].empty()) {
            dist[x][y][curr_dir][new_bm] = dist[x][y][curr_dir][bm] + 'X';
            q.emplace(x, y, curr_dir, new_bm);
          }
        }
      }
    }
  }
  if (!found) cout << "no solution\n";
}
