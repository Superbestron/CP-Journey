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
  for (int i = 0; i < n; i++)
    value += cost[i][Lmate[i]];

  return value;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, s, t, q, a;
  cin >> n >> s >> t >> q;
  unordered_map<int, int> springs, towns;
  int maxi = max(s, t);
  VVD cost(maxi, VD(maxi, 0));
  vector<tuple<int, int, int>> v(n);
  for (auto &[x, y, h] : v) cin >> x >> y >> h;
  vector<vector<double>> AM(n, vector<double>(n, 1e9));
  for (int i = 0; i < n; i++) {
    auto &[x1, y1, h1] = v[i];
    for (int j = 0; j < n; j++) {
      auto &[x2, y2, h2] = v[j];
      if (h1 <= h2) continue;
      double dist = hypot(x1 - x2, y1 - y2, h1 - h2);
      if (dist < q) AM[i][j] = dist;
    }
  }
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        AM[i][j] = min(AM[i][j], AM[i][k] + AM[k][j]);
      }
    }
  }
  for (int i = 0; i < s; i++) {
    cin >> a;
    a--;
    springs[a] = i;
  }
  for (int i = 0; i < t; i++) {
    cin >> a;
    a--;
    towns[a] = i;
  }
  for (int i = 0; i < n; i++) {
    if (!springs.count(i) && !towns.count(i)) continue;
    bool is_first_spring = springs.count(i);
    auto &[x1, y1, h1] = v[i];
    for (int j = i + 1; j < n; j++) {
      if (!springs.count(j) && !towns.count(j)) continue;
      auto &[x2, y2, h2] = v[j];
      bool is_second_spring = springs.count(j);
      if (is_first_spring && !is_second_spring) {
        cost[springs[i]][towns[j]] = AM[i][j];
      } else if (!is_first_spring && is_second_spring) {
        cost[springs[j]][towns[i]] = AM[j][i];
      }
    }
  }

  VI Lmate(maxi, -1), Rmate(maxi, -1);
  double maxCost = MinCostMatching(cost, Lmate, Rmate);
  if (maxCost >= 1e9) cout << "IMPOSSIBLE\n";
  else cout << setprecision(6) << fixed << maxCost;
}
