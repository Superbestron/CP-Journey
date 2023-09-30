#include <bits/stdc++.h>

using namespace std;

typedef vector<double> VD;
typedef vector<VD> VVD;
typedef vector<int> VI;

double MinCostMatching(const VVD &cost, VI &Lmate, VI &Rmate) {
  int n = int(cost.size());

  // construct dual feasible solution
  VD u(n);
  VD v(n);
  for (int i = 0; i < n; i++) {
    u[i] = cost[i][0];
    for (int j = 1; j < n; j++) u[i] = min(u[i], cost[i][j]);
  }
  for (int j = 0; j < n; j++) {
    v[j] = cost[0][j] - u[0];
    for (int i = 1; i < n; i++) v[j] = min(v[j], cost[i][j] - u[i]);
  }

  // construct primal solution satisfying complementary slackness
  Lmate = VI(n, -1);
  Rmate = VI(n, -1);
  int mated = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (Rmate[j] != -1) continue;
      if (fabs(cost[i][j] - u[i] - v[j]) < 1e-10) {
        Lmate[i] = j;
        Rmate[j] = i;
        mated++;
        break;
      }
    }
  }

  VD dist(n);
  VI dad(n);
  VI seen(n);

  // repeat until primal solution is feasible
  while (mated < n) {

    // find an unmatched left node
    int s = 0;
    while (Lmate[s] != -1) s++;

    // initialize Dijkstra
    fill(dad.begin(), dad.end(), -1);
    fill(seen.begin(), seen.end(), 0);
    for (int k = 0; k < n; k++)
      dist[k] = cost[s][k] - u[s] - v[k];

    int j = 0;
    while (true) {

      // find closest
      j = -1;
      for (int k = 0; k < n; k++) {
        if (seen[k]) continue;
        if (j == -1 || dist[k] < dist[j]) j = k;
      }
      seen[j] = 1;

      // termination condition
      if (Rmate[j] == -1) break;

      // relax neighbors
      const int i = Rmate[j];
      for (int k = 0; k < n; k++) {
        if (seen[k]) continue;
        const double new_dist = dist[j] + cost[i][k] - u[i] - v[k];
        if (dist[k] > new_dist) {
          dist[k] = new_dist;
          dad[k] = j;
        }
      }
    }

    // update dual variables
    for (int k = 0; k < n; k++) {
      if (k == j || !seen[k]) continue;
      const int i = Rmate[k];
      v[k] += dist[k] - dist[j];
      u[i] -= dist[k] - dist[j];
    }
    u[s] += dist[j];

    // augment along path
    while (dad[j] >= 0) {
      const int d = dad[j];
      Rmate[j] = Rmate[d];
      Lmate[Rmate[j]] = j;
      j = d;
    }
    Rmate[j] = s;
    Lmate[s] = j;

    mated++;
  }

  double value = 0;
  for (int i = 0; i < n; i++) {
    if (cost[i][Lmate[i]] == 0) continue;
    value += cost[i][Lmate[i]];
  }

  return value;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, h, w;
  int directions[4][2]{{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
  cin >> t;
  while (t--) {
    cin >> h >> w;
    vector<string> a(h);
    map<pair<int, int>, int> x_to_idx, b_to_idx;
    int x_ctr = 0, b_ctr = 0;
    for (int i = 0; i < h; i++) {
      cin >> a[i];
      for (int j = 0; j < w; j++) {
        if (a[i][j] == 'X') {
          x_to_idx[make_pair(i, j)] = x_ctr++;
        } else if (a[i][j] == 'B') {
          b_to_idx[make_pair(i, j)] = b_ctr++;
        }
      }
    }
    VVD cost(b_ctr, VD(x_ctr, 1e9));
    VI Lmate(b_ctr, -1), Rmate(x_ctr, -1);
    queue<pair<int, int>> q;
    for (auto& [c, idx] : b_to_idx) {
      vector<vector<int>> dist(h, vector<int>(w, 1e9));
      q.emplace(c.first, c.second);
      dist[c.first][c.second] = 0;
      while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        pair<int, int> temp_pair(x, y);
        if (x_to_idx.count(temp_pair)) {
          int x_idx = x_to_idx[temp_pair];
          cost[idx][x_idx] = dist[x][y];
        }
        for (auto& dir : directions) {
          int new_x = x + dir[0], new_y = y + dir[1];
          if (new_x < 0 || new_x == h || new_y < 0 || new_y == w) continue;
          if (dist[new_x][new_y] != 1e9 || a[new_x][new_y] == '#') continue;
          dist[new_x][new_y] = dist[x][y] + 1;
          q.emplace(new_x, new_y);
        }
      }
    }
    int minCost = MinCostMatching(cost, Lmate, Rmate);
    cout << minCost << '\n';
  }
}
