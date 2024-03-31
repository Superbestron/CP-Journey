#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

const ll INF = 1e9;

class Hungarian {
 private:
  int n, m; // n <= m, where n m is the bisection of the graph
  vll u, v;
  vi p, way;

 public:
  // A is 1 indexed so is (n + 1) * (m + 1)
  Hungarian(int left, int right, vector<vll> &A) : n(left), m(right) {
    u.assign(n + 1, 0);
    v.assign(m + 1, 0);
    p.assign(m + 1, 0);
    way.assign(m + 1, 0);

    for (int i = 1; i <= n; ++i) {
      p[0] = i;
      int j0 = 0;
      vll minv(m + 1, INF);
      vector<char> used(m + 1);
      do {
        used[j0] = true;
        int i0 = p[j0], j1;
        ll delta = INF;
        for (int j = 1; j <= m; ++j)
          if (!used[j]) {
            ll cur = A[i0][j] - u[i0] - v[j];
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

  vector<int> matching() {
    vector<int> match(n + 1); // 1-indexed
    for (int i = 1; i <= m; i++)
      match[p[i]] = i;
    return match;
  }

  ll mincost() { return -v[0]; }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int m, n, k, i, j, p;
  cin >> m >> n >> k;
  int maxi = max(n, m);
  vector<vll> cost(maxi + 1, vll(maxi + 1));
  for (int c = 0; c < k; c++) {
    cin >> i >> j >> p;
    cost[i][j] = -p;
  }
  Hungarian h(maxi, maxi, cost);
  int minCost = h.mincost();
  vi matching = h.matching();
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (matching[i] != 0 && matching[i] <= m) ans++;
  }
  cout << -minCost << '\n' << ans << '\n';
  for (int i = 1; i <= n; i++) {
    if (matching[i] != 0 && matching[i] <= m) cout << i << ' ' << matching[i] << '\n';
  }
}
