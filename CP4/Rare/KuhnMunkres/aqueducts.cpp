#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<double> vd;
typedef tuple<int, int, int> iii;
typedef vector<iii> viii;

const double INF = 1e9;

class Hungarian {
 private:
  int n, m; // n <= m, where n m is the bisection of the graph
  vd u, v;
  vi p, way;

 public:
  // A needs to be 1-indexed!!!!!
  Hungarian(int left, int right, vector<vd> &A) : n(left), m(right) {
    u.assign(n + 1, 0);
    v.assign(m + 1, 0);
    p.assign(m + 1, 0);
    way.assign(m + 1, 0);

    for (int i = 1; i <= n; ++i) {
      p[0] = i;
      int j0 = 0;
      vd minv(m + 1, INF);
      vector<char> used(m + 1, false);
      do {
        used[j0] = true;
        int i0 = p[j0], j1;
        double delta = INF;
        for (int j = 1; j <= m; ++j)
          if (!used[j]) {
            double cur = A[i0][j] - u[i0] - v[j];
            if (cur < minv[j])
              minv[j] = cur, way[j] = j0;
            if (minv[j] < delta)
              delta = minv[j], j1 = j;
          }
        for (int j = 0; j <= m; ++j)
          if (used[j])
            u[p[j]] += delta, v[j] -= delta;
          else
            minv[j] -= delta;
        j0 = j1;
      } while (p[j0] != 0);
      do {
        int j1 = way[j0];
        p[j0] = p[j1];
        j0 = j1;
      } while (j0);
    }
  }

  vi matching() {
    vi match(n + 1); // 1-indexed
    for (int i = 1; i <= m; i++)
      match[p[i]] = i;
    return match;
  }

  double mincost() { return -v[0]; }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, s, t, q, a;
  cin >> n >> s >> t >> q;
  unordered_map<int, int> springs, towns;
  int maxi = max(s, t);
  vector<vd> cost(maxi + 1, vd(maxi + 1));
  viii v(n);
  for (auto &[x, y, h] : v) cin >> x >> y >> h;
  vector<vd> AM(n, vd(n, INF));
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
        cost[springs[i] + 1][towns[j] + 1] = AM[i][j];
      } else if (!is_first_spring && is_second_spring) {
        cost[springs[j] + 1][towns[i] + 1] = AM[j][i];
      }
    }
  }

  Hungarian hun(maxi, maxi, cost);
  double minCost = hun.mincost();
  if (minCost >= INF) cout << "IMPOSSIBLE\n";
  else cout << setprecision(6) << fixed << minCost << '\n';
}
