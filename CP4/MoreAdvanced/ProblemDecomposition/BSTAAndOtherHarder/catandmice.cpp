#include <bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;

typedef tuple<double, int> ii;
typedef tuple<int, int, int> iii;

int n, use = 0;
const int INF = 1e9;
double m, speed;
const double EPS = 1e-9;
vector<vector<double>> AM;
vector<iii> v;
double powers[16], memo[15][1 << 15], last_used[15][1 << 15];

// Variant of Held-Karp DP
// Instead of the usual way of having a state(u, mask) where u is the current node visited and mask
// is the set of nodes not visited ('1' represents not visited), we do the DP backwards. We still use
// the same state (u, mask) but mask represents the nodes that we have already visited (by the '1's),
// while u is the last visited node of the currently visited nodes.
// So at a given state (u, mask), for the set of nodes that we have already visited, we try every
// possible node k to be the node that we have just visited BEFORE u.
// If the time taken for every possible node k is greater than the time the mouse returns to the hole,
// we return INF.

double dp(int u, int mask) {
  double &ans = memo[u][mask];
  if (last_used[u][mask] == use) return ans;
  last_used[u][mask] = use;

  if (__builtin_popcount(mask) == 1) {
    double time = hypot(get<0>(v[u]), get<1>(v[u])) / speed;
    return ans = (time <= get<2>(v[u]) ? time : INF);
  }

  ans = INF;
  int bm = mask ^ (1 << u);
  int mice_eaten = __builtin_popcount(bm);
  ans = 1e9;
  double new_speed = speed * powers[mice_eaten];
  while (bm) {
    int two_pow = LSOne(bm);
    int idx = __builtin_ctz(two_pow);
    ans = min(ans, AM[u][idx] / new_speed + dp(idx, mask ^ (1 << u)));
    bm -= two_pow;
  }
  if (ans > get<2>(v[u])) ans = INF;
  return ans;
}

bool can(double x) {
  speed = x;
  use++;
  for (int i = 0; i < n; i++) {
    if (INF - dp(i, (1 << n) - 1) > EPS) return true;
  }
  return false;
}

int main() {
  cin >> n;
  AM.assign(n, vector<double>(n));
  for (int i = 0; i < n; i++) {
    int x, y, s;
    cin >> x >> y >> s;
    for (int j = 0; j < v.size(); j++) {
      auto &[x1, y1, s1] = v[j];
      AM[i][j] = AM[j][i] = hypot(x1 - x, y1 - y);
    }
    v.emplace_back(x, y, s);
  }
  cin >> m;
  powers[0] = 1;
  for (int j = 1; j <= n; j++) {
    powers[j] = powers[j - 1] * m;
  }
  double lo = 0, hi = 1000000;
  memset(memo, -1, sizeof memo);
  while (fabs(hi - lo) > EPS) {
    double mid = (lo + hi) / 2.0;
    can(mid) ? hi = mid : lo = mid;
  }
  cout << setprecision(3) << fixed << lo << '\n';
}
