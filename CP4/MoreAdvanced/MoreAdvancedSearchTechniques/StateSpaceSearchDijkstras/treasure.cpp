#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
typedef tuple<int, int, int, int, int> iiiii;
typedef vector<iiiii> viiiii;
typedef long long ll;
typedef vector<int> vi;
const int INF = 1e9;

int direc[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, k;
  string s;
  ii start, end;
  cin >> n >> m >> k;
  int sz = n * m * 3 / k;
  vector<vector<vector<vi>>> dist(n, vector<vector<vi>>(m, vector<vi>(k + 1, vi(sz, INF))));
  vector<string> AM(n);
  for (int i = 0; i < n; i++) {
    cin >> s;
    AM[i] = s;
    for (int j = 0; j < m; j++) {
      if (AM[i][j] == 'S') start = {i, j};
      if (AM[i][j] == 'G') end = {i, j};
    }
  }

  unordered_map<char, int> mp = {{'G', 1}, {'.', 1}, {'F', 2}, {'M', 3}, {'#', INF}, {'S', 1}};
  priority_queue<iiiii, viiiii, greater<>> pq;
  dist[start.first][start.second][k][0] = 0;
  pq.emplace(0, 0, -k, start.first, start.second);
  while (!pq.empty()) { // main loop
    auto [day, d, energy, x, y] = pq.top();
//    cout << x << ' ' << y << '\n';
    energy = -energy;
    pq.pop(); // shortest unvisited u
    if (ii{x, y} == end) {
      cout << day + 1 << '\n';
      return 0;
    }
    bool can_recharge = false;
    if (d > dist[x][y][energy][day]) continue; // a very important check
    for (auto &dir : direc) {
      int new_x = x + dir[0];
      int new_y = y + dir[1];
      if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= m) continue;
      int energy_left = energy - mp[AM[new_x][new_y]];
      if (energy_left < 0) {
        if (k >= mp[AM[new_x][new_y]]) can_recharge = true;
        continue; // not enough energy (very important to avoid TLE)
      }
      int new_d = dist[x][y][energy][day] + 1;
      if (dist[new_x][new_y][energy_left][day] <= new_d) continue;
      dist[new_x][new_y][energy_left][day] = dist[x][y][energy][day] + 1;
      pq.emplace(day, dist[new_x][new_y][energy_left][day], -energy_left, new_x, new_y);
    }
    // option to rest
    if (can_recharge && day != sz - 1) {
      dist[x][y][k][day + 1] = dist[x][y][energy][day];
      pq.emplace(day + 1, dist[x][y][k][day + 1], -k, x, y);
    }
  }
  cout << -1 << '\n';
}